//
// Created by zack on 9/16/23.
//

#ifndef CLOCK_DIVIDER_BUTTONS_H
#define CLOCK_DIVIDER_BUTTONS_H
#include <Arduino.h>

const int pins[4] = {7,6,5,12};
const int numButtons = 4;

struct Button {
    int pressed = 1;
    int pin;
public:
    static int (*digitalReadPtr)(uint8_t);

    Button(int pin) : pin(pin) {}
    /*! NOTE: In arduino, the pushbutton is LOW when pressed and HIGH when left alone. */
    int isPressed() const {
        return !pressed;
    }

    void updateState() {
        pressed = digitalReadPtr(pin);
    }
};

class Buttons {
    Button buttons[4] = {Button(pins[0]), Button(pins[1]), Button(pins[2]), Button(pins[3])};

public:
    void setup() {
        for(int pin : pins) {
            pinMode(pin, INPUT_PULLUP);
        }
    }

    Button* getButtonsArray() {
        return buttons;
    }

    void updateStates() {
        /* Don't forget that range based loops copy the arrays unless you & ref */
        for(Button& button : buttons) {
            button.updateState();
        }
    }

};

#endif //CLOCK_DIVIDER_BUTTONS_H
