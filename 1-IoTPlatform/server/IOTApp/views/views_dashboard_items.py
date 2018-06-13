from django.shortcuts import render
from django.views.decorators.csrf import csrf_protect
from django.views.decorators.csrf import csrf_exempt
from django.contrib.auth.decorators import login_required

from IOTApp.models import tMeasure, tRouting
import json

maxdatarows = 100
maxtablerows = 10
maxgauagerows = 1

@login_required(login_url='/admin/login/')
@csrf_exempt
def chart_guage(request,qsensor):

    qsensor = qsensor.upper()
    rowcnt = int(tMeasure.objects.filter(SensorNo=qsensor).count())

    sensordata = ""
    columns = ""

    if rowcnt == 0:
        sensordata = ""
    else:
        sensordata = tMeasure.objects.filter(SensorNo=qsensor).order_by('-MeasureDT').values('Value')[:maxgauagerows]
        columns = list(json.loads(sensordata[0]['Value']).keys())
        columns.remove('measuredt')
        columns.remove('controller')
        columns.remove('sensor')
        columns.remove('uptime')
        columns.remove('ip')

    return render(request,'IOTApp/chart_guage.html',{'sensordata':sensordata,'columns':columns})


@login_required(login_url='/admin/login/')
@csrf_exempt
def chart_org(request):

    sensordata = ""
    columns = ""

    return render(request,'IOTApp/chart_org.html',{'sensordata':sensordata})


@login_required(login_url='/admin/login/')
@csrf_exempt
def chart_line(request,qsensor):

    qsensor = qsensor.upper()
    rowcnt = int(tMeasure.objects.filter(SensorNo=qsensor).count())

    sensordata = ""
    columns = ""

    try:
        if rowcnt == 0:
            sensordata = ""
        else:
            sensordata = tMeasure.objects.filter(SensorNo=qsensor).order_by('-MeasureDT').values('Value')[:maxdatarows]
            columns = list(json.loads(sensordata[0]['Value']).keys())
            columns.remove('measuredt')
            columns.remove('controller')
            columns.remove('sensor')
            columns.remove('uptime')
            columns.remove('ip')
    except:
        pass

    return render(request,'IOTApp/chart_line.html',{'sensordata':sensordata,'columns':columns})


@login_required(login_url='/admin/login/')
@csrf_exempt
def chart_scatter(request,qsensor):

    qsensor = qsensor.upper()
    rowcnt = int(tMeasure.objects.filter(SensorNo=qsensor).count())

    sensordata = ""
    columns = ""

    try:
        if rowcnt == 0:
            sensordata = ""
        else:
            sensordata = tMeasure.objects.filter(SensorNo=qsensor).order_by('-MeasureDT').values('Value')[:maxdatarows]
            columns = list(json.loads(sensordata[0]['Value']).keys())
            columns.remove('measuredt')
            columns.remove('controller')
            columns.remove('sensor')
            columns.remove('uptime')
            columns.remove('ip')
    except:
        pass

    return render(request,'IOTApp/chart_scatter.html',{'sensordata':sensordata,'columns':columns})


@login_required(login_url='/admin/login/')
@csrf_exempt
def chart_table(request,qsensor):

    qsensor = qsensor.upper()
    rowcnt = int(tMeasure.objects.filter(SensorNo=qsensor).count())

    sensordata = ""
    columns = ""

    try:
        if rowcnt == 0:
            sensordata = ""
        else:
            sensordata = tMeasure.objects.filter(SensorNo=qsensor).order_by('-MeasureDT').values('Value')[:maxtablerows]
            columns = list(json.loads(sensordata[0]['Value']).keys())
            columns.remove('measuredt')
            columns.remove('controller')
            columns.remove('sensor')
            columns.remove('uptime')
            columns.remove('ip')
    except:
        pass

    return render(request,'IOTApp/chart_table.html',{'sensordata':sensordata,'columns':columns})


@login_required(login_url='/admin/login/')
@csrf_exempt
def chart_map(request,qsensor):

    qsensor = qsensor.upper()
    rowcnt = int(tMeasure.objects.filter(SensorNo=qsensor).count())

    sensordata = ""
    columns = ""

    try:
        if rowcnt == 0:
            sensordata = ""
        else:
            sensordata = tMeasure.objects.filter(SensorNo=qsensor).order_by('-MeasureDT').values('Value')[:maxdatarows]
            columns = list(json.loads(sensordata[0]['Value']).keys())
            columns.remove('measuredt')
            columns.remove('controller')
            columns.remove('sensor')
            columns.remove('uptime')
            columns.remove('ip')
    except:
        pass

    return render(request,'IOTApp/chart_map.html',{'sensordata':sensordata,'columns':columns})


@login_required(login_url='/admin/login/')
@csrf_exempt
def chart_sankey(request,qsensor):

    qsensor = qsensor.upper()
    rowcnt = int(tRouting.objects.count())
    rows = rowcnt - maxdatarows - 1

    if rows < 0 :
        rows = 0

    sensordata = tRouting.objects.all()[rows:]
    
    columns = {"PDeviceSeq","CDeviceSeq"}#list(json.loads(sensordata[0]).keys())

    return render(request,'IOTApp/chart_sankey.html',{'sensordata':sensordata,'columns':columns})