//
// Created by zack on 9/3/23.
//

#ifndef CLOCK_DIVIDER_ENCODERKNOBSERVICE_H
#define CLOCK_DIVIDER_ENCODERKNOBSERVICE_H

#include <Arduino.h>
#include <Encoder.h>
// TODO: global config vars should really be in some kind of config file
#define ENCODER_PIN_LEFT 6
#define ENCODER_PIN_RIGHT 9

class EncoderKnobService {
private:
    Encoder encoder = Encoder(ENCODER_PIN_LEFT, ENCODER_PIN_RIGHT);
    long oldPosition = -999;
public:
    EncoderKnobService() {
        pinMode(ENCODER_PIN_LEFT, INPUT_PULLUP);
        pinMode(ENCODER_PIN_RIGHT, INPUT_PULLUP);
    }

    long getCurrentPosition() {
        long np = encoder.read();
        long newPosition = np / 4;
        if (newPosition != oldPosition) {
            oldPosition = newPosition;
        }
        return newPosition;
    }
};

#endif //CLOCK_DIVIDER_ENCODERKNOBSERVICE_H
