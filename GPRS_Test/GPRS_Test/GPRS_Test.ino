#include <LGPRS.h>
#include <LGPRSClient.h>
#define SITE_URL "www.google.com" 

LGPRSClient globalClient;  // See this support topic from Mediatek - http://labs.mediatek.com/forums/posts/list/75.page

//LGPRSClient client;

void setup() {
  Serial.begin(9600);
  while (!LGPRS.attachGPRS("gprs.swisscom.ch","","")) { //attachGPRS(const char *apn, const char *username, const char *password);
    Serial.println("wait for SIM card ready");
    delay(1000);
  }
  LGPRSClient client;    //Client has to be initiated after GPRS is established with the correct APN settings - see above link
  globalClient = client;  // Again this is a temporary solution described in support forums
  
  Serial.print("Connecting to : " SITE_URL "...");
  if (!globalClient.connect(SITE_URL, 80)) {
    Serial.println("FAIL!");
    return;
  }
  Serial.println("done");
  Serial.print("Sending GET request...");
  globalClient.println("GET / HTTP/1.1");
  globalClient.println("Host: " SITE_URL ":80");
  globalClient.println();
  Serial.println("done");
}

void loop() {
  int v;
  while (globalClient.available()) {
    v = globalClient.read();
    if (v < 0)
      break;
    Serial.write(v);
  }
  delay(500);
}
