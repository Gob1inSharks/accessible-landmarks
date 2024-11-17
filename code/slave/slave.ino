#include <Wire.h>

#define SLAVE_ID 9

bool inPlace = false;

void setup() {
  Wire.begin(SLAVE_ID);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

void requestEvent() {
  if (inPlace){
    Wire.write("<1>");
  }else{
    Wire.write("<0>");
  }
}