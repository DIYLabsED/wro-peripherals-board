#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "motor-driver.h"
#include "pindefs.h"


const uint8_t OLED_WIDTH = 128;
const uint8_t OLED_HEIGHT = 64;
const uint8_t OLED_RESET = -1;
const uint8_t OLED_ADDR = 0x3C;
TwoWire* OLED_I2C_INSTANCE = &Wire;


Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);


void setup(){

  Wire.setSCL(PIN_WIRE0_SCL);
  Wire.setSDA(PIN_WIRE0_SDA);

  if(!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)){
    // no failure handling
  }

  oled.clearDisplay();
  oled.display();

  initMotorDriver();

}

void loop(){

}