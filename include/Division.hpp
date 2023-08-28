#pragma once

#include "Buffer.hpp"

/*! Division is the data class representing the pulse frequency of a clock output. */
class Division {
public:
    Division() : divisor(1) {}

    Division(int divisor) : divisor(divisor) {}

    static const int PULSE = 1;
    Buffer buffer = *(new Buffer());
    unsigned int divisor;
    unsigned int pulsing = 0;

    int findLastPulse() {
        bool pulseFound = false;
        int tries = Buffer::SIZE;
        while (!pulseFound && tries) {
            int iterateIndex = buffer.backwardIterate(1);
            int pulse = buffer.getElementAt(iterateIndex);
            if (pulse) { pulseFound = true; }
            tries--;
        }

        return tries;
    }

    int calcDistanceFromOneBufferIndexToOther(int subtrahend, int minuend, int size) {
        int distance = subtrahend - minuend;
        if (distance < 0) { distance = distance * -1; }
        return distance;
    }

    /*!   */
    void evaluate() {
        /*!
         * call findLastPulse() which returns the index of the pulse backwards from us
         * if the distance between last index and currentIndex == divisor-1, PULSE
         * otherwise 0
         */
        bool shouldPulse = false;
        int pulseIndex = findLastPulse();
        if (calcDistanceFromOneBufferIndexToOther(buffer.getCurrentIndex(), pulseIndex, Buffer::SIZE) == divisor - 1) {
            shouldPulse = true;
        }

        if (shouldPulse) { pulsing = pulsing ^ PULSE; }
        buffer.iterate(pulsing);
    }
};
