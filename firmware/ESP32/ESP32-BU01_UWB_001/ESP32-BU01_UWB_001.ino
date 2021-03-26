/*
         [ UPDATE ]       [ AUTHOR ]
        =2021.03.12=     =Sean Chang=
*/
#include <SimpleTimer.h>
#include <HardwareSerial.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

SimpleTimer timer;

HardwareSerial UWBSerial(1);
//========================================//
int timerId;

float x1 = 0.00, y_1 = 0.00,
      x2 = 300.00, y2 = 0.00,
      x3 = 0.00, y3 = 300.00;
float x , y;
String UWB_Data;
String an1, an2, an3;
//========================================//



void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-UWB"); //Bluetooth device name
  Serial.println("\n= NodeMCU ESP32 DONE =");
  UWBSerial.begin(115200, SERIAL_8N1, 16, 17);

  UWBSerial.println("AT");
  while (!UWBSerial.available()) {
    delay(200);
    Serial.println("= UWB BU01 Detecting =");
  }

  timerId = timer.setInterval(1283L, sendDATA);
  timer.disable(timerId);
}

void loop() {
  if (SerialBT.available()) {
    UWBSerial.write(SerialBT.read());
  }
  if (Serial.available()) {
    UWBSerial.write(Serial.read());
  }
  if (UWBSerial.available()) {
    UWB_Data = UWBSerial.readString();
    Serial.print(UWB_Data);
    SerialBT.print(UWB_Data);
  }
  AN_detect();

  float an1_f = an1.toFloat();
  float an2_f = an2.toFloat();
  float an3_f = an3.toFloat();
  an1_f = an1_f * 100;
  an2_f = an2_f * 100;
  an3_f = an3_f * 100;
  an1_f = sqrt(an1_f * an1_f - 100);
  an2_f = sqrt(an2_f * an2_f - 100);
  an3_f = sqrt(an3_f * an3_f - 100);
  float a = (-2 * x1 + 2 * x2);
  float b = (-2 * y_1 + 2 * y2);
  float c = (an1_f * an1_f - an2_f * an2_f - x1 * x1 + x2 * x2 - y_1 * y_1 + y2 * y2);
  float d = (-2 * x2 + 2 * x3);
  float e = (-2 * y2 + 2 * y3);
  float f = (an2_f * an2_f - an3_f * an3_f - x2 * x2 + x3 * x3 - y2 * y2 + y3 * y3);
  x = (c * e - f * b) / (e * a - b * d);
  y = (c * d - a * f) / (b * d - a * e);

  if (timer.isEnabled(timerId)) {
    timer.run();
  }

  UWB_Data = ""; an1 = ""; an2 = ""; an3 = "";
}


void sendDATA () {
  Serial.println("an1=" + an1 + "," + "an2=" + an2 + "," + "an3=" + an3);
  Serial.print("x=");
  Serial.print(x, 2);
  Serial.print(",");
  Serial.print("y=");
  Serial.println(y, 2);

  SerialBT.print("x=");
  SerialBT.print(x, 2);
  SerialBT.print(",");
  SerialBT.print("y=");
  SerialBT.println(y, 2);
}

void AN_detect () {
  if (UWB_Data.substring(0, 3) == "an1") {
    if (UWB_Data.substring(11, 14) == "an2") {
      if (UWB_Data.substring(22, 25) == "an3") {
        an1 = UWB_Data.substring(4, 8);
        an2 = UWB_Data.substring(15, 19);
        an3 = UWB_Data.substring(26, 30);
      } else {
        an1 = UWB_Data.substring(4, 8);
        an2 = UWB_Data.substring(15, 19);
      }
    } else {
      if (UWB_Data.substring(11, 14) == "an3") {
        an1 = UWB_Data.substring(4, 8);
        an3 = UWB_Data.substring(15, 19);
      } else {
        an1 = UWB_Data.substring(4, 8);
      }
    }
    timer.enable(timerId);
  } else if (UWB_Data.substring(0, 3) == "an2") {
    if (UWB_Data.substring(11, 14) == "an3") {
      an2 = UWB_Data.substring(4, 8);
      an3 = UWB_Data.substring(15, 19);
    } else {
      an2 = UWB_Data.substring(4, 8);
    }
    timer.enable(timerId);
  } else if (UWB_Data.substring(0, 3) == "an3") {
    an3 = UWB_Data.substring(4, 8);
    timer.enable(timerId);
  } else {
    timer.disable(timerId);
  }
}
