#include <HardwareSerial.h>
HardwareSerial UWBSerial(1);

void setup() {
  Serial.begin(115200);
  Serial.println("\n= NodeMCU ESP32 DONE =");
  UWBSerial.begin(115200, SERIAL_8N1, 16, 17);

  UWBSerial.println("AT");
  while (!UWBSerial.available()) {
    delay(200);
    Serial.println("= UWB BU01 Detecting =");
    }
  }
 
void loop() {
  if (UWBSerial.available()) {
        Serial.write(UWBSerial.read());
    }
  if (Serial.available()) {
        UWBSerial.write(Serial.read());
    }
}
