#include <Arduino.h>
#include "physical/IlluminatedEncoder.h"
#include "physical/OledDisplay.h"
#include "util/Macros.h"
#include "ArduinoBuffer.h"
#include "ArduinoClawk.h"
#include "ArduinoOutput.h"
#include "ArduinoConstants.h"
#include "state/Program.h"
#include "physical/Jacks.h"
#include "state/Divider.h"

Program program;
IlluminatedEncoder encoder;
OledDisplay display;
Divider divider1(1);
Divider divider2(2);
Divider divider3(3);
Divider divider4(4);


volatile int encoderValue = 0;  // Your encoder value will go here.
volatile bool toggle = false;
volatile int lastEncoderValue = 255;
int counter = 0;
int counterMax = 3;

void startupAnimate() {
    program.updateProgramState();
    encoder.hardWareTest();
    display.hardwareTest();
    Jacks::hardwareTest();
}



void setup() {
    display.setup();
    encoder.setup();
    Jacks::setup();


    // ==== Startup
    //    startupAnimate();
    // ==== Timer
    // Initialize Timer1 for a 1 Hz frequency
    // assuming a 16MHz clock
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12); // CTC mode
    OCR1A = 15624; // For 1 Hz at 16 MHz (1 pulse per second)
    TCCR1B |= (1 << CS10);  // No prescaling
    TCCR1B |= (1 << CS10) | (1 << CS12); // 1024 prescaler
    TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
    sei();
}
void loop() {
    encoderValue = IlluminatedEncoder::readEncoder();
    if( lastEncoderValue != encoderValue) {
        display.printLine(encoderValue);
    }
    lastEncoderValue = encoderValue;
    counter = (counter + 1) % counterMax;

    // Adjust these values to make the thing change frequency. if 0, on the right were 1000 for instance
    // the max speed would decrease significantly.
    OCR1A = map(encoderValue, 0, 255, 15624, 0); // change limits according to your needs
#ifdef DEBUG

#endif
}

ISR(TIMER1_COMPA_vect) {
    toggle = !toggle; // toggle state
    divider1.tick();
//    digitalWrite(TEST_PIN, toggle ? HIGH : LOW); // Generate the pulse
    if(toggle) {
        encoder.green();
    } else {
        encoder.red();
    }
}