//
// Created by zack on 9/15/23.
//

#ifndef CLOCK_DIVIDER_DIVIDER_H
#define CLOCK_DIVIDER_DIVIDER_H

class Divider {
public:
    int counter;
    int counterMax = 8;
    int currentDivisionIndex = 0;
    const int divisions[8] = {1,2,3,4,5,6,7, 8};

    Divider(int division) {
        currentDivisionIndex = (division - 1);
    }
    bool tick() {
        int tick = false;
        if(counter % divisions[currentDivisionIndex] == 0) {
            tick = true;
        }
        counter = (counter + 1) % counterMax;
        return tick;
    }

};

#endif //CLOCK_DIVIDER_DIVIDER_H
