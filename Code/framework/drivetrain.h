#include "Arduino.h"
#include "encoder.h"
class Drivebase
{
private:
  Servo left;
  Servo right;
  Encoder leftEncoder;
  Encoder rightEncoder;
  int zeroL, zeroR;
public:
  Drivebase() {
    zeroL = zeroR = 90;
  }
  Drivebase(int leftPin, int rightPin, int leftEncoderPin, int rightEncoderPin) {
    left.attach(leftPin);
    right.attach(rightPin);
    leftEncoder.SetPin(leftEncoderPin);
    rightEncoder.SetPin(rightEncoderPin);
    zeroL = zeroR = 90;
  }
  void Zero(int leftZero, int rightZero) {
    zeroL = leftZero;
    zeroR = rightZero;
  }
  void SetPins(int leftPin, int rightPin, int leftEncoderPin, int rightEncoderPin) {
    left.attach(leftPin);
    right.attach(rightPin);
    leftEncoder.SetPin(leftEncoderPin);
    rightEncoder.SetPin(rightEncoderPin);
  }
  void TankDrive(float leftInp, float rightInp) {
    float leftPower = leftInp * 7 + zeroL;
    float rightPower = -rightInp * 7 + zeroR;
    left.write(leftPower);
    right.write(rightPower);
    leftEncoder.Update(leftInp > 0);
    rightEncoder.Update(rightInp > 0);
  }
  int LeftClicks() {
    return leftEncoder.GetClicks();
  }
  int RightClicks() {
    return rightEncoder.GetClicks();
  }
  void Calibrate() {
    for (int i = 0; i < 500; i++) {
      rightEncoder.Calibrate(); leftEncoder.Calibrate();
      TankDrive(1, 1);
    }
    TankDrive(0, 0);
    Reset();
  }
  void Reset() {
    leftEncoder.Reset();
    rightEncoder.Reset();
  }
};
