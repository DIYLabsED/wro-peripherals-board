#include "motor-driver.h"

void initMotorDriver(){

  pinMode(PIN_TB6612_PWMA, OUTPUT);
  pinMode(PIN_TB6612_PWMB, OUTPUT);

  pinMode(PIN_TB6612_AIN1, OUTPUT);
  pinMode(PIN_TB6612_AIN2, OUTPUT);
  pinMode(PIN_TB6612_BIN1, OUTPUT);
  pinMode(PIN_TB6612_BIN2, OUTPUT);

  pinMode(PIN_TB6612_STBY, OUTPUT);

  disarmMotorDriver();              
  driveMotors(0, false, 0, false);

}

void initMotorDriver(uint32_t aWriteRange){

  initMotorDriver();
  setAnalogWriteRange(aWriteRange);

}

void setAnalogWriteRange(uint32_t range){

  analogWriteRange(constrain(range, 16, 65535));

}

void armMotorDriver(){

  digitalWrite(PIN_TB6612_STBY, HIGH);

}

void disarmMotorDriver(){

  digitalWrite(PIN_TB6612_STBY, LOW);

}

void driveMotors(int aSpeed, boolean aDir, int bSpeed, boolean bDir){

  driveMotorA(aSpeed, aDir);
  driveMotorB(bSpeed, bDir);

}

void driveMotorA(int speed, boolean dir){

  digitalWrite(PIN_TB6612_AIN1, dir);
  digitalWrite(PIN_TB6612_AIN2, !dir);
  analogWrite(PIN_TB6612_PWMA, speed);

}

void driveMotorB(int speed, boolean dir){

  digitalWrite(PIN_TB6612_BIN1, !dir);
  digitalWrite(PIN_TB6612_BIN2, dir);
  analogWrite(PIN_TB6612_PWMB, speed);

}