import pyvisa
import time
import numpy as np

rm = pyvisa.ResourceManager('@py')

print(rm.list_resources())

# Open the Arbitrary Function Generator
afg = rm.open_resource('USB0::1689::851::1516313::0::INSTR')

# Open Digital Multimeter
dmm = rm.open_resource('USB0::0x05E6::0x2110::8005314::INSTR')

# Print devices
print(afg.query('*IDN?'))

### SETUP AFG ###

# Reset the instrument to a known state
afg.write("*RST")

# Clears all event registers and queues
afg.write('*CLS')


time.sleep(1)

# Query amplitude voltage
afg.write("SOURce1:FUNCtion:SHAPe PULSe")

time.sleep(1)

afg.write("SOURce1:PULSe:DCYC 99.9")

# enable output
time.sleep(1)

afg.write('OUTPut1:STATe ON')

time.sleep(1)

afg.write("SOURce1:VOLTage:LEVel:IMMediate:AMPLitude 1.0")
afg.write("SOURce1:VOLTage:LEVel:IMMediate:OFFSet 0.5")
    
time.sleep(1)

dmm.query('MEAS:VOLT:DC?')

seconds_per_observation = 1 # seconds
voltage = -0.02

previous_dmm_voltage = 0

f = open("data.txt", "w")

while True:
    if (previous_dmm_voltage >= 3.3): break
    
    voltage += 0.02
    voltage = round(voltage * 1000) / 1000
    offset = round(voltage/2 * 1000) / 1000
    print(f"Voltage: {voltage}, Offset: {offset}")
    
    start_time = time.time_ns() # get current time in nanoseconds
    afg.write("SOURce1:VOLTage:LEVel:IMMediate:AMPLitude " + str(voltage))
    afg.write("SOURce1:VOLTage:LEVel:IMMediate:OFFSet " + str(offset))
    time.sleep(0.01)
    previous_dmm_voltage = float(dmm.query('MEAS:VOLT:DC?'))
    print(previous_dmm_voltage)
    f.write(f"{time.time_ns()/1e9}, {voltage}, {previous_dmm_voltage}\n") # Time (s), AFG Voltage (V), DMM Voltage (V)
    end_time = time.time_ns()
    
    time.sleep(seconds_per_observation - (end_time - start_time)/1e9)

f.close()