#include <Arduino.h>
#include "physical/IlluminatedEncoder.h"
#include "physical/OledDisplay.h"
#include "util/Macros.h"
#include "state/OutputManager.h"
#include "physical/Buttons.h"


IlluminatedEncoder encoder;
OledDisplay display;
OutputManager outputManager;
Buttons buttons;

/*
 * Set function pointer for digitalRead
 */
int (*Button::digitalReadPtr)(uint8_t) = digitalRead;

volatile int encoderValue = 0;  // we don't init with these, they are just to bust cache and read encoder.
volatile int lastEncoderValue = 1;

void startupAnimate() {
    encoder.hardWareTest();
    display.hardwareTest();
    outputManager.hardwareTest();
}


/* No idea how this works :) */
void initTimerInterrupt() {
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12); // CTC mode
    OCR1A = 15624; // For 1 Hz at 16 MHz (1 pulse per second)
    TCCR1B |= (1 << CS10);  // No prescaling
    TCCR1B |= (1 << CS10) | (1 << CS12); // 1024 prescaler
    TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
    sei(); // enables global interrupts
}

void setup() {
    display.setup();
    encoder.setup();
    outputManager.setup();
    buttons.setup();
    startupAnimate();
    initTimerInterrupt();
    Serial.begin(31250); // Standard MIDI Baud rate
#ifdef DEBUG
//    Serial.begin(115200);
#endif
}

bool readAndPrintEncoderValue() {
    encoderValue = encoder.readEncoder();
    bool valueChanged = lastEncoderValue != encoderValue;
    if (valueChanged) {
        display.printLine(encoderValue);
    }
    lastEncoderValue = encoderValue;
    return valueChanged;
}

void updateButtonStates() {
    buttons.updateStates();
}

void applyButtonStatesToDividers() {
    Button *buttonsArr = buttons.getButtonsArray();
    for (int i = 0; i < numButtons; i++) {
        bool pressed = buttonsArr[i].isPressed();
        if (pressed) {
            display.printLine(outputManager.incrementDivision(i));
            outputManager.resetState();
        }
    }
}

void loop() {
    updateButtonStates();
    applyButtonStatesToDividers();

    bool valueChanged = readAndPrintEncoderValue();
    if (valueChanged) {
        OCR1A = map(encoderValue, 0, 255, 1000, 0);
//        outputManager.resetState();
    }
}

ISR(TIMER1_COMPA_vect) {
    encoder.blink();
    Serial.write(0xF8);
    for (int i = 0; i < OutputManager::numJacks; i++) {
        Serial.write(0xF8); // Send the MIDI clock byte
        outputManager.pulse(i);
    }
}