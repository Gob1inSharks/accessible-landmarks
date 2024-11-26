#include <Wire.h>

#define SLAVES_NUM 2
#define SLAVES_IDS (int[]){9,10}

#define DELAY_TIME 1000

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

int cleanMessageFromSlave(String msg){
  
  //iterate through message and remove all characters except numbers
  String cleanedMsg = "";
  for(char& c : msg) {
    if(isdigit(c)) cleanedMsg += c;
  }

  return cleanedMsg.toInt();
}

void showSlaveSignalInSerial(int id){

  int BYTES_REQUESTED = 8;

  Wire.requestFrom(id, BYTES_REQUESTED);

  while (Wire.available() > 0) { // peripheral may send less than requested
    char c = Wire.read();
    Serial.print(c);
  }

}

void test(){

  Serial.println("----------------------------------------------");

  int piecesInPlace = 0;

  for(int i = 0; i < SLAVES_NUM; i++){

    String msg = recieveSignalFromSlave(i);

    int foo = cleanMessageFromSlave(msg);
    piecesInPlace += foo;

    Serial.print("Slave "); Serial.print(SLAVES_IDS[i]); Serial.print(": ");
    Serial.print(msg);
    Serial.print("Cleaned:"); Serial.print(foo);Serial.print("\n");

    delay(DELAY_TIME);
  }
  //Serial.print("\n");

  Serial.println(piecesInPlace);

  delay(50);

  Serial.println("----------------------------------------------");
}

void loop() {
  
  test();

}
