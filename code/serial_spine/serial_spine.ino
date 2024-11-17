/*
AUTHOR: Jayden Chen
PURPOSE: just a proof of concept

*/

#define ID 1

void sendSignalToBrain(String msg)
{
  Serial.println(msg);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

String msg;
int status = 0;

void loop() {

  String msg = String("<") + String(ID) + String("-") + String(status) + String(">");

  sendSignalToBrain(msg);
  delay(50);

  status ++;
}
