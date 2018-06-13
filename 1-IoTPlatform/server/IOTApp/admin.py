from django.contrib import admin
from IOTApp.models import *

# Register your models here.

# Setting admin title
admin.site.site_header = 'IOT Manage( Server )'
admin.site.site_title = 'IOT Manage:'

#============================================================
# ON/OFF
def SWON(modeladmin, request, queryset):
    selected = request.POST.getlist(admin.ACTION_CHECKBOX_NAME)   
    masters = tDevice.objects.filter(DeviceSeq__in=selected)

    reqno = ""
    for master in masters:      
        sensor = master.SensorNo
    
    url = "http://127.0.0.1:8000/Intentjson?"  #gateway
    post_fields = {
    "controller":"NodeMcU",
    "sensor":sensor,
    "onof":"on"
    }

    data = json.dumps(post_fields).encode('utf8')
    urlopen(url,data=data)
    return 0

def SWOFF(modeladmin, request, queryset):
    selected = request.POST.getlist(admin.ACTION_CHECKBOX_NAME)   
    masters = tDevice.objects.filter(DeviceSeq__in=selected)

    reqno = ""
    for master in masters:      
        sensor = master.SensorNo
    
    url = "http://127.0.0.1:8000/Intentjson?"  #gateway
    post_fields = {
    "controller":"NodeMcU",
    "sensor":sensor,
    "onof":"off"
    }

    data = json.dumps(post_fields).encode('utf8')
    urlopen(url,data=data)
    return 0
#============================================================

#=====================================
# Measure
#=====================================
class MeasureAdmin(admin.ModelAdmin):
    save_on_top = True
    list_display = ['MeasureDT','EquipNo','ControllerNo','SensorNo','RcvDT','SndDT','Value','OrderCd']
    list_display_links = list_display
    search_fields = ['EquipNo','ControllerNo','SensorNo']

admin.site.register(tMeasure, MeasureAdmin)

#=====================================
# Master Data
#=====================================
class DeviceAdmin(admin.ModelAdmin):
    actions = [SWON,SWOFF]
    save_on_top = True
    list_display = ['DeviceNo','DeviceName','DeviceType','Remark','StatusCd']
    list_display_links = list_display
    search_fields = ['DeviceNo','DeviceName','DeviceType']

admin.site.register(tDevice, DeviceAdmin)

class RoutingAdmin(admin.ModelAdmin):
    save_on_top = True
    list_display = ['PDeviceSeq','CDeviceSeq']
    list_display_links = list_display
    search_fields = ['PDeviceSeq','CDeviceSeq']

admin.site.register(tRouting, RoutingAdmin)


