#=========================================
# Listen from usb serial port and save data to log file
#=========================================

import serial
import time
import subprocess
import os
from time import strftime
from datetime import datetime

serialbaudrate = 2000000 # speed to get data from serial port
logfilepath = "./data/"

def prompt(prompt):
    return input(prompt).strip()

def putSerial(ser):

    #makes filename every min
    ymdhms = datetime.now().strftime('%Y%m%d%H%M%S.%f')
    ymdhm = ymdhms[:12]#datetime.now().strftime('%Y%m%d%H%M')
    filename = logfilepath +  ymdhm + ".log" 

    row = ser.readline()

    f = open(filename, 'ab')
    #if row[:1].decode('utf-8') == "{":
    if row[:1].decode('utf-8') == "{":
        #adddata = "{\"measuredt\":\"" + ymdhms + "\",\"data\":"
        adddata = row.decode('utf-8').replace("\"measuredt\":\"\"","\"measuredt\":\"" + ymdhms + "\"")
        f.write(adddata.encode('ascii'))
        #f.write(row)
    else:
        f.write(row)
    f.close()

if __name__ == "__main__":
    #python -m serial.tools.list_ports
    portlist = subprocess.Popen(["python","-m","serial.tools.list_ports"],
                        shell=False,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE)

    print("currently connected ports list : ")
    #print(portlist.stdout.readlines().replace('\r\n', ''))
    for line in iter(portlist.stdout.readline, b''):
        print( line.strip().decode('utf-8') )
        print("")

    print("Present baudrate is : " + str(serialbaudrate))

    comport = prompt("Input comport (ex)COM22): ")
    serialbaudrate = prompt("Input baudrate (ex)9600): ")
   
    try:

        ser = serial.Serial(
            port=comport, 
            baudrate = serialbaudrate,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=0)

        print("Receiving data...")
        while(True):
            putSerial(ser)
            time.sleep(0.0001)
    except:
        print("")
        print("Incoreect port. Please check port")
        exit
