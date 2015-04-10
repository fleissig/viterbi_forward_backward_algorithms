#ifndef VITERBI_H
#define VITERBI_H

#include "hmm.h"
#include "helpers.h"
#include <cassert>
#include <limits>

class HiddenMarkovModel;

class Viterbi
{
private:
    const HiddenMarkovModel &hmm;
    std::vector<int> outputSequence;
    std::vector<std::vector<int> > paths;
    std::vector<std::vector<double> > lnProbs;

    double computeLnMostLikelyPathProb(int stateIndex, int time);

public:
    Viterbi(const HiddenMarkovModel &hmm, const std::vector<int> &outputSequence);

    std::vector<int> computeMostLikelySequence();
};

#endif // VITERBI_H
