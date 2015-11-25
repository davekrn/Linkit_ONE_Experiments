#include <LBT.h>
#include <LBTServer.h>

void setup()
{
  Serial.begin(9600);
  bool success = LBTServer.begin();
  if ( !success )
  {
    Serial.println("Cannot begin Bluetooth Server successfully");
    // don't do anything else
    while (true);
  }
  else
  {
    Serial.println("Bluetooth Server begin successfully");
  }

  // waiting for Spp Client to connect
  bool connected = LBTServer.accept(120);

  if ( !connected )
  {
    Serial.println("No connection request yet");
    // don't do anything else
    while (true);
  }
  else
  {
    Serial.println("Connected");
  }
}

void loop()
{

}
