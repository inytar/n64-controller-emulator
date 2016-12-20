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
    n64Controller.write(1);
    delay(400);
}
