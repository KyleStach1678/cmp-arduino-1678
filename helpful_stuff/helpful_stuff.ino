#include <Servo.h>//this must be the first thing included
#include "Arduino.h"
#include "color_sensor.h"
#include "drivetrain.h"
float stp;
 
Drivebase drivetrain;
LineFollower follower(0, 1);

void setup() {
  Serial.begin(9600);
  stp = 0;
  drivetrain.SetPins(11, 10);
  drivetrain.Zero(97, 97);
}

void loop() {
  stp += .02;
//  drivetrain.TankDrive(sin(stp) * .25 + .75, cos(stp) * .25 + .75);
  drivetrain.TankDrive(1,1.2);
  int leftColor = follower.ReadLeftColor();
  int rightColor = follower.ReadRightColor();
  Serial.print(leftColor);
  Serial.print(" ");
  Serial.println(rightColor);
  delay(50);
}
