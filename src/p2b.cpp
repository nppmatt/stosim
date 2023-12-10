/* stosim/src/p2b.cpp */

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

/* Evaluating MC integral with antithetic variable. */
int main() {
    Uniform uniformGenerator = Uniform();
    double U_1 = 0.0;
    double U_2 = 0.0;
    double sampleMean = 0.0;

    cout << "ANTITHETIC CASE:" << endl;
    uint64_t totalTrials = 0;
    for (uint64_t i = 2; i < 7; ++i) {
        totalTrials = (uint64_t) pow(10, i);
        double sample = 0.0;
        std::vector<double> sampleVector;

        for (uint64_t trialNum = 0; trialNum < totalTrials; ++trialNum) {
            U_1 = uniformGenerator.next();
            U_2 = 1 - U_1;
            sample = 0.5 * (exp(U_1 * U_1) + exp(U_2 * U_2));
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

/* stosim/src/p2b.cpp */
