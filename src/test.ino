#include <Arduino.h>

const int pin = 12;
// Length of input sequence 4 units per bit (32 bits)
#define SEQLEN 132

// Input refs
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

// Frame counter
int frame;

// Request Bit Counter - counts bits in the console request byte
int requestBitCounter;

// Keeps track of whether the last input was sent
volatile bool sentLast;

// Arrays to define input sequences to be sent to console
bool seq[SEQLEN] = {false};
bool emptyAction[SEQLEN] = {false};

// Timer for interpreting console request
elapsedMicros requestTimer;

void setup() {
    Serial.begin(9600);
    delay(500);
    Serial.print("Starting Program");
    Serial.println();
    init();
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

    // Set initial values
    frame = 0;
    sentLast = true;
    requestBitCounter = 0;

    // Set pin interupt
    pinMode(pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(pin), getResponse, FALLING);
}

void loop() {
    if (sentLast) {
        nextCommand();
        noInterrupts();
        sentLast = false;
        interrupts();
    }
}

void getResponse() {
    detachInterrupt(digitalPinToInterrupt(pin));
    attachInterrupt(digitalPinToInterrupt(pin), count, RISING);
}

void count() {
    requestBitCounter++;
    if (requestBitCounter >= 8) {
        noInterrupts();
        writeSeq(requestTimer <= 2);
        interrupts();

        requestBitCounter = 0;
        attachInterrupt(digitalPinToInterrupt(pin), getResponse, FALLING);
    } else if (requestBitCounter >= 7) {
        requestTimer = 0;
    }
}

void writeSeq(bool input) {
    bool *response;
    if (input) {
        response = seq;
        sentLast = true;
    } else {
        response = emptyAction;
    }

    // Switch in pin mode dettaches (pin, count, RISING) interrupt
    pinMode(pin, OUTPUT);
    for (int i=0 ; i<SEQLEN ; i++) {
        if (response[i]) {
            digitalWrite(pin, HIGH);
        } else {
            digitalWrite(pin, LOW);
        }
    }
    pinMode(pin, INPUT);
}

void nextCommand() {
    resetSeq();

    if (frame == 0){
        pressButton(cU);
    }
    if (frame == 3) {
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