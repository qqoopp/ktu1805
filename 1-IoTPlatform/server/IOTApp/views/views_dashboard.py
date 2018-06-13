from django.shortcuts import render
from django.views.decorators.csrf import csrf_protect
from django.views.decorators.csrf import csrf_exempt
from django.contrib.auth.decorators import login_required

from IOTApp.models import tMeasure
import json

# dashboard
@login_required(login_url='/admin/login/')
@csrf_exempt
def dashboard(request):
    return render(request,'IOTApp/dashboard.html')


@login_required(login_url='/admin/login/')
@csrf_exempt
def dashboard2(request):
    return render(request,'IOTApp/dashboard2.html')
