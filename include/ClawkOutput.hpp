#ifndef CLAWK_CLAWK_OUTPUT_HPP
#define CLAWK_CLAWK_OUTPUT_HPP

typedef void (*OnPulse)();

class ClawkOutput {
private:
    static const int DEFAULT_DIVISION = 2;
public:
    Buffer* buffer = nullptr;
    ClawkOutput() {
        buffer = new Buffer(2);
    }
    ~ClawkOutput() { delete buffer; }
//    ClawkOutput(Buffer* buffer) : buffer(buffer) {}

    OnPulse onPulse = nullptr;

    bool progress() {
        bool pulsing = buffer->pulsing();
        if (onPulse != nullptr && buffer->pulsing()) {
            onPulse();
        }
        buffer->iterate();
        return pulsing;
    }
};

#endif
