/* stosim/src/p2a.cpp */

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

/* "Raw" evaluation of MC integral. */
int main() {
    Uniform uniformGenerator = Uniform();
    double U = 0.0;
    double sampleMean = 0.0;

    cout << "REGULAR CASE:" << endl;
    uint64_t totalTrials = 0;
    for (uint64_t i = 2; i < 7; ++i) {
        totalTrials = (uint64_t) pow(10, i);
        double sample = 0.0;
        std::vector<double> sampleVector;

        for (uint64_t trialNum = 0; trialNum < totalTrials; ++trialNum) {
            U = uniformGenerator.next();
            sample = exp(U * U);
            sampleVector.emplace_back(sample);
        } /* REALIZATION END */ 

        /* Realization Statistics */
        for (double& s : sampleVector) {
            sampleMean += s;
        }
        sampleMean /= (double) totalTrials;

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

/* stosim/src/p2a.cpp */
