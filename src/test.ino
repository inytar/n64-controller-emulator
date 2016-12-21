#include <Arduino.h>

const int pin = 12;
#define SEQLEN 32

IntervalTimer timer;
uint32_t seq;
unsigned currBit = 0;
bool flip = true;

void setup() {
    init();
    Serial.begin(9600);
    delay(100);
}

void loop() {
    seq = 5;
    test2Loop();
    delay(10);
}

void init() {
    pinMode(pin, OUTPUT);
    digitalWriteFast(pin, HIGH);
    // Set pin interupt
}

void writeNextHighLow() {
    if ((1 << (SEQLEN - currBit - 1)) & seq) {
        digitalWriteFast(pin, HIGH);
    } else {
        digitalWriteFast(pin, LOW);
    }
    currBit++;
    if (currBit >= SEQLEN) {
        timer.end();
        currBit = 0;
    }
}

void testLoop() {
    timer.begin(writeNextHighLow, 2);
    timer.priority(0);
}

void writeHigh() {
    digitalWrite(pin, HIGH);
    /*digitalWriteFast(pin, HIGH);
    digitalWriteFast(pin, HIGH);
    digitalWriteFast(pin, HIGH);
    digitalWriteFast(pin, HIGH);
    digitalWriteFast(pin, HIGH);
    digitalWriteFast(pin, HIGH);
    digitalWriteFast(pin, HIGH);
    digitalWriteFast(pin, HIGH);
    digitalWriteFast(pin, HIGH);
    digitalWriteFast(pin, HIGH);
    digitalWriteFast(pin, HIGH);*/
}

void writeLow() {
    digitalWrite(pin, LOW);
    /*digitalWriteFast(pin, LOW);
    digitalWriteFast(pin, LOW);
    digitalWriteFast(pin, LOW);
    digitalWriteFast(pin, LOW);
    digitalWriteFast(pin, LOW);
    digitalWriteFast(pin, LOW);
    digitalWriteFast(pin, LOW);
    digitalWriteFast(pin, LOW);
    digitalWriteFast(pin, LOW);
    digitalWriteFast(pin, LOW);*/
}

void test2Loop() {
    writeLow();
    writeHigh();
    writeLow();
    writeHigh();
    writeLow();
    writeHigh();
}