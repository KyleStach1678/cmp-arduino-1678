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

class LineFollower
{
public:
  LineFollower(int leftPin, int rightPin) : left(leftPin), right(rightPin) {}
  int ReadLeftColor() {
    int val = left.Read();
    if (val < 420) {
      return COLOR_BLACK;
    } else if (val < 505) {
      return COLOR_DARKGRAY;
    } else if (val < 574) {
      return COLOR_LIGHTGRAY;
    } else {
      return COLOR_WHITE;
    }
  }
  int ReadRightColor() {
    int val = right.Read();
    if (val < 400) {
      return COLOR_BLACK;
    } else if (val < 500) {
      return COLOR_DARKGRAY;
    } else if (val < 550) {
      return COLOR_LIGHTGRAY;
    } else {
      return COLOR_WHITE;
    }
  }
private:
  AnalogInput left, right;
};

