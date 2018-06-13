from django.contrib import admin
from IOTApp.models import *
import json
import urllib 

# Register your models here.

# Setting admin title
admin.site.site_header = 'IOT Manage( Gateway )'
admin.site.site_title = 'IOT Manage:'

#=====================================
# ON
#=====================================
def SWON(modeladmin, request, queryset):
    selected = request.POST.getlist(admin.ACTION_CHECKBOX_NAME)   
    masters = tDevice.objects.filter(DeviceSeq__in=selected)

    reqno = ""
    for master in masters:      
        sensor = master.DeviceNo
    
    url = "http://127.0.0.1:8000/Intentjson?"  #gateway
    post_fields = {
    "controller":"NodeMcU",
    "sensor":sensor,
    "onof":"on"
    }

    data = json.dumps(post_fields).encode('utf8')
    urllib.request.urlopen(url,data=data)
    return 0

#=====================================
# OFF
#=====================================
def SWOFF(modeladmin, request, queryset):
    selected = request.POST.getlist(admin.ACTION_CHECKBOX_NAME)   
    masters = tDevice.objects.filter(DeviceSeq__in=selected)

    reqno = ""
    for master in masters:      
        sensor = master.DeviceNo
    
    url = "http://127.0.0.1:8000/Intentjson?"  #gateway
    post_fields = {
    "controller":"NodeMcU",
    "sensor":sensor,
    "onof":"off"
    }

    data = json.dumps(post_fields).encode('utf8')
    urllib.request.urlopen(url,data=data)
    return 0
#============================================================

#=====================================
# Measure
#=====================================
class MeasureAdmin(admin.ModelAdmin):
    save_on_top = True
    list_display = ['MeasureDT','EquipNo','ControllerNo','SensorNo','RcvDT','SndDT','Value']
    list_display_links = list_display
    search_fields = ['EquipNo','ControllerNo','SensorNo']

admin.site.register(tMeasure, MeasureAdmin)


#=====================================
# Master Data
#=====================================
class DeviceAdmin(admin.ModelAdmin):
    actions = [SWON,SWOFF]
    save_on_top = True
    list_display = ['DeviceNo','DeviceName','DeviceType','Remark','IPaddress']
    list_display_links = list_display
    search_fields = ['DeviceNo','DeviceName','DeviceType']

admin.site.register(tDevice, DeviceAdmin)

class RoutingAdmin(admin.ModelAdmin):
    save_on_top = True
    list_display = ['PDeviceSeq','CDeviceSeq']
    list_display_links = list_display
    search_fields = ['PDeviceSeq','CDeviceSeq']

admin.site.register(tRouting, RoutingAdmin)


class MyServerinfoAdmin(admin.ModelAdmin):
    save_on_top = True
    list_display = ['ServerName','DeviceSeq','IPaddress','DatastoreIPaddress']
    list_display_links = list_display
    search_fields = ['ServerName','DeviceSeq','IPaddress']

admin.site.register(tMyServerinfo, MyServerinfoAdmin)

