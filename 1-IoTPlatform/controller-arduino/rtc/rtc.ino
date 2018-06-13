#include <DS1302.h>

//GPIO******************** 
int pinrst = 2;
int pindat = 3;  //SDA
int pinclk = 4;  //SCL
// Init the DS1302
DS1302 rtc(2, 3, 4);
// Init a Time-data structure
Time t;
//********************GPIO 

//usonicvalue******************** 
String curdatetime;
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
  // Set the clock to run-mode, and disable the write protection
  //rtc.halt(false);
  //rtc.writeProtect(false);
  //rtc.setDOW(SUNDAY);    // Set Day-of-Week to FRIDAY
  //rtc.setTime(21, 51, 5);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(d,m, y);   // Set the date to August 6th, 2010
}

void loop_usonic(){
  // Get data from the DS1302
  t = rtc.getTime();
  curdatetime = "";
  curdatetime += String(t.year);
  /*
  curdatetime += ("0" + String(t.mon)).substring(1,2);
  curdatetime += ("0" + String(t.date)).substring(1,2);
  curdatetime += ("0" + String(t.hour)).substring(1,2);
  curdatetime += ("0" + String(t.min)).substring(1,2);
  curdatetime += ("0" + String(t.sec)).substring(1,2);
  */
  Serial.println(curdatetime);
  Serial.println(rtc.getDateStr());
  Serial.println(rtc.getTimeStr());
}





