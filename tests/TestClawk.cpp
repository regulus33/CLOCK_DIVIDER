#include "../include/Buffer.hpp"
#include "../include/Division.hpp"
#include "../include/Clawk.hpp"
#include "../include/ClawkOutput.hpp"
#include <iostream>
#include <gtest/gtest.h>
#include <random>

struct BufferTest : public ::testing::Test {
    Buffer *buffer = nullptr;
    Buffer &GetBuffer() const {
        return *buffer;
    }

    void SetUp() override  // Note the capital 'U'
    {
        buffer = new Buffer;
    }

    void TearDown() override  // Note the capital 'D'
    {
        delete buffer;
    }
};

struct DivisionTest : public ::testing::Test {
    Division *division = nullptr;

    void SetUp() override  // Note the capital 'U'
    {
        division = new Division(2);
    }

    void TearDown() override  // Note the capital 'D'
    {
        delete division;
    }
};


struct IntegrationTest : public testing::Test {
    Clawk *clawk = nullptr;

    void SetUp() override  // Note the capital 'U'
    {
        clawk = new Clawk;
    }

    void TearDown() override  // Note the capital 'D'
    {
        delete clawk;
    }

    void testClockArray(int array[8]) {

        EXPECT_EQ(1, 1);
    }
};

TEST_F(BufferTest, backwardsIterate) {
    int expected = buffer->size - 1;
    /*! it returns the value of the backwardsIndex */
    EXPECT_EQ(expected, buffer->backwardIterate(1));
    /* ! it modifies the backwardsIndex variable */
    EXPECT_EQ(expected, buffer->getBackWardsIndex());
    int nextExpected = buffer->size - 2;
    buffer->backwardIterate(1);
    /* ! it moves the backwardsIndex variable and persists */
    EXPECT_EQ(nextExpected, buffer->getBackWardsIndex());
}

TEST_F(BufferTest, backwardsIterate2) {
    /*! From early in the buffer 3, backwards 7 should result in 11 */
    for(int i = 0; i < 4; i++) {
        buffer->iterate();
    }
    EXPECT_EQ(buffer->getCurrentIndex(), 4);
    buffer->resetBackwardsIndex();
    EXPECT_EQ(buffer->getBackWardsIndex(), 4);
    int backwardIterateResult = buffer->backwardIterate(1);
    EXPECT_EQ(buffer->getBackWardsIndex(), 3);
    EXPECT_EQ(backwardIterateResult, 3);
    for(int i = 0; i < 3; i++) {
        buffer->backwardIterate(1);
    }
    EXPECT_EQ(buffer->getBackWardsIndex(), 0);

    buffer->backwardIterate(1);
    EXPECT_EQ(buffer->getBackWardsIndex(), buffer->size-1);
}

TEST_F(BufferTest, getElementAt) {
    int upPulse = 1;
    buffer->setData(0, upPulse);
    int pulseItem = GetBuffer().getData()[0];

    EXPECT_EQ(pulseItem, upPulse) << "pulseItem: " << pulseItem;
}

TEST_F(BufferTest, iterate) {
    buffer->setData(3, 1);
    for (int i = 0; i < 3; i++) {
        buffer->iterate();
    }
}

TEST_F(DivisionTest, findLastPulse) {
    division->buffer.setData(6, 1);
    int indexOfLastPulse = division->findLastPulse();
    EXPECT_EQ(6, indexOfLastPulse);
}

TEST_F(DivisionTest, findLastPulseAndGetDistance) {
    division->buffer.setData(7, 1);
    int indexOfLastPulse = division->findLastPulse();
    int currentIndex = 2;
    EXPECT_EQ(indexOfLastPulse, 7);
    int distance = division->calcDistanceFromOneBufferIndexToOther(currentIndex, indexOfLastPulse, division->buffer.size);
    EXPECT_EQ(distance,11);
}

