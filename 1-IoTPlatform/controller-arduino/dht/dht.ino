#include <DHT.h>

//GPIO******************** 
//Power 3V
int pinDHT = 2;
//********************GPIO 

//DHT******************** 
typedef enum
{
    DHTTYPE_DHT11         = DHT11, // DHT 11
    DHTTYPE_DHT22         = DHT22, // DHT 22, AM2302, AM2321
    DHTTYPE_DHT21         = DHT21 // DHT 21, AM2301
} DHTTYPE;

DHT dht(pinDHT, DHTTYPE_DHT11);
float temp, humi;
String strValue;
//********************DHT 

void setup(){
  Serial.begin(9600); 
  setup_dht();
}

void loop(){
  loop_dht();
}

void setup_dht(){
  dht.begin();
}

void loop_dht(){

  temp = dht.readTemperature();
  humi = dht.readHumidity();

  Serial.print("temp:");
  Serial.print(temp);
  Serial.print(" : ");
  Serial.print("humi:");
  Serial.println(humi);

  delay(1000); 
}

