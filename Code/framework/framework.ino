#include <Servo.h>//this must be the first thing included
#include "Arduino.h"
#include "color_sensor.h"
#include "drivetrain.h"

Drivebase drivetrain;
LineFollower follower(1, 0);

int countdown;
bool turnL;
bool straight;
bool following;

void setup() {
  Serial.begin(9600);
  drivetrain.SetPins(11, 10, 2, 3);
  drivetrain.Zero(97, 97);
  drivetrain.Calibrate();
  drivetrain.Reset();
  turnL = false;
  straight = false;
  countdown = 0;
  following = false;
}

void loop() {
  bool L = follower.ReadLeftColor() != COLOR_WHITE;
  bool R = follower.ReadRightColor() != COLOR_WHITE;
  if (!following) {
    if (countdown == 0) {
      if (L && !R) {
        turnL = false;
        countdown = 10;
      }
      if (!L && R) {
        turnL = true;
        countdown = 10;
      }
      if (L && R) {
        turnL = false;
        straight = true;
        countdown = 10;
      }
      else {
        straight = true;
        turnL = false;
        drivetrain.TankDrive(1, 1);
      }
    }
    else if (countdown > 0) {
      if (straight) {
        if (turnL) {
          drivetrain.TankDrive(-.75, .75);
        }
        else {
          drivetrain.TankDrive(.75, -.75);
        }
      }
      else if (turnL) {
        drivetrain.TankDrive(.5, 1);
      }
      else {
        drivetrain.TankDrive(1, .5);
      }
      countdown--;
      if (countdown == 0) {
        following = true;
      }
    }
  }
  else {
    if (countdown == 0)
    {
      if (L && !R)
      {
        turnL = true;
        countdown = 100;
      }
      if (R && !L)
      {
        turnL = false;
        countdown = 100;
      }
      if (R && L)
      {
        straight = true;
        countdown = 100;
      }
      if (!R && !L)
      {
        drivetrain.TankDrive(1, 1);
      }
    }
    if (countdown > 0)
    {
      if (straight) {
        if (turnL) drivetrain.TankDrive(-1, .75);
        else drivetrain.TankDrive(.75, -1);
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
}
