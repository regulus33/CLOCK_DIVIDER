#include "../include/Buffer.hpp"
#include "../include/Output.hpp"
#include <gtest/gtest.h>
#include <random>
#include <functional>
#include "include/testOnPulseFunction.hpp"
#include "include/TestAllDivisions.hpp"
#include "include/TestClawk.hpp"



TEST_P(TestAllDivisions, buffer_dot_pulsing) {
    int length = GetParam();
    Buffer buffer = Buffer(length);
    for(int i = 0; i < 128; i++) {
        if(i % length == 0) {
            EXPECT_TRUE(buffer.pulsing());
        } else {
            EXPECT_FALSE(buffer.pulsing());
        }
        buffer.iterate();
    }
}

INSTANTIATE_TEST_SUITE_P(TestClawk, TestAllDivisions, ::testing::ValuesIn(my_vector));

TEST_F(TestClawk, buffer_dot_iterate) {
    buffer->setData(3, 1);
    for (int i = 0; i < 3; i++) {
        buffer->iterate();
    }
}

TEST_F(TestClawk, buffer_dot_backwardsIterate) {
    int expected = buffer->getLength() - 1;
    /*! it returns the value of the backwardsIndex */
    EXPECT_EQ(expected, buffer->backwardIterate(1));
    /* ! it modifies the backwardsIndex variable */
    EXPECT_EQ(expected, buffer->getCurrentIndex());
    int nextExpected = buffer->getLength() - 2;
    buffer->backwardIterate(1);
    /* ! it moves the backwardsIndex variable and persists */
    EXPECT_EQ(nextExpected, buffer->getCurrentIndex());
}

TEST_F(TestClawk, buffer_dot_getElementAt) {
    int upPulse = 1;
    buffer->setData(0, upPulse);
    int pulseItem = buffer->getData()[0];

    EXPECT_EQ(pulseItem, upPulse) << "pulseItem: " << pulseItem;
}

TEST_F(TestClawk, buffer_iterate_method_makes_buffer_pulsing_true_every_other_step) {
    for(int i = 0; i < 2048; i++) {
        if(i % 2 == 0) {
            EXPECT_EQ(buffer->pulsing(), true);
        } else {
            EXPECT_EQ(buffer->pulsing(), false);
        }
        buffer->iterate();
    }
}

TEST_F(TestClawk, buffer_iterate_with_various_divisions) {
    TestPulseForClockDivision(2, [](bool pulsing, Buffer* buffer, Output* clawkOutput) -> bool {
        return buffer->pulsing() == pulsing;
    });
}

TEST_F(TestClawk, clock_output_calls_function_pointer_set_as_onPulse) {
    clawkOutput->onPulse = onPulse1;
    clawkOutput->progress();
    EXPECT_EQ(onPulseCalled, true);
    onPulseCalled = false;
    clawkOutput->progress();
    EXPECT_EQ(onPulseCalled, false);
    clawkOutput->progress();
    EXPECT_EQ(onPulseCalled, true);
}