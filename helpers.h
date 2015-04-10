#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <algorithm>
#include <cmath>

template <class T>
std::vector<std::vector<T> > initMatrix(int n, int m, T value = T())
{
    std::vector<std::vector<T> > ans;
    ans.resize(n);
    for (typename std::vector<std::vector<T> >::iterator it = ans.begin();
         it != ans.end(); ++it)
    {
        it->resize(m, value);
    }
    return ans;
}

double lnSumExpTrick(const std::vector<double> &v);

#endif // HELPERS_H
