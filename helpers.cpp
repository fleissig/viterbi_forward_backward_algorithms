#include "helpers.h"

using namespace std;

double lnSumExpTrick(const std::vector<double> &v)
{
    std::vector<double>::const_iterator max = std::max_element(v.begin(), v.end());

    double sum = 0.0;
    for (size_t i = 0; i < v.size(); i++) {
        sum += exp(v[i] - *max);
    }

    return *max + log(sum);
}
