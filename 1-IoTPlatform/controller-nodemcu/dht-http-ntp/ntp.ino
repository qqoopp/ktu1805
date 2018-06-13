#include <WiFiUdp.h>

//NTP******************** 
unsigned int localPort = 2390; // local port to listen for UDP packets
const char* ntpServerName = "kr.pool.ntp.org"; // ===== to your region npt server 
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
#define LEAP_YEAR(_year) ((_year%4)==0)
static  byte monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};
float utcoffset = 9; // UTC+9 // ===== change to your region time zone 
WiFiUDP udp;
IPAddress timeServerIP; // time.nist.gov NTP server address
//********************NTP

void setup_ntp(){
  udp.begin(localPort);
}

void loop_ntp(){

  //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP); 

  Serial.print(timeServerIP);

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  // wait to see if a reply is available
  //delay(100);
  
  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("no packet yet");
  }
  else {
    
    //Serial.print("packet received, length=");
    //Serial.println(cb);
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    unsigned long secsSince1900 = ( highWord << 16 | lowWord ) + 3600 * utcoffset; //32400; //UTC+9 : 60*60*9 
    
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears; //epoch = present - 1970

  int year;
  byte month;
  byte monthLength;
  unsigned long tempepoch;
  year = 1970;
  unsigned long days = 0;

  tempepoch = epoch;
  tempepoch/=60; // now it is minutes
  tempepoch/=60; // now it is hours
  tempepoch/=24; // now it is days
  
  while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= tempepoch) {
    year++;
  }
  
  days -= LEAP_YEAR(year) ? 366 : 365;
  tempepoch -= days; // now it is days in this year, starting at 0
  days=0;
  month=0;
  monthLength=0;
  
  for (month=0; month<12; month++) {
    if (month==1) { // february
      if (LEAP_YEAR(year)) {
        monthLength=29;
      } else {
        monthLength=28;
      }
    } else {
      monthLength = monthDays[month];
    }
    
    if (tempepoch>=monthLength) {
      tempepoch-=monthLength;
    } else {
        break;
    }
  }
  month+=1; // jan is month 1
  days=tempepoch+1;  // day of month

  hm = String(year);
  if ( month < 10 ) {hm += "0";};
  hm += String(month);
  if ( days < 10 ) {hm += "0";};
  hm += String(days);
  hm += String((epoch  % 86400L) / 3600);
  if ( ((epoch % 3600) / 60) < 10 ) {hm += "0";};
  hm += String((epoch  % 3600) / 60); // minute (3600 equals secs per minute)
  if ( (epoch % 60) < 10 ) {hm += "0";};
  hm += String(epoch % 60);
  
  //Serial.print(year); //YYYY
  //if ( month < 10 ) { Serial.print('0');}
  //Serial.print(month); //MM
  //if ( days < 10 ) { Serial.print('0');}
  //Serial.print(days); //DD
  //Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
   
  //if ( ((epoch % 3600) / 60) < 10 ) {Serial.print('0');}
  //Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
  //if ( (epoch % 60) < 10 ) {Serial.print('0');}
  //Serial.println(epoch % 60); // print the second
  }
  
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  //Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}


