#include "N64Controller.h"


N64Controller::N64Controller(int pin) {
    _pin = pin;
}


void N64Controller::init() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    // Set pin interupt
}

void N64Controller::write1() {
    /* Serial.print('1'); */
    digitalWriteFast(_pin, LOW);
    delayMicroseconds(1);
    digitalWriteFast(_pin, HIGH);
    delayMicroseconds(3);
}

void N64Controller::write0() {
    /* Serial.print('0'); */
    digitalWriteFast(_pin, LOW);
    delayMicroseconds(3);
    digitalWriteFast(_pin, HIGH);
    delayMicroseconds(1);
}

void N64Controller::writeStop() {
    /* Serial.println(); */
    digitalWriteFast(_pin, LOW);
    delayMicroseconds(2);
    digitalWriteFast(_pin, HIGH);
    delayMicroseconds(2);
    /* pinMode(_pin, INPUT); */
}

void N64Controller::write(uint32_t input) {
    for (int _ = 0; _ < 32; _++) {
        if (input & (1<<31)) {
            write1();
        } else {
            write0();
       }
        input <<= 1;
    }
    writeStop();
}
