#pragma once

#include "Buffer.hpp"
#include "constants.hpp"

/*! Division is the data class representing the pulse frequency of a clock output. */
class Division {
public:
    Division() : divisor(2) {}
    Division(int divisor) : divisor(divisor) {}

    Buffer buffer;
    unsigned int divisor;
//    unsigned int pulsing = 0;

    int findLastPulse() {
        buffer.resetBackwardsIndex();
        bool pulseFound = false;
        int tries = buffer.size;
        while (!pulseFound && tries) {
            int iterateIndex = buffer.backwardIterate(1);
            int pulse = buffer.getElementAt(iterateIndex);
            tries--;
            if (pulse) {
                pulseFound = true;
                break;
            }
        }

        return buffer.getBackWardsIndex();
    }

    int calcDistanceFromOneBufferIndexToOther(int subtrahend, int minuend, int size) {
        int distance;
        if(subtrahend > minuend) {
            distance = subtrahend - minuend;
        } else {
            int x = size - minuend;
            distance = x + subtrahend;
        }
        return distance;

//        if (distance < 0) { distance = distance * -1; }
//        return distance;
    }

    /*!   */
    void evaluate() {
        /*!
         move 1 place forward through the buffer
         find the index at which the closest ON pulse exists if we traverse backwards through the buffer

         */
        int pulsing = OFF;
        buffer.setData(buffer.getCurrentIndex(), OFF);
        buffer.iterate();
        int pulseIndex = findLastPulse();
        if(buffer.getCurrentElement() == ON) {
            pulsing = ON;
            buffer.setCurrentPulse(pulsing);
            return;
        } else if (calcDistanceFromOneBufferIndexToOther(buffer.getCurrentIndex(), pulseIndex, buffer.size) == divisor) {
            pulsing = ON;
        }
        buffer.setCurrentPulse(pulsing);
    }
};
