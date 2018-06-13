#==================================
# source code for raspberry pi gateway
#==================================

#sudo nano serialtest.py

import serial

#serACM0 = serial.Serial('/dev/ttyACM0',9600)
#serUSB0 = serial.Serial('/dev/ttyUSB0',9600)
serACM0 = serial.Serial('/dev/ttyUSB0',9600)
serUSB0 = serial.Serial('/dev/ttyUSB1',9600)

while True:
    lineACM0 = serACM0.readline().decode("utf-8").strip('\n').strip('\r')
    lineUSB0 = serUSB0.readline().decode("utf-8").strip('\n').strip('\r')
    print( "Arduino : " + lineACM0 + " , NodeMCU : " + lineUSB0 )
