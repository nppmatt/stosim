/* stosim/src/ch9_p5.cpp */

#include "include/mc_random.hpp"

#include <numbers>
#include <cmath>
#include <limits>
#include <iostream>

using mcr::Uniform;
using std::numbers::pi;
using std::cout;
using std::endl;

int main() {
    /* Problem Setup */
    const double intervalSize = 0.1;
    const double Z = 1.96;

    /* Linearity of expecations: E[Z^3] * E[e^Z] = 0 */
    const double knownMean = 0.0;
    Uniform uniformGenerator = Uniform();

    /* Simulation: Generating std. normal RVs pairwise and their antithetic counterparts and taking their means.
     */
    double u1, u2;
    double circleDistance = 0.0;
    double errorBound = std::numeric_limits<double>::max(); // start large
    double sampleMean = 0.0;
    double sampleVar = 0.0;

    uint64_t indicator = 0;
    uint64_t numRuns = 0;
    const uint64_t RUN_LIMIT = 1000;
    while (errorBound > (intervalSize / 2) && numRuns < RUN_LIMIT) {
        ++numRuns;
        u1 = uniformGenerator.next();
        u2 = uniformGenerator.next();

        /* This form shaves off a single operation. */
        circleDistance = 4 * (u1*u1 + u2*u2 - u1 - u2) + 2;

        if (circleDistance <= 1.0) {
            ++indicator;
        }

        /* Bernoulli recursive statistics update (Ross pg. 137-138). */
        sampleMean = (double) indicator / (double) numRuns;
        sampleVar = sampleMean * (1.0 - sampleMean);

        errorBound = std::abs(
            knownMean - sampleMean - (Z * std::sqrt(sampleVar / (double) numRuns))
            );
    } 

    cout << "Expected Value: " << sampleMean;
    cout << " within interval " << intervalSize << " wide." << endl;
    cout << "Quick check: 3.14 / 4 = 0.785" << endl;
    cout << endl;
    cout << "Number of runs: " << numRuns << endl;

    return 0;
}

/* stosim/src/ch8_p10.cpp */
