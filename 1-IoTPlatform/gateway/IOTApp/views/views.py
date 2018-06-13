from django.shortcuts import render
import json
from django.http import StreamingHttpResponse
from django.http import HttpResponseRedirect
from django.urls import reverse
from django.views.decorators.csrf import csrf_protect
from django.views.decorators.csrf import csrf_exempt

from IOTApp.models import *
from django.utils import timezone
from datetime import datetime
import http
from django.http import HttpResponse

import requests
import time

def getMyIP():
    ipaddresss = tMyServerinfo.objects.values('IPaddress')
    for ipaddress in ipaddresss:
        return ipaddress["IPaddress"]

def getDatastoreIP():
    ipaddresss = tMyServerinfo.objects.values('DatastoreIPaddress')
    for ipaddress in ipaddresss:
        return ipaddress["DatastoreIPaddress"]

#===============================
# save json data to db
#===============================
#@csrf_protect
@csrf_exempt
def Postjson(request):
    if request.method=="POST":

        try:
            bodydata = request.body.decode("utf-8").replace('\n', '').replace('\r', '').replace(' ', '')
            jdata = json.loads(bodydata)
            
            rdt = timezone.now().strftime("%Y%m%d%H%M%S.%f")
            mdt = jdata.get('measuredt')
            if (mdt == ""):
                mdt = rdt
                bodydata = bodydata.replace("\"measuredt\":\"\"","\"measuredt\":\"" + rdt + "\"")

            controller = jdata.get("controller").upper()
            sensor = jdata.get("sensor").upper()
            controllerip = jdata.get("ip")

            ipaddress = ""
            mydevice = 0
            ipaddresss = tDevice.objects.filter(DeviceNo=controller).values('IPaddress')
            ipaddresss2 = tDevice.objects.filter(DeviceNo=sensor).values('IPaddress')
            mydevices = tMyServerinfo.objects.values('DeviceSeq')[:1]

            #update controller ip
            for ipaddress in ipaddresss:
                if controllerip != ipaddress:
                    tDevice.objects.filter(DeviceNo=controller).update(IPaddress=controllerip)

            #update sensor ip( controller ip )
            for ipaddress in ipaddresss2:
                if controllerip != ipaddress:
                    tDevice.objects.filter(DeviceNo=sensor).update(IPaddress=controllerip)

            # #update gateway ip
            # for mydevice in mydevices:
            #     ipaddresss = tDevice.objects.filter(DeviceSeq=mydevice).values('IPaddress')
            #     for ipaddress in ipaddresss:
            #         tDevice.objects.filter(DeviceNo=sensor).update(IPaddress=request)   

        except Exception as e:
            return StreamingHttpResponse("err: " + str(request.body))

        try:
            postdata = tMeasure(
                MeasureDT=mdt, #jdata.get('measuredt'),
                ControllerNo=controller,
                SensorNo=jdata.get("sensor").upper(),
                RcvDT=rdt,
                Value=bodydata,
            )
            postdata.save()

        except Exception as e:
            return StreamingHttpResponse("err: " + str(request.body))

        return StreamingHttpResponse(str(request.body))
        #return HttpResponse(status=200)
    
    return StreamingHttpResponse("GET")

#===============================
# Trans data to server
#===============================
@csrf_exempt
def Transdata(request):
    if request.method=="POST":
        url="http://" + getDatastoreIP() + "/Postjson"

        # read table rows. update senddata
        rdata = tMeasure.objects.all().filter(SndDT__isnull=True)[:1]

        try:
            for row in rdata:
                payload = row.Value.strip()
                response = requests.post(url, payload)
                time.sleep(0.1)

                rdt = timezone.now().strftime("%Y%m%d%H%M%S.%f")
                tMeasure.objects.filter(id=row.id).update(SndDT=rdt)

        except Exception as e:
            return StreamingHttpResponse("err: " + str(request.body))

        return StreamingHttpResponse(str(request.body))
        #return HttpResponse(str(request.body))

    return StreamingHttpResponse("GET")

#===============================
# Save Intent order to file
#===============================
@csrf_exempt
def Intentjsonfile(request):
    if request.method=="POST":

        logfilepath = "./Datacontrol/intent/"

        try:
            bodydata = request.body.decode("utf-8").replace('\n', '').replace('\r', '').replace(' ', '')
            jdata = json.loads(bodydata)
            
        except Exception as e:
            return StreamingHttpResponse("err: " + str(request.body))

        try:
            ymdhms = datetime.now().strftime('%Y%m%d%H%M%S.%f')
            ymdhm = ymdhms[:12]
            filename = logfilepath +  ymdhm + ".log" 
            
            f = open(filename, 'ab')
            adddata = "{\"sensor\":\"" + jdata.get("sensor") + "\",\"onoff\":\"" + jdata.get("onoff") + "\"}"
            f.write(adddata.encode('ascii'))
            f.close()

        except Exception as e:
            return StreamingHttpResponse("err: " + str(request.body))

        return StreamingHttpResponse(str(request.body))
    
    return StreamingHttpResponse("GET")


#===============================
# Intent order call controller
#===============================
@csrf_exempt
def Intentjson(request):
    if request.method=="POST":

        bodydata = request.body.decode("utf-8").replace('\n', '').replace('\r', '').replace(' ', '')
        jdata = json.loads(bodydata)

        controller = jdata.get("controller")
        sensor = jdata.get("sensor")
        onoff = jdata.get("onoff")

        controllerip = ""

        controllerips = tDevice.objects.filter(DeviceNo=sensor).values('IPaddress')
        for controllerip in controllerips:
            controllerip = controllerip

        url="http://" + controllerip + "/Postjson"

        try:
            requests.adapters.DEFAULT_RETRIES = 1
            requests.adapters.DEFAULT_POOL_TIMEOUT = 5
            response = requests.post(url, bodydata)
            return StreamingHttpResponse(str(requests) + ":" + str(request.body))
        except Exception as e:
            return StreamingHttpResponse("err: " + str(request.body) + "\n" + str(e)[:90] + "...")
    
    return StreamingHttpResponse("GET")