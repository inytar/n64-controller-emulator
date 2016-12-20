#include "N64Controller.h"

elapsedMicros inputStart;

N64Controller::N64Controller(int pin) {
    _pin = pin;
}


void N64Controller::init() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    // Set pin interupt
}

void N64Controller::write1(unsigned startTime) {
    /* Serial.print('1'); */
    digitalWriteFast(_pin, LOW);
    int i = 0;
    while (i < 5000) {
        i++;
    }
    digitalWriteFast(_pin, HIGH);
    delayMicroseconds(2);
    i = 0;
    while (i < 500) {
        i++;
    }
}

void N64Controller::write0(unsigned startTime) {
    /* Serial.print('0'); */
    digitalWriteFast(_pin, LOW);
    delayMicroseconds(2);
    int i = 0;
    while (i < 500) {
        i++;
    }
    digitalWriteFast(_pin, HIGH);
    i = 0;
    while (i < 500) {
        i++;
    }
}

void N64Controller::writeStop(unsigned startTime) {
    /* Serial.println(); */
    while (inputStart < startTime) {
    }
    digitalWriteFast(_pin, LOW);
    while (inputStart < (startTime + 2)) {
    }
    digitalWriteFast(_pin, HIGH);
    /* pinMode(_pin, INPUT); */
}

/* void N64Controller::write(uint32_t input) { */
/*     for (int _ = 0; _ < 32; _++) { */
/*         if (input & (1<<31)) { */
/*             write1(); */
/*         } else { */
/*             write0(); */
/*        } */
/*         input <<= 1; */
/*     } */
/*     writeStop(); */
/* } */

/* void N64Controller::write2(uint32_t input) { */
/*     for (int i = 31; i > 0; i--) { */
/*         if (input & (1<<i)) { */
/*             write1(); */
/*         } else { */
/*             write0(); */
/*        } */
/*     } */
/*     writeStop(); */
/* } */

/* void N64Controller::write3(bool input[32]) { */
/*     for (int i = 0; i < 32; i++) { */
/*         if (input[i]) { */
/*             write1(); */
/*         } else { */
/*             write0(); */
/*        } */
/*     } */
/*     writeStop(); */
/* } */

void N64Controller::testLoop() {
    inputStart = 0;
    write0(4);
    write1(8);
    write0(12);
    write1(16);
}

void N64Controller::writenoloop2(uint32_t input) {
    inputStart = 0;
    if (input & (1<<31)) {
        write1(0);
    } else {
        write0(0);
    }
    if (input & (1<<30)) {
        write1(4);
    } else {
        write0(4);
    }
    if (input & (1<<29)) {
        write1(8);
    } else {
        write0(8);
    }
    if (input & (1<<28)) {
        write1(12);
    } else {
        write0(12);
    }
    if (input & (1<<27)) {
        write1(16);
    } else {
        write0(16);
    }
    if (input & (1<<26)) {
        write1(20);
    } else {
        write0(20);
    }
    if (input & (1<<25)) {
        write1(24);
    } else {
        write0(24);
    }
    if (input & (1<<24)) {
        write1(28);
    } else {
        write0(28);
    }
    if (input & (1<<23)) {
        write1(32);
    } else {
        write0(32);
    }
    if (input & (1<<22)) {
        write1(36);
    } else {
        write0(36);
    }
    if (input & (1<<21)) {
        write1(40);
    } else {
        write0(40);
    }
    if (input & (1<<20)) {
        write1(44);
    } else {
        write0(44);
    }
    if (input & (1<<19)) {
        write1(48);
    } else {
        write0(48);
    }
    if (input & (1<<18)) {
        write1(52);
    } else {
        write0(52);
    }
    if (input & (1<<17)) {
        write1(56);
    } else {
        write0(56);
    }
    if (input & (1<<16)) {
        write1(60);
    } else {
        write0(60);
    }
    if (input & (1<<15)) {
        write1(64);
    } else {
        write0(64);
    }
    if (input & (1<<14)) {
        write1(68);
    } else {
        write0(68);
    }
    if (input & (1<<13)) {
        write1(72);
    } else {
        write0(72);
    }
    if (input & (1<<12)) {
        write1(76);
    } else {
        write0(76);
    }
    if (input & (1<<11)) {
        write1(80);
    } else {
        write0(80);
    }
    if (input & (1<<10)) {
        write1(84);
    } else {
        write0(84);
    }
    if (input & (1<<9)) {
        write1(88);
    } else {
        write0(88);
    }
    if (input & (1<<8)) {
        write1(92);
    } else {
        write0(92);
    }
    if (input & (1<<7)) {
        write1(96);
    } else {
        write0(96);
    }
    if (input & (1<<6)) {
        write1(100);
    } else {
        write0(100);
    }
    if (input & (1<<5)) {
        write1(104);
    } else {
        write0(104);
    }
    if (input & (1<<4)) {
        write1(108);
    } else {
        write0(108);
    }
    if (input & (1<<3)) {
        write1(112);
    } else {
        write0(112);
    }
    if (input & (1<<2)) {
        write1(116);
    } else {
        write0(116);
    }
    if (input & (1<<1)) {
        write1(120);
    } else {
        write0(120);
    }
    if (input & (1<<0)) {
        write1(124);
    } else {
        write0(124);
    }
    writeStop(128);
}

