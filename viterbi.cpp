#include "viterbi.h"

double Viterbi::computeLnMostLikelyPathProb(int stateIndex, int time)
{
    if (lnProbs.at(time).at(stateIndex) < 1.0) {
        return lnProbs[time][stateIndex];
    }

    int outputStateIndex = outputSequence.at(time);

    double maxLnProb = -1 * std::numeric_limits<double>::max();
    int maxPrevStateIndex = -1;

    for (size_t i = 0; i < hmm.getAmountHiddenStates(); i++) {
        double lnProb = hmm.lnEmission.at(stateIndex).at(outputStateIndex)
                + hmm.lnTransition.at(i).at(stateIndex)
                + computeLnMostLikelyPathProb(i, time-1);
        if (lnProb > maxLnProb) {
            maxLnProb = lnProb;
            maxPrevStateIndex = i;
        }
    }

    paths.at(time).at(stateIndex) = maxPrevStateIndex;
    return lnProbs[time][stateIndex] = maxLnProb;
}

Viterbi::Viterbi(const HiddenMarkovModel &hmm, const std::vector<int> &outputSequence)
    : hmm(hmm), outputSequence(outputSequence)
{
    assert(outputSequence.size() > 0);

    paths = initMatrix(outputSequence.size(), hmm.getAmountHiddenStates(), -1);
    lnProbs = initMatrix(outputSequence.size(), hmm.getAmountHiddenStates(), 1.0);

    int start = 0;

    int outputStateIndex = outputSequence.at(start);
    for (size_t i = 0; i < hmm.getAmountHiddenStates(); i++) {
        lnProbs.at(start).at(i) = hmm.lnInitial.at(i) + hmm.lnEmission.at(i).at(outputStateIndex);
    }
}

std::vector<int> Viterbi::computeMostLikelySequence()
{
    for (size_t state = 0; state < hmm.getAmountHiddenStates(); state++) {
        computeLnMostLikelyPathProb(state, outputSequence.size()-1);
    }

    std::vector<int> ans;
    ans.resize(outputSequence.size());

    int stateIndex = -1;

    std::vector<double>::const_iterator max
            = std::max_element(lnProbs.at(outputSequence.size()-1).begin(), lnProbs.at(outputSequence.size()-1).end());

    stateIndex = max - lnProbs.at(outputSequence.size()-1).begin();
    ans.at(outputSequence.size()-1) = stateIndex;

    for (int i = ans.size()-1; i >= 1; i--) {
        stateIndex = paths.at(i).at(stateIndex);
        ans.at(i-1) = stateIndex;
    }
    return ans;
}
