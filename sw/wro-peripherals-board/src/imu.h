#include <Arduino.h>


struct IMUData{

  float gyroX, gyroY, gyroZ;
  float accelX, accelY, accelZ;
  float mpuTemp;

  float bmpPres;

  float magX, magY, magZ;

};


bool initIMU();             // initialise sensors, returns true if all sensors initialise, else returns false
bool initMPU();             // initialise MPU6050
bool initBMP();             // initialise BMP085
bool initHMC();             // initialise HMC5883L
IMUData getIMUData();       // main func to get data from IMU
void printMPU6050Data();    // internal func to get and print MPU data