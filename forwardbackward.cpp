#include "forwardbackward.h"

double ForwardBackward::forwardLn(int state, int time)
{
    if (lnForward.at(time).at(state) < 1.0) {
        return lnForward[time][state];
    }

    int outputIndex = outputSequence.at(time);

    std::vector<double> multiplications;

    for (size_t i = 0; i < hmm.getAmountHiddenStates(); i++) {
        multiplications.push_back(hmm.lnEmission.at(state).at(outputIndex)
                                  + hmm.lnTransition.at(i).at(state)
                                  + forwardLn(i, time-1));
    }

    return lnForward.at(time).at(state) = lnSumExpTrick(multiplications);
}

double ForwardBackward::backwardLn(int state, int time)
{
    if (lnBackward.at(time).at(state) < 1.0) {
        return lnBackward[time][state];
    }

    int outputIndex = outputSequence.at(time+1);
    std::vector<double> multiplications;

    for (size_t i = 0; i < hmm.getAmountHiddenStates(); i++) {
        multiplications.push_back(
                    backwardLn(i, time+1) + hmm.lnEmission.at(i).at(outputIndex)
                    + hmm.lnTransition.at(state).at(i)
                    );
    }
    return lnBackward.at(time).at(state) = lnSumExpTrick(multiplications);
}

double ForwardBackward::computeJointLn(int stateIndex, int time)
{
    return forwardLn(stateIndex, time)
            + backwardLn(stateIndex, time);
}

ForwardBackward::ForwardBackward(const HiddenMarkovModel &hmm, const std::vector<int> &outputSequence)
    : hmm(hmm), outputSequence(outputSequence)
{
    assert(outputSequence.size() > 0);

    int timeEnd = outputSequence.size()-1;

    lnForward = initMatrix(timeEnd + 1, hmm.getAmountHiddenStates(), 1.0);

    int start = 0;
    int outputIndex = outputSequence.at(start);
    for (size_t i = 0; i < hmm.getAmountHiddenStates(); i++) {
        lnForward.at(start).at(i) = hmm.lnInitial.at(i)
                + hmm.lnEmission.at(i).at(outputIndex);
    }

    lnBackward = initMatrix(timeEnd + 1, hmm.getAmountHiddenStates(), 1.0);

    for (size_t i = 0; i < hmm.getAmountHiddenStates(); i++) {
        lnBackward.at(timeEnd).at(i) = 0;
    }
}

double ForwardBackward::computeLnConditionalProb(int state, int time)
{
    std::vector<double> multiplications;

    for (size_t i = 0; i < hmm.getAmountHiddenStates(); i++) {
        multiplications.push_back(
                    computeJointLn(i, time)
                    );
    }

    double lnConstant = -1.0 * lnSumExpTrick(multiplications);

    return computeJointLn(state, time) + lnConstant;
}
