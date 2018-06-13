//DHT******************** 
typedef enum
{
    DHTTYPE_DHT11         = DHT11, // DHT 11
    DHTTYPE_DHT22         = DHT22, // DHT 22, AM2302, AM2321
    DHTTYPE_DHT21         = DHT21 // DHT 21, AM2301
} DHTTYPE;

DHT dht(pinDHT, DHTTYPE_DHT11);
float temp, humi;
String jsonDHT;
//********************DHT 

//setup========================
void setup_dht(){
  dht.begin();
}
//========================setup

//loop========================
void loop_dht(){

  temp = dht.readTemperature();
  humi = dht.readHumidity();

  // change noise data to 0
  if ( !isFloat(String(temp)) ) { 
    temp = 0;
    humi = 0;
  }
  
  //======================
  // testdata ============
  if (isTest == 1) {
    if (temp == 0){ temp = random(10,40);}
    if (humi == 0){ humi = random(10,60);}
  }
  // testdata ============
  //======================

  //Json data generation ============================
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["measuredt"] = "";       
  root["controller"] = controllerid;        
  root["sensor"] = "DHT";
  root["uptime"] = millis();
  root["ip"] = myIP.toString();
  root["temp"] = temp;
  root["humi"] = humi; 
  
  root.printTo(jsonResult);
  root.printTo(Serial);
  Serial.println("");
  //============================Json data generation
}
//========================loop

