from django.db import models
from django.utils import timezone
from IOTSite import dictionary as dic

#=====================================
# common codes
#=====================================
Choices_DeviceType = (
    ('1', 'sensor'),
    ('2', 'controller'),
    ('3', 'gateway'),
    ('4', 'server'),
)

Choices_StatusCd = (
    ('ON', 'On'),
    ('OFF', 'Off'),
)


#=====================================
# Measurement
#=====================================
class tMeasure(models.Model):    
    MeasureDT = models.CharField(blank=False,null=True,max_length=20,verbose_name="Measured DateTime")
    EquipNo = models.CharField(blank=False,null=True,max_length=20,verbose_name="Equipment No")
    ControllerNo = models.CharField(blank=False,null=True,max_length=20,verbose_name="ControllerNo No")
    SensorNo = models.CharField(blank=False,null=True,max_length=20,verbose_name="Sensor No")
    RcvDT = models.CharField(blank=False,null=True,max_length=20,verbose_name="Received DateTime")
    SndDT = models.CharField(blank=False,null=True,max_length=20,verbose_name="Send DateTime")    
    Value = models.CharField(blank=False,null=True,max_length=1000,verbose_name="Values")
    OrderCd = models.CharField(blank=False,null=True,max_length=1000,verbose_name="Order code")

    #for translate to local lanuage
    MeasureDT.verbose_name = dic.getName(MeasureDT.verbose_name)
    EquipNo.verbose_name = dic.getName(EquipNo.verbose_name)
    ControllerNo.verbose_name = dic.getName(ControllerNo.verbose_name)
    SensorNo.verbose_name = dic.getName(SensorNo.verbose_name)
    RcvDT.verbose_name = dic.getName(RcvDT.verbose_name)
    SndDT.verbose_name = dic.getName(SndDT.verbose_name)
    Value.verbose_name = dic.getName(Value.verbose_name)
    OrderCd.verbose_name = dic.getName(OrderCd.verbose_name)

    def __str__(self):
        return "%s %s %s %s %s" %(self.MeasureDT,self.EquipNo,self.ControllerNo,self.SensorNo,self.Value)

    class Meta:
        verbose_name="Measure"
        verbose_name_plural = "Measure"  
        unique_together = (("EquipNo","ControllerNo","SensorNo"),)   

#=====================================
# Master Data
#=====================================
class tDevice(models.Model):    
    DeviceSeq = models.AutoField(primary_key=True,verbose_name="Device Sequence")
    DeviceNo = models.CharField(blank=False,null=True,max_length=20,verbose_name="Device No")
    DeviceName = models.CharField(blank=False,null=True,max_length=40,verbose_name="Device Name")
    DeviceType = models.CharField(choices=Choices_DeviceType,blank=False,null=True,max_length=1,verbose_name="Device Type")
    Remark = models.CharField(blank=True,null=True,max_length=20,verbose_name="Remark")
    IPaddress = models.CharField(blank=True,null=True,max_length=20,verbose_name="IP address")
    RegDT = models.DateTimeField(default=timezone.now,editable=False,verbose_name="Register DateTime")
    RegUserSeq = models.ForeignKey('auth.User',null=True,on_delete=models.SET_NULL,related_name='+',editable=False,db_column="RegUserSeq",verbose_name="Register")
    UptDT = models.DateTimeField(blank=True,null=True,editable=False,verbose_name="Update DateTime")
    UptUserSeq = models.ForeignKey('auth.User',null=True,on_delete=models.SET_NULL,related_name='+',editable=False,db_column="UptUserSeq",verbose_name="Updater")
    StatusCd = models.CharField(choices=Choices_StatusCd,blank=False,null=True,max_length=3,verbose_name="Status")

    def __str__(self):
        return "%s %s" %(self.DeviceNo, self.DeviceName)

    class Meta:
        verbose_name="Device"
        verbose_name_plural = "Device" 
        unique_together = (("DeviceNo"),)   

class tRouting(models.Model):    
    PDeviceSeq = models.ForeignKey(tDevice,blank=True,null=True,on_delete=models.SET_NULL,related_name='+',db_column="PDeviceSeq",verbose_name="Parent Device")
    CDeviceSeq = models.ForeignKey(tDevice,blank=True,null=True,on_delete=models.SET_NULL,related_name='+',db_column="CDeviceSeq",verbose_name="Child Device")

    class Meta:
        verbose_name="Routing"
        verbose_name_plural = "Routing"  
        unique_together = (("PDeviceSeq", "CDeviceSeq"),)   


