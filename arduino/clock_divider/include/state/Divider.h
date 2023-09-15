//
// Created by zack on 9/15/23.
//

#ifndef CLOCK_DIVIDER_DIVIDER_H
#define CLOCK_DIVIDER_DIVIDER_H


class Divider {
public:
    int counter = 0;
    int counterMax = 3;

    Divider(int division) { counterMax = division; }

    int tick() {
        int tick = 0;
        if (counter % counterMax == 0) {
            tick = 1;
        }
        counter = (counter + 1) % counterMax;
        return tick;
    }
};


#endif //CLOCK_DIVIDER_DIVIDER_H
