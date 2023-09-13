//
// Created by zack on 9/13/23.
//

#ifndef CLOCK_DIVIDER_JACKS_H
#define CLOCK_DIVIDER_JACKS_H
#include <Arduino.h>
static const int jackPins[] = {8, 9, 10, 11};  // Pins for the jacks, corresponding to D8, D9, D10, D11
static const int numJacks = 4;  // Number of jacks
class Jacks {
public:
    static void setup() {
        for (int i = 0; i < numJacks; ++i) {
            pinMode(jackPins[i], OUTPUT);
            digitalWrite(jackPins[i], HIGH);  // Initialize the pin as LOW
        }
    }

   static void pulse(int jackIndex, bool up = true) {
        if (jackIndex < 0 || jackIndex >= numJacks) {
            return;  // Invalid index
        }

        int pin = jackPins[jackIndex];  // Get the pin corresponding to the index
        int intensity = up ? HIGH : LOW;
        digitalWrite(pin, intensity);
    }

    static void hardwareTest() {
        for(int i = 0; i < numJacks; i++) {
            pulse(jackPins[i]);
            delay(100);
            pulse(jackPins[i], false);
            delay(100);
        }
    }

};
#endif //CLOCK_DIVIDER_JACKS_H
