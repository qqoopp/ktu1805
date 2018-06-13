#=========================================
#Transfer data from gateway to elasticsearch pc server
#=========================================
import subprocess
import time
import os

elkurl='localhost:9200/tmeasure/_doc?pretty'
path = "./data/"

def postdata(data):
    data = data.strip().replace("\r\n","")
    data = data.replace("measuredt","@timestamp")
    argss=["curl","-X","POST",elkurl,"-H","Content-Type: application/json","-d",data]
    output = subprocess.Popen(args=argss,
                        shell=False,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE)

    # print( output.stdout.readline )
    for line in iter(output.stdout.readline, b''):
        print( line.strip().decode('utf-8') )

    for line in iter(output.stderr.readline, b''):
        print( line.strip().decode('utf-8') )

if __name__ == "__main__":
    for filename in os.listdir(path):
        if filename.endswith(".log") and filename[:2] !="@@":

            f = open(path + filename, 'rb')
            rows = f.readlines()
            f.close()

            os.rename(path + filename, path + "@" + filename)  #check trensferred data file

            for row in rows:
                postdata(row.decode('utf-8'))
                time.sleep(1)
