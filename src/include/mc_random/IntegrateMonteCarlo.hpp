/* stosim/src/include/mc_random/IntegrateMonteCarlo.hpp */
#ifndef STOSIM_INCLUDE_MC_RANDOM_INTEGRATEMONTECARLO_H_
#define STOSIM_INCLUDE_MC_RANDOM_INTEGRATEMONTECARLO_H_

#include "Uniform.hpp"

#include <cstdint>
#include <vector>

namespace mcr {
    /* Monte Carlo integration based loosely on non-stochastic analogue in numeric header.
     * Parameters:
     * integFunc    -   The function we would like to approximate via random
     *                  trials. Uses a template to take in any callable
     *                  function from outside.
     * lowerBound   -   Left bound of integration, or "a".
     * upperBound   -   Right bound of integration, or "b".
     * n            -   Number of trials to perform.
     *
     * Operates by treating function to integrate as evaluating an
     * expected value.
     * i.e. theta = E[f(Uniform)] = sum(f(Uniform)) / k; k -> inf.
     * (Simulation, Ross pg. 40)
     * Depends on Law of Large Numbers, user should be picking a large enough n.
     *
     * TODO: Add template for upper and lower infinity bounds. (2023/09/25)
     * TODO: Cleanup/optimization. (2023/09/25)
     * TODO: Multithreading/concurrency. (2023/09/25)
     */
    template<typename Function>
    double integrateMonteCarlo(Function integFunc, double lowerBound, double upperBound, uint64_t n) {
        /* Quick sanity check. */
        uint64_t trials;
        if (n >= 1) {
            trials = n;
        }
        else {
            trials = 1;
        }

        /* Generate needed Uniform RV outputs. */
        Uniform u_rand = Uniform();
        std::vector<double> u_vector(trials);
        for (auto & element : u_vector) {
            element = u_rand.next();
        }

        /* Normalizing  if needed. */
        double scalingFactor = 1.0;
        if (lowerBound != 0 || upperBound != 1) {
            scalingFactor = (upperBound - lowerBound);
            for (auto & element : u_vector) {
                element = scalingFactor * element + lowerBound;
            }
        }

        double integMonteCarloResult = 0.0;
        for (unsigned int i = 0; i < trials; ++i) {
            integMonteCarloResult += integFunc(u_vector[i]);
        }
        integMonteCarloResult = integMonteCarloResult * scalingFactor / trials;

        return integMonteCarloResult;
    }

    /* Ditto the above, but adjusted for special case of a bound over (0, infinity). */
    template<typename Function>
    double integrateMonteCarloInfUpper(Function integFunc, uint64_t n) {
        /* Quick sanity check. */
        uint64_t trials;
        if (n >= 1) {
            trials = n;
        }
        else {
            trials = 1;
        }

        /* Generate needed Uniform RV outputs. */
        Uniform u_rand = Uniform();
        std::vector<double> u_vector(trials);
        for (auto & element : u_vector) {
            element = u_rand.next();
        }

        /* Transform to (0,1). */
        for (auto & element : u_vector) {
            element = integFunc((1 / element) - 1) / (element * element);
        }

        double integMonteCarloResult = 0.0;
        for (unsigned int i = 0; i < trials; ++i) {
            integMonteCarloResult += u_vector[i];
        }
        integMonteCarloResult = integMonteCarloResult / trials;

        return integMonteCarloResult;
    }
}

#endif
/* stosim/src/include/mc_random/IntegrateMonteCarlo.hpp */

