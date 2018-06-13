//GPIO******************** 
int pintmp = A0;
//********************GPIO 

//tmpvalue******************** 
int tmpvalue;
//********************tmpvalue

void setup(){
  Serial.begin(9600);  
  setup_tmp(); 
}

void loop(){
  loop_tmp();
  delay(1000);
}

void setup_tmp(){
  
}

void loop_tmp(){
  int tmpvalue = analogRead(pintmp);
  float v = tmpvalue * 5.0 / 1024.0;
  float temp = 100.0 * v - 50;
  Serial.println(temp);
}



