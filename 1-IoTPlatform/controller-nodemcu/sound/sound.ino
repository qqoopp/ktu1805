//GPIO******************** 
int pinSound = A0;
//********************GPIO 

//Sound******************** 
int sound;
//********************Sound

void setup(){
  Serial.begin(9600);  
  setup_sound(); 
}

void loop(){
  loop_sound();
  delay(1000);
}

void setup_sound(){
  
}

void loop_sound(){
  sound = analogRead(A0);
  Serial.println(sound);
}

