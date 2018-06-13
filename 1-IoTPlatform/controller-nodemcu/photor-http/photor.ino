//GPIO******************** 
int pinlds = A0;
//********************GPIO 

void setup_photor(){
  
}

void loop_photor(){
  photorvalue = analogRead(pinlds);
  Serial.println(photorvalue);
}



