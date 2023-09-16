//
// Created by zack on 9/16/23.
//
//
// Created by zack on 9/2/23.
//

#include "unity.h"
#include "Arduino.h"
#include "physical/Buttons.h"

int digitalReadOutput = HIGH;
// In one of your .cpp files, define the static member.



int digitalReed(uint8_t pin) {
    // Your stub code here.
    // For example, always return HIGH:
    TEST_ASSERT(true);
    return digitalReadOutput;

}
int (*Button::digitalReadPtr)(uint8_t) = digitalReed;

void test_buttons_high(void) {
    digitalReadOutput = HIGH;
    Buttons buttons;
    buttons.updateStates();
    Button* buttonsArr = buttons.getButtonsArray();

    for(int i = 0; i < numButtons; i++) {
        TEST_ASSERT_EQUAL(buttonsArr[i].isPressed(), 0);
    }

    digitalReadOutput = LOW;
    buttons.updateStates();

    for(int i = 0; i < numButtons; i++) {
        TEST_ASSERT_EQUAL(buttonsArr[i].isPressed(), 1);
    }

}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_buttons_high);
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

void loop() {

}
