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

public:
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
        delay(100);
        green();
        delay(100);
        red();
        delay(100);
        kill();
        delay(100);
    }

    static unsigned int readEncoder(uint8_t encoderBits) {
        static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
        static uint8_t oldAB = 0;
        oldAB <<= 2;
        oldAB |= (encoderBits & 0x03);
        static uint8_t counter = 0;
        int8_t reading = enc_states[(oldAB & 0x0f)];

        if (reading) {
            counter += reading;
        }
        return counter;
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
