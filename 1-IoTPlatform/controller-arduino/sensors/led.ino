//setup========================
void setup_led(){
  pinMode(pinLED, OUTPUT); // on/off
}
//========================setup

//loop========================
void loop_led(){
  if ( getStatus("LED") == "ON"){  
    digitalWrite(pinLED, HIGH);    
  }
  else {
    digitalWrite(pinLED, LOW);    
  }

   //Json data generation ============================
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["measuredt"] = "";       
  root["controller"] = controllerid;        
  root["sensor"] = "LED";
  root["uptime"] = millis();

  if ( getStatus("LED") == "ON"){  
    root["onoff"] = "ON";
  }
  else {
    root["onoff"] = "OFF";
  }
  
  //root.printTo(Serial);
  //Serial.println("");
  //============================Json data generation
}
//========================loop




