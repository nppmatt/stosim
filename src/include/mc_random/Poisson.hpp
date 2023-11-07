/* stosim/src/include/mc_random/Poisson.hpp */
#ifndef STOSIM_INCLUDE_MC_RANDOM_POISSON_H_
#define STOSIM_INCLUDE_MC_RANDOM_POISSON_H_

#include "Exponential.hpp"

#include <cmath>

namespace mcr {
    class Poisson : public Exponential {
        private:
            double genPoisson() {
                uint64_t candidate = 0;

                double elapsed = 0.0;
                while (elapsed < lambda) {
                    elapsed += Exponential::next();
                    ++candidate;
                }
                return candidate;
            }
        protected:
            double lambda;
            double poissonValue;
        public:
            explicit Poisson(double inputParam)
            : Exponential(inputParam) {
                lambda = inputParam;
                poissonValue = genPoisson();
            }

            explicit Poisson(double inputParam, uint64_t customSeed)
            : Exponential(inputParam, customSeed) {
                seed = customSeed;
                lambda = inputParam;
                poissonValue = genPoisson();
            }

            constexpr double getValue() { return poissonValue; }

            double next() {
                poissonValue = genPoisson();
                return poissonValue;
            }
    };
}

#endif
/* stosim/src/include/mc_random/Poisson.hpp */

