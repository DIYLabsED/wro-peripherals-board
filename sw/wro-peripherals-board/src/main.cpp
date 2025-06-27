#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "pindefs.h"

void setup(){

  Wire.setSCL(PIN_I2C0_SCL);
  Wire.setSDA(PIN_I2C0_SDA);

  Serial.begin(115200);
  delay(5000);

  Serial.println("Adafruit MPU6050 test!");

}

void loop(){

}