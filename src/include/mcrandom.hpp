/* stosim/src/include/mcrandom.hpp */
#ifndef STOSIM_INCLUDE_MCRANDOM_H_
#define STOSIM_INCLUDE_MCRANDOM_H_

#include <cstdint>

namespace mcr {
    class LinearCongruential {
        private:
            uint64_t const multiply = 6364136223846793005;
            uint64_t const increment = 1;
        protected:
            uint64_t seed; 
            uint64_t value;
        public:
            LinearCongruential() {
                seed = 31254066;
                value = seed;
            }

            explicit LinearCongruential(uint64_t customSeed) {
                seed = customSeed;
                value = seed;
            }
            
            constexpr uint64_t getSeed() { return seed; }

            constexpr uint64_t getValue() { return value; }

            constexpr uint64_t next() {
                value = multiply * value + increment;
                return value;
            }
    };

    /* Our scheme for simulating a Uniform Random Variable U ~ U(1,0):
    * - Grab a pseudorandom number from the Linear Congruential Generator.
    * - Normalize the LCG output by dividing with the largest 64-bit integer (both already explicit-cast to double).
    * - Store as uniformValue.
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
/* stosim/src/include/mcrandom.hpp */
