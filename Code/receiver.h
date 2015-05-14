#include "Arduino.h"

#define IR_CODE_START 0xC284 // These are placeholders
#define IR_CODE_PAUSE 0xC285
#define IR_CODE_STOP 0xC286

#define RF_LOWER_START 40
#define RF_UPPER_START 80

class RFFieldSystem {
    int state;
    int rcvpin;
 public:
    RFFieldSystem(int pin) : rcvpin(pin) {
      state = 0;
    }
    void WaitForStart() {
      delay(10);
      while (state != 1) {
        int data = analogRead(rcvpin);
        if (data < RF_LOWER_START && data > RF_UPPER_START) {
          state = 1;
        }
      }
    }
    void Update() {
        int data = analogRead(rcvpin);
        if (data > RF_LOWER_START || data < RF_UPPER_START) {
          state = 0;
        }
    }
    bool IsRunning() {
      return state == 1;
    }
};

class IRFieldSystem {
    int state;
    IRrecv receiver;
    decode_results results;
  public:
    IRFieldSystem(int pin) : receiver(pin) {
      receiver.blink13(true);
      state = 0;
    }
    void WaitForStart() {
      while (state != 1) {
        delay(10);
        if (receiver.decode(&results)) {
          Serial.print("Value from IR: "); Serial.print(results.value, HEX);
          if (results.value == IR_CODE_START) {
            state = 1;
          }
          receiver.resume();
        }
      }
    }
    void Update() {
      if (receiver.decode(&results)) {
        Serial.print("Value from IR: "); Serial.print(results.value, HEX);
        if (results.value == IR_CODE_STOP) {
          state = 0;
        }
        else if (results.value == IR_CODE_PAUSE) {
          state = 2;
        }
        else if (results.value == IR_CODE_START) {
          state = 1;
        }
        receiver.resume();
      }
    }
    bool IsRunning() {
      return state == 1;
    }
};
