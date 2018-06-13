//Host Server config********************
const char* ssid     = "AP1-000";
const char* password = "12345678";
const char * gatewayip = "192.168.137.1"; // ip or dns
const uint16_t port = 8000;
IPAddress myIP;
ESP8266WebServer server(80);
//********************Host Server config

void setup_http(){

    //connect to AP +++++++++++++++++++++
    WiFi.mode(WIFI_STA);
    delay(100);
    WiFi.begin( ssid, password );

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    myIP = WiFi.localIP();

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(myIP);
    delay(10);
    //+++++++++++++++++++++connect to AP

    setup_webserver();
}

void setup_webserver(void){  
    //Start web server+++++++++++++++++++++
    server.on ( "/", handleRoot );
    server.on ( "/Postjson", handleBody );
    server.begin();
    Serial.println("HTTP server started");
    //+++++++++++++++++++++Start web server
}

void loop_webserver(void){
  server.handleClient();
}

void handleRoot() {
  String msg = server.arg("");
  msg += "You are connected!";
  server.send ( 200, "text/plain", msg );
}

void handleBody() { //Handler for the body path
      String message = "";
      if (server.hasArg("plain")){ 
          message = server.arg("plain");
      }
      else if (server.hasArg("json")){ 
          message + server.arg("json");
      }
      else {
        server.send(200, "text/plain", "Body not received");
        return;
      }

       //Json data generation ============================
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(message);
    
        setStatus(root["sensor"], root["onoff"]);
        //============================Json data generation
      
      server.send(200, "text/plain", message);
      Serial.println(message);
      message = "";
}

void loop_http(){
    loop_webserver();
    
    if (jsonResult == "") return;
    
    Serial.print(myIP);
    Serial.print(" -> ");
    Serial.println(gatewayip);

    if(WiFi.status() == WL_CONNECTED) {
      if ( jsonResult != "" )  {
        sendhttp(jsonResult);
        jsonResult = "";
      }
    }
    Serial.print("wait ");
    Serial.print(String(postdelaytime));
    Serial.println(" sec...");
}

//send data to server 
void sendhttp(String postdata){ 
  if (postdata == "") return; 
  String hosturl = "http://" + String(gatewayip) + ":" + String(port) + "/Postjson";
  
  HTTPClient http;
  http.begin(hosturl);
  //http.addHeader("POST /PostMeasure HTTP/1.1");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Cache-Control","no-cache");
  http.POST(postdata);
  http.writeToStream(&Serial);
  String rtnmsg = http.getString();
  http.end();

  //Serial.println(rtnmsg);  
  Serial.print("posted");
  Serial.println(postdata);
}

