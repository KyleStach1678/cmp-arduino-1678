#include <Servo.h>//this must be the first thing included
#include "Arduino.h"
#include "color_sensor.h"
#include "drivetrain.h"

Drivebase drivetrain;
LineFollower follower(1, 0);

void setup() {
  Serial.begin(9600);
  drivetrain.SetPins(10, 11, 2, 3);
  drivetrain.Zero(97, 97);
  drivetrain.Calibrate();
}	
void loop() {
  bool L = follower.ReadLeftColor() != COLOR_WHITE;
  bool R = follower.ReadRightColor() != COLOR_WHITE;
  follower.followLine(drivetrain);
  Serial.print(L);
  Serial.print(" ");
  Serial.println(R);
}
