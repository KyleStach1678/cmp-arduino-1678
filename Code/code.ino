// Libraries must be included first
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>

#include "Arduino.h"
#include "color_sensor.h"
#include "drivetrain.h"

#define PIN_DRIVE_LEFT 10
#define PIN_DRIVE_RIGHT 11
#define PIN_ENCODER_PR_LEFT 2
#define PIN_ENCODER_PR_RIGHT 3
#define PIN_LINETRACKER_PR_LEFT 1
#define PIN_LINETRACKER_PR_RIGHT 0
#define PIN_IR_RECEIVER 9

Drivebase drivetrain(PIN_DRIVE_LEFT, PIN_DRIVE_RIGHT);
LineFollower follower(PIN_LINETRACKER_PR_LEFT, PIN_LINETRACKER_PR_RIGHT);

void setup() {
  Serial.begin(9600);
  drivetrain = Drivebase(PIN_DRIVE_LEFT, PIN_DRIVE_RIGHT);
  drivetrain.SetPins(PIN_DRIVE_LEFT, PIN_DRIVE_RIGHT);
  drivetrain.Zero(97, 97);
}

void loop() {
  follower.FollowLine(drivetrain);
}
