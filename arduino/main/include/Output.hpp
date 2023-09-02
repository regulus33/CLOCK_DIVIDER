#ifndef CLAWK_CLAWK_OUTPUT_HPP
#define CLAWK_CLAWK_OUTPUT_HPP
#include "Buffer.hpp"
typedef void (*OnPulse)();

class Output {
private:
    static const int DEFAULT_DIVISION = 2;
public:
    Buffer* buffer = nullptr;
    Output() {
        buffer = new Buffer(2);
    }
    ~Output() { delete buffer; }

    OnPulse onPulse = nullptr;

    bool progress() {
        bool pulsing = buffer->pulsing();
        if (onPulse != nullptr && pulsing) {
            onPulse();
        }
        buffer->iterate();
        return pulsing;
    }

    void changeDivision(int division) {
        buffer->changeDivision(division);
    }
};

#endif
