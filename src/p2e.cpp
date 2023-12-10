/* stosim/src/p2e.cpp */

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

/* Evaluation of MC integral with importance sampling. */
int main() {
    Uniform uniformGenerator = Uniform();
    double U = 0.0;
    double sampleMean = 0.0;

    /* Would like to fit a convenient function, such as the one
     * used in the control variate scenario. */
    const double KNOWN_MEAN = 1.56666666666;
    const double PDF_SCALING = 1 / KNOWN_MEAN;

    cout << "IMPORTANCE SAMPLING CASE:" << endl;
    uint64_t totalTrials = 0;
    for (uint64_t i = 2; i < 7; ++i) {
        totalTrials = (uint64_t) pow(10, i);
        double sample = 0.0;
        double importanceShift = 0.0;
        std::vector<double> sampleVector;

        for (uint64_t trialNum = 0; trialNum < totalTrials; ++trialNum) {
            U = uniformGenerator.next();
            sample = exp(U * U);

            /* Fitting Y = 1 + 1.7 * X^2 to integral. */
            importanceShift = (1 + 1.7*U*U) * PDF_SCALING;
            sampleVector.emplace_back(sample / importanceShift);
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

/* stosim/src/p2e.cpp */
