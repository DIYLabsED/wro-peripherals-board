#include "motor-driver.h"

void initMotorDriver(TB6612_pindef pindef){

  tb6612Pindef = pindef;

  pinMode(tb6612Pindef.PIN_PWMA, OUTPUT);
  pinMode(tb6612Pindef.PIN_PWMB, OUTPUT);

  pinMode(tb6612Pindef.PIN_AIN1, OUTPUT);
  pinMode(tb6612Pindef.PIN_AIN2, OUTPUT);
  pinMode(tb6612Pindef.PIN_BIN1, OUTPUT);
  pinMode(tb6612Pindef.PIN_BIN2, OUTPUT);

  pinMode(tb6612Pindef.PIN_STBY, OUTPUT);

  disarmMotorDriver();              
  driveMotors(0, false, 0, false);

}

void initMotorDriver(TB6612_pindef pindef, uint32_t aWriteRange){

  initMotorDriver(pindef);
  setAnalogWriteRange(aWriteRange);

}

void setAnalogWriteRange(uint32_t range){

  analogWriteRange(constrain(range, 16, 65535));

}

void armMotorDriver(){

  digitalWrite(tb6612Pindef.PIN_STBY, LOW);

}

void disarmMotorDriver(){

  digitalWrite(tb6612Pindef.PIN_STBY, HIGH);

}

void driveMotors(int aSpeed, boolean aDir, int bSpeed, boolean bDir){

  driveMotorA(aSpeed, aDir);
  driveMotorB(bSpeed, bDir);

}

void driveMotorA(int speed, boolean dir){

  digitalWrite(tb6612Pindef.PIN_AIN1, dir);
  digitalWrite(tb6612Pindef.PIN_AIN2, !dir);
  analogWrite(tb6612Pindef.PIN_PWMA, speed);

}

void driveMotorB(int speed, boolean dir){

  digitalWrite(tb6612Pindef.PIN_BIN1, dir);
  digitalWrite(tb6612Pindef.PIN_BIN2, !dir);
  analogWrite(tb6612Pindef.PIN_PWMB, speed);

}