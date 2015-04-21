// Libraries must be included first
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>

#include "Arduino.h"
#include "color_sensor.h"
#include "drivetrain.h"
#include "receiver.h"

#define PIN_DRIVE_LEFT 10
#define PIN_DRIVE_RIGHT 11
#define PIN_ENCODER_PR_LEFT 2
#define PIN_ENCODER_PR_RIGHT 3
#define PIN_LINETRACKER_PR_LEFT 1
#define PIN_LINETRACKER_PR_RIGHT 0
#define PIN_IR_RECEIVER 9

Drivebase drivetrain(PIN_DRIVE_LEFT, PIN_DRIVE_RIGHT, PIN_ENCODER_PR_LEFT, PIN_ENCODER_PR_RIGHT);
LineFollower follower(PIN_LINETRACKER_PR_LEFT, PIN_LINETRACKER_PR_RIGHT);

IRFieldSystem fms(PIN_IR_RECEIVER);

void setup() {
  Serial.begin(9600);
  drivetrain.Zero(97, 97);
  // Calibrate the encoders
  drivetrain.Calibrate();
  fms.WaitForStart(); // Wait for the signal from the TV remote
}

void loop() {
  fms.Update();
  if (fms.IsRunning()) {
    follower.followLine(drivetrain);
  }
}
