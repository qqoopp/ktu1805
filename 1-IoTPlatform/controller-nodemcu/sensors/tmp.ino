//tmpvalue******************** 
int tmpvalue;
//********************tmpvalue

//setup========================
void setup_tmp(){
  
}
//========================setup

//loop========================
void loop_tmp(){
  int tmpvalue = analogRead(pinTmp);
  float v = tmpvalue * 5.0 / 1024.0;
  float temp = 100.0 * v - 50;

  //======================
  // testdata ============
  if (isTest == 1) {
    if (temp == 0){ temp = random(10,40);}
  }
  // testdata ============
  //======================

  //Json data generation ============================
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["measuredt"] = "";       
  root["controller"] = controllerid;        
  root["sensor"] = "TMP";
  root["uptime"] = millis();
  root["ip"] = myIP.toString();
  root["temp"] = temp;
  
  root.printTo(jsonResult);
  root.printTo(Serial);
  Serial.println("");
  //============================Json data generation
  
  //Serial.println(temp);
}
//========================loop



