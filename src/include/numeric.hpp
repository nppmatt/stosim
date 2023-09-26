/* stosim/src/include/numeric.hpp */
#ifndef STOSIM_INCLUDE_NUMERIC_H_
#define STOSIM_INCLUDE_NUMERIC_H_

#include <cstdint>
#include <vector>

/* A one-off numerical methods library for stosim. Not intended to replace existing libraries, but is meant to be
 * reasonably easy enough to read and understand.
 */
namespace num {
    /* Naive trapezoidal rule for numerical integration over a given function.
     * Parameters:
     * integFunc    -   Intended to be an arithmetic function like sqrt(x). Uses a template to take in any callable function
     *                  from outside.
     * a            -   Lower or left bound.
     * b            -   Upper or right bound.
     * n            -   Number of steps or trapezoids the rule is supposed to evaluate.
     */
    template<typename Function>
    double trapezoidRule(Function integFunc, double a, double b, uint64_t n) {
        /* Quick sanity check. */
        uint64_t numSteps;
        if (n >= 1) {
            numSteps = n;
        }
        else {
            numSteps = 1;
        }
        double stepSize = (b - a) / numSteps;

        /* Define the partition/mesh that we iterate the numerical integration over.
         * The number of steps is IN ADDITION to the initial, or leftmost, point.
         * e.g. n = 4 steps, results in a 5-point mesh with 4 trapezoids.
         */
        std::vector<double> mesh(numSteps + 1);
        mesh[0] = a;
        for (unsigned int i = 1; i < mesh.size(); ++i) {
            mesh[i] = mesh[i - 1] + stepSize;
        }
        mesh.back() = b;

        /* Watch out for container indices, as this looks forward one step. */
        double integResult = 0.0;
        for (unsigned int i = 0; i < numSteps; ++i) {
           integResult += ( (stepSize * 0.5) * (integFunc(mesh[i]) + integFunc(mesh[i + 1])) );
        }

        return integResult;
    }
}

#endif
/* stosim/src/include/numeric.hpp */

