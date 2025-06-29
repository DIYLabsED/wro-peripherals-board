#include "Arduino.h"
#include "pindefs.h"

void initMotorDriver();                                                // initialise pins, set driver in safe state
void initMotorDriver(uint32_t aWriteRange);                            // initialise pins, set driver in safe state, sets analog write range
void setAnalogWriteRange(uint32_t range);                              // set tb6612_AnalogWriteRange, clamped between 16 -> 65535, see https://arduino-pico.readthedocs.io/en/latest/analog.html#void-analogwriterange-uint32-t-range-and-analogwriteresolution-int-res
void armMotorDriver();                                                 // sets STBY pin HIGH, enabling motor driver until disarmMotorDriver() is called
void disarmMotorDriver();                                              // sets STY pin LOW, disabling motor driver until armMotorDriver() is called
void driveMotors(int aSpeed, boolean aDir, int bSpeed, boolean bDir);  // send commands to both motors, speed range 0 -> tb6612AnalogWriteRange, internally calls driveMotorA() and driveMotorB()
void driveMotorA(int speed, boolean dir);                              // sends commands to A output of driver
void driveMotorB(int speed, boolean dir);                              // sends commands to B output of driver