import serial 
import MySQLdb
import time

#Connection to the database.
dbConn = MySQLdb.connect("localhost","root","","rfiddatabase") or die ("could not connect to database")

#cursor to the database.
cursor = dbConn.cursor()

device = 'COM3'
try:
  print "Trying...",device 
  arduino = serial.Serial(device, 9600) 
except: 
  print "Failed to connect on",device
while True:
    time.sleep(1)
    try:
        data=arduino.readline()
        print data
        pieces=data.split(" ")
        try:
            cursor=dbConn.cursor()
            cursor.execute("""INSERT INTO intersection1 (ID,INTERSECTION_ADDRESS,RFID_NUMBER,STATUS,
NEAREST_POLICE) VALUES (NULL,%s,%s,%s,%s)""", ("sec - 47 ",pieces[0],pieces[1],"9566117389"))
            dbConn.commit()
            cursor.close()
        except MySQLdb.IntegrityError:
            print "failed to insert data"
        finally:
            cursor.close()
    except:
        print "Processing"
