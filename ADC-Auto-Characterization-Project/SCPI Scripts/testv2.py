import serial
import pyvisa
import time

# Todo, add startup prints to see process

# Docs with afg commands: https://mmrc.caltech.edu/Tektronics/AFG3021B/AFG3021B%20Programmer%20Manual.pdf

rm = pyvisa.ResourceManager('@py')

# You'll need to copy paste some of the IDs here into the rm.open_resource() functions below
print(rm.list_resources())

# Open arbitrary function generator & digital multimeter
# NOTE: the USB device/resource tags below will be different for you, that's why we print the resources above, see wiki for more info
afg = rm.open_resource('USB0::1689::851::1516313::0::INSTR')
dmm = rm.open_resource('USB0::0x05E6::0x2110::8005314::INSTR')

afg.write("*RST") # Reset instrument to the default state (sine wave)
afg.write("*CLS") # Clear all event registers and queues

time.sleep(0.1) # Wait until after reset/clear is complete, give the afg some time to breathe

afg.write("SOURce1:FUNCtion:SHAPe PULSe") # Pulse function mode
afg.write("SOURce1:PULSe:DCYC 99.9") # Max 99.9% duty cycle

time.sleep(0.1) # 0.1 seconds

afg.write("SOURce1:PULSe:PERiod 1s") # Set period to 1000s

time.sleep(0.1) # 0.1 seconds
# Default voltage of 1V
# We want a high of 1V and low of 0V, so we have to adjust the waveform up by 0.5V, since 1V is the wave amplitude
afg.write("SOURce1:VOLTage:LEVel:IMMediate:AMPLitude 1.0")
afg.write("SOURce1:VOLTage:LEVel:IMMediate:OFFSet 0.5")

time.sleep(0.1) # 0.1 seconds

afg.write("OUTPUT1:STATe ON") # NOTE: We are using output 1

time.sleep(0.1) # 0.1 seconds

# Remember to replace COM7 with the COM port that the Nucleo or ST Link is attachted to
# You can check in Windows Device Manager
serial_bus = serial.Serial(
    port="COM6",
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

time.sleep(0.1)

voltage = 0.01 # Setting intial to 0 gives an erroneous result
voltage_step = 0.05
voltage_offset = 0.005 # Because the voltage field is the amplitude of the waveform, we need to offset upwards to get 0V as the low value
dmm_voltage = 0

f = open("data.csv", "w")
f.write(f"Input Voltage,DMM Voltage,ADC Value,Iteration Time\n")

while True:
    start_time = time.time() # Seconds
    
    # Set voltage
    # We around to the thousandths place to ensure no floating point nonsense that messes up the afg, it wants nice decimal numbers, not 8 trailing zeroes
    afg.write("SOURce1:VOLTage:LEVel:IMMediate:AMPLitude " + str(voltage))
    afg.write("SOURce1:VOLTage:LEVel:IMMediate:OFFSet " + str(voltage_offset))
    
    time.sleep(0.01)
    
    serial_bus.write("s".encode()) # Send command to the STM32 to start reading, 5 is arbitrary
    adc_value = int(serial_bus.readline().decode('utf-8', errors='ignore').replace("\x00", "")) # The serial read function waits until it has received a line (\n)
    
    dmm_voltage = float(dmm.query('MEASure:VOLTage:DC?')) # After the STM32 is done, read the DMM voltage
    
    elapsed_time = time.time() - start_time # End timer
    
    print(f"Input Voltage: {voltage}, DMM Voltage: {dmm_voltage}, ADC Value: {adc_value}, Iteration Time: {elapsed_time}")
    f.write(f"{voltage}, {dmm_voltage}, {adc_value}, {elapsed_time}\n".format(width=10))
    
    # Round to thousandths place to avoid floating point nonsense
    voltage = round((voltage + voltage_step) * 1000) / 1000
    voltage_offset = round((voltage_offset + voltage_step / 2) * 1000) / 1000
    
    # Stop when dmm voltage reaches 3.3
    if (dmm_voltage >= 3.3): break
    
f.close()
