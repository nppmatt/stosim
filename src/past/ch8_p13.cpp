/* stosim/src/ch8_p13.cpp */

#include "include/mc_random.hpp"

#include <array>
#include <iostream>

using mcr::Uniform;
using std::cout;
using std::endl;

int main() {
    /* Problem Setup */
    const uint64_t N = 10;
    const double a = -5.0;
    const double b = 5.0;

    /* Obtain empirical ("sample") mean from data. */
    std::array<uint64_t, N> data = {
        56, 101, 78, 67, 93, 87, 64, 72, 80, 69
    };
    uint64_t sampleSum = 0;
    for (uint64_t& elem : data) sampleSum += elem;
    double sampleMean = (double) sampleSum / (double) N;

    /* Restating the problem so that we're not subtracting all the time. */
    double lowerBound = a + sampleMean;
    double upperBound = b + sampleMean;

    /* Use indicator and take simple proportion in order to calculate p. */
    uint64_t index = 0;
    uint64_t indicator = 0;    
    Uniform uniformGenerator = Uniform();
    const uint64_t trials = 100000;
    for (int trialCount = 0; trialCount < trials; ++trialCount) {
        uint64_t tempSum = 0;
        double bootstrapEstimate = 0.0;

        /* Random sampling with replacement from data. */
        for (int i = 0; i < N; ++i) {
            index = (uint64_t) (uniformGenerator.next() * N);
            tempSum += data[index];
        }
        bootstrapEstimate = (double) tempSum / (double) N;

        /* How many are in the window? */
        if (bootstrapEstimate > lowerBound && bootstrapEstimate < upperBound) {
            ++indicator;
        }
    }

    cout << "Estimate of p after " << trials << " trials: ";
    cout << (double) indicator / (double) trials << endl;

    return 0;
}

/* stosim/src/ch8_p13.cpp */
