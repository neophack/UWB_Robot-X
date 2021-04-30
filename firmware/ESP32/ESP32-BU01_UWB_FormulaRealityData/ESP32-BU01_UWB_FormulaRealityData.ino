/*
         [ UPDATE ]       [ AUTHOR ]
        =2021.04.30=     =Sean Chang=
*/

//========================================//
float x1 = 0.00, y_1 = 0.00,
      x2 = 300.00, y2 = 0.00,
      x3 = 0.00, y3 = 300.00;
float x = 0.00 , y = 0.00;
float delta = 90; //CM
String  an1 = "1.68",
        an2 = "2.41",
        an3 = "2.41";
//========================================//


void setup() {
  Serial.begin(115200);
  Serial.println("\n= NodeMCU ESP32 DONE =\n");
}

void loop() {
  Serial.println("= Please enter the Data =");
  Serial.print(" an1:");
  while (an1 == "") {
    an1 = Serial.readString();
  }
  Serial.print(an1);
  Serial.print("\n an2:");
  while (an2 == "") {
    an2 = Serial.readString();
  }
  Serial.print(an2);
  Serial.print("\n an3:");
  while (an3 == "") {
    an3 = Serial.readString();
  }
  Serial.print(an3);

  float an1_f = an1.toFloat();
  float an2_f = an2.toFloat();
  float an3_f = an3.toFloat();
  an1_f = an1_f * 100;
  an2_f = an2_f * 100;
  an3_f = an3_f * 100;
  an1_f = sqrt(an1_f * an1_f - delta * delta);
  an2_f = sqrt(an2_f * an2_f - delta * delta);
  an3_f = sqrt(an3_f * an3_f - delta * delta);
  float a = (-2 * x1 + 2 * x2);
  float b = (-2 * y_1 + 2 * y2);
  float c = (an1_f * an1_f - an2_f * an2_f - x1 * x1 + x2 * x2 - y_1 * y_1 + y2 * y2);
  float d = (-2 * x2 + 2 * x3);
  float e = (-2 * y2 + 2 * y3);
  float f = (an2_f * an2_f - an3_f * an3_f - x2 * x2 + x3 * x3 - y2 * y2 + y3 * y3);
  x = (c * e - f * b) / (e * a - b * d);
  y = (c * d - a * f) / (b * d - a * e);

  Serial.print("\n[ x=");
  Serial.print(x);
  Serial.print(" | y=");
  Serial.print(y);
  Serial.print(" ]\n\n\n");

  an1 = ""; an2 = ""; an3 = "";
}
