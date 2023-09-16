//
// Created by zack on 9/15/23.
//

#ifndef CLOCK_DIVIDER_DIVISION_H
#define CLOCK_DIVIDER_DIVISION_H


class Division {
    int counter = 0;
    int counterMax = 0;
public:
    void setDivision(int division) {
        counterMax = division;
    }

    Division() { counterMax = 4; }

    int tick() {
        int tick = 0;
        if (counter % counterMax == 0) {
            tick = 1;
        }
        counter = (counter + 1) % counterMax;
        return tick;
    }
};


#endif //CLOCK_DIVIDER_DIVISION_H
