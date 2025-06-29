#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "motor-driver.h"
#include "imu.h"
#include "pindefs.h"


const uint8_t OLED_WIDTH = 128;
const uint8_t OLED_HEIGHT = 64;
const uint8_t OLED_RESET = -1;
const uint8_t OLED_ADDR = 0x3C;
TwoWire* OLED_I2C_INSTANCE = &Wire;


Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);


void printSensorData();   // Output sensor data over Serial


void setup(){

  Serial.begin();
  while(!Serial);
  Serial.println("Init");


  Wire.setSCL(PIN_I2C0_SCL);
  Wire.setSDA(PIN_I2C0_SDA);

  if(!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)){
    // no failure handling
  }

  oled.clearDisplay();
  oled.display();


  initMotorDriver();
  Serial.println(initIMU());

}

void loop(){

  //printSensorData();

}

void printSensorData(){

  IMUData data = getIMUData();

  Serial.print(data.gyroX);
  Serial.print(",");
  Serial.print(data.gyroY);
  Serial.print(",");
  Serial.print(data.gyroZ);
  Serial.print(",");
  Serial.print(data.accelX);
  Serial.print(",");
  Serial.print(data.accelY);
  Serial.print(",");
  Serial.print(data.accelZ);
  Serial.print(",");
  Serial.print(data.mpuTemp);
  Serial.print(",");
  Serial.print(data.bmpPres);
  Serial.print(",");
  Serial.print(data.magX);
  Serial.print(",");
  Serial.print(data.magY);
  Serial.print(",");
  Serial.print(data.magZ);
  
  Serial.println();

}