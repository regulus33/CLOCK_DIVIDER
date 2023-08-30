#include "../include/Buffer.hpp"
#include "../include/ClawkOutput.hpp"
#include <iostream>
#include <gtest/gtest.h>
#include <random>

bool onPulseCalled = false;

struct FunctionPointerStruct {
    static void onPulse1() {
        onPulseCalled = true;
    }
};

struct TestClawk : public ::testing::Test {
    Buffer *buffer = nullptr;
    ClawkOutput *clawkOutput = nullptr;

    Buffer &GetBuffer() const {
        return *buffer;
    }

    ClawkOutput &GetClockOutput() {
        return *clawkOutput;
    }

    void SetUp() override  // Note the capital 'U'
    {
        buffer = new Buffer;
        clawkOutput = new ClawkOutput;
        onPulseCalled = false;
    }

    void TearDown() override  // Note the capital 'D'
    {
        delete buffer;
        delete clawkOutput;
        onPulseCalled = false;
    }
};


TEST_F(TestClawk, iterate) {
    buffer->setData(3, 1);
    for (int i = 0; i < 3; i++) {
        buffer->iterate();
    }
}


TEST_F(TestClawk, backwardsIterate) {
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

TEST_F(TestClawk, changeDivision) {

}

TEST_F(TestClawk, getElementAt) {
    int upPulse = 1;
    buffer->setData(0, upPulse);
    int pulseItem = buffer->getData()[0];

    EXPECT_EQ(pulseItem, upPulse) << "pulseItem: " << pulseItem;
}

TEST_F(TestClawk, progress) {
    for(int i = 0; i < 2048; i++) {
        if(i % 2 == 0) {
            EXPECT_EQ(buffer->pulsing(), true);
        } else {
            EXPECT_EQ(buffer->pulsing(), false);
        }
        buffer->iterate();
    }
}



//
///*! INTEGRATION TESTS */
//


TEST_F(TestClawk, callback) {
    GetClockOutput().onPulse = FunctionPointerStruct::onPulse1;
    GetClockOutput().progress();
    EXPECT_EQ(onPulseCalled, true);
    onPulseCalled = false;
    GetClockOutput().progress();
    EXPECT_EQ(onPulseCalled, false);
    GetClockOutput().progress();
    EXPECT_EQ(onPulseCalled, true);
}