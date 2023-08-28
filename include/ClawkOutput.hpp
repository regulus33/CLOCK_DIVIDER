#pragma once

#include "Division.hpp"

typedef void (*OnPulse)();

class ClawkOutput {
private:
    int pulseState = 0;
public:
    Division division;
    /* Timer interrupt -> Clawk.tick() */
    /* Arduino pins -> ClawkOutput.pulse() */
    ClawkOutput() : division(Division(2)) {}
    ClawkOutput(Division &division) : division(division) {}

    OnPulse onPulse = nullptr;

    void pulse(unsigned int pulsing) {
        if (onPulse != nullptr && pulsing) {  // Check if onPulse is not nullptr
            onPulse();
        }
    }
};
