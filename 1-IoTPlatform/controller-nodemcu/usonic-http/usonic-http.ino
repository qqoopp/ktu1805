#include <ESP8266WiFi.h> // ap connection
#include <ESP8266HTTPClient.h> // webs server call

//web ********************
const char* ssid     = "AP1-00";   // AP name : AP1-nn
const char* password = "12345678"; // AP password
const char * gatewayip = "192.168.137.1"; // gateway ip 192.168.10.x
const uint16_t gatewayport = 8000;  // gateway webserver port
const char* posturl = "/Postjson";  // gateway webserver receive url
IPAddress myIP;
//******************** web

//usonicvalue******************** 
float usonicvalue;
//********************usonicvalue

float temp, humi;

void setup(){
  Serial.begin(9600);  
  setup_usonic(); 
  setup_web();
}

void loop(){
  loop_usonic();
  loop_web();
  delay(1000);
}

void setup_web(){
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
}

void loop_web(){

    Serial.print(myIP);
    Serial.print(" --> ");
    Serial.println(gatewayip);

    if(WiFi.status() == WL_CONNECTED) {
      String data = "{";
      data += "\"measuerdt\":\"\",";    // set sensig time to blank because we do not have RTC
      data += "\"controller\":\"NodeMCU\",";
      data += "\"sensor\":\"usonic\",";
      data += "\"uptime\":" + String(millis()) + ",";
      data += "\"dist\":" + String(usonicvalue) + ",";
      data += "}";
      
      Serial.println(data);
      sendhttp(data);
    }

    Serial.print("wait ");
    Serial.println(" sec...");
}

void sendhttp(String postdata){ 
  String gatewayipurl = "http://" + String(gatewayip) + ":" + String(gatewayport) + posturl;
  
  HTTPClient http;
  http.begin(gatewayipurl);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Cache-Control","no-cache");
  http.POST(postdata);
  http.writeToStream(&Serial);
  String rtnmsg = http.getString();
  http.end();

  Serial.println("posted");
}


