#pragma once

class Buffer {
public:
    static const int SIZE = 16;

    int getCurrentElement() const {
        return data[currentIndex];
    }

    int getElementAt(int index) {
        return data[index];
    }

    void iterate(int pulse) {
        currentIndex = (currentIndex + 1) % SIZE;
        data[currentIndex] = pulse;
    }

    /*! nudge the backwards index n steps backwards, it wraps */
    int backwardIterate(int steps) {
        int i = backwardsIndex;
        for (int count = 0; count < steps; ++count) {
            /*! modulo always returns the 0 if left of operand is evenly divisible by right side otherwise it returns
                the remainder 15 % 5 = 0 but 15 % 6 is 3. This allows us to create a boundary around any incrementally
                bumped numbers. Because, every time you increment until you hit a multiple of 5, like 25 30 etc, you go
                back to 0.
                1 % 5 == 1
                2 % 5 == 2
                3 % 5 == 3
                4 % 5 == 4
                5 % 5 == 0
                6 % 5 == 1
                7 % 5 == 2
                8 % 5 == 3
                9 % 5 == 4
                10 % 5 == 0
                ... and then back to 1 until we hit 4 and then 0
             */
            i = (i - 1 + SIZE) % SIZE;
        }
        backwardsIndex = i;
        return i;
    }

    /*! ----- Getters and Setters ----- */

    int (&getData())[SIZE] {
        return data;
    }

    void setData(int index, int newValue) {
        data[index] = newValue;
    }

    int getCurrentIndex() const {
        return currentIndex;
    }

    int getBackWardsIndex() const {
        return backwardsIndex;
    }

private:
    int data[SIZE]{0};
    int currentIndex = 0;
    int backwardsIndex = 0;
};
