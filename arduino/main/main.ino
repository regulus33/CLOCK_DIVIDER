#include "include/ArduinoClawk.h"

void setup() {
    // Your setup code here
    Clawk c = Clawk(7);
    c.tick();
}

void loop() {
    // Your loop code here
}
