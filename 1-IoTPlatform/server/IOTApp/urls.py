from django.conf.urls import include, url
from IOTApp.views import *
from django.urls import path
from django.contrib import admin

urlpatterns = [
    path(r'', view=dashboard2),
    url(r'^Postjson$', view=Postjson),
    url(r'^Transdata$', view=Transdata),
    url(r'^dashboard$', view=dashboard),
    url(r'^dashboard2$', view=dashboard2),
    url(r'^chart_guage/(?P<qsensor>[A-Za-z0-9]+)', view=chart_guage),
    url(r'^chart_org$', view=chart_org),
    url(r'^chart_scatter/(?P<qsensor>[A-Za-z0-9]+)', view=chart_scatter),
    url(r'^chart_sankey/(?P<qsensor>[A-Za-z0-9]+)', view=chart_sankey),
    url(r'^chart_line/(?P<qsensor>[A-Za-z0-9]+)', view=chart_line),
    url(r'^chart_table/(?P<qsensor>[A-Za-z0-9]+)', view=chart_table),
    url(r'^chart_map/(?P<qsensor>[A-Za-z0-9]+)', view=chart_map),    
]