TEST_F(DivisionTest, findLastPulseAndGetDistanceLonger) {
    division->buffer.setData(0, 1);
    division->buffer.iterate();
    division->buffer.resetBackwardsIndex();
    EXPECT_EQ(division->buffer.getBackWardsIndex(), division->buffer.getCurrentIndex());
    EXPECT_EQ(division->buffer.getCurrentIndex(), 1);
    int dist = division->calcDistanceFromOneBufferIndexToOther(division->buffer.getBackWardsIndex(), division->findLastPulse(), division->buffer.size);
    EXPECT_EQ(division->findLastPulse(), 0);
    EXPECT_EQ(dist, 1);
    division->buffer.iterate();
    EXPECT_EQ(division->buffer.getBackWardsIndex(), 0);
    EXPECT_EQ(division->buffer.getCurrentIndex(), 2);
    int last = division->findLastPulse();
    EXPECT_EQ(division->buffer.getBackWardsIndex(), 0);
    EXPECT_EQ(last, 0);
    dist = division->calcDistanceFromOneBufferIndexToOther(division->buffer.getCurrentIndex(), division->findLastPulse(), division->buffer.size);
    EXPECT_EQ(dist, 2);
}

TEST_F(DivisionTest, findLastPulseRandom) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, division->buffer.size - 1);
    int randomIndex = dist(gen);
    division->buffer.setData(randomIndex, 1);
    int indexOfLastPulse = division->findLastPulse();
    EXPECT_EQ(randomIndex, indexOfLastPulse);
}

TEST_F(DivisionTest, calcDistanceFromOneBufferIndexToOther) {
    /*
     * find distance between two indices in any SIZE array
    */
    int result1 = division->calcDistanceFromOneBufferIndexToOther(16, 8, 16);
    EXPECT_EQ(result1, 8);
}


TEST_F(DivisionTest, calcDistanceFromOneBufferIndexToOtherWeirdNumbers) {
    /*
     * find distance when subtrahend is smaller than minuend
    */
    int result1 = division->calcDistanceFromOneBufferIndexToOther(7, 14, 16);
    EXPECT_EQ(result1, 9);
}


TEST_F(DivisionTest, evaluate) {
    division->buffer.setData(0, 1);
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 0);
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 1) << division->buffer.getData();
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 0) << division->buffer.getData();
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 1) << division->buffer.getData();
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 0) << division->buffer.getData();
}

TEST_F(DivisionTest, evaluate3) {
    division->divisor = 3;
    division->buffer.setData(0, 1);
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 0);
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 0) << division->buffer.getData();
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 1) << division->buffer.getData();
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 0);
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 0) << division->buffer.getData();
    division->evaluate();
    EXPECT_EQ(division->buffer.pulsing(), 1) << division->buffer.getData();
}


/*! INTEGRATION TESTS */

struct FunctionPointerStruct {
    static bool onPulseCalled;

    static void onPulse1() {
        FunctionPointerStruct::onPulseCalled = true;
    }
};

bool FunctionPointerStruct::onPulseCalled = false;

TEST_F(IntegrationTest, integration) {
    for(int i = 0; i < Clawk::MAX_OUTPUTS; i++) {
        clawk->getOutputs()[i].division.buffer.setData(0, 1);
        clawk->getOutputs()[i].onPulse = FunctionPointerStruct::onPulse1;
    }
    clawk->tick();
//    EXPECT_EQ(FunctionPointerStruct::onPulseCalled, false);
    EXPECT_EQ(clawk->getOutputs()[0].division.buffer.pulsing(), 1);
    clawk->tick();
    EXPECT_EQ(clawk->getOutputs()[0].division.buffer.pulsing(), 1);
    clawk->tick();
    EXPECT_EQ(clawk->getOutputs()[0].division.buffer.pulsing(), 1);
    clawk->tick();
    EXPECT_EQ(clawk->getOutputs()[0].division.buffer.pulsing(), 1);
//    EXPECT_EQ(FunctionPointerStruct::onPulseCalled, true);
}











