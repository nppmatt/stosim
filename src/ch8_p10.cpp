/* stosim/src/ch8_p10.cpp */

#include "include/mc_random.hpp"

#include <limits>
#include <iostream>

using mcr::Uniform;
using std::cout;
using std::endl;

int main() {
    /* Problem Setup */
    const double intervalSize = 0.1;
    const double tolerance = intervalSize / 2;
    const double Z = 1.96;
    Uniform uniformGenerator = Uniform();

    /* Simulation: Generating points in unit square and culling ones outside of 
     * unit circle.
     */
    double u1, u2;
    double circleDistance = 0.0;
    double errorBound = std::numeric_limits<double>::max(); // start large
    uint64_t indicator = 0;
    uint64_t numRuns = 0;
    while (errorBound > tolerance) {
        u1 = uniformGenerator.next();
        u2 = uniformGenerator.next();

        /* Shave off a single operation. */
        circleDistance = 4 * (u1*u1 + u2*u2 - u1 - u2) + 2;

        if (circleDistance < 1.0) {
            ++indicator;
        }


        ++numRuns;
    }



    return 0;
}

/* stosim/src/ch8_p10.cpp */
