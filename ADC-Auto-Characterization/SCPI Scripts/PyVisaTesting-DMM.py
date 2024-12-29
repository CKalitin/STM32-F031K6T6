import pyvisa
import time

rm = pyvisa.ResourceManager('@py')

print(rm.list_resources())
print(rm)

instrument = rm.open_resource('USB0::0x05E6::0x2110::8005314::INSTR')
print(instrument.query('*IDN?'))

# print(instrument.read())

delay_per_obv = 0.5 # seconds

while True:
    # get current time in nanoseconds
    start_time = time.time_ns()
    voltage = instrument.query('MEAS:VOLT:DC?')
    end_time = time.time_ns()
    
    #print(f"{start_time}, {end_time}, {end_time - start_time} {(end_time - start_time)/1e9}")
    time.sleep(delay_per_obv - (end_time - start_time)/1e9)
    print(f"{time.time_ns()/1e9}, {voltage}, {(end_time - start_time)/1e9}") # Time (s), Voltage (v), Obv Time (s)