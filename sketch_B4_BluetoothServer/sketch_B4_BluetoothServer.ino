#include <LGATTServer.h>

void setup() {
  LGATTServer.begin(2, &myServiceA, &myServiceB);
}

void loop() {
  LGATTServer.handleEvents();
}

class LGATTSample : public LGATTService {
  public:
    virtual LGATTServiceInfo *onLoadService(int32_t index);
};

static LGATTServiceInfo MY_SERVICE_DEFINITION [] = {
  {TYPE_SERVICE, "6e400001-b5a3-f393-e0a9-e50e24dcca9e", TRUE, 0, 0, 0},
  {TYPE_CHARACTERISTIC, "6e400002-b5a3-f393-e0a9-e50e24dcca9e", FALSE, VM_GATT_CHAR_PROP_WRITE, VM_GATT_PERM_WRITE, 0},
  {TYPE_CHARACTERISTIC, "6e400003-b5a3-f393-e0a9-e50e24dcca9e", FALSE, VM_GATT_CHAR_PROP_NOTIFY | VM_GATT_CHAR_PROP_INDICATE, VM_GATT_PERM_READ, 0},
  {TYPE_DESCRIPTOR, "00002902-0000-1000-8000-00805f9b34fb", FALSE, VM_GATT_CHAR_PROP_NOTIFY, VM_GATT_PERM_READ | VM_GATT_PERM_WRITE, 0},
  {TYPE_END, 0, 0, 0, 0, 0}
};
LGATTServiceInfo* LGATTSample::onLoadService(int32_t index) {
  return MY_SERVICE_DEFINITION;
}

boolean LGATTSample::onRead(LGATTReadRequest &request) {
  LGATTAttributeValue value = {0};
  const char *str = "value string";
  memcpy(value.value, str, strlen(str));
  value.len = strlen(str);
}

boolean LGATTSample::onWrite(LGATTWriteRequest &data) {
  // if need to rsp to central.
  if (data.need_rsp) {
    data.ackOK();
    // Send ACK
  }
  // Update device internal status by the written data according.
  // Here we simply print the length of received data.
  Serial.print("Received data length:");
  Serial.println(data.value.len);
  return true;
}

