#include "Arduino.h"

struct TB6612_pindef{

  uint8_t PIN_PWMA;
  uint8_t PIN_PWMB;

  uint8_t PIN_AIN1;
  uint8_t PIN_AIN2;
  uint8_t PIN_BIN1;
  uint8_t PIN_BIN2;

  uint8_t PIN_STBY;  

};

TB6612_pindef tb6612Pindef;

void initMotorDriver(TB6612_pindef pindef);                            // initialise pins, set driver in safe state
void initMotorDriver(TB6612_pindef pindef, uint32_t aWriteRange);      // initialise pins, set driver in safe state, sets analog write range
void setAnalogWriteRange(uint32_t range);                              // set tb6612_AnalogWriteRange, clamped between 16 -> 65535, see https://arduino-pico.readthedocs.io/en/latest/analog.html#void-analogwriterange-uint32-t-range-and-analogwriteresolution-int-res
void armMotorDriver();                                                 // sets STBY pin HIGH, enabling motor driver until disarmMotorDriver() is called
void disarmMotorDriver();                                              // sets STY pin LOW, disabling motor driver until armMotorDriver() is called
void driveMotors(int aSpeed, boolean aDir, int bSpeed, boolean bDir);  // send commands to both motors, speed range 0 -> tb6612AnalogWriteRange, internally calls driveMotorA() and driveMotorB()
void driveMotorA(int speed, boolean dir);                              // sends commands to A output of driver
void driveMotorB(int speed, boolean dir);                              // sends commands to B output of driver