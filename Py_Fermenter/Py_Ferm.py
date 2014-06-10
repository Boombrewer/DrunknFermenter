#! /usr/bin/python
# The script is used to pass information between the alamode and the raspberry pi.

#Written by Casey McHenry
#Version 1.0

import sys
import serial
import time
from datetime import datetime
#import car1data
#import car2data
#import car3data

port = "/dev/ttyS0"

#opens the serial port the alamode is connected to
ser = serial.Serial(port, 9600)

time.sleep(1.5)

setTempCar1 = 63
setTempCar2 = 37
setTempCar1Str = str(setTempCar1)
setTempCar2Str = str(setTempCar2)
setTemps = [setTempCar1Str, setTempCar2Str]
print (setTempCar1)
print (setTempCar2)
print (setTempCar1Str)
print (setTempCar2Str)
#print (setTemps)
ser.open()
ser.write (setTempCar1Str)
ser.close()

ser.open()
print("connected to: " + ser.portstr)

line = ser.readline()
print(str(line))

ser.close()
