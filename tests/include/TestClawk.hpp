//
// Created by zack on 8/31/23.
//
#ifndef CLAWK_TESTCLAWK_HPP
#define CLAWK_TESTCLAWK_HPP
#include "Buffer.hpp"
#include "Output.hpp"
#include "testOnPulseFunction.hpp"
#include <gtest/gtest.h>

struct TestClawk : public ::testing::Test {
    Buffer *buffer = nullptr;
    Output *clawkOutput = nullptr;

    void SetUp() override  // Note the capital 'U'
    {
        buffer = new Buffer;
        clawkOutput = new Output;
        onPulseCalled = false;
    }

    void TearDown() override  // Note the capital 'D'
    {
        delete buffer;
        delete clawkOutput;
        onPulseCalled = false;
    }

    void testBufferIterate(int times, int division, int expectedIndex) {
        buffer->changeDivision(division);
        for (int i = 0; i < times; i++) {
            buffer->iterate();
        }

        EXPECT_EQ(buffer->getCurrentIndex(), expectedIndex);
    }

    bool checkForBufferInstance(Buffer* pointer) {
        if (Buffer* bufferPointer = dynamic_cast<Buffer*>(pointer)) {
            return true;
        }
        return false;
    }

    bool checkForOutputInstance(Output* pointer) {
        if (Output* outPutPointer = dynamic_cast<Output*>(pointer)) {
            return true;
        }
        return false;
    }

    void TestPulseForClockDivision(int division, std::function<bool(bool, Buffer*, Output*)> pulsing) {
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
