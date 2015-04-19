#define COLOR_BLACK 0
#define COLOR_DARKGRAY 85
#define COLOR_LIGHTGRAY 170
#define COLOR_WHITE 255

#include "Arduino.h"

class AnalogInput {
public:
  AnalogInput(int pin) : pin(pin) {}
  ~AnalogInput() {}
  int Read() {
    return analogRead(pin);
  }
private:
  int pin;
};

class LineFollower//5V to photoresistor to 3000ohm resistor, input between
{
public:
  LineFollower(int leftPin, int rightPin) : left(leftPin), right(rightPin) {}
  int ReadLeftColor() {
    int val = left.Read();
    if (val < 100) {
      return COLOR_BLACK;
    } else if (val < 200) {
      return COLOR_DARKGRAY;
    } else if (val < 300) {
      return COLOR_LIGHTGRAY;
    } else {
      return COLOR_WHITE;
    }
  }
  int ReadRightColor() {
    int val = right.Read();
    if (val < 100) {
      return COLOR_BLACK;
    } else if (val < 200
    ) {
      return COLOR_DARKGRAY;
    } else if (val < 300) {
      return COLOR_LIGHTGRAY;
    } else {
      return COLOR_WHITE;
    }
  }
  int ReadLeft() {
    return left.Read();
  }
  int ReadRight() {
    return right.Read();
  }
private:
  AnalogInput left, right;
};

