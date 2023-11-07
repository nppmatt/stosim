/* stosim/src/include/mc_random/Exponential.hpp */
#ifndef STOSIM_INCLUDE_MC_RANDOM_EXPONENTIAL_H_
#define STOSIM_INCLUDE_MC_RANDOM_EXPONENTIAL_H_

#include "Uniform.hpp"

#include <cmath>

namespace mcr {
    /* Generator for Exponential random variable with parameter lambda.
     * Builds upon the Uniform generator using inversion.
     * General scheme for random variable generation is:
     *  - Grab Uniform random numbers as needed.
     *  - Transform the UPRNG into desired output with unique member function.
     *  - Store as protected variable, output via next() iteration.
     *
     *  TODO: Also split this off into its own header. Dependencies getting
     *  twisted. (2023/10/17)
     *  TODO: Probably should review copy/move semantics for library.
     *  (2023/10/17)
     *  TODO: Add tests for custom seed constuctor. (2023/10/17)
     */
    class Exponential : public Uniform {
        private:
            constexpr double exponentialTransform(double lambda) {
                return -log(1 - uniformValue) / lambda;
            }
        protected:
            double lambda;
            double exponentialValue;
        public:
            explicit Exponential(double inputParam) {
                lambda = inputParam;
                exponentialValue = exponentialTransform(lambda);
            }

            explicit Exponential(double inputParam, uint64_t customSeed) {
                seed = customSeed;
                lambda = inputParam;
                exponentialValue = exponentialTransform(lambda);
            }

            constexpr double getValue() { return exponentialValue; }

            constexpr double next() {
                Uniform::next();
                exponentialValue = exponentialTransform(lambda);
                return exponentialValue;
            }
    };
}

#endif
/* stosim/src/include/mc_random/Exponential.hpp */

