#include "hmm.h"

HiddenMarkovModel::HiddenMarkovModel(size_t amountHiddenStates, size_t amountOutputStates,
    std::vector<std::vector<double> > &lnEmission,
    std::vector<std::vector<double> > &lnTransition,
    std::vector<double> &lnInitial )
    : amountHiddenStates(amountHiddenStates), amountOutputStates(amountOutputStates),
      lnEmission(lnEmission), lnTransition(lnTransition), lnInitial(lnInitial)
{
    assert(amountHiddenStates > 0);
    assert(amountOutputStates > 0);
    assert(lnEmission.size() == amountHiddenStates);
    assert(lnEmission[0].size() == amountOutputStates);
    assert(lnTransition.size() == amountHiddenStates);
    assert(lnTransition[0].size() == amountHiddenStates);
    assert(lnInitial.size() == amountHiddenStates);
}

size_t HiddenMarkovModel::getAmountHiddenStates() const
{
    return amountHiddenStates;
}

size_t HiddenMarkovModel::getAmountOutputStates() const
{
    return amountOutputStates;
}
