// Libraries must be included first
#include <Servo.h>

#include "Arduino.h"
#include "color_sensor.h"
#include "drivetrain.h"
#include "sonar.h"

#define PIN_DRIVE_LEFT 10
#define PIN_DRIVE_RIGHT 11
#define PIN_ENCODER_PR_LEFT 2
#define PIN_ENCODER_PR_RIGHT 3
#define PIN_LINETRACKER_PR_LEFT 1
#define PIN_LINETRACKER_PR_RIGHT 0
#define PIN_IR_RECEIVER 9
#define TRIG_PIN 13
#define ECHO_PIN 12
Drivebase drivetrain(PIN_DRIVE_LEFT, PIN_DRIVE_RIGHT, PIN_ENCODER_PR_LEFT, PIN_ENCODER_PR_RIGHT);
LineFollower follower(PIN_LINETRACKER_PR_LEFT, PIN_LINETRACKER_PR_RIGHT);
SonarSensor range(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);
  drivetrain.Zero(97, 97);
  // Calibrate the encoders
  drivetrain.Calibrate();
}

void loop() {
    //follower.followLine(drivetrain);
    float dist=range.getDist();
    Serial.println();
    if(dist==-1)
    {
      Serial.println("out of range");
    }
    else
    {
      Serial.println(dist);
      Serial.println(" cm");
    }
    delay(100);
}
