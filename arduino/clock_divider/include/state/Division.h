//
// Created by zack on 9/15/23.
//

#ifndef CLOCK_DIVIDER_DIVISION_H
#define CLOCK_DIVIDER_DIVISION_H

const int maxDivision = 8;
const char* divisions[] = {
        "one",
        "Two",
        "Three",
        "Four",
        "Five",
        "Six",
        "Seven",
        "Eight",
};
const int divs[8] = {1,2,3,4,5,6,7,8};

class Division {
    int counter = 0;
    int divIndex = 0;

public:
    const char* incrementDiv() {
        divIndex = (divIndex + 1) % maxDivision;
        return divisions[divIndex];
    }

    int tick() {
        int tick = 0;
        if (counter % divs[divIndex] == 0) {
            tick = 1;
        }
        counter = (counter + 1) % maxDivision;
        return tick;
    }

    void resetState() {
        counter = 0;
    }
};


#endif //CLOCK_DIVIDER_DIVISION_H
