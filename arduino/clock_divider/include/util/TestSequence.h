//
// Created by zack on 9/12/23.
//

#ifndef CLOCK_DIVIDER_TESTSEQUENCE_H
#define CLOCK_DIVIDER_TESTSEQUENCE_H
#include "physical/IlluminatedEncoder.h"
#include "physical/OledDisplay.h"
class TestSequence {
public:
    static void run() {
        while(1 > 0) {
            IlluminatedEncoder encoder;
            OledDisplay display;

            display.setup();
            encoder.setup();

            encoder.hardWareTest();
            display.hardwareTest();
        }

    }
};

#endif //CLOCK_DIVIDER_TESTSEQUENCE_H
