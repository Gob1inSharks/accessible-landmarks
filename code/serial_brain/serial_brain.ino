/*
AUTHOR: Jayden Chen https://github.com/Gob1inSharks
PURPOSE: proof of concept
*/

#define numSpine 4
#define numChars 32

char spineStatus[numSpine];
/*
each spine has an id as a number char
each spine has a status:
  0 - 
  1 - 
  2 - 
  3 - 
*/

String recvSpines() {

  bool newData = false;
  char receivedChars[numChars];
  static bool recvInProgress = false;
  static int ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
 
  while (Serial.available() > 0 && newData == false) {

    rc = Serial.read();

    if (recvInProgress){

      if (rc != endMarker){
        
        receivedChars[ndx] = rc;
        ndx++;

        if (ndx >= numChars) ndx = numChars - 1; //limit the number of char
                                                 //to save space

      } else {

        receivedChars[ndx] = '\0'; //terminate the string & reset
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    
    }else if (rc == startMarker) {
      recvInProgress = true;
    }
  }

  return String(receivedChars);
}

void sendToLaptop(String msg) {
  Serial.print("<Received: ");
  Serial.print(msg);
  Serial.println(">");
}

void setup() {
  Serial.begin(9600);
  Serial.println("<Brain Ready>");
}

String msg;

void loop() {
  msg = String(recvSpines());
  delay(30);
  sendToLaptop(msg);
}
