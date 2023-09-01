//
// Created by zack on 9/1/23.
//

#ifndef CLAWK_CLAWK_HPP
#define CLAWK_CLAWK_HPP

class Clawk {
private:
    int numOutputs;
    Output** outputs;

public:
    Clawk(int numOutput) : numOutputs(numOutput) {
        outputs = new Output*[numOutputs];
        for (int i = 0; i < numOutputs; i++) {
            outputs[i] = new Output();
        }
    }

    Output** getOutputs() {
        return outputs;
    }

    Output& getOutPut(int index) {
        return *(outputs[index]);
    }

    void tick() {
        for(int i = 0; i < numOutputs; i++) {
            outputs[i]->progress();
        }
    }

    ~Clawk() {
        for (int i = 0; i < numOutputs; i++) {
            delete outputs[i];
        }
        delete[] outputs;
    }
};

#endif //CLAWK_CLAWK_HPP
