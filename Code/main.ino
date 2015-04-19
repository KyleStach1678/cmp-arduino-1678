#include <Servo.h>//this must be the first thing included
#include "Arduino.h"
#include "color_sensor.h"
#include "drivetrain.h"

Drivebase drivetrain;
LineFollower follower(1, 0);

int countdown;
bool turnL;
bool straight;

void setup() {
  Serial.begin(9600);
  drivetrain.SetPins(11, 10, 2, 3);
  drivetrain.Zero(97, 97);
  drivetrain.Calibrate();
  turnL = false;
}

void loop() {
  bool L = follower.ReadLeftColor() != COLOR_WHITE;
  bool R = follower.ReadRightColor() != COLOR_WHITE;
  if (countdown == 0)
  {
    if (L && !R)
    {
      turnL = true;
      countdown = 10;
    }
    if (R && !L)
    {
      turnL = false;
      countdown = 10;
    }
    if (R && L)
    {
      straight = true;
      countdown = 10;
    }
    if (!R && !L)
    {
      drivetrain.TankDrive(1, 1);
    }
  }
  if (countdown > 0)
  {
    if (straight) {
      if (turnL) drivetrain.TankDrive(-1, 1);
      else drivetrain.TankDrive(1, -1);
    }
    else if (turnL) {
      drivetrain.TankDrive(0, 1);
    }
    else {
      drivetrain.TankDrive(1, 0);
    }
    countdown--;
    if (countdown == 0) countdown = -1;
  }
  if (countdown == -1)
  {
    straight = false;
    drivetrain.TankDrive(1, 1);
    if (!R && !L) countdown = 0;
  }
}
