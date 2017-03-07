#include <Arduino.h>

// pin on Teensy through which communications happen
const int pin = 12;

/* emptyAction and seq represent 32bit responses from the controller 
    representing controller input for a given frame.
    Each entry of emptyAction and seq represents a microsecond of high or 
    low voltage over the data wire. Each bit is represented by 4 microseconds 
    of voltage.
    0:    LOW LOW  LOW  HIGH
    1:    LOW HIGH HIGH HIGH
    STOP: LOW LOW  HIGH HIGH */
#define SEQLEN 132
bool seq[SEQLEN] = {false};  // input to be sent to console
bool emptyAction[SEQLEN] = {false};  // input of no button presses

// Buffer variables to deal with nonsense request from console
#define BUFFLEN 4
volatile int8_t bttn1;
volatile int8_t bttn2;
volatile int8_t xAxis;
volatile int8_t yAxis;
// keeps track of when to queue the next input to send to the console
// helps deal with nonsense request from console
volatile bool sentLast;
// interrupt for queueing the next command, also deals with nonsense request
IntervalTimer setCommand;

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


void setup() {
    init();
    // start connection to Serial port
    Serial.begin(115200);
    Serial.print("Starting Program");
    Serial.println();
    // set up interrupts for console input request + command queueing
    attachInterrupt(digitalPinToInterrupt(pin), writeSeq, FALLING);
    setCommand.priority(0);
    setCommand.begin(nextCommand, 400);
}

void init() {
    // 32 0 bits
    for (int i=3 ; i < SEQLEN - 4 ; i = i + 4) {
        emptyAction[i] = true;
    }
    // stop bit
    emptyAction[128] = false;
    emptyAction[129] = false;
    emptyAction[130] = true;
    emptyAction[131] = true;
    resetSeq();

    // on start always queue next command
    sentLast = true;

    // on start default buttons to queue are an empty command
    bttn1 = 0;
    bttn2 = 0;
    xAxis = 0;
    yAxis = 0;

    // set pin mode for FALLING interrupt - listen for console request
    pinMode(pin, INPUT);
}

void loop() {
    // Buffer next command
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

void writeSeq() {
    // communicate command in seq to the console
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
    // set seq to be the next command in the queue
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

    // default buttons to queue are an empty command
    bttn1 = 0;
    bttn2 = 0;
    xAxis = 0;
    yAxis = 0;

    sentLast = true;
}

void pressButton(int button) {
    // set analog button values in seq
    seq[button * 4 + 1] = true;
    seq[button * 4 + 2] = true;
}

void setAxis(int axis, int8_t val) {
    // set joystiq values in seq
    for (int i=0 ; i<8 ; i++) {
        bool bit = (1<<(7-i)) & val;
        if (bit) {
            pressButton(axis + i);
        }
    }
}

void resetSeq() {
    // set all seq values to controller input with no button presses
    for (int i=0 ; i<SEQLEN ; i++) {
        seq[i] = emptyAction[i];
    }
}
