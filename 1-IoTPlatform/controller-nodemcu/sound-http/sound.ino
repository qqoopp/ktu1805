//GPIO******************** 
int pinSound = A0;
//********************GPIO 

//Sound******************** 
int sound;
//********************Sound

void setup_sound(){
  
}

void loop_sound(){
  sound = analogRead(A0);
  Serial.println(sound);
}

