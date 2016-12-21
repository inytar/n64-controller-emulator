#include <Arduino.h>

const int pin = 12;
#define SEQLEN 132

// Button refs
#define A 0
#define B 1
#define Z 2
#define S 3
#define dU 4
#define dD 5
#define dL 6
#define dR 7
#define rst 8
#define L 10
#define R 11
#define cU 12
#define cD 13
#define cL 14
#define cR 15
#define X 16
#define Y 24

int frame;
volatile bool sentLast = true;

bool seq[SEQLEN] = {false};
bool emptyAction[SEQLEN] = {false};

unsigned currBit = 0;
bool flip = true;

void setup() {
    init();
    Serial.begin(9600);
    Serial.print("Starting Program");
    Serial.println();
    delay(500);
    Serial.print("Ready");
    Serial.println();
    attachInterrupt(digitalPinToInterrupt(pin), writeSeq, FALLING);
}

void loop() {
    if (sentLast) {
        nextCommand();
        noInterrupts();
        sentLast = false;
        interrupts();
    }
}

void init() {
    for (int i=3 ; i < SEQLEN - 4 ; i = i + 4) {
        emptyAction[i] = true;
    }
    // Stop Bit
    emptyAction[128] = false;
    emptyAction[129] = false;
    emptyAction[130] = true;
    emptyAction[131] = true;
    resetSeq();

    frame = 0;

    pinMode(pin, INPUT);
    // Set pin interupt
}

void writeSeq() {
    noInterrupts();
    delayMicroseconds(32);
    pinMode(pin, OUTPUT);
    for (int i=0 ; i<SEQLEN ; i++) {
        if (seq[i]) {
            digitalWrite(pin, HIGH);
        } else {
            digitalWrite(pin, LOW);
        }
    }
    pinMode(pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(pin), writeSeq, FALLING);
    sentLast = true;
    interrupts();
}

void nextCommand() {
    resetSeq();

    if (frame == 0 || frame == 1){
        pressButton(cU);
    }
    if (frame == 3 || frame == 4) {
        pressButton(B);
    }
    setAxis(Y, -80);
    setAxis(X, 40);
    frame++;
    if (frame > 13) {
        frame = 0;
    }
}

void pressButton(int button) {
    seq[button * 4 + 1] = true;
    seq[button * 4 + 2] = true;
}

void setAxis(int axis, int8_t val) {
    for (int i=0 ; i<8 ; i++) {
        bool bit = (1<<(7-i)) & val;
        if (bit) {
            pressButton(axis + i);
        }
    }
}

void resetSeq() {
    for (int i=0 ; i<SEQLEN ; i++) {
        seq[i] = emptyAction[i];
    }
}