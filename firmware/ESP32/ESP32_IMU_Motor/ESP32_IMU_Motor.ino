/*
         [ UPDATE ]       [ AUTHOR ]
        =2021.06.26=     =Sean Chang=
*/
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_MPU6050.h>
#include <MPU9250.h>
#include <Adafruit_Sensor.h>
#include <Arduino_JSON.h>
#include "SPIFFS.h"

//============= MOTOR CONTROL ============//
//ENA
const int IN1 = 27;
const int IN2 = 26;
const int ENA = 14;
//ENB
const int IN3 = 25;
const int IN4 = 33;
const int ENB = 32;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel_A = 1;
const int pwmChannel_B = 2;
const int resolution = 8;
int dutyCycle = 180;
//========================================//

MPU9250 IMU(Wire, 0x68);
int status;

const char* ssid = "";
const char* password = "";

AsyncWebServer server(80);
AsyncEventSource events("/events");
JSONVar readings;

// Timer variables
unsigned long lastTime = 0;
unsigned long lastTimeAcc = 0;
unsigned long gyroDelay = 10;
unsigned long accelerometerDelay = 200;

float gyroX, gyroY, gyroZ;
float accX, accY, accZ;

//Gyroscope sensor deviation
float gyroXerror = 0.03;
float range = 0.05;

void initSPIFFS() {
  if (!SPIFFS.begin()) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
}

String getGyroReadings() {
  float gyroX_temp = IMU.getGyroX_rads();
  if (abs(gyroX_temp) > gyroXerror)  {
    gyroX += gyroX_temp * 0.05 / 3.95;
  }

  readings["gyroX"] = String("0.00");
  readings["gyroY"] = String("0.40");
  readings["gyroZ"] = String(gyroX);

  String jsonString = JSON.stringify(readings);
  return jsonString;
}

String getAccReadings() {
  // Get current acceleration values
  accX = IMU.getAccelX_mss();
  accY = IMU.getAccelY_mss();
  accZ = IMU.getAccelZ_mss();
  readings["accX"] = String(accX);
  readings["accY"] = String(accY);
  readings["accZ"] = String(accZ);
  String accString = JSON.stringify (readings);
  return accString;
}


void setup() {
  Serial.begin(115200);
  initWiFi();
  initSPIFFS();

  while (!Serial) {}

  // start communication with IMU
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while (1) {}
  }

  // Handle Web Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.serveStatic("/", SPIFFS, "/");

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest * request) {
    gyroX = 0;
    gyroY = 0;
    gyroZ = 0;
    request->send(200, "text/plain", "OK");
  });

  server.on("/resetX", HTTP_GET, [](AsyncWebServerRequest * request) {
    gyroX = 0;
    request->send(200, "text/plain", "OK");
  });

  server.on("/resetY", HTTP_GET, [](AsyncWebServerRequest * request) {
    gyroY = 0;
    request->send(200, "text/plain", "OK");
  });

  server.on("/resetZ", HTTP_GET, [](AsyncWebServerRequest * request) {
    gyroZ = 0;
    request->send(200, "text/plain", "OK");
  });

  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient * client) {
    if (client->lastId()) {
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);

  server.begin();

  //============= MOTOR CONTROL ============//
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(pwmChannel_A, freq, resolution);
  ledcSetup(pwmChannel_B, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ENA, pwmChannel_A);
  ledcAttachPin(ENB, pwmChannel_B);
  //========================================//
}

void loop() {
  IMU.readSensor();
  if ((millis() - lastTime) > gyroDelay) {
    events.send(getGyroReadings().c_str(), "gyro_readings", millis());
    lastTime = millis();
  }
  if ((millis() - lastTimeAcc) > accelerometerDelay) {
    events.send(getAccReadings().c_str(), "accelerometer_readings", millis());
    lastTimeAcc = millis();
  }
  if (gyroX < range && gyroX > -range) {
    ledcWrite(pwmChannel_A, 180);
    ledcWrite(pwmChannel_B, 180);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  if (gyroX > range) {
    ledcWrite(pwmChannel_A, 180);
    ledcWrite(pwmChannel_B, 180);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  if (gyroX < -range) {
    ledcWrite(pwmChannel_A, 180);
    ledcWrite(pwmChannel_B, 180);

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}
