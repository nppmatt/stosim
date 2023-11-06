#include "include/mc_random.hpp"

#include <cmath>
#include <vector>
#include <iostream>

/* Given piecewise "steady" increase/decrease for lambda function. */
double thinned_NHPP(double t) {
    double modTime = std::fmod(t, 10.0);
    if ( modTime <= 5 ) {
        return (3.0 / 19.0) * modTime + (4.0 / 19.0);
    }
    modTime -= 5.0;
    return 1 - (modTime * (3.0 / 19.0));
}

void p7_3() {
    double rateMax = 19.0;
    mcr::Exponential expThinning = mcr::Exponential(rateMax);
    mcr::Uniform uniformGenerator = mcr::Uniform();

    /* Generate arrivals via thinning. */
    std::vector<double> arrivals;
    double candidateTime;
    double timeLimit = 100.0;
    double timeElapsed = expThinning.next();
    while (timeElapsed < timeLimit) {
        candidateTime = thinned_NHPP(timeElapsed);
        if (uniformGenerator.next() <= candidateTime) {
            arrivals.emplace_back(candidateTime);
        }
        timeElapsed += expThinning.next();
    }

    double serviceRate = 25.0;
    mcr::Exponential expService = mcr::Exponential(serviceRate);

    double breakMax = 0.3;
    double breakTotal = 0.0;
    uint64_t trials = 500;
    for (int i = 0; i < trials; ++i) {
        double accumulatedBreak = 0.0; 
        double breakTime = 0.0;

        uint64_t nextArrival = 1;
        double simulationTime = arrivals[0];
        while (simulationTime < timeLimit) {
            if (simulationTime < arrivals[nextArrival]) {
                breakTime = uniformGenerator.next() * breakMax;
                accumulatedBreak += breakTime;
                simulationTime += breakTime;
            }
            else {
                simulationTime += expService.next();
                ++nextArrival;
            }
        }
        breakTotal += accumulatedBreak;
    }

    std::cout << "Average break time server is taking for first 100 hours: " << (breakTotal / (double) trials) << " hours" << std::endl;
}

int main() {
    p7_3();
    return 0;
}
