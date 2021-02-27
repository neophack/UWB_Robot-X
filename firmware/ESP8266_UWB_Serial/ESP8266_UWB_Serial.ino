#include <SoftwareSerial.h>

SoftwareSerial UWB(12, 14);  //(RX, TX) ESP8266

void setup() {
    Serial.begin(115200);
    Serial.println("\nNodeMCU ESP8266...OK");
    UWB.begin(115200);
    Serial.println("\nUWB BU01...OK");
}

void loop() {
    if (UWB.available()) {
        Serial.write(UWB.read());
    }
    if (Serial.available()) {
        UWB.write(Serial.read());
    }
}
