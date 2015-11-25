#include <LBT.h>
#include <LBTServer.h>
void setup() {
  Serial.begin(9600);
  if (!LBTServer.begin((uint8_t*)"My_BTServer"))
  {
    Serial.println("Fail to start BT.");
    return;
  }
  Serial.println("BT server is started.");
}
void loop() {
  uint8_t buf[64];
  int bytesRead;
  if (LBTServer.connected()) {
    // echo back all received data
    while (true)
    {
      bytesRead = LBTServer.readBytes(buf, 64);
      if (!bytesRead)
        break;
      Serial.write(buf, bytesRead);
      LBTServer.write(buf, bytesRead);
    }
    delay(100);
  }
  else
  {
    LBTServer.accept(5);
  }
}
