#!/usr/bin/python
import serial
import syslog
import time
import datetime
import MySQLdb as mdb

#The following line is for serial over GPIO
port = '/dev/ttyS0'

ard = serial.Serial(port,9600,timeout=5)

# Edit this line to point to where web_fermenter is
dir = '/var/www'

# Open db connection
db = mdb.connect("localhost","root","morebeers","drunknfermenter" )

# Prepare a cursor object using cursor() method
cursor = db.cursor()

# Create tables if they don't exist

sql_set_temp = """CREATE TABLE IF NOT EXISTS 'set_temp' (
		'DATE_TIME' DATETIME NOT NULL,
		'SET_TEMP_1' float(3,1) NOT NULL,
		'SET_TEMP_2' float(3,1) NOT NULL,
		PRIMARY KEY ('DATE_TIME'))"""

cursor.execute(sql_set_temp)

sql_current_temp = """CREATE TABLE IF NOT EXISTS 'current_temp' (
		'DATE_TIME' DATETIME NOT NULL,
		'IN_TEMP' float(3,1) NOT NULL,
		'CAR_1_TEMP' float(3,1) NOT NULL,
		'CAR_2_TEMP' float(3,1) NOT NULL,
		'CAR_3_TEMP' float(3,1) NOT NULL,
		PRIMARY KEY ('DATE_TIME'))"""
				
cursor.execute(sql_current_temp)

sql_status = """CREATE TABLE IF NOT EXISTS 'status' (
		'DATE_TIME' DATETIME NOT NULL,
		'COOL_STATUS' tinyint(1) NOT NULL DEFAULT 0,
		'HEAT_1_STATUS' tinyint(1) NOT NULL DEFAULT 0,
		'HEAT_2_STATUS' tinyint(1) NOT NULL DEFAULT 0,
		'IN_FAN_STATUS' tinyint(1) NOT NULL DEFAULT 0,
		'CAR_3_FAN' tinyint(1) NOT NULL DEFAULT 0,
		'RADIO_1' tinyint(1) NOT NULL DEFAULT 0,
		'RADIO_2' tinyint(1) NOT NULL DEFAULT 0,
		'RADIO_3' tinyint(1) NOT NULL DEFAULT 0,
		PRIMARY KEY ('DATE_TIME'))"""

cursor.execute(sql_status)

# Read the temps & status from the alamode
running = True

try:
	while running:
		msg = ard.readline(ard.inWaiting())
	if not msg:
		continue
	#split up the string into temps & statuses
	a,b,c,d,e,f,g,h,i = msg.split(";")
	if (a[0] == "i" and a[1] == "T"):
		i_temp = int(a[2:6])
	if (b[0] == "C" and b[1] == "1"):
		c_1_temp = int(b[2:6])
	if (c[0] == "C" and c[1] == "2"):
		c_2_temp = int(c[2:6])
	if (d[0] == "C" and c[1] == "3"):
		c_3_temp = int(d[2:6])
	if (e[0] == "C" and e[1] == "S"):
		c_status = int(e[2])
	if (f[0] == "H" and f[1] == "1"):
		h_1_status = int(f[2])
	if (g[0] == "H" and g[1] == "2"):
		h_2_status = int(f[2])
	if (h[0] == "i" and h[1] == "F"):
		i_fan_status = int(g[2])
	if (i[0] == "c" and i[1] == "3"):
		c_3_fan = int(i[2])
	else:
		print ("Unknown message: "+msg)
	
# Pass temps & status to db

insert_temp = "INSERT INTO current_temp (DATE_TIME, IN_TEMP, CAR_1_TEMP, CAR_2_TEMP,\
		CAR_3_TEMP) VALUES (%d, %d, %d, %d, %d) % (NOW(), i_temp, c_1_temp, c_2_temp, c_3_temp)"
				
insert_status = """INSERT INTO 'status' (DATE_TIME, COOL_STATUS, HEAT_1_STATUS,
		HEAT_2_STATUS,IN_FAN_STATUS, CAR_3_FAN) VALUES (NOW(), $c_status,
		$h_1_status, $h_2_status,$i_fan_status, $c_3_fan)"""
				
try:
   # Execute the insert_temp command
   cursor.execute(insert_temp)
   # Commit your changes in the database
   db.commit()
except:
   # Rollback in case there is any error
   db.rollback()
   
try:
   # Execute the insert_status command
   cursor.execute(insert_status)
   # Commit your changes in the database
   db.commit()
except:
   # Rollback in case there is any error
   db.rollback()
   
# Pull temp settings from db

get_set_temps = "SELECT * FROM set_temp WHERE DATETIME < '%d' (DATETIME(NOW))"

try:
   cursor.execute(get_set_temps)
   # Fetch all the rows in a list of lists.
   results = cursor.fetchone()
   for row in results:
      datetime = row[0]
      set_temp_1 = row[1]
      set_temp_2 = row[2]
      # Now print fetched result
      print "datetime=%s,set_temp_1=%d,set_temp_2=%d" % \
             (datetime, set_temp_1, set_temp_2)
except:
   print "Error: unable to fecth data"

# send set temps and radio status (in the future) to alamode

ard.flushOutput()
		
# Radion button settings as message placeholder for later versions
radioCar1 = 1
radioCar2 = 1
radioCar3 = 1
		
#converts the int setting to strings
setTemp1 = str(set_temp_1)
setTemp2 = str(set_temp_2)
rC1 = str(radioCar1)
rC2 = str(radioCar2)
rC3 = str(radioCar3)
		
#debugging print to see what's sent
#print ("Python value sent: ")
#print ("S1: "+ setTemp1)
#print ("T2: "+ setTemp2)
#print ("rC1: "+ rC1)
#print ("rC2: "+ rC2)
#print ("rC3: "+ rC3)

#writes out the message to the alamode
ard.write('S1')
ard.write(setTemp1)
ard.write('T2')
ard.write(setTemp2)
ard.write('C1')
ard.write(rC1)
ard.write('C2')
ard.write(rC2)
ard.write('C3')
ard.write(rC3)
ard.write('/n')
		
#gives alamode time to process
time.sleep(2)
		
exit()