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
     */
    class Exponential {
        private:
            constexpr double exponentialTransform(double lambda) {
                return -log(1 - uniformGenerator.getValue()) / lambda;
            }
        protected:
            Uniform uniformGenerator;
            double lambda;
            double exponentialValue;
        public:
            Exponential() = default;

            Exponential(double inputParam)
            :   uniformGenerator( Uniform() ),
                lambda(inputParam),
                exponentialValue( exponentialTransform(lambda) )
            {}

            Exponential(double inputParam, uint64_t customSeed)
            :   uniformGenerator( Uniform(customSeed) ),
                lambda(inputParam),
                exponentialValue( exponentialTransform(lambda) )
            {}

            constexpr double getValue() { return exponentialValue; }

            constexpr double next() {
                uniformGenerator.next();
                exponentialValue = exponentialTransform(lambda);
                return exponentialValue;
            }
    };
}

#endif
/* stosim/src/include/mc_random/Exponential.hpp */

