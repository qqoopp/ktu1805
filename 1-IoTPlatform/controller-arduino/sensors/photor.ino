//GPIO******************** 
int pinlds = A0;
//********************GPIO 

//photorvalue******************** 
int photorvalue;
//********************photorvalue

//setup========================
void setup_photor(){
  
}
//========================setup

//loop========================
void loop_photor(){
  photorvalue = analogRead(pinPhotor);

  //======================
  // testdata ============
  if (isTest == 1) {
    if (photorvalue == 0){ photorvalue = random(0,1023);}
  }
  // testdata ============
  //======================

  //Json data generation ============================
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["measuredt"] = "";       
  root["controller"] = controllerid;        
  root["sensor"] = "PHOTO";
  root["uptime"] = millis();
  root["light"] = photorvalue;
  
  //root.printTo(jsonDHT);
  root.printTo(Serial);
  Serial.println("");
  //============================Json data generation
  
  //Serial.println(photorvalue);
}
//========================loop


