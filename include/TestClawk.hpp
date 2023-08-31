//
// Created by zack on 8/31/23.
//
#ifndef CLAWK_TESTCLAWK_HPP
#define CLAWK_TESTCLAWK_HPP
#include "Buffer.hpp"
#include "ClawkOutput.hpp"
#include "testOnPulseFunction.hpp"
#include <gtest/gtest.h>

struct TestClawk : public ::testing::Test {
    Buffer *buffer = nullptr;
    ClawkOutput *clawkOutput = nullptr;

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

    void TestPulseForClockDivision(int division, std::function<bool(bool, Buffer*, ClawkOutput*)> pulsing) {
        for(int i = 0; i < 32; i++) {
            if(i % division == 0) {
                EXPECT_TRUE(pulsing(true, buffer, clawkOutput)) << i;
            } else {
                EXPECT_TRUE(pulsing(false, buffer, clawkOutput)) << i;
            }
            buffer->iterate();
        }
    }
};
#endif //CLAWK_TESTCLAWK_HPP
