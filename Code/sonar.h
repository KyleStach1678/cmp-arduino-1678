#include <Arduino.h>
class SonarSensor
{
private:
  int trig, echo;
public:
  SonarSensor(int trigPin, int echoPin) : trig(trigPin), echo(echoPin)
  {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
  }
  float getDist()//gets distance, in centimeters
  {
    float duration, distance;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = (duration/2) / 29.1;
    if (distance >= 200 || distance <= 0){
      return -1;
    }
    else {
      return distance;
    }
  }
};
