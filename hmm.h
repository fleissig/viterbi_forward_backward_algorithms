#ifndef HMM_H
#define HMM_H

#include <vector>
#include <cassert>
#include <cstdlib>

class ForwardBackward;
class Viterbi;

class HiddenMarkovModel
{
public:
    HiddenMarkovModel(size_t amountHiddenStates, size_t amountOutputStates,
        std::vector<std::vector<double> > &lnEmission,
        std::vector<std::vector<double> > &lnTransition,
        std::vector<double> &lnInitial
        );

    size_t getAmountHiddenStates() const;
    size_t getAmountOutputStates() const;

private:
    size_t amountHiddenStates;
    size_t amountOutputStates;
    std::vector<std::vector<double> > lnEmission;
    std::vector<std::vector<double> > lnTransition;
    std::vector<double> lnInitial;

    friend class ForwardBackward;
    friend class Viterbi;
};

#endif // HMM_H
