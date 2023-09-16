//
// Created by zack on 9/16/23.
//

#ifndef CLOCK_DIVIDER_BUTTONS_H
#define CLOCK_DIVIDER_BUTTONS_H
#include <Arduino.h>

const int pins[4] = {7,6,5,13};
const int numButtons = 4;
struct Button {
    int pressed = 0;
    int pin;
public:
    Button(int pin) : pin(pin) {}

    int isPressed() {
        return pressed;
    }

    void togglePressed() {
        pressed = !pressed;
    }

    void updateState() {
        pressed = digitalRead(pin);
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

    Button* getButtons() {
        return buttons;
    }

    void updateStates() {
        for(Button button : buttons) {
            button.updateState();
        }
    }

};

#endif //CLOCK_DIVIDER_BUTTONS_H
