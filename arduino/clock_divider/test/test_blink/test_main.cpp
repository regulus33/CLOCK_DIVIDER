//
// Created by zack on 9/2/23.
//

#include "unity.h"
#include "ArduinoClawk.h"
#include "Arduino.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_ArduinoClawk_functionality(void) {
    Clawk c = Clawk(1);
    c.tick();
    TEST_ASSERT_EQUAL(0, c.getOutPut(0).buffer->pulsing());
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ArduinoClawk_functionality);
    return UNITY_END();
}

// WARNING!!! PLEASE REMOVE UNNECESSARY MAIN IMPLEMENTATIONS //

/**
  * For native dev-platform or for some embedded frameworks
  */
int main(void) {
    return runUnityTests();
}

/**
  * For Arduino framework
  */
void setup() {
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);

    runUnityTests();
}
void loop() {}

/**
  * For ESP-IDF framework
  */
void app_main() {
    runUnityTests();
}