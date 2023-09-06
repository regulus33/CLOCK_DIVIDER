#include <Arduino.h>
#include "ArduinoLedEncoder.h"


ArduinoLedEncoder encoder;

void setup() {
    encoder.setup();
}

void loop() {
    encoder.colorCycle();
    encoder.read_encoder();
}

