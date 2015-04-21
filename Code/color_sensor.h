#define COLOR_BLACK 0
#define COLOR_DARKGRAY 85
#define COLOR_LIGHTGRAY 170
#define COLOR_WHITE 255

#include "Arduino.h"
#include "drivetrain.h"

class AnalogInput {
public:
  AnalogInput(int pin) : pin(pin) {}
  ~AnalogInput() {}
  int Read() {
    return analogRead(pin);
  }
private:
  int pin;
};

class LineFollower//5V to photoresistor to 3000ohm resistor, input between
{
public:
  LineFollower(int leftPin, int rightPin) : left(leftPin), right(rightPin) {}
  int ReadLeftColor() {
    int val = left.Read();
    if (val < 70) {
      return COLOR_BLACK;
//    } else if (val < 120) {
//      return COLOR_DARKGRAY;
//    } else if (val < 190) {
//      return COLOR_LIGHTGRAY;
    } else {
      return COLOR_WHITE;
    }
  }
  int ReadRightColor() {
    int val = right.Read();
    Serial.print(val);
    Serial.print(" ");
    if (val < 70) {
      return COLOR_BLACK;
//    } else if (val < 120) {
//      return COLOR_DARKGRAY;
//    } else if (val < 120) {
//      return COLOR_LIGHTGRAY;
    } else {
      return COLOR_WHITE;
    }
  }
  int ReadLeft() {
    return left.Read();
  }
  int ReadRight() {
    return right.Read();
  }
  void followLine(Drivebase drivetrain)
  {
    bool L = ReadLeftColor() != COLOR_WHITE;
    bool R = ReadRightColor() != COLOR_WHITE;
    if(L&&!R)
    {
      turnL=true;
      isOff=true;
    }
    if(R&&!L)
    {
      turnL=false;
      isOff=true;
    }
    if(R&&L)
    {
      isOff=true;
      turnL=!turnL;
    }
    if(!R&&!L)
    {
      drivetrain.TankDrive(1, 1);
      isOff=false;
    }
    if(isOff)
    {
      if(turnL) drivetrain.TankDrive(-.5, 1);
      else drivetrain.TankDrive(1, -.5);
    }
  }
private:
  AnalogInput left, right;
  bool isOff=false;
  bool turnL;
  bool straight;
};

