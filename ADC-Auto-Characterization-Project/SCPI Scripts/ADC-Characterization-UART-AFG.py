import serial
import pyvisa
import time

import HelperFunctions as hf

rm = pyvisa.ResourceManager('@py')

# You'll need to copy paste some of the IDs here into the rm.open_resource() functions below
print(rm.list_resources())

# Open arbitrary function generator & digital multimeter
# NOTE: the USB device/resource tags below will be different for you, that's why we print the resources above, see wiki for more info
afg = rm.open_resource('USB0::1689::851::1516313::0::INSTR')
dmm = rm.open_resource('USB0::0x05E6::0x2110::8005314::INSTR')

# Setup the afg to output a pulse with a 99.9% duty cycle and period of 1000000s
hf.set_afg_pulse_high_voltage(afg)
hf.enable_afg_output(afg)

serial_bus = hf.open_serial("COM7", 115200)

voltage = 0.1
voltage_step = 0.1

exit_dmm_voltage = 3.3 # When the DMM hits this value, we stop

max_ADC_values_count = 0 # When there are >5 max ADC values (4095), we stop
exit_max_ADC_value = 5 # Exit when 5 adc values have been at the max
max_ADC_value = 4095

f = open("data.csv", "w")
f.write(f"Input Voltage,DMM Voltage,ADC Raw Value,ADC Adjusted Value, ADC Current Adjusted Value,Iteration Time\n")

while True:
    timer = hf.Timer()
    
    hf.set_afg_pulse_high_voltage(afg, voltage)
    time.sleep(0.5) # Let the capacitor charge, this was for a specific test with the LVS_CURR_SENSE pin
    
    adc_raw_value, adc_adjusted_value, adc_current_adjusted_value = hf.get_adc_value_from_stm32(serial_bus)
    dmm_voltage = hf.get_dmm_voltage(dmm)
    
    dmm_voltage = float(dmm.query('MEASure:VOLTage:DC?')) # After the STM32 is done, read the DMM voltage
    
    elapsed_time = timer.get_elapsed_time()
    
    raw_str_out = f"{voltage},{dmm_voltage},{adc_raw_value},{adc_adjusted_value},{adc_current_adjusted_value},{elapsed_time}"
    labeled_str_out = f"Input Voltage: {voltage}, DMM Voltage: {dmm_voltage}, ADC Raw Value: {adc_raw_value}, ADC Adjusted Value {adc_adjusted_value}, ADC Current Adjusted Value {adc_current_adjusted_value}, Iteration Time: {elapsed_time}"
    
    print(labeled_str_out)
    f.write(raw_str_out + "\n")
    
    # Round to thousandths place to avoid floating point nonsense
    voltage = round((voltage + voltage_step) * 1000) / 1000
    voltage_offset = round((voltage_offset + voltage_step / 2) * 1000) / 1000
    
    # Stop when dmm voltage reaches 3.3
    if (dmm_voltage >= exit_dmm_voltage): break
    
    # Stop when we have 5 max ADC values
    if (adc_raw_value >= max_ADC_value): max_ADC_values_count += 1
    if (max_ADC_values_count >= exit_max_ADC_value): break
    
    
f.close()