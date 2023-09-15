#include <Arduino.h>
#include "physical/IlluminatedEncoder.h"
#include "physical/OledDisplay.h"
#include "util/Macros.h"
#include "physical/Jacks.h"
#include "state/Divider.h"

IlluminatedEncoder encoder;
OledDisplay display;
Jacks jacks;

volatile int encoderValue = 0;  // Your encoder value will go here.
volatile int lastEncoderValue = 255;
int counter = 0;
int counterMax = 3;

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

void readAndPrintEncoderValue() {
    encoderValue = encoder.readEncoder();
    if( lastEncoderValue != encoderValue) {
        display.printLine(encoderValue);
    }
    lastEncoderValue = encoderValue;
    counter = (counter + 1) % counterMax;
}

void loop() {

    readAndPrintEncoderValue();

    OCR1A = map(encoderValue, 0, 255, 15624, 0); // change limits according to your needs

}


ISR(TIMER1_COMPA_vect) {
   encoder.blink();
   for(int i = 0; i < Jacks::numJacks; i++) {
       jacks.pulse(i);
   }
}