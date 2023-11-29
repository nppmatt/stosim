/* stosim/src/ch8_p14.cpp */

#include "include/mc_random.hpp"

#include <array>
#include <iostream>

using mcr::Uniform;
using std::cout;
using std::endl;

int main() {
    /* Problem Setup */
    const uint64_t N = 2;
    std::array<uint64_t, N> data = {
        1, 3
    };
    uint64_t sampleSum = 0;
    for (uint64_t& elem : data) sampleSum += elem;
    double empiricalMean = (double) sampleSum / (double) N;

    /* Accumulating bootstrap sample variances. */
    uint64_t index = 0;
    Uniform uniformGenerator = Uniform();
    const uint64_t trials = 10000;
    std::array<double, trials> varianceCollection;
    for (uint64_t trialCount = 0; trialCount < trials; ++trialCount) {
        uint64_t tempSum = 0;
        double bootstrapVar = 0.0;

        /* Random sampling with replacement from data. */
        for (uint64_t i = 0; i < N; ++i) {
            index = (uint64_t) (uniformGenerator.next() * N);
            bootstrapVar += (
                (double) (data[index] - empiricalMean)
                * (double) (data[index] - empiricalMean)
            );
        }
        bootstrapVar /= (double)(N - 1);
        varianceCollection[trialCount] = bootstrapVar;
    }

    double experimentMean = 0.0;
    for (double& elem : varianceCollection) {
        experimentMean += elem;
    }
    experimentMean /= (double) trials;

    double varOfVar = 0.0;
    for (double& elem : varianceCollection) {
        varOfVar += (
            (elem - experimentMean)
            * (elem - experimentMean)
        );
    }
    varOfVar /= (double) trials;

    cout << "Estimate of Var(S^2) after " << trials << " trials: ";
    cout << varOfVar << endl;

    return 0;
}

/* stosim/src/ch8_p14.cpp */
