#include <Arduino.h>
#define ENCODER_THRESHOLD 40
class Encoder {
private:
  int minValue;
  int maxValue;
  int pin;
  int clicks;
  bool wasTriggered;
  int lastValue;
  int cCounter;
public:
  Encoder() {
    pin = 0;
    minValue = maxValue = cCounter = 0;
    lastValue = analogRead(pin);
  }
  Encoder(int npin) {
    pin = npin;
    minValue = maxValue = cCounter = 0;
    lastValue = analogRead(pin);
  }
  void SetPin(int npin) {
    pin = npin;
  }
  int GetClicks() {
    return clicks;
  }
  void Reset() {
    clicks = 0;
  }
  void Update(bool forward) {
    Serial.println(wasTriggered);
    if (!wasTriggered && analogRead(pin) > ((minValue + maxValue) / 2)) {
      if (forward) clicks++;
      else clicks--;
    }
    wasTriggered = analogRead(pin) > ((minValue + maxValue) / 2);
  }
  bool Calibrate() {
    cCounter++;
    int val = analogRead(pin);
    minValue = val < minValue ? val : minValue;
    maxValue = val > maxValue ? val : maxValue;
    return cCounter > 500;
  }
};
