#include <Wire.h>

#define SLAVES_NUM 2
#define SLAVES_IDS (int[]){9,10}

#define DELAY_TIME 100

void setup() {
  
  Wire.begin();
  Serial.begin(9600);

}

String recieveSignalFromSlave(int id){

  int BYTES_REQUESTED = 8;

  Wire.requestFrom(id, BYTES_REQUESTED);

  String msg = "";
  while (Wire.available() > 0) { // peripheral may send less than requested
    char c = Wire.read();
    msg += c;
  }
  
  return msg;
}

void showSlaveSignalInSerial(int id){

  int BYTES_REQUESTED = 8;

  Wire.requestFrom(id, BYTES_REQUESTED);

  while (Wire.available() > 0) { // peripheral may send less than requested
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.print("\n");

}

void loop() {
  
  for(int i = 0; i < SLAVES_NUM; i++){
    Serial.print("Slave "); Serial.print(SLAVES_IDS[i]); Serial.print(": ");
    showSlaveSignalInSerial(SLAVES_IDS[i]);
    delay(DELAY_TIME);
  }
}
