#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include "motor-driver.h"
#include "imu.h"
#include "pindefs.h"


const uint8_t OLED_WIDTH = 128;
const uint8_t OLED_HEIGHT = 64;
const uint8_t OLED_RESET = -1;
const uint8_t OLED_ADDR = 0x3C;
TwoWire* OLED_I2C_INSTANCE = &Wire;


int steeringServoPosition;  // 0 <-> 180
int throttle;               // -1024 <-> 1024


Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);
Servo steeringServo;


void printSensorData();   // Output sensor data over Serial
void getInputsFromSerial();
void getInputsFromRadio();
void printInputsToOLED();


void setup(){

  Serial.begin();
  //while(!Serial);
  Serial.println("Init");

  steeringServo.attach(4);

  Wire.setSCL(PIN_I2C0_SCL);
  Wire.setSDA(PIN_I2C0_SDA);

  if(!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)){
    // no failure handling
  }

  initMotorDriver();
  armMotorDriver();
  initIMU();

  pinMode(PIN_RX_STEERING, INPUT);
  pinMode(PIN_RX_THROTTLE, INPUT);

}

void loop(){

  //printSensorData();
  getInputsFromSerial();
  printInputsToOLED();

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

void getInputsFromSerial(){

  if(Serial.available()){

    String command = Serial.readString();

    int commaIndex = command.indexOf(",");
    throttle = command.substring(0, commaIndex).toInt();
    steeringServoPosition = command.substring(commaIndex + 1).toInt();
    
    steeringServo.write(steeringServoPosition);
    driveMotorA(abs(throttle), (throttle > 0));
     
    Serial.println(String(throttle) + ", " + String(steeringServoPosition));  
     
  }

}

void getInputsFromRadio(){

  steeringServoPosition = constrain(map(pulseIn(PIN_RX_STEERING, HIGH), 1000, 2000, 0, 180), 0, 180);
  throttle = constrain(map(pulseIn(PIN_RX_THROTTLE, HIGH), 1000, 2000, -100, 100), -100, 100);

  steeringServo.write((steeringServoPosition));
  driveMotorA(abs(throttle), (throttle > 0));  

}

void printInputsToOLED(){

  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.setTextSize(2);
  oled.setTextColor(SSD1306_WHITE);
  oled.println("THR " + String(throttle));
  oled.println("STR " + String(steeringServoPosition));
  oled.display();

}