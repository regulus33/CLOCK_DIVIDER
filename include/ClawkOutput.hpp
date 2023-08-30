#pragma once

typedef void (*OnPulse)();

class ClawkOutput {
private:
    static const int DEFAULT_DIVISION = 2;
public:
    Buffer* buffer = nullptr;
    ClawkOutput() {
        buffer = new Buffer(2,2);
    }
    ~ClawkOutput() { delete buffer; }
//    ClawkOutput(Buffer* buffer) : buffer(buffer) {}

    OnPulse onPulse = nullptr;

    void progress() {
        if (onPulse != nullptr && buffer->pulsing()) {
            onPulse();
        }
        buffer->iterate();
    }
};
