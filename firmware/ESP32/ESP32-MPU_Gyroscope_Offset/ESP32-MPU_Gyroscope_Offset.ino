/*
         [ UPDATE ]       [ AUTHOR ]
        =2021.06.26=     =Sean Chang=
*/
#include "MPU9250.h"

float gyroXerror = 0.03;
float gyroYerror = 0.03;
float gyroZerror = 0.00;


// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire, 0x68);
int status;

void setup() {
  Serial.begin(115200);
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
  // setting the accelerometer full scale range to +/-8G
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);
}

void loop() {
  // read the sensor
  IMU.readSensor();

  // display the data

  //Serial.print(IMU.getAccelX_mss(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getAccelY_mss(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getAccelZ_mss(),6);
  //Serial.print("\t");
  Serial.println("");
  Serial.print(IMU.getTemperature_C(), 2);
  Serial.print("°C");

  if (abs(IMU.getGyroX_rads()) > gyroXerror)  {
    Serial.print(" | GyroX: ");
    Serial.print(IMU.getGyroX_rads(), 4);
    Serial.print("\t");
  }
  if (abs(IMU.getGyroY_rads()) > gyroYerror)  {
    Serial.print(" | GyroY: ");
    Serial.print(IMU.getGyroY_rads(), 4);
    Serial.print("\t");
  }
  if (abs(IMU.getGyroZ_rads()) > gyroZerror)  {
    Serial.print(" | GyroZ: ");
    Serial.print(IMU.getGyroZ_rads(), 4);
    Serial.print("\t");
  }
  //Serial.print(IMU.getGyroX_rads(), 4);
  //Serial.print("\t");
  //Serial.print(IMU.getGyroY_rads(), 4);
  //Serial.print("\t");
  //Serial.print(IMU.getGyroZ_rads(), 4);
  //Serial.print("\t");

  //Serial.print(IMU.getMagX_uT(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getMagY_uT(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getMagZ_uT(),6);
  //Serial.print("\t");

  delay(20);
}
