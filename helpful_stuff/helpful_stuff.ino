#include <Servo.h>//this must be the first thing included
#include "Arduino.h"
#include "color_sensor.h"
#include "drivetrain.h"

float stp;
float kP, kI, kD;

int lastColorVal;
float integral;
float lastProportional;

Drivebase drivetrain;
LineFollower follower(1, 0);

void setup() {
  kP = 0;
  kI = 0;
  kD = 0;
  lastProportional = 0;
  integral = 0;
  Serial.begin(9600);
  stp = 0;
  drivetrain.SetPins(11, 10, 2, 3);
  drivetrain.Zero(97, 97);
  drivetrain.Calibrate();
}

void loop() {
  //  int leftColor = follower.ReadLeftColor();
  //  int rightColor = follower.ReadRightColor();
  //  Serial.print("Left: "); Serial.print(leftColor);
  //  Serial.print("Right: "); Serial.println(rightColor);
  //  if (leftColor == COLOR_WHITE && rightColor == COLOR_WHITE) {
  //    drivetrain.TankDrive(1, 1);
  //    if (lastColorVal == COLOR_WHITE) {
  //      lastProportional = 0;
  //      integral = 0;
  //    }
  //  }
  //  else {
  //    if (leftColor == COLOR_WHITE && rightColor != COLOR_WHITE) {
  //      drivetrain.TankDrive(-.25, .75);
  //    }
  //    else if (leftColor != COLOR_WHITE && rightColor == COLOR_WHITE) {
  //      drivetrain.TankDrive(.75, -.25);
  //    }
  //    else if (leftColor != COLOR_WHITE && rightColor != COLOR_WHITE) {
  //      drivetrain.TankDrive(.75, -.75);
  //    }
  //
  //    // Run PID control to track the line
  ////    float proportional = follower.ReadLeft() - follower.ReadRight();
  ////    integral += proportional;
  ////    float derivative = proportional - lastProportional;
  ////    float correction = proportional * kP + integral * kI + derivative * kD;
  ////    drivetrain.TankDrive(0.75 - correction, 0.75 + correction);
  ////    lastProportional = proportional;
  //  }
  //  lastColorVal = (follower.ReadLeftColor() + follower.ReadRightColor()) / 2;
  drivetrain.TankDrive(.1, .1);
  //  drivetrain.TankDrive(1, -1);
  Serial.print("Left Encoder: "); Serial.println(drivetrain.LeftClicks());
  Serial.print("Right Encoder: "); Serial.println(drivetrain.RightClicks());
}
