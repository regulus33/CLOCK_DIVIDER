#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>
#include "EncoderKnobService.h"

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define POT_PIN A0
#define A_CLOCK 5
#define B_CLOCK 2
#define C_CLOCK 3
#define A_PUSH_BUTTON 7
#define B_PUSH_BUTTON 11
#define C_PUSH_BUTTON 12

// initialize the pushbutton pins as inputs with pull-up resistors:
// pinMode(A_PUSH_BUTTON, INPUT_PULLUP);
// pinMode(B_PUSH_BUTTON, INPUT_PULLUP);
// pinMode(C_PUSH_BUTTON, INPUT_PULLUP);

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
#define PUSH_BUTTON_LED 10

// CLASSES TODO: abstract us out of this file please
//
//
//
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
EncoderKnobService encoderKnobService;

//// END CLASSES




/*! vars TODO: fix me, no global vars please */
volatile unsigned long ticks = 0;

void initDisplay() {
    Serial.begin(9600);
    display.begin(i2c_Address, true); // Address 0x3C default
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
    delay(250); // wait for the OLED to power up
}

void printNumber(long number) {
    display.clearDisplay(); // clear the display first
    display.setCursor(25, 25); // reset cursor position
    display.print(number);
    display.display();
}

void initTimerInterrupts() {
    noInterrupts(); // We need to disable them first i guess?
    TCCR1A = 0;
    TCCR1B = 0;
    // Set compare match register to desired timer count
    // (16,000,000 / (prescaler * desired interrupt frequency))
    OCR1A = 15624;            // Compare match register for 1Hz output
    // Enable Timer1 interrupt
    TIMSK1 |= (1 << OCIE1A);  // Enable timer compare interrupt
    // Initialize Timer1
    // WGM12 = CTC Mode, CS12 = 256 prescaler
    TCCR1B |= (1 << WGM12) | (1 << CS12);
    interrupts();             // Enable all interrupts
}

void setup() {
    // Literal push buttons
//    pinMode(A_PUSH_BUTTON, INPUT_PULLUP);
//    pinMode(B_PUSH_BUTTON, INPUT_PULLUP);
//    pinMode(C_PUSH_BUTTON, INPUT_PULLUP);

    // Display stuff
    initDisplay();
    display.display();
}

ISR(TIMER1_COMPA_vect) {
    // This ISR is called every second
    ticks++;
//    int tickss = ticks;
//    Serial.println(ticks);
//    printNumber(tickss);
}



void loop() {
//    if(encoderKnobService.valueChanged()) {
//        Serial.println(encoderKnobService.getCurrentPosition());
//        printNumber(encoderKnobService.getCurrentPosition());
//    }
    printNumber(encoderKnobService.getCurrentPosition());
}
