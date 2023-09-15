//
// Created by zack on 9/2/23.
//

#include "unity.h"
#include "ArduinoClawk.h"
#include "Arduino.h"
#include "physical/IlluminatedEncoder.h"
#include "state/Divider.h"


void test_div_2(void) {
    Divider divider = Divider(2);

    int arr[] = {1,0,1,0,1,0,1,0};
    for (int i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL(divider.tick(), arr[i]);
    }
}

void test_div_3(void) {

}


void test_div_4(void) {
    Divider divider = Divider(4);

    int arr[] = {1,0,0,0,1,0,0,0};
    for (int i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL(divider.tick(), arr[i]);
    }
}

void test_div_5(void) {
    Divider divider = Divider(5);

    int arr[] = {1,0,0,0,0,1,0,0};
    for (int i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL(divider.tick(), arr[i]);
    }
}


int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_div_2);
    RUN_TEST(test_div_3);
    RUN_TEST(test_div_4);
    RUN_TEST(test_div_5);
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
