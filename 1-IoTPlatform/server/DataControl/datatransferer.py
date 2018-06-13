#=========================================
#Transfer data from gateway to server
#=========================================
import requests
import json
import time

gatewayurl="http://127.0.0.1:8000/Transdata"

while(True):
    payload = ""
    response = requests.post(gatewayurl, payload)
    #print(response)
    time.sleep(1)