#ifndef FORWARDBACKWARD_H
#define FORWARDBACKWARD_H

#include "hmm.h"
#include "helpers.h"
#include <cassert>

class ForwardBackward
{
private:
    double forwardLn(int state, int time);
    double backwardLn(int state, int time);

    // ln p(Sk, O)
    double computeJointLn(int stateIndex, int time);

    const HiddenMarkovModel &hmm;
    std::vector<int> outputSequence;
    std::vector<std::vector<double> > lnForward;
    std::vector<std::vector<double> > lnBackward;

public:
    ForwardBackward(const HiddenMarkovModel &hmm, const std::vector<int> &outputSequence);

    // ln p(Sk / O)
    double computeLnConditionalProb(int state, int time);
};

#endif // FORWARDBACKWARD_H
