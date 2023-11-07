/* stosim/src/include/mc_random/LinearCongruential.hpp */
#ifndef STOSIM_INCLUDE_MC_RANDOM_LINEARCONGRUENTIAL_H_
#define STOSIM_INCLUDE_MC_RANDOM_LINEARCONGRUENTIAL_H_

#include <cstdint>

namespace mcr {
    /* Linear congruential generator that forms the basis for the pseudorandom Uniform generator and therefore the rest
     * of our library.
     *
     * Multiplier is based on Donald Knuth's choice for the MMIX virtual machine as its random properties have undergone
     * years of scrutiny and real-world usage (notably in musl libc) and it has a provably long period (Art of Computer Programming Vol. 2 Ch. 3) relative to our assumed word size of 64-bits.
     *
     * The increment differs from Knuth's choice, and is simply adding 1. This does not change randomness relative to
     * the original by one bit and keeps things simple.
     * 
     * The modulus is simply the machine word size, exactly 2^64. This is chosen in order to take advantage of the CPU's
     * ability to perform mod(2^64) on-the-fly by calculating overflow or wrap-around for unsigned 64-bit integers.
     *
     * Our algorithm assumes the usage of a "normal" (Intel/AMD) CPU with SSE2 support (post-year 2000 / Pentium 4).
     *
     * TODO: Add tests for custom seed constuctor. (2023/10/17)
     */
    class LinearCongruential {
        private:
            uint64_t const multiply = 6364136223846793005;
            uint64_t const increment = 1;
        protected:
            uint64_t seed; 
            uint64_t value;
        public:
            LinearCongruential() {
                seed = 31254066; // Some student's ID.
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
}

#endif
/* stosim/src/include/mc_random/LinearCongruential.hpp */
