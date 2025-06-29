#include "imu.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_HMC5883_U.h>
#include <Wire.h>


#define DEBUG_IMU_SERIAL    // Prints debug messages to serial when defined


Adafruit_MPU6050 mpu;
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
Adafruit_HMC5883_Unified hmc = Adafruit_HMC5883_Unified(12345);

bool initIMU(){

  return initMPU() && initBMP() && initHMC();

}

bool initMPU(){

  if(!mpu.begin()){

    #ifdef DEBUG_IMU_SERIAL
      Serial.println("MPU6050 initialisation failed");
    #endif

    return false;

  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  #ifdef DEBUG_IMU_SERIAL
    Serial.println("MPU6050 initialised!");
  #endif

  return true;

}

bool initBMP(){

  if(!bmp.begin()){

    #ifdef DEBUG_IMU_SERIAL
      Serial.println("BMP085 initialisation failed");
    #endif

    return false;

  }

  #ifdef DEBUG_IMU_SERIAL
    Serial.println("BMP075 initialised!");
  #endif

  return true;  

}

bool initHMC(){

  if(!hmc.begin()){

    #ifdef DEBUG_IMU_SERIAL
      Serial.println("HMC5883L initialisation failed");
    #endif

    return false;

  }

  #ifdef DEBUG_IMU_SERIAL

    Serial.println("HMC5883L initialised!");

    sensor_t magSensor;
    hmc.getSensor(&magSensor);

    Serial.print("magSensor name:");
    Serial.println(magSensor.name);
    Serial.print("magSensor version:");
    Serial.println(magSensor.version);
    Serial.print("magSensor ID:");
    Serial.println(magSensor.sensor_id);
    Serial.print("magSensor max value:");
    Serial.println(magSensor.max_value);
    Serial.print("magSensor min value:");
    Serial.println(magSensor.min_value);
    Serial.print("magSensor resolution:");
    Serial.println(magSensor.resolution);

  #endif

  return true;  

}

IMUData getIMUData(){

  IMUData data;

  sensors_event_t mpuA, mpuG, mpuT;
  sensors_event_t bmpP;
  sensors_event_t hmcM;

  mpu.getEvent(&mpuA, &mpuG, &mpuT);  
  bmp.getEvent(&bmpP);
  hmc.getEvent(&hmcM);

  data.accelX  = mpuA.acceleration.x;
  data.accelY  = mpuA.acceleration.y;
  data.accelZ  = mpuA.acceleration.z;
  data.gyroX   = mpuG.gyro.x;
  data.gyroY   = mpuG.gyro.y;
  data.gyroZ   = mpuG.gyro.z;
  data.mpuTemp = mpuT.temperature;
  data.bmpPres = bmpP.pressure;
  data.magX    = hmcM.magnetic.x;
  data.magY    = hmcM.magnetic.y;
  data.magZ    = hmcM.magnetic.z;

  return data;

}

