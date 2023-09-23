//
// Created by zack on 9/6/23.
//

#ifndef CLOCK_DIVIDER_ILLUMINATEDENCODER_H
#define CLOCK_DIVIDER_ILLUMINATEDENCODER_H
#define GREEN 2
#define RED 3
#define BUTTON 4
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC

#include "util/Macros.h"
#include <Arduino.h>

struct IlluminatedEncoder {
    int beRed = 0;
public:
    void blink() {
        if (beRed) {
            red();
            beRed = !beRed;
        } else {
            green();
            beRed = !beRed;
        }
    }

    void setup() {
        initEncoder();
        initLED();
    }

    void red() {
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, LOW);
    }

    void green() {
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, HIGH);
    }

    void yellow() {
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, HIGH);
    }

    void kill() {
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
    }

    /* ! in a perfect world this would be enforced by an interface. But we want to be fast */
    void hardWareTest() {
        yellow();
        delay(1);
        green();
        delay(1);
        red();
        delay(1);
        kill();
        delay(1);
    }

    int readEncoder() {
        return analogRead(A0);
    }

private:
    void initLED() {
        pinMode(RED, OUTPUT);
        pinMode(GREEN, OUTPUT);
        pinMode(BUTTON, INPUT);
    }

    void initEncoder() {
        pinMode(ENC_A, INPUT);
        digitalWrite(ENC_A, HIGH);
        pinMode(ENC_B, INPUT);
        digitalWrite(ENC_B, HIGH);
    }
};

#endif //CLOCK_DIVIDER_ILLUMINATEDENCODER_H
