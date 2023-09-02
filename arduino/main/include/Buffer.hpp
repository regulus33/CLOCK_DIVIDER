#ifndef CLAWK_BUFFER_HPP
#define CLAWK_BUFFER_HPP
#include "constants.hpp"

class Buffer {
public:
    static const int MAX = 128;

    Buffer(int length = 2) : length(length) {
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
        length = div;
        currentIndex = 0;
    }

    int getDivision() {
        return length;
    }

private:
    int defaultData[MAX] = {1};
    int data[MAX] = {0};
    int currentIndex = 0;
    int length = 2;
};

#endif //CLAWK_BUFFER_HPP
