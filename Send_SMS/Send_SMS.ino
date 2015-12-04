/*
 SMS sender

 This sketch, for the Linkit ONE, waits for a SMS message
 and displays it through the Serial port and then confirms
 the receiption by a reply SMS

 On the serial monitor you will see the following log:
---
SIM ready for work!
There is new message.
Number:+41123456789
Content:Hello are you ready?
Message received: Hello are you ready?
---

*/
#include <LGSM.h>
void setup() {
  Serial.begin(9600);
  while(!LSMS.ready()) delay(1000);
  Serial.println("SIM ready for work!");
}

void loop() {
  char buf[20];
  String msg = String("Message received: ");
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
      msg += (char)v;
      Serial.print((char)v);
      
    }
    Serial.println();
    Serial.println(msg);
    LSMS.flush();
    // send confirmation
    LSMS.beginSMS(buf); 
    LSMS.print(msg); 
    LSMS.endSMS();
    LSMS.flush();
  }
  delay(1000);
}

