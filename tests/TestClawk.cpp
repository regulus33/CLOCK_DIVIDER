#include "../include/Buffer.hpp"
#include "../include/Output.hpp"
#include <gtest/gtest.h>
#include <random>
#include <functional>
#include "include/testOnPulseFunction.hpp"
#include "include/TestAllDivisions.hpp"
#include "include/TestClawk.hpp"
#include "Clawk.hpp"


TEST_F(TestClawk, basic) {
    Clawk clawwk = Clawk(3);
    clawwk.getOutPut(0).onPulse = onpC1P;
    clawwk.getOutPut(1).onPulse = onpC2P;
    clawwk.getOutPut(2).onPulse = onpC3P;

    for (int i = 0; i < 3; i++) {
        clawwk.getOutPut(i).changeDivision(2);
    }

    testOnCallbacksFalse();
    clawwk.tick();
    testOnCallbacksTrue();
}
/*!
    Checks that Clawk's pointers to Outputs work and Outputs pointers to Buffer work
*/
TEST_F(TestClawk, pointers) {
    Clawk clawwk = Clawk(7);
    for (int i = 0; i < 7; i++) {
        EXPECT_TRUE(clawwk.getOutputs()[i] != nullptr);
        EXPECT_TRUE(checkForOutputInstance(clawwk.getOutputs()[i]));
        Buffer *buffer = clawwk.getOutputs()[i]->buffer;
        EXPECT_TRUE(checkForBufferInstance(buffer));
    }
    /*!
     *
     * If you were to check as high as outputs[65] you'd still get a pointer to Buffer.
     * No idea where or why it cuts off. But pointers are just integers in base 16 format...
     * I think this is just some built in default of how cpp will initialize an undefined length array of pointers...
     *
     * */
    EXPECT_FALSE(checkForOutputInstance(clawwk.getOutputs()[10000]));
}

/*!
    Checks every possible clock division up to 128 will make Buffer be in "pulsing" state appropriately.
*/
TEST_P(TestAllDivisions, buffer_dot_pulsing) {
    int length = GetParam();
    Buffer buffer = Buffer(length);
    for (int i = 0; i < 128; i++) {
        if (i % length == 0) {
            EXPECT_TRUE(buffer.pulsing());
        } else {
            EXPECT_FALSE(buffer.pulsing());
        }
        buffer.iterate();
    }
}

/*! see above */
INSTANTIATE_TEST_SUITE_P(TestClawk, TestAllDivisions, ::testing::ValuesIn(my_vector));

/*!
 *  Checks that iterate advances buffer index and wraps around at end of buffer.
 */
TEST_F(TestClawk, buffer_dot_iterate) {
    /*!
     Division 1
     */
    testBufferIterate(1, 1, 0);
    testBufferIterate(2, 1, 0);
    /*!
     Division 2
     */
    testBufferIterate(1, 2, 1);
    testBufferIterate(2, 2, 0);
    /*!
    Division 3
    */
    testBufferIterate(3, 3, 0);
    testBufferIterate(4, 3, 1);
    testBufferIterate(5, 3, 2);
    testBufferIterate(6, 3, 0);
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
    for (int i = 0; i < 2048; i++) {
        if (i % 2 == 0) {
            EXPECT_EQ(buffer->pulsing(), true);
        } else {
            EXPECT_EQ(buffer->pulsing(), false);
        }
        buffer->iterate();
    }
}

TEST_F(TestClawk, buffer_iterate_with_various_divisions) {
    TestPulseForClockDivision(2, [](bool pulsing, Buffer *buffer, Output *clawkOutput) -> bool {
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