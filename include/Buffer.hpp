#pragma once
#include "constants.hpp"

class Buffer {
public:
    static const int MAX = 32;

    Buffer(int division = 2, int length = 2) : division(division), length(length) {
        for(int i = 0; i < MAX; i++) {
            data[i] = defaultData[i];
        }
    }

    bool pulsing() {
        return getCurrentElement() == ON;
    }

    int getCurrentElement() const {
        return data[currentIndex];
    }

    int getElementAt(int index) {
        return data[index];
    }

    void iterate() {
        currentIndex = (currentIndex + 1) % length;
    }

    void setCurrentPulse(int pulseState) {
        data[currentIndex] = pulseState;
    }

    /*! nudge the backwards index n steps backwards, it wraps */
    int backwardIterate(int steps) {
        for (int count = 0; count < steps; ++count) {
            currentIndex = (currentIndex - 1 + length) % length;
        }
        return currentIndex;
    }

    /*! ----- Getters and Setters ----- */

    int* getData() {
        return data;
    }

    void setData(int index, int newValue) {
        data[index] = newValue;
    }

    int getCurrentIndex() const {
        return currentIndex;
    }

    int getLength() {
        return length;
    }

    void changeDivision(int div) {

    }

private:
    int defaultData[MAX] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int data[MAX] = {0};
    int currentIndex = 0;
    int length = 2;
    int division;
};
