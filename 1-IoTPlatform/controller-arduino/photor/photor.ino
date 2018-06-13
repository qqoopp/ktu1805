//GPIO******************** 
int pinlds = A0;
//********************GPIO 

//photorvalue******************** 
int photorvalue;
//********************photorvalue

void setup(){
  Serial.begin(9600);  
  setup_photor(); 
}

void loop(){
  loop_photor();
  delay(1000);
}

void setup_photor(){
  
}

void loop_photor(){
  photorvalue = analogRead(pinlds);
  Serial.println(photorvalue);
}



