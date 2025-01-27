# This test automatically gets data from the DMM in voltmeter mode, DMM in ammeter mode, and the STM32 ADC reading
# You manually change the PSU input since it isn't programmable

import pyvisa
import serial
import time

import HelperFunctions

text = "1212, 8989\n\x00"
print(text + "!")

# write a line to convert the text into a list of floats
# First, clean it
text1, text2 = text.replace("\n", "").replace("\x00", "").replace(" ", "").split(",")
print(text1)
print(text2)

# Replace all terms in a string that equal delete_chars with ""
def remove_chars(text, delete_chars):
    for char in delete_chars:
        text = text.replace(char, "")
    return text

print(" --- ")
print(text)
print(remove_chars(text, ["\n", "\x00", " "]))
