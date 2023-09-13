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

Program program;
IlluminatedEncoder encoder;
OledDisplay display;
//Clawk clawk(7);
void setup() {
    display.setup();
    encoder.setup();
    Jacks::setup();
}
void loop() {
    program.updateProgramState();
    encoder.hardWareTest();
    display.hardwareTest();
    Jacks::hardwareTest();

    delay(500);
#ifdef DEBUG

#endif

}