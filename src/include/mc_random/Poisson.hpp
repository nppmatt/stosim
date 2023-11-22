/* stosim/src/include/mc_random/Poisson.hpp */
#ifndef STOSIM_INCLUDE_MC_RANDOM_POISSON_H_
#define STOSIM_INCLUDE_MC_RANDOM_POISSON_H_

#include "Exponential.hpp"

namespace mcr {
    class Poisson {
        private:
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
            Poisson() = default;

            Poisson(double inputParam)
            :   lambda(inputParam),
                expGenerator( Exponential(lambda) ),
                poissonValue( genPoisson() )
            {}

            Poisson(double inputParam, uint64_t customSeed)
            :   lambda(inputParam),
                expGenerator( Exponential(lambda, customSeed) ),
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

