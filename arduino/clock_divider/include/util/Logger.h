//
// Created by zack on 9/6/23.
//

#ifndef CLOCK_DIVIDER_LOGGER_H
#define CLOCK_DIVIDER_LOGGER_H
#include <Arduino.h>

class Logger {
public:
    void info(const int value, const char label[] = "[INFO]" ) {
        Serial.print(label);
        Serial.print(": ");
        Serial.println(value);
    }

    void info(const char value[], const char label[] = "[INFO]" ) {
        Serial.print(label);
        Serial.print(": ");
        Serial.println(value);
    }

    void info(const char value, const char label[] = "[INFO]" ) {
        Serial.print(label);
        Serial.print(": ");
        Serial.println(value);
    }
};


#endif //CLOCK_DIVIDER_LOGGER_H
