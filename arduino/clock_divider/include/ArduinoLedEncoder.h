//
// Created by zack on 9/6/23.
//

#ifndef CLOCK_DIVIDER_ARDUINOLEDENCODER_H
#define CLOCK_DIVIDER_ARDUINOLEDENCODER_H

#include <Arduino.h>

struct ArduinoLedEncoder {
#define GREEN 2
#define RED 3
#define BUTTON 4
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC
#define MAX_CYCLE = 255
// TODO: using var infinite and read_encoder, find a way to stop moving the num upwards until you start turning dial reverse

private:
    bool infinte = true;

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

    /*! Used for testing, don't use this in production */
    void colorCycle() {
        yellow();
        delay(100);
        green();
        delay(100);
        red();
        delay(100);
        kill();
        delay(100);
    }

    static unsigned int read_encoder() {
        static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
        static uint8_t old_AB = 0;
        old_AB <<= 2;
        /*!
         * on encport register, perform a bitwise AND with 0x03 (which is 0000 0011 in binary).
         * Isolates the bits that represent A0 and A1
         */

        old_AB |= (ENC_PORT & 0x03);
        static uint8_t counter = 0;
        int8_t tmpdata = enc_states[(old_AB & 0x0f)];

        if (tmpdata) {
            Serial.print("Counter: ");
            Serial.println(counter, DEC);
            counter += tmpdata;
        }

        return counter;
    }
};

#endif //CLOCK_DIVIDER_ARDUINOLEDENCODER_H
