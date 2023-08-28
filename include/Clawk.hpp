#pragma once

#include "ClawkOutput.hpp"
#include "Division.hpp"

/* Master orchestrator for clock divider. Connects Divisions to Buffers to Clock Outputs */
class Clawk {
public:
    static const int MAX_OUTPUTS = 7;
    Division divisions[MAX_OUTPUTS];
    ClawkOutput outputs[MAX_OUTPUTS];

    Clawk() {
        for (int i = 0; i < MAX_OUTPUTS; i++) {
            divisions[i] = Division(2);
            outputs[i] = ClawkOutput(divisions[i]);
        }
    }

    bool tick() {
        for (int i = 0; i < MAX_OUTPUTS; i++) {
            divisions[i].evaluate();
            outputs[i].pulse(divisions[i].pulsing);
        }

        return true;
    }


};
