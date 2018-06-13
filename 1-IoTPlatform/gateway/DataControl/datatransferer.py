#=========================================
#Transfer data from gateway to server
#=========================================
import requests
import sqlite3
import sys
import time

sqlite_file = '../db.sqlite3'
conn = sqlite3.connect(sqlite_file)
c = conn.cursor()
c.execute('SELECT IPaddress FROM IOTApp_tmyserverinfo')   # get gateway ip
all_rows = c.fetchall()
gatewayip = all_rows[0][0]
conn.close()

def prompt(prompt):
    return input(prompt).strip()

comport = prompt("Change gateway ip:port " + gatewayip + " ?")

gatewayurl="http://" + gatewayip + "/Transdata"

while(True):
    try:
        payload = ""
        response = requests.post(gatewayurl, payload)
        time.sleep(1)
    except KeyboardInterrupt:
        sys.exit()
    except Exception as e:
        print('error : ' + str(e) )
        sys.exit()