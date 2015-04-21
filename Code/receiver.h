#include "Arduino.h"

#define IR_CODE_START 0xC284 // These are placeholders
#define IR_CODE_PAUSE 0xC285
#define IR_CODE_STOP 0xC286

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
        if (receiver.decode(&results)) {
          Serial.print("Value from IR: "); Serial.print(results.value, HEX);
          if (results.value == IR_CODE_START) {
            state = 1;
          }
          receiver.resume();
        }
        delay(10);
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
