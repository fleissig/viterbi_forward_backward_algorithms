#ifndef TESTING_H
#define TESTING_H

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <limits>
#include "helpers.h"

std::vector<std::string> splitSkippingEmptyParts(const std::string &line, char sep);

struct StepStateEmission
{
    int time;
    std::string state;
    char emission;

    StepStateEmission(int time, const std::string &state, char emission)
        : time(time), state(state), emission(emission)
    {
    }
};

void initData(std::vector<std::string> &hiddenStates, std::vector<char> &outputStates,
              std::vector<std::vector<double> > &lnTransition,
          std::vector<std::vector<double> > &lnEmission, std::vector<double> &lnInitial);

void printEfficiencyDetectingSt1(const std::vector<StepStateEmission> &simulationData,
                                 const std::vector<int> &mostLikelySequence);

std::vector<StepStateEmission> readSimulationData();

template<class T>
void printSequence(const std::vector<int> sequence, const std::vector<T> &statesAlphabet)
{
    for (size_t i = 0; i < sequence.size(); i++) {
        std::cout << statesAlphabet.at(sequence[i]) << std::endl;
    }
}

#endif // TESTING_H
