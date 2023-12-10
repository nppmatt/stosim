/* stosim/src/p2c.cpp */

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

/* Evaluating MC integral with control variate. */
int main() {
    Uniform uniformGenerator = Uniform();
    double U = 0.0;
    double sampleMean = 0.0;
    double sampleControlMean = 0.0;
    double sampleControlVar = 0.0;
    double sampleCov = 0.0;
    double cStar = 0.0;
    double integralResult = 0.0;
    const double KNOWN_CONTROL_MEAN = 1.56666666666;

    cout << "CONTROL VARIATE CASE:" << endl;
    uint64_t totalTrials = 0;
    for (uint64_t i = 2; i < 7; ++i) {
        totalTrials = (uint64_t) pow(10, i);
        double sample = 0.0;
        double sampleControl = 0.0;
        std::vector<double> sampleVector;
        std::vector<double> sampleControlVector;

        for (uint64_t trialNum = 0; trialNum < totalTrials; ++trialNum) {
            U = uniformGenerator.next();
            sample = exp(U * U);
            sampleVector.emplace_back(sample);

            /* Fitting Y = 1 + 1.7 * X^2 to integral. */
            sampleControl = 1 + 1.7*U*U;
            sampleControlVector.emplace_back(sampleControl);
        } /* REALIZATION END */ 

        /* Realization Statistics, obtaining estimate of correlation. */
        for (double& s : sampleVector) {
            sampleMean += s;
        }
        sampleMean /= (double) totalTrials;

        for (double& cs : sampleControlVector) {
            sampleControlMean += cs;
        }
        sampleControlMean /= (double) totalTrials;

        for (uint64_t i = 0; i < totalTrials; ++i) {
            sampleControlVar += (sampleControlVector[i] - sampleControlMean)
                * (sampleControlVector[i] - sampleControlMean);

            sampleCov += (sampleVector[i] - sampleMean)
                * (sampleControlVector[i] - sampleControlMean);
        }
        sampleControlVar /= (double) (totalTrials - 1);
        sampleCov /= (double) (totalTrials - 1);

        /* Estimating optimal cStar for given samples. */
        cStar = -sampleCov / sampleControlVar;
        integralResult = sampleMean
            + cStar * (sampleControlMean - KNOWN_CONTROL_MEAN);

        /* Printing to console.
         * Sanity checks:
         * Result should definitely be less than 1.7
         * Calculators yield ~1.46265
         */
        cout << "Total trials:" << totalTrials;
        cout << "\t| Integral Result: " << integralResult << endl;
    }
    cout << endl;
    
    return 0;
}

/* stosim/src/p2c.cpp */
