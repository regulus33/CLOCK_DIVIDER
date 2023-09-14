//
// Created by zack on 9/6/23.
//

#ifndef CLOCK_DIVIDER_ARDUINOPROGRAM_H
#define CLOCK_DIVIDER_ARDUINOPROGRAM_H
#include <Arduino.h>
#include "physical/IlluminatedEncoder.h"
class Program {
private:
    uint8_t encoderValue{};
    IlluminatedEncoder* encoder;
public:
    void setEncoder(IlluminatedEncoder* encPtr) {
        encoder = encPtr;
    }

    void updateProgramState() {
        encoderValue = IlluminatedEncoder::readEncoder();
    }

    uint8_t getEncoderValue() const {
        return  encoderValue;
    }
};



#endif //CLOCK_DIVIDER_ARDUINOPROGRAM_H
