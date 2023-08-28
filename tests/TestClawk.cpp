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
    int expected = Buffer::SIZE - 1;
    /*! it returns the value of the backwardsIndex */
    EXPECT_EQ(expected, buffer->backwardIterate(1));
    /* ! it modifies the backwardsIndex variable */
    EXPECT_EQ(expected, buffer->getBackWardsIndex());
    int nextExpected = Buffer::SIZE - 2;
    buffer->backwardIterate(1);
    /* ! it moves the backwardsIndex variable and persists */
    EXPECT_EQ(nextExpected, buffer->getBackWardsIndex());
}

TEST_F(BufferTest, backwardsIterate2) {
    /*! From early in the buffer 3, backwards 7 should result in 11 */

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
        buffer->iterate(0);
    }
}

TEST_F(DivisionTest, findLastPulse) {
    /*!  finds a pulse  */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, Buffer::SIZE - 1);
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
    EXPECT_EQ(result1, 7);
}

TEST_F(DivisionTest, evaluate) {
    division->buffer.setData(0, 1);
    division->evaluate();
    EXPECT_EQ(division->pulsing, 0);
    division->evaluate();
    EXPECT_EQ(division->pulsing, 1);
}


/*! INTEGRATION TESTS */

struct FunctionPointerStruct {
    static bool onPulseCalled;
    static void onPulse1() {
        onPulseCalled = true;
    }
};

bool FunctionPointerStruct::onPulseCalled = false;

TEST_F(IntegrationTest, integration) {
    clawk->outputs[0].onPulse = FunctionPointerStruct::onPulse1;
    clawk->tick();
    EXPECT_FALSE(FunctionPointerStruct::onPulseCalled);
    clawk->tick();
    EXPECT_TRUE(FunctionPointerStruct::onPulseCalled);
}










