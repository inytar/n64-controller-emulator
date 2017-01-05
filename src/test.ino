#include <Arduino.h>

const int pin = 12;
#define SEQLEN 132
#define BUFFLEN 4

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
volatile bool sentLast;
volatile int8_t bttn1;
volatile int8_t bttn2;
volatile int8_t xAxis;
volatile int8_t yAxis;

IntervalTimer setCommand;

bool seq[SEQLEN] = {false};
bool emptyAction[SEQLEN] = {false};

unsigned currBit = 0;
bool flip = true;

void setup() {
    init();
    Serial.begin(115200);
    Serial.print("Starting Program");
    Serial.println();
    delay(500);
    Serial.print("Ready");
    Serial.println();
    attachInterrupt(digitalPinToInterrupt(pin), writeSeq, FALLING);
    setCommand.priority(0);
    setCommand.begin(nextCommand, 400);
}

void loop() {
    int count = 0;
    int8_t buff[BUFFLEN];
    while (count<BUFFLEN) {
        if (Serial.available() && sentLast) {
            buff[count++] = Serial.read();
        }
    }
    bttn1 = buff[0];
    bttn2 = buff[1];
    xAxis = buff[2];
    yAxis = buff[3];
    sentLast = false;
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
    sentLast = true;
    bttn1 = 0;
    bttn2 = 0;
    xAxis = 0;
    yAxis = 0;

    pinMode(pin, INPUT);
    // Set pin interupt
}

void writeSeq() {
    noInterrupts();
    setCommand.end();
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
    setCommand.begin(nextCommand, 4000);
    interrupts();
}

void nextCommand() {
    setCommand.end();
    resetSeq();

    for (int i=0 ; i<8 ; i++){
        if ((1<<i) & bttn1) {
            pressButton(i);
        }
        if ((1<<i) & bttn2) {
            pressButton(i + 8);
        }
    }

    setAxis(X, xAxis);
    setAxis(Y, yAxis);

    bttn1 = 0;
    bttn2 = 0;
    xAxis = 0;
    yAxis = 0;

    //Serial.print('p');
    sentLast = true;

    /*
    if ((1<<0) & bttn1) {
        pressButton(A);
    }
    if ((1<<1) & bttn1) {
        pressButton(B);
    }
    if ((1<<2) & bttn1) {
        pressButton(Z);
    }
    if ((1<<3) & bttn1) {
        pressButton(S);
    }
    if ((1<<4) & bttn1) {
        pressButton(dU);
    }
    if ((1<<5) & bttn1) {
        pressButton(dD);
    }
    if ((1<<6) & bttn1) {
        pressButton(dL);
    }
    if ((1<<7) & bttn2) {
        pressButton(dR);
    }
    if ((1<<2) & bttn2) {
        pressButton(L);
    }
    if ((1<<3) & bttn2) {
        pressButton(R);
    }
    if ((1<<4) & bttn2) {
        pressButton(cU);
    }
    if ((1<<5) & bttn2) {
        pressButton(cD);
    }
    if ((1<<6) & bttn2) {
        pressButton(cL);
    }
    if ((1<<7) & bttn2) {
        pressButton(cR);
    } */
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
