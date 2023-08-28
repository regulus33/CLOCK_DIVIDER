#pragma once

#include "Division.hpp"

typedef void (*OnPulse)();

class ClawkOutput {
private:
    static const int DEFAULT_DIVISION = 2;
public:
    Division division;
    ClawkOutput() : division(Division(DEFAULT_DIVISION)) {}
    ClawkOutput(Division &division) : division(division) {}

    OnPulse onPulse = nullptr;

    void pulse(unsigned int pulsing) {
        /*!
         * pulsing is 1 when we've passed enough clock signals to hit the division tied to this output
         * so we call the callback that we want to tick when we hit the division
         * */
        if (onPulse != nullptr && pulsing) {
            onPulse();
        }
    }
};
