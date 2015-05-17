#ifndef DRIVETRAIN_INCLUDED
#define DRIVETRAIN_INCLUDED

#include "Arduino.h"
#include "encoder.h"
class Drivebase
{
private:
  Servo left;
  Servo right;
  int zeroL, zeroR;
public:
  Drivebase() {
    zeroL = zeroR = 90;
  }
  Drivebase(int leftPin, int rightPin) {
    left.attach(leftPin);
    right.attach(rightPin);
    zeroL = zeroR = 90;
  }
  void Zero(int leftZero, int rightZero) {
    zeroL = leftZero;
    zeroR = rightZero;
  }
  void SetPins(int leftPin, int rightPin) {
    left.attach(leftPin);
    right.attach(rightPin);
  }
  void TankDrive(float leftInp, float rightInp) {
    float leftPower = leftInp * 7 + zeroL;
    float rightPower = -rightInp * 7 + zeroR;
    left.write(leftPower);
    right.write(rightPower);
  }
};

#endif
