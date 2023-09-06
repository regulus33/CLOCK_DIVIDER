 TODO: redo this with WORKING code in main.cpp

//
// Created by zack on 9/3/23.
//

#ifndef CLOCK_DIVIDER_OLEDDISPLAYSERVICE_H
#define CLOCK_DIVIDER_OLEDDISPLAYSERVICE_H


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SH1106_I2C_ADDRESS 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO


class OledDisplayService {
private:

    Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
public:
    // Initialize display
    bool begin() {
        if (!display.begin(SH1106_I2C_ADDRESS)) {
            return false;
        }
        display.display();  // Show splash screen (optional)
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        return true;
    }

    // Display text at a specific position
    void displayText(const char *text, int x, int y) {
        display.setCursor(x, y);
        display.print(text);
        display.display();
    }

    // Display an integer value at a specific position
    void displayInt(int value, int x, int y) {
        display.setCursor(x, y);
        display.print(value);
        display.display();
    }

    // Display BPM at a specific position
    void displayBPM(int bpm, int x, int y) {
        display.setCursor(x, y);
        display.print("BPM: ");
        display.print(bpm);
        display.display();
    }

    // Clear display
    void clear() {
        display.clearDisplay();
    }
};


#endif //CLOCK_DIVIDER_OLEDDISPLAYSERVICE_H
