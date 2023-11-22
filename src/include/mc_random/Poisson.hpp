/* stosim/src/include/mc_random/Poisson.hpp */
#ifndef STOSIM_INCLUDE_MC_RANDOM_POISSON_H_
#define STOSIM_INCLUDE_MC_RANDOM_POISSON_H_

#include "Exponential.hpp"

namespace mcr {
    /* Generator for the endpoint of a homogenous Poisson process with 
     * parameter lambda. Is somewhat limited when it comes to path generation,
     * but it's here for any niche cases where the path is not needed.
     * Scheme for generation is to accumulate exponentially distributed
     * deltas until the parameter is reached.
     */
    class Poisson {
        private:
            Poisson() = default;

            double genPoisson() {
                uint64_t candidate = 0;

                double elapsed = 0.0;
                while (elapsed < lambda) {
                    elapsed += expGenerator.getValue();
                    ++candidate;
                }
                return candidate;
            }
        protected:
            Exponential expGenerator;
            double lambda;
            double poissonValue;
        public:
            Poisson(Exponential inputGenerator, double inputParam)
            :   expGenerator(inputGenerator),
                lambda(inputParam),
                poissonValue( genPoisson() )
            {}

            Poisson(double inputParam)
            :   expGenerator( Exponential(inputParam) ),
                lambda(inputParam),
                poissonValue( genPoisson() )
            {}

            Poisson(double inputParam, uint64_t customSeed)
            :   expGenerator( Exponential(inputParam, customSeed) ),
                lambda(inputParam),
                poissonValue( genPoisson() )
            {}

            constexpr double getValue() { return poissonValue; }

            double next() {
                expGenerator.next();
                poissonValue = genPoisson();
                return poissonValue;
            }
    };
}

#endif
/* stosim/src/include/mc_random/Poisson.hpp */

