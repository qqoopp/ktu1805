int data[3];

//arduino
int pin1 = A0;
int pin2 = D1;
int pin3 = D2;

void setup(){
  Serial.begin(9600);
}

void loop(){
  while(1){
    data[0] = analogRead(pin1);
    data[1] = analogRead(pin2);
    data[2] = analogRead(pin3);
    Serial.print("NodeMCU:");
    Serial.print(data[0]);
    Serial.print(":");
    Serial.print(data[1]);
    Serial.print(":");
    Serial.print(data[2]);
    Serial.println();
    delay(1000);
  }
}

