#include "testing.h"

using namespace std;

std::vector<std::string> splitSkippingEmptyParts(const std::string &line, char sep)
{
    vector<string> ans;
    istringstream ins(line);
    string word;

    while (ins.good()) {
        getline(ins, word, sep);
        if (!word.empty()) {
            ans.push_back(word);
        }
    }
    return ans;
}

void initData(std::vector<std::string> &hiddenStates, std::vector<char> &outputStates,
              std::vector<std::vector<double> > &lnTransition,
              std::vector<std::vector<double> > &lnEmission, std::vector<double> &lnInitial)
{
    double lnSmallNumber = log(numeric_limits<double>::min());

    hiddenStates.clear();
    outputStates.clear();

    hiddenStates.push_back("B");
    hiddenStates.push_back("St1");
    hiddenStates.push_back("St2");
    hiddenStates.push_back("E");

    outputStates.push_back('a');
    outputStates.push_back('b');
    outputStates.push_back('c');

    lnTransition = initMatrix(hiddenStates.size(), hiddenStates.size(), lnSmallNumber);
    lnEmission = initMatrix(hiddenStates.size(), outputStates.size(), lnSmallNumber);
    lnInitial = initMatrix(1, hiddenStates.size(), lnSmallNumber).at(0);

    lnTransition[0][1] = log(0.526);
    lnTransition[0][2] = log(0.474);
    lnTransition[1][3] = log(0.002);
    lnTransition[1][1] = log(0.969);
    lnTransition[1][2] = log(0.029);
    lnTransition[2][3] = log(0.002);
    lnTransition[2][1] = log(0.063);
    lnTransition[2][2] = log(0.935);

    lnEmission[1][0] = log(0.005);
    lnEmission[1][1] = log(0.775);
    lnEmission[1][2] = log(0.220);
    lnEmission[2][0] = log(0.604);
    lnEmission[2][1] = log(0.277);
    lnEmission[2][2] = log(0.119);

    lnInitial[0] = log(1.0);
}

void printEfficiencyDetectingSt1(const vector<StepStateEmission> &simulationData,
                                 const vector<int> &mostLikelySequence)
{
    int truePositives = 0, falsePositives = 0, trueNegatives = 0, falseNegatives = 0;

    for (size_t i = 0; i < simulationData.size(); i++) {
        if (simulationData[i].state == "St1" && mostLikelySequence[i] == 1) {
            truePositives++;
        }
        else if (simulationData[i].state == "St1" && mostLikelySequence[i] != 1) {
            falseNegatives++;
        }
        else if (simulationData[i].state != "St1" && mostLikelySequence[i] == 1) {
            falsePositives++;
        }
        else if (simulationData[i].state != "St1" && mostLikelySequence[i] != 1) {
            trueNegatives++;
        }
    }

    cout << "TP: " << truePositives << endl;
    cout << "FN: " << falseNegatives << endl;
    cout << "FP: " << falsePositives << endl;
    cout << "TN: " << trueNegatives << endl;

    if (truePositives + falsePositives == 0) {
        cout << "truePositives + falsePositives == 0" << endl;
        return;
    }

    if (truePositives + falseNegatives == 0) {
        cout << "truePositives + falseNegatives == 0" << endl;
        return;
    }

    double precision = (double) truePositives / (truePositives + falsePositives);
    double recall = (double) truePositives / (truePositives + falseNegatives);

    if (precision + recall == 0) {
        cout << "precision + recall == 0" << endl;
        return;
    }

    double fMeasure = 2 * precision * recall / (precision + recall);

    cout << "F-measure: " << fMeasure << endl;
}

vector<StepStateEmission> readSimulationData()
{
    vector<StepStateEmission> simulationData;

    const char *fileName = "hmmdata";

    ifstream in;
    in.open(fileName);
    if (!in.is_open()) {
        cerr << "is_open";
        exit(1);
    }

    string line;
    getline(in, line);

    while(in.good()) {
        getline(in, line);
        if (!in.good()) break;
        vector<string> stepStateEmission = splitSkippingEmptyParts(line, '\t');
        simulationData.push_back(
                    StepStateEmission(
                        atoi(stepStateEmission.at(0).c_str()),
                        stepStateEmission.at(1),
                        stepStateEmission.at(2).at(0)
                        )
                    );
    }
    return simulationData;
}
