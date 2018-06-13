#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <DHT.h>
#include<Wire.h>
#include <ArduinoJson.h>

//Test or Real********************
int isTest = 1; // [0:Real data, 1:Test data]
//********************Test or Real

//Device & Sensor info********************
const char ver[] = "v0.1";  //version info for source management
const char controllerid[] = "NodeMCU"; //controller id
//String supportedsensors[] = {"DHT","PHOTOR","TMP","USONIC"};// supported sensor list

String sensors[] = {"DHT","PHOTOR","LED"};// select connected senssors from supportedsensors and write here
String sensorsstatus[] = {"ON","ON","OFF"};// select connected senssors from supportedsensors and write here

String jsonResult;
//********************Device & Sensor info

//GPIO******************** 
int pinDHT = D2;
int pinTmp = 0;
int pinPhotor = A0;
int pinTrig = D3;
int pinEcho = D4;
int pinLED = D5;
//********************GPIO 

//delaytime********************
int baudrate = 9600; // Change baud rate to 2000000 if postdelaytime < 1000
unsigned int postdelaytime = 3000; // post to server delay time in ms
unsigned long actdiffTime = 0; // main scenario difference
unsigned long actprevTime = 0; // main scenario temp
//********************delaytime 

//setup========================
void setup(){
  Serial.begin(baudrate);  
  
  for( int i=0; i<10; i++){
      if ( sensors[i] == NULL ) break;
      sensors[i].toUpperCase();
      if ( getStatus(sensors[i]) == "ON"){
        if ( sensors[i] == "DHT") setup_dht();
        if ( sensors[i] == "PHOTOR") setup_photor();
        if ( sensors[i] == "TMP") setup_tmp();
        if ( sensors[i] == "USONIC") setup_usonic();
       } 
      if ( sensors[i] == "LED") setup_led();       
   }
   setup_http();
}
//========================setup

//loop=========================
void loop(){

  //for delay calculation*****************
  unsigned long currentTime = millis();
  actdiffTime = currentTime - actprevTime;
  //*****************for delay calculation
  
   for( int i=0; i<10; i++){
      if ( sensors[i] == NULL ) break;
      sensors[i].toUpperCase();
      if ( getStatus(sensors[i]) == "ON" ) {
        if ( actdiffTime >= postdelaytime ){ // delaytime manage
          if ( sensors[i] == "DHT" ) { loop_dht(); loop_http(); }
          if ( sensors[i] == "PHOTOR" ) { loop_photor(); loop_http(); }
          if ( sensors[i] == "TMP") { loop_tmp(); loop_http(); }
          if ( sensors[i] == "USONIC") { loop_usonic(); loop_http(); }
          actprevTime = currentTime;
        }
      }
      if ( sensors[i] == "LED") loop_led();      
   }
/*
   if ( jsonResult != "" ){
      loop_http();
   }
*/
}
//=========================loop

