/* stosim/src/include/mc_random/Uniform.hpp */
#ifndef STOSIM_INCLUDE_MC_RANDOM_UNIFORM_H_
#define STOSIM_INCLUDE_MC_RANDOM_UNIFORM_H_

#include "LinearCongruential.hpp"

namespace mcr {
    /* Our scheme for simulating a Uniform Random Variable U ~ U(1,0):
     *  - Grab a pseudorandom number from the Linear Congruential Generator.
     *  - Normalize the LCG output by dividing with the largest 64-bit integer
     *    (both already explicit-cast to double).
     *  - Store as uniformValue.
     */
    class Uniform {
        private:
            constexpr double normalize(uint64_t LCGValue) {
                return double(LCGValue) / double(UINT64_MAX);
            }
        protected:
            LinearCongruential lcgGenerator;
            double uniformValue;
        public:
            Uniform()
            :   lcgGenerator( LinearCongruential() ),
                uniformValue( normalize(lcgGenerator.getValue()) )
            {}

            Uniform(LinearCongruential inputGenerator)
            :   lcgGenerator(inputGenerator),
                uniformValue( normalize(lcgGenerator.getValue()) )
            {}

            Uniform(uint64_t customSeed)
            :   lcgGenerator( LinearCongruential(customSeed) ),
                uniformValue( normalize(lcgGenerator.getValue()) )
            {}

            constexpr double getValue() { return uniformValue; }

            constexpr double next() {
                lcgGenerator.next();
                uniformValue = normalize(lcgGenerator.getValue());
                return uniformValue;
            }
    };
}

#endif
/* stosim/src/include/mc_random/Uniform.hpp */
