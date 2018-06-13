#from django.test import TestCase
from urllib.request import Request, urlopen
from urllib.parse import urlencode
from random import randint
from datetime import datetime
from django.http import HttpResponse
import json
import time
import re

def application(env, start_response):
    start_response('200 OK', [('Content-Type','text/html')])
    return [b"Hello World"] # python3

def ParseIEEEOui():
    url = "http://standards.ieee.org/develop/regauth/oui/oui.txt"
    req = Request(url)
    res = urlopen(req)
    data = res.read()

    IEEOUI = []
    for line in data.split("\n"):
        mac, company = re.search(r'([0-9A-F]{2}-[0-9A-F]{2}-[0-9A-F]{2})\s+\(hex\)\s+(.+)', line)
        IEEOUI.append(dict(mac=mac, company=company))

    return IEEOUI


def PostTester():
    url = "http://127.0.0.1:8000/Postjson?"
    post_fields = {"measuredt":datetime.now().strftime("%Y%m%d%H%M%S.%f"),
    "controller":"Arduino",
    "sensor":"DHT",
    "uptime":131164,
    "temp":randint(-10,20),
    "humi":randint(20,80)
    }

    data = json.dumps(post_fields).encode('utf8')
    print(data)
    urlopen(url,data=data)
    return 0

if __name__ == "__main__":
    # execute only if run as a script
    for i in range(1,2):
        PostTester()
        time.sleep(2)

    #ParseIEEEOui()