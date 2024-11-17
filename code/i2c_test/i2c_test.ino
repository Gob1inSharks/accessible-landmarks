#include <Wire.h>

#define ID 8

void setup() {
  Serial.begin(19200);
  Wire.begin(ID);
}

void loop() {
  test();
  delay(100);
}

void test() {
  Wire.write("lunch");
  Serial.println("lunch");
}
