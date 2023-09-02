#include <Arduino.h>
#include "ArduinoClawk.h"

void setup() {
// write your initialization code here
Clawk clawk = Clawk(1);
clawk.tick();
}

void loop() {
// write your code here
}