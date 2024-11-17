#include <Wire.h>

#define MASTER_ID 8
#define SLAVES_ID 8

void setup() {
  Wire.begin();
  Serial.begin(9600);  // start serial for output
}

String getRequestFromSlave(int id){

  String msg = "";
  Wire.requestFrom(id, 8);

  while (Wire.available() > 0) { // peripheral may send less than requested
    char c = Wire.read();
    msg += c;
    Serial.print(c);
  }
  Serial.print("\n");

  return msg;
}

String cleanSlaveRequest(String msg){

  char startMarker = '<';
  char endMarker = '>';

  String cleanedMsg = "";

  bool flag = false;
  for(char& c : msg) {

    if(c == startMarker) flag = true;
    if(c == endMarker) flag = false;

    if(flag){
      cleanedMsg += c;
    }
  }

  return cleanedMsg;
}

int count = 0;
void loop() {

  count++; Serial.print(count); Serial.print(": ");
  String msg = getRequestFromSlave(SLAVES_ID);
  String cleanedMsg = cleanSlaveRequest(msg);
  Serial.println(msg);
  Serial.println(cleanedMsg);
  Serial.println("----------------------------------------------------");

  if(count == 10000) count = 0;

  delay(100);
}
