//
// Created by zack on 9/13/23.
//

#ifndef CLOCK_DIVIDER_JACKS_H
#define CLOCK_DIVIDER_JACKS_H
#include <Arduino.h>
#include "state/Divider.h"



/*
 * this class just represents the 4 output jacks at the top of the device
 * it keeps the alignment of both the arrays and the buttons
 */
class Jacks {
public:
    static const int numJacks = 4;
    const int jackIndexesToPins[numJacks] = {8,9,10,11};
    void setup() {
        for(int jackIndexesToPin : jackIndexesToPins) {
            pinMode(jackIndexesToPin, OUTPUT);
            digitalWrite(jackIndexesToPin, LOW);
        }
        digitalWrite(11, LOW);
    }

    void setDivision(int jackIndex, int division) {
        dividers[jackIndex].setDivision(division);
    }

    void pulse(int jackIndex) {
        if(!dividers[jackIndex].tick()) { return; }
        int pin = jackIndexesToPins[jackIndex];
        if (pin < 8 || pin >= 12) {
            return;  // Invalid index
        }
        jackStates[jackIndex] = !jackStates[jackIndex];
        digitalWrite(pin, jackStates[jackIndex]);
    }

    void hardwareTest() {
        for(int i = 0; i < 4; i++) {
            pulse(i);
            delay(100);
            pulse(i);
            delay(100);
        }
    }
private:
    int jackStates[numJacks] = {LOW,LOW,LOW, LOW};
    Divider dividers[numJacks];

};
#endif //CLOCK_DIVIDER_JACKS_H
