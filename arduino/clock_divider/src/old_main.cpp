///*********************************************************************
//A beat is a quarter note. 60 bpm is 60 quarter notes in a minute or
//it is 1 quarter note in a second. A quarter note is not the clock, it
//is a function of the synchornization provided by the clock. So the
//question is, what the fuck is the clock then? Well, its just pulses
//firing off rapidly. A slow square wave. Different devices use different
//resolutions but the standard is 24 pulses per quarter note. To go back
//to our example of 60 bpm. 24 ppqn would generate a pulse 24 times per
//second.
//
//*********************************************************************/
//
//
//
//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SH110X.h>
//#include <MIDI.h>
//// TODO: this needs to be organized
//MIDI_CREATE_DEFAULT_INSTANCE();
//
///*!
//===============================SCREEN==================================================
//*/
//#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#define OLED_RESET -1   //   QT-PY / XIAO
//Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//#define POT_PIN A0
//#define A_CLOCK 5
//#define B_CLOCK 2
//#define C_CLOCK 3
//#define PUSH_BUTTON_LED 10
//#define A_PUSH_BUTTON 7
//#define B_PUSH_BUTTON 11
//#define C_PUSH_BUTTON 12
//
//int minBPM = 0;
//int maxBPM = 200;
//int bpm = 140;
//int lastPotValue = 0;
//int pushButtonDown = false;
//int ppqnsArray[] = {2, 4, 8, 12, 24, 48};
//const int ppqnIndicesMax = (sizeof(ppqnsArray) / sizeof(ppqnsArray[0]));
//int ppqnIndices[] = {0, 0, 0};
//bool clockStates[] = {false, false, false};
//unsigned long previousTime[] = {0, 0, 0};
//int lastButtonState[] = {HIGH, HIGH, HIGH};
///*! pushbuttons */
//int aPushState = HIGH;
//int bPushState = HIGH;
//int cPushState = HIGH;
///*! MIDI LIGHT */
//bool midiLight = false;
//
//void handlePushLED() {
//    if (pushButtonDown) {
//        digitalWrite(PUSH_BUTTON_LED, HIGH);
//    } else {
//        digitalWrite(PUSH_BUTTON_LED, LOW);
//    }
//}
//
//bool boolToDigitalPol(bool i) {
//    if (i) {
//        return HIGH;
//    }
//    return LOW;
//}
//
//void drawPPQN(int clockIndex) {
//    display.clearDisplay(); // clear the display first
//    display.setCursor(25, 25); // reset cursor position
//    int ppqn = ppqnsArray[ppqnIndices[clockIndex]];
//    display.print(ppqn);
//    display.print(" PPQN");
//    display.display(); // Update the display with all the above changes
//}
//
//void initDisplay() {
//    display.begin(i2c_Address, true); // Address 0x3C default
//// Clear the buffer.
//    display.clearDisplay();
//    display.setTextSize(2);
//    display.setTextColor(SH110X_WHITE);
//}
//
//void setupClockOutputs() {
//    pinMode(A_CLOCK, OUTPUT);
//    pinMode(B_CLOCK, OUTPUT);
//    pinMode(C_CLOCK, OUTPUT);
//}
//
//void updateClock(int clockPin, int clockIndex, unsigned long currentTime) {
//    int pulseCount = ppqnsArray[ppqnIndices[clockIndex]];
//    int beatTime = 60000 / bpm;
//    int pulseTime = (beatTime / pulseCount) / 2; // 2? TODO
//
//    if (currentTime - previousTime[clockIndex] >= pulseTime) {
//        if (clockPin == A_CLOCK) {
//            MIDI.sendRealTime(midi::Clock);
//            int lightState = !midiLight;
//            digitalWrite(3, lightState);
//        }
//        bool pol = boolToDigitalPol(!clockStates[clockIndex]);
//        clockStates[clockIndex] = !clockStates[clockIndex];
//        digitalWrite(clockPin, pol);
//        previousTime[clockIndex] = currentTime;
//    }
//}
//
//bool updatePushState(int &pushState, int clockIndex) {
//    if (pushState == LOW && lastButtonState[clockIndex] == HIGH) {
//
//        ppqnIndices[clockIndex] = (ppqnIndices[clockIndex] + 1) % ppqnIndicesMax;
//        drawPPQN(clockIndex);
//        return true;
//    }
//    return false;
//}
//
//void drawBPM() {
//    display.clearDisplay(); // clear the display first
//    display.setCursor(25, 25); // reset cursor position
//    display.print("BPM: ");
//    display.print(bpm);
//    display.display(); // Update the display with all the above changes
//}
//
//void updatePushStates() {
//    aPushState = digitalRead(A_PUSH_BUTTON);
//    bPushState = digitalRead(B_PUSH_BUTTON);
//    cPushState = digitalRead(C_PUSH_BUTTON);
//
//    bool a = updatePushState(aPushState, 0);
//    bool b = updatePushState(bPushState, 1);
//    bool c = updatePushState(cPushState, 2);
//
//    lastButtonState[0] = aPushState;
//    lastButtonState[1] = bPushState;
//    lastButtonState[2] = cPushState;
//
//    if (a || b || c) {
//        pushButtonDown = true;
//    } else {
//        pushButtonDown = false;
//    }
//}
//
//bool potChangedSignificantly(int newPotValue) {
//    int potDiff = lastPotValue - newPotValue;
//    int absPotDiff = abs(potDiff);
//    if ((absPotDiff > 5)) {
//        return true;
//    }
//    return false;
//}
//
//
//void setup() {
////    Serial.begin(9600);
//    delay(250); // wait for the OLED to power up
//    initDisplay();
//    display.display();
//    setupClockOutputs();
//    pinMode(PUSH_BUTTON_LED, OUTPUT);
//
//// initialize the pushbutton pins as inputs with pull-up resistors:
//    pinMode(A_PUSH_BUTTON, INPUT_PULLUP);
//    pinMode(B_PUSH_BUTTON, INPUT_PULLUP);
//    pinMode(C_PUSH_BUTTON, INPUT_PULLUP);
//
//// ... your existing setup code
//    MIDI.begin(MIDI_CHANNEL_OMNI);  // listen on all channels
//    Serial.begin(31250);
//}
//
//
//void loop() {
//    int newPotValue = analogRead(POT_PIN);
//    // check if the potentiometer value has changed
//    if (newPotValue != lastPotValue && potChangedSignificantly(newPotValue)) {
//        bpm = map(newPotValue, 0, 1023, minBPM, maxBPM); // just make 0 - 1023 50 - 300
//        lastPotValue = newPotValue;
//        drawBPM();
//    }
//    unsigned long currentTime = millis();
//    updateClock(A_CLOCK, 0, currentTime);
//    updateClock(B_CLOCK, 1, currentTime);
//    updateClock(C_CLOCK, 2, currentTime);
//
//    updatePushStates();
//    handlePushLED();
//}