void N64Controller::writenoloop3(bool input[32]) {
    inputStart = 0;
    if (input[0]) {
        write1(0);
    } else {
        write0(0);
    }
    if (input[1]) {
        write1(4);
    } else {
        write0(4);
    }
    if (input[2]) {
        write1(8);
    } else {
        write0(8);
    }
    if (input[3]) {
        write1(12);
    } else {
        write0(12);
    }
    if (input[4]) {
        write1(16);
    } else {
        write0(16);
    }
    if (input[5]) {
        write1(20);
    } else {
        write0(20);
    }
    if (input[6]) {
        write1(24);
    } else {
        write0(24);
    }
    if (input[7]) {
        write1(28);
    } else {
        write0(28);
    }
    if (input[8]) {
        write1(32);
    } else {
        write0(32);
    }
    if (input[9]) {
        write1(36);
    } else {
        write0(36);
    }
    if (input[10]) {
        write1(40);
    } else {
        write0(40);
    }
    if (input[11]) {
        write1(44);
    } else {
        write0(44);
    }
    if (input[12]) {
        write1(48);
    } else {
        write0(48);
    }
    if (input[13]) {
        write1(52);
    } else {
        write0(52);
    }
    if (input[14]) {
        write1(56);
    } else {
        write0(56);
    }
    if (input[15]) {
        write1(60);
    } else {
        write0(60);
    }
    if (input[16]) {
        write1(64);
    } else {
        write0(64);
    }
    if (input[17]) {
        write1(68);
    } else {
        write0(68);
    }
    if (input[18]) {
        write1(72);
    } else {
        write0(72);
    }
    if (input[19]) {
        write1(76);
    } else {
        write0(76);
    }
    if (input[20]) {
        write1(80);
    } else {
        write0(80);
    }
    if (input[21]) {
        write1(84);
    } else {
        write0(84);
    }
    if (input[22]) {
        write1(88);
    } else {
        write0(88);
    }
    if (input[23]) {
        write1(92);
    } else {
        write0(92);
    }
    if (input[24]) {
        write1(96);
    } else {
        write0(96);
    }
    if (input[25]) {
        write1(100);
    } else {
        write0(100);
    }
    if (input[26]) {
        write1(104);
    } else {
        write0(104);
    }
    if (input[27]) {
        write1(108);
    } else {
        write0(108);
    }
    if (input[28]) {
        write1(112);
    } else {
        write0(112);
    }
    if (input[29]) {
        write1(116);
    } else {
        write0(116);
    }
    if (input[30]) {
        write1(120);
    } else {
        write0(120);
    }
    if (input[31]) {
        write1(124);
    } else {
        write0(124);
    }
    writeStop(128);
}
