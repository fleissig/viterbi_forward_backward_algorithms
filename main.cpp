#include "forwardbackward.h"
#include "viterbi.h"
#include "testing.h"

using namespace std;

void work()
{
    vector<StepStateEmission> simulationData = readSimulationData();

    std::vector<std::string> hiddenStates;
    std::vector<char> outputStates;
    std::vector<std::vector<double> > lnTransition;
    std::vector<std::vector<double> > lnEmission;
    std::vector<double> lnInitial;

    initData(hiddenStates, outputStates, lnTransition, lnEmission, lnInitial);

    HiddenMarkovModel hmm(hiddenStates.size(), outputStates.size(), lnEmission, lnTransition, lnInitial);

    vector<int> outputSequence;
    outputSequence.reserve(simulationData.size());

    for (size_t i = 0; i < simulationData.size(); i++) {
        for (size_t j = 0; j < outputStates.size(); j++) {
            if (simulationData[i].emission == outputStates[j]) {
                outputSequence.push_back(j);
                break;
            }
        }
    }

    ForwardBackward fb(hmm, outputSequence);

    vector<int> mostLikelySequenceFB;
    mostLikelySequenceFB.reserve(outputSequence.size());

    for (size_t time = 0; time < outputSequence.size(); time++) {
        double maxLnProb = -1 * std::numeric_limits<double>::max();
        int mostLikelyState = -1;

        for (size_t i = 0; i < hiddenStates.size(); i++) {
            double lnProb = fb.computeLnConditionalProb(i, time);
            if (lnProb > maxLnProb) {
                maxLnProb = lnProb;
                mostLikelyState = i;
            }
        }
        mostLikelySequenceFB.push_back(mostLikelyState);
    }

    cout << "Forward-backward algorithm:" << endl;
    printEfficiencyDetectingSt1(simulationData, mostLikelySequenceFB);
    cout << endl;


    //     prints a most likely sequence using Forward-backward algorithm
    //        printSequence(mostLikelySequenceFB, hiddenStates);
    //        cout << endl;

    Viterbi viterbi(hmm, outputSequence);

    vector<int> mostLikelySequenceViterbi = viterbi.computeMostLikelySequence();

    cout << "Viterbi algorithm:" << endl;
    printEfficiencyDetectingSt1(simulationData, mostLikelySequenceViterbi);
    cout << endl;

    //     prints a most likely sequence using Viterbi algorithm
    //        printSequence(mostLikelySequenceViterbi, hiddenStates);
    //        cout << endl;
}

int main()
{
    work();
    //    test();
}

