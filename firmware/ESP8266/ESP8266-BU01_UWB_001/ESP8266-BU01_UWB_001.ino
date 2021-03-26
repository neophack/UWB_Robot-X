/*
         [ UPDATE ]       [ AUTHOR ]
        =2021.02.27=     =Sean Chang=
*/
#include <SoftwareSerial.h>
#include <SimpleTimer.h>

SoftwareSerial UWBSerial(12, 14);  //(RX, TX) ESP8266
SimpleTimer timer;

//int timerId;
//========================================//
String UWB_Data;
String an1, an2, an3;
//========================================//



void setup() {
  Serial.begin(115200);
  Serial.println("\n= NodeMCU ESP8266 DONE =");
  UWBSerial.begin(115200);

  UWBSerial.println("AT");
  while (!UWBSerial.available()) {
    delay(200);
    Serial.println("= UWB BU01 Detecting =");
  }

  //timerId = timer.setInterval(1283L, sendDATA);
  //timer.disable(timerId);
}

void loop() {

  if (Serial.available()) {
    UWBSerial.write(Serial.read());
  }
  if (UWBSerial.available()) {
    UWB_Data = UWBSerial.readString();
    Serial.print(UWB_Data);
  }
  AN_detect();
  //if (timer.isEnabled(timerId)) {
  //  timer.run();
  //}
  UWB_Data = ""; an1 = ""; an2 = ""; an3 = "";
}


//void sendDATA () {
//  Serial.println(an1 + " - " + an2 + " - " + an3);
//}

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
    //timer.enable(timerId);
  } else if (UWB_Data.substring(0, 3) == "an2") {
    if (UWB_Data.substring(11, 14) == "an3") {
      an2 = UWB_Data.substring(4, 8);
      an3 = UWB_Data.substring(15, 19);
    } else {
      an2 = UWB_Data.substring(4, 8);
    }
    //timer.enable(timerId);
  } else if (UWB_Data.substring(0, 3) == "an3") {
    an3 = UWB_Data.substring(4, 8);
    //timer.enable(timerId);
  } else {
    //timer.disable(timerId);
  }
}
