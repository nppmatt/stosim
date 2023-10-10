/* stosim/src/include/mc_random.hpp */
#ifndef STOSIM_INCLUDE_MC_RANDOM_H_
#define STOSIM_INCLUDE_MC_RANDOM_H_

#include <cstdint>
#include <vector>

/* The random number library for stosim. Intended to hold generators and methods for creating pseudorandom numbers to be
 * used for Monte Carlo methods.
 */
namespace mcr {
    /* Linear congruential generator that forms the basis for the pseudorandom Uniform generator and therefore the rest
     * of our library.
     *
     * Multiplier is based on Donald Knuth's choice for the MMIX virtual machine as its random properties have undergone
     * many years of scrutiny and real-world usage and it has a provably long period (Art of Computer Programming Vol. 2
     * Ch. 3) relative to our assumed word size of 64-bits.
     *
     * The increment differs from Knuth's choice, and is simply adding 1. This does not change randomness relative to
     * the original by one bit and keeps things simple.
     * 
     * The modulus is simply the machine word size, exactly 2^64. This is chosen in order to take advantage of the CPU's
     * ability to perform mod(2^64) on-the-fly by calculating overflow or wrap-around for unsigned 64-bit integers.
     *
     * Our algorithm assumes the usage of a "normal" (Intel/AMD) CPU with SSE2 support (post-year 2000 / Pentium 4).
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

    /* Our scheme for simulating a Uniform Random Variable U ~ U(1,0):
    *   - Grab a pseudorandom number from the Linear Congruential Generator.
    *   - Normalize the LCG output by dividing with the largest 64-bit integer (both already explicit-cast to double).
    *   - Store as uniformValue.
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

    /* Monte Carlo integration based loosely on non-stochastic analogue in numeric header.
     * Parameters:
     * integFunc    -   The function we would like to approximate via random trials. Uses a template to take in any
     *                  callable function from outside.
     * lowerBound   -   Left bound of integration, or "a".
     * upperBound   -   Right bound of integration, or "b".
     * n            -   Number of trials to perform.
     *
     * Operates by treating function to integrate as evaluating an expected value.
     * i.e. theta = E[f(Uniform)] = sum(f(Uniform)) / k; k -> inf. (Simulation, Ross pg. 40)
     * Depends on Law of Large Numbers, user should be picking a large n for a given function.
     *
     * TODO: Split off into own header. (2023/09/25)
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
/* stosim/src/include/mc_random.hpp */

