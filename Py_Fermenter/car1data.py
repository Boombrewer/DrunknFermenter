#! /usr/bin/python
# The script is used to read carboy 1 data and variables.

#Written by Casey McHenry
#Version 1.0


# view_rows.py - Fetch and display the rows from a MySQL database query
# import the MySQLdb and sys modules
import MySQLdb
import sys

# open a database connection
# be sure to change the host IP address, username, password and database name to match your own
connection = MySQLdb.connect (host = "192.168.1.2", user = "user", passwd = "password, db = "scripting_mysql")

# prepare a cursor object using cursor() method
cursor = connection.cursor ()

# execute the SQL query using execute() method.
cursor.execute ("select name_first, name_last from address")

# fetch all of the rows from the query
data = cursor.fetchall ()

# print the rows
for row in data :
print row[0], row[1]

# close the cursor object
cursor.close ()

# close the connection
connection.close ()

# exit the program
sys.exit()