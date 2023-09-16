#include <Arduino.h>
#include "physical/IlluminatedEncoder.h"
#include "physical/OledDisplay.h"
#include "util/Macros.h"
#include "physical/Jacks.h"
#include "state/Divider.h"

IlluminatedEncoder encoder;
OledDisplay display;
Jacks jacks;

volatile int encoderValue = 0;  // we don't init wuith these, they are just to bust cache and read encoder.
volatile int lastEncoderValue = 1;

void startupAnimate() {
    encoder.hardWareTest();
    display.hardwareTest();
    jacks.hardwareTest();
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
    jacks.setup();
    startupAnimate();
    initTimerInterrupt();

#ifdef DEBUG
    Serial.begin(115200);
#endif
}

bool readAndPrintEncoderValue() {
    encoderValue = encoder.readEncoder();
    bool valueChanged = lastEncoderValue != encoderValue;
    if(valueChanged) {
        display.printLine(encoderValue);
    }
    lastEncoderValue = encoderValue;
    return valueChanged;
}

void loop() {
    bool valueChanged = readAndPrintEncoderValue();
    if(valueChanged) {
//        OCR1A = map(encoderValue, 0, 255, 15624, 0); //0 is faster
        OCR1A = map(encoderValue, 0, 255, 500, 0);
    }
}

ISR(TIMER1_COMPA_vect) {
   encoder.blink();
   for(int i = 0; i < Jacks::numJacks; i++) {
       jacks.pulse(i);
   }
}