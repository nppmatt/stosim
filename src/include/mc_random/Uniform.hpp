/* stosim/src/include/mc_random/Uniform.hpp */
#ifndef STOSIM_INCLUDE_MC_RANDOM_UNIFORM_H_
#define STOSIM_INCLUDE_MC_RANDOM_UNIFORM_H_

#include "LinearCongruential.hpp"

namespace mcr {
	/* Our scheme for simulating a Uniform Random Variable U ~ U(1,0):
     *  - Grab a pseudorandom number from the Linear Congruential Generator.
     *  - Normalize the LCG output by dividing with the largest 64-bit integer (both already explicit-cast to double).
     *  - Store as uniformValue.
     *
     *  TODO: Add tests for custom seed constuctor. (2023/10/17)
     */
    class Uniform : public LinearCongruential {
        private:
            constexpr double normalize(uint64_t value) { return double(value) / double(UINT64_MAX); }
        protected:
            double uniformValue;
        public:
            Uniform() {
                uniformValue = normalize(value);
            }

            explicit Uniform(uint64_t customSeed) {
                seed = customSeed;
                uniformValue = normalize(value);
            }

            constexpr double getValue() { return uniformValue; }

            constexpr double next() {
                LinearCongruential::next();
                uniformValue = normalize(value);
                return uniformValue;
            }
    };
}

#endif
/* stosim/src/include/mc_random/Uniform.hpp */
