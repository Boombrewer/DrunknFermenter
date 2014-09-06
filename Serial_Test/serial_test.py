#!/usr/bin/python
import serial
import syslog
import time

#The following line is for serial over GPIO
port = '/dev/ttyS0'


ard = serial.Serial(port,9600,timeout=10)
time.sleep(2)  # wait for arduino

i = 0

if (i == 0):
		# Serial write section
		#initial adjustment of settings
		ard.flush()
		
		#initial adjustment of settings
		setTempCar1 = 63
		setTempCar2 = 37
		radioCar1 = 1
		radioCar2 = 0
		radioCar3 = 1
		
		#converts the int setting to strings
		setTemp1 = str(setTempCar1)
		setTemp2 = str(setTempCar2)
		rC1 = str(radioCar1)
		rC2 = str(radioCar2)
		rC3 = str(radioCar3)
		
		#debugging print to see what's sent
		print ("Python value sent: ")
		print ('S1')
		print (setTemp1)
		print ('S2')
		print (setTemp2)
		print ('rC1')
		print (rC1)
		print ('rC1')
		print (rC2)
		print ('rC3')
		print (rC3)
		
		#writes out the message to the alamode
		ard.write('S1')
		ard.write(setTemp1)
		ard.write('S2')
		ard.write(setTemp2)
		ard.write('C1')
		ard.write(rC1)
		ard.write('C2')
		ard.write(rC2)
		ard.write('C3')
		ard.write(rC3)
		ard.write('/n')
		
		# Serial read section
		msg = ard.read(ard.inWaiting())
		print ("Message from arduino: ")
		print (msg)
		i = i + 1
		
if (i == 1):
		# Serial write section
		#initial adjustment of settings
		ard.flush()
		
		#second adjustment of settings
		setTempCar1 = 53
		setTempCar2 = 45
		radioCar1 = 0
		radioCar2 = 1
		radioCar3 = 1

		#converts the int setting to strings
		setTemp1 = str(setTempCar1)
		setTemp2 = str(setTempCar2)
		rC1 = str(radioCar1)
		rC2 = str(radioCar2)
		rC3 = str(radioCar3)
		
		#debugging print to see what's sent
		print ("Python value sent: ")
		print ('S1')
		print (setTemp1)
		print ('S2')
		print (setTemp2)
		print ('rC1')
		print (rC1)
		print ('rC1')
		print (rC2)
		print ('rC3')
		print (rC3)
		
		#writes out the message to the alamode
		ard.write('S1')
		ard.write(setTemp1)
		ard.write('S2')
		ard.write(setTemp2)
		ard.write('C1')
		ard.write(rC1)
		ard.write('C2')
		ard.write(rC2)
		ard.write('C3')
		ard.write(rC3)
		ard.write('/n')
		
		# Serial read section
		msg = ard.read(ard.inWaiting())
		print ("Message from arduino: ")
		print (msg)
		i = i + 1
else:
        time.sleep(1)
        print "Exiting"
exit()