#define COLOR_BLACK 0
#define COLOR_DARKGRAY 85
#define COLOR_LIGHTGRAY 170
#define COLOR_WHITE 255

#include "Arduino.h"
#include "drivetrain.h"

class LineFollower//5V to photoresistor to 3000ohm resistor, input between
{
public:
  LineFollower(int leftPin, int rightPin) : leftPin(leftPin), rightPin(rightPin) {}
  int ReadLeftColor() {
    int val = analogRead(leftPin);
    if (val < 70) {
      return COLOR_BLACK;
    } else if (val < 120) {
      return COLOR_DARKGRAY;
    } else if (val < 190) {
      return COLOR_LIGHTGRAY;
    } else {
      return COLOR_WHITE;
    }
  }
  int ReadRightColor() {
    int val = analogRead(rightPin);
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
    return analogRead(leftPin);
  }
  int ReadRight() {
    return analogRead(rightPin);
  }
  void FollowLine(Drivebase drivetrain) {
    FollowLineAlg1(Drivebase drivetrain);
  }
  void FollowLineAlg1(Drivebase drivetrain)
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
  void FollowLineAlg2(Drivebase drivetrain) {
    bool L = ReadLeftColor() != COLOR_WHITE;
    bool R = ReadRightColor() != COLOR_WHITE;
    
    if (stage == 0) {
      if (L && !R) {
        // The left sensor is on a line, so turn left
        stage = 3; // Start turning
        turnL = true;
      }
      else if (!L && R) {
        // The right sensor is on a line, so turn right
        stage = 3; // Start turning
        turnL = false;
      }
      else if (!L && !LR) {
        TankDrive(1, 1);
      }
    }
    else if (stage == 1) {
      if (counter-- <= 0) {
        stage = 0;
      }
      if (turnL) {
        drivetrain.TankDrive(.5, -1);
      }
      else {
        drivetrain.TankDrive(-1, .5);
      }
    }
    else if (stage == 2) {
      // Drive straight
      if ((turnLeft && !R) || (turnRight && !L)) {
        drivetrain.TankDrive(1, 1);
      }
      else {
        stage = 1;
        counter = counter / 2;
      }
    }
    else if (stage == 3) {
      // Turn
      if (isOff && (L || R)) {
        stage = 2;
      }
      counter++;
      
      if ((turnL && !L) || (turnR && !R)) {
        isOff = true;
      }
      
      if (turnL) {
        drivetrain.TankDrive(0, 1);
      }
      else {
        drivetrain.TankDrive(1, 0);
      }
    }
  }
private:
  int leftPin, rightPin;
  int counter = 0;
  int stage = 0;
  bool isOff=false;
  bool turnL;
  bool straight;
};

