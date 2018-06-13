//usonicvalue******************** 
float usonicvalue;
//********************usonicvalue

//setup========================
void setup_usonic(){
  pinMode(pinTrig, OUTPUT); // sender
  pinMode(pinEcho, INPUT); // receiver
}
//========================setup

//loop========================
void loop_usonic(){
    digitalWrite(pinTrig, LOW); delayMicroseconds(2);  // initialize to set to high
    digitalWrite(pinTrig, HIGH); delayMicroseconds(10); // sending for 10 microsec during 10 microsec it busrst signal 8times 
    digitalWrite(pinTrig, LOW);  // closing
    
    float duration = pulseIn(pinEcho, HIGH);
    usonicvalue = duration * 0.034 / 2;  // 340m/s = 34000cm/s = 34000/1000000 cm/microsec = 0.034 cm/microsec

    
  //======================
  // testdata ============
  if (isTest == 1) {
    if (usonicvalue == 0){ usonicvalue = random(10,40);}
  }
  // testdata ============
  //======================

  //Json data generation ============================
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["measuredt"] = "";       
  root["controller"] = controllerid;        
  root["sensor"] = "USONIC";
  root["uptime"] = millis();
  root["ip"] = myIP.toString();
  root["dist"] = usonicvalue;
  
  root.printTo(jsonResult);
  root.printTo(Serial);
  Serial.println("");
  //============================Json data generation
 
  //Serial.println(usonicvalue);
}
//========================loop




