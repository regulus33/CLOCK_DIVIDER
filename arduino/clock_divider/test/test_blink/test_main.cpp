//
// Created by zack on 9/2/23.
//

#include "unity.h"
#include "ArduinoClawk.h"
#include "Arduino.h"
#include "OledDisplayService.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

//void test_OledDisplayServe_displayTest(void) {
////    OledDisplayService display;
////    display.displayText("Hello world!", 0, 0);
////    delay(100);
//}
//
//void test_ArduinoClawk_functionality(void) {
//    Clawk c = Clawk(1);
//    c.tick();
//    TEST_ASSERT_EQUAL(0, c.getOutPut(0).buffer->pulsing());
//}

void test_EncoderKnobService_counter() {
    exp
}



int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_EncoderKnobService_counter);
//    RUN_TEST(test_ArduinoClawk_functionality);
//    RUN_TEST(test_OledDisplayServe_displayTest);
    return UNITY_END();
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


// UNCOMMENT 1 of the following for platforms other than Arduino //

/**
  * For native dev-platform or for some embedded frameworks
  * --- The main function and app_main would be for other platforms ESP etc. ---
  */

//int main(void) {
//    return runUnityTests();
//}

/**
  * For ESP-IDF framework
  */
//void app_main() {
//    runUnityTests();
//}