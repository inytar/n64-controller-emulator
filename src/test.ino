#include <Arduino.h>

#include "N64Controller.h"

const int pin = 12;

N64Controller n64Controller(pin);

void setup() {
    n64Controller.init();
    Serial.begin(9600);
    delay(3000);
}

void loop() {
    bool arr[32] = {false};
    arr[31] = true;
    n64Controller.testLoop();
    delay(100);
    /* n64Controller.writenoloop2(1); */
    /* delay(30); */
    /* n64Controller.writenoloop2(9); */
    /* delay(40); */
    /* n64Controller.writenoloop3(arr); */
    /* delay(50); */
}
