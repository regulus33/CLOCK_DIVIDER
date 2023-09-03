#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>

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
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PUSH_BUTTON_LED 10


/* init timer */



void initDisplay() {
    display.begin(i2c_Address, true); // Address 0x3C default
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
}

void printNumber(int number) {
    display.clearDisplay(); // clear the display first
    display.setCursor(25, 25); // reset cursor position
    display.print(number);
    display.display();
}

void setup() {
    Serial.begin(9600);
    delay(250); // wait for the OLED to power up
    initDisplay();
    display.display();
    delay(2000);
    pinMode(PUSH_BUTTON_LED, OUTPUT);
}

void loop() {
    int m = millis();
    delay(333);
    printNumber(m);
}
