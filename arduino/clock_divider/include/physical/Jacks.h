//
// Created by zack on 9/13/23.
//

#ifndef CLOCK_DIVIDER_JACKS_H
#define CLOCK_DIVIDER_JACKS_H
#include <Arduino.h>
static const int numJacks = 4;  // Number of jacks
class Jacks {
public:
    static void setup() {
        pinMode(8, OUTPUT);
        pinMode(9, OUTPUT);
        pinMode(10, OUTPUT);
        pinMode(11, OUTPUT);
        // low
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
    }

   static void pulse(int pin, bool up = true) {
        if (pin < 8 || pin >= 12) {
            return;  // Invalid index
        }
        // Get the pin corresponding to the index
        int intensity = up ? HIGH : LOW;
        digitalWrite(pin, intensity);
    }

    static void hardwareTest() {
        for(int i = 8; i < 12; i++) {
            pulse(i);
            delay(100);
            pulse(i, false);
            delay(100);
        }
    }

};
#endif //CLOCK_DIVIDER_JACKS_H
