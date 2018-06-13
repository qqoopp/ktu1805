//GPIO******************** 
int pintrig = 3;
int pinecho = 4;
//********************GPIO 

//usonicvalue******************** 
float usonicvalue;
//********************usonicvalue

void setup(){
  Serial.begin(9600);  
  setup_usonic(); 
}

void loop(){
  loop_usonic();
  delay(1000);
}

void setup_usonic(){
  pinMode(pintrig, OUTPUT); // sender
  pinMode(pinecho, INPUT); // receiver
}

void loop_usonic(){
    digitalWrite(pintrig, LOW); delayMicroseconds(2);  // initialize to set to high
    digitalWrite(pintrig, HIGH); delayMicroseconds(10); // sending for 10 microsec during 10 microsec it busrst signal 8times 
    digitalWrite(pintrig, LOW);  // closing
    
    float duration = pulseIn(pinecho, HIGH);
    usonicvalue = duration * 0.034 / 2;  // 340m/s = 34000cm/s = 34000/1000000 cm/microsec = 0.034 cm/microsec
       
  Serial.println(usonicvalue);
}





