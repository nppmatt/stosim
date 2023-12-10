/* stosim/src/p2d.cpp */

#include "include/mc_random.hpp"

#include <cstdint>
#include <array>
#include <vector>
#include <limits>
#include <iostream>
#include <cmath>

using mcr::Uniform;
using std::cout;
using std::endl;

/* Stratified evaluation of MC integral. */
int main() {
    Uniform uniformGenerator = Uniform();
    double U = 0.0;
    const uint64_t STRATA_COUNT = 10;
    double strataInterval = 1.0 / (double) STRATA_COUNT;

    cout << "STRATIFIED CASE:" << endl;
    uint64_t totalTrials = 0;
    /* Exponential scaling of realizations. */
    for (uint64_t i = 2; i < 7; ++i) {
        totalTrials = (uint64_t) pow(10, i);
        uint64_t strataSize = totalTrials / STRATA_COUNT;
        double sample = 0.0;
        double sampleMean = 0.0;
        std::vector<double> sampleVector(strataSize);
        std::vector<double> strataMeans(STRATA_COUNT);

        /* Get centered means on each strata. */
        for (uint64_t strataNum = 0; strataNum < STRATA_COUNT; ++strataNum) {

            /* Divide total # of realizations across strata. */
            for (uint64_t trialNum = 0; trialNum < strataSize; ++trialNum) {
                U = uniformGenerator.next();
                U = (strataNum + U) * strataInterval;

                sample = exp(U * U);
                sampleVector[trialNum] = sample;
            }

            /* Strata Statistics */
            for (double& s : sampleVector) {
                sampleMean += s;
            }
            sampleMean /= (double) strataSize;
            strataMeans[strataNum] = sampleMean;
            sampleMean = 0.0;
        } /* REALIZATION END */

        /* Realization Statistics, reusing sampleMean variable. */
        for (double& sm : strataMeans) {
            sampleMean += sm;
        }
        sampleMean /= (double) STRATA_COUNT;

        /* Printing to console.
         * Sanity checks:
         * Result should definitely be less than 1.7
         * Calculators yield ~1.46265
         */
        cout << "Total trials:" << totalTrials;
        cout << "\t| Integral Result: " << sampleMean << endl;
    }
    cout << endl;
    
    return 0;
}

/* stosim/src/p2d.cpp */
