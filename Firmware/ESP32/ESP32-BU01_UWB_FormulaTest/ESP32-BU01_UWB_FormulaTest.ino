/*
         [ UPDATE ]       [ AUTHOR ]
        =2021.02.26=     =Sean Chang=
*/

float x1 = 0.00, y_1 = 0.00,
      x2 = 10.00, y2 = 0.00,
      x3 = 0.00, y3 = 10.00;

float r1 = 13.2, r2 = 6.1, r3 = 12.4;
float x , y;

void setup() {

  Serial.begin(115200);

  //(x-x1)*(x-x1)+(y-y1)*(y-y1)=r1*r1
  //(x-x2)*(x-x2)+(y-y2)*(y-y2)=r2*r2
  //(x-x3)*(x-x3)+(y-y3)*(y-y3)=r3*r3
  /*
     A= -2*x1 + 2*x2
     B= -2*y1 + 2*y2
     C= r1*r1 - r2*r2 - x1*x1 + x2*x2 - y1*y1 + y2*y2
     D= -2*x2 + 2*x3
     E= -2*y2 + 2*y3
     F= r2*r2 - r3*r3 - x2*x2 + x3*x3 - y2*y2 + y3*y3
  */

  float a = (-2 * x1 + 2 * x2);
  float b = (-2 * y_1 + 2 * y2);
  float c = (r1 * r1 - r2 * r2 - x1 * x1 + x2 * x2 - y_1 * y_1 + y2 * y2);
  float d = (-2 * x2 + 2 * x3);
  float e = (-2 * y2 + 2 * y3);
  float f = (r2 * r2 - r3 * r3 - x2 * x2 + x3 * x3 - y2 * y2 + y3 * y3);

  //x = ((r1 * r1 - r2 * r2 - x1 * x1 + x2 * x2 - y1 * y1 + y2 * y2) * (-2 * y2 + 2 * y3) - (r2 * r2 - r3 * r3 - x2 * x2 + x3 * x3 - y2 * y2 + y3 * y3) * (-2 * y1 + 2 * y2)) / ((-2 * y2 + 2 * y3) * (-2 * x1 + 2 * x2) - (-2 * y1 + 2 * y2) * (-2 * x2 + 2 * x3));
  //y = ((r1 * r1 - r2 * r2 - x1 * x1 + x2 * x2 - y1 * y1 + y2 * y2) * (-2 * x2 + 2 * x3) - (-2 * x1 + 2 * x2) * (r2 * r2 - r3 * r3 - x2 * x2 + x3 * x3 - y2 * y2 + y3 * y3)) / ((-2 * y1 + 2 * y2) * (-2 * x2 + 2 * x3) - (-2 * x1 + 2 * x2) * (-2 * y2 + 2 * y3));

  x = (c * e - f * b) / (e * a - b * d);
  y = (c * d - a * f) / (b * d - a * e);
}

void loop() {
  Serial.print("x = ");
  Serial.println(x, 4);
  Serial.print("y = ");
  Serial.println(y, 4);

  delay(1000);
}
