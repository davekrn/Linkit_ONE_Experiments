/*
 SMS receiver

 This sketch, for the Linkit ONE, waits for a SMS message
 and displays it through the Serial port.

 This example is copied out of the MediaTek Linkit ONE Developer's Guide.

 On the serial monitor you will see the following log:
---
SIM ready for work!
There is new message.
Number:+41791234567   (sender number)
Content:Hello World
---

*/
#include <LGSM.h>
String initializeBuffer;    // This will store what you enter to start the serial port
String message = "Hello World";

void setup() {
  Serial.begin(9600);
  while(Serial.available()== 0 ){}   // This will wait until anything is input by the user
  initializeBuffer = Serial.readString();
  Serial.println(message);

  while(!LSMS.ready()) delay(1000);
  Serial.println("SIM ready for work!");
}

void loop() {
  char buf[20];
  int v; 
  if(LSMS.available()) {
    // Check if there is new SMS 
    Serial.println("There is new message.");
    LSMS.remoteNumber(buf, 20); 
    Serial.print("Number:"); 
    Serial.println(buf);
    Serial.print("Content:"); 
    while(true) {
      v = LSMS.read();
      if(v < 0) 
        break; 
      Serial.print((char)v);
    }
    Serial.println();
    LSMS.flush();
  }
  delay(1000);
}

