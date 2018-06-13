
//getStatus=========================
// get senssor status : on/off
//====================================
String getStatus(String sensorname){
  sensorname.toUpperCase();
  for( int i=0; i<10; i++){
      if ( sensors[i] == NULL ) break;
      sensors[i].toUpperCase();
      sensorsstatus[i].toUpperCase();
      if ( sensors[i] == sensorname ) {
        return sensorsstatus[i];
        break;
      }
   }
   return "OFF";
}
//=========================getStatus


//setStatus=========================
// get senssor status : on/off
//====================================
void setStatus(String sensorname, String statusvalue){
  sensorname.toUpperCase();
  statusvalue.toUpperCase();
  for( int i=0; i<10; i++){
      if ( sensors[i] == NULL ) break;
      sensors[i].toUpperCase();
      if ( sensors[i] == sensorname ) {
        sensorsstatus[i] = statusvalue ;
        return;
      }
   }
}
//=========================setStatus


//isFloat=========================
//check whether tString is numeric or not ( to filter noise data  )
//====================================
boolean isFloat(String tString) {
  String tBuf;
  boolean decPt = false;
  
  if(tString.charAt(0) == '+' || tString.charAt(0) == '-') tBuf = &tString[1];
  else tBuf = tString;  

  for(int x=0;x<tBuf.length();x++)
  {
    if(tBuf.charAt(x) == '.') {
      if(decPt) return false;
      else decPt = true;  
    }    
    else if(tBuf.charAt(x) < '0' || tBuf.charAt(x) > '9') return false;
  }
  return true;
}
//=========================isFloat

