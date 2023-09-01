
//
// Created by zack on 8/31/23.
//

#ifndef CLAWK_TESTONPULSEFUNCTION_HPP
#define CLAWK_TESTONPULSEFUNCTION_HPP
#include <vector>

bool onPulseCalled = false;

static void onPulse1() {
    onPulseCalled = true;
}
/*!
    For clawk test, we need to test multiple outputs from tick() at once.*
 */
bool onpC1 = false;
static void onpC1P() {
    onpC1 = true;
}

bool onpC2 = false;
static void onpC2P() {
    onpC2 = true;
}

bool onpC3 = false;
static void onpC3P() {
    onpC3 = true;
}
/* ------------------------------------------------------------------- */
std::vector<int> buildDynamicArray() {
    std::vector<int> my_vector;
    for (int i = 2; i <= Buffer::MAX; ++i) {  // Replace this loop with your dynamic logic.
        my_vector.push_back(i);
    }
    return my_vector;
}

std::vector<int> my_vector = buildDynamicArray();

#endif //CLAWK_TESTONPULSEFUNCTION_HPP
