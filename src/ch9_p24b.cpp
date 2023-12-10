/* stosim/src/ch9_p24b.cpp */

#include "include/mc_random.hpp"

#include <cstdint>
#include <array>
#include <vector>
#include <limits>
#include <iostream>
#include <cmath>

using mcr::Uniform;
using mcr::Exponential;
using std::cout;
using std::endl;

double regularExp(double U, double lambda) {
    return -log(1 - U) / lambda;
}
double antitheticExp(double U, double lambda) {
    return -log(U) / lambda;
}

/* Using antithetic variables. */
int main() {
    Uniform uniformGenerator = Uniform();

    /* Service times are exponential. */
    const double SERVICE_RATE = 1.0;

    /* Arrival times are spanning Poi(2.0),
     * aka have delta with distribution Exp(2.0).
     */
    const double ARRIVAL_RATE = 2.0;

    /* Goal (theta) is estimating "raw" variance of first 10 wait times. */
    const uint64_t DEPARTURE_LIMIT = 10;

    const double Z = 3.0; // sure to within 0.27%
    double lastMean = 0.0;
    double sampleMean = 0.0;
    double sampleVar = 0.0;
    double sampleSD = 0.0;

    bool isAnti = true;
    std::array<double, 100> uniformVector;
    uint64_t trialNum = 0;
    double estimate = 1.0;
    const double TOLERANCE = 1.0; // within 1 min
    while (trialNum <= 100 || estimate >= TOLERANCE) {
        /* Generating uniform variables in batches of 100. */
        for (uint64_t i = 0; i < 100; ++i) {
            uniformVector[i] = uniformGenerator.next();
        }
        ++trialNum;


        /* Counters */
        double currentTime = 0.0;
        uint64_t numArrivals = 0; // AKA Customer ID
        uint64_t numDepartures = 0;

        /* System State, alternate with antithetic sim. */
        uint64_t currentCustomers = 0;
        isAnti = (isAnti != true);

        /* Event Variables */
        const double NIL = std::numeric_limits<double>::max();
        double nextArrivalT = regularExp(uniformVector[0], ARRIVAL_RATE);
        double nextDepartureT = NIL;

        /* Recordkeeping */
        const uint64_t PREALLOCATE_COUNT = 100;
        std::vector<double> arrivalTimes;
        std::vector<double> departureTimes;
        arrivalTimes.reserve(PREALLOCATE_COUNT);
        departureTimes.reserve(PREALLOCATE_COUNT);

        /* Simulation done pairwise with antithetic variate. */
        while (numDepartures < DEPARTURE_LIMIT) {
            if (nextArrivalT <= nextDepartureT) {
                currentTime = nextArrivalT;
                ++numArrivals;
                ++currentCustomers;

                if (!isAnti) {
                    nextArrivalT = currentTime
                        + regularExp(uniformVector[numArrivals - 1], ARRIVAL_RATE);
                    if (currentCustomers == 1) {
                        nextDepartureT = currentTime
                        + regularExp(uniformVector[numArrivals], SERVICE_RATE);
                    }
                }
                else {
                    nextArrivalT = currentTime
                        + antitheticExp(uniformVector[numArrivals - 1], ARRIVAL_RATE);
                    if (currentCustomers == 1) {
                        nextDepartureT = currentTime
                        + antitheticExp(uniformVector[numArrivals], SERVICE_RATE);
                    }
                }
                arrivalTimes.emplace_back(currentTime);
            }
            else if (nextDepartureT < nextArrivalT) {
                currentTime = nextDepartureT;
                ++numDepartures;
                --currentCustomers;

                if (currentCustomers == 0) {
                    nextDepartureT = NIL;
                }
                else if (!isAnti) {
                    nextDepartureT = currentTime
                    + regularExp(uniformVector[numArrivals], SERVICE_RATE);
                }
                else {
                    nextDepartureT = currentTime
                    + antitheticExp(1 - uniformVector[numArrivals], SERVICE_RATE);
                }
                departureTimes.emplace_back(currentTime);
            }
        } /* SIM END */
    
        /* Realization Statistics 
         * Sum of simulated wait times is a single sample "X"
         * i.e. X = T_1 + T_2 + ... + T_10
         */
        std::array<double, DEPARTURE_LIMIT> waitTimes;
        for (uint64_t i = 0; i < DEPARTURE_LIMIT; ++i) {
            waitTimes[i] = departureTimes[i] - arrivalTimes[i];
        }
        
        double sample = 0.0;
        for (double& wt : waitTimes) {
            sample += wt;
        }

        /* Goal: estimate theta = Var(X) recursively (Ross pg. 137) */
        lastMean = sampleMean;
        sampleMean += (sample - sampleMean) / trialNum;

        if (trialNum > 1) {
            sampleVar = ( 1 - (1 / ((double) trialNum - 1)) ) * sampleVar
                + (double) trialNum * pow((sampleMean - lastMean), 2);
            sampleSD = sqrt(sampleVar);
            estimate = Z * sampleSD / sqrt((double) trialNum);
        }
    } /* REALIZATION END */

    /* Printing to console. */
    cout << "Goal/Theta: Average total wait time of first ";
    cout << DEPARTURE_LIMIT << " customers." << endl;

    cout << "Percent Certainty (alpha): " << "99.73 (0.27)\%" << endl;
    cout << "Time Tolerance: " << TOLERANCE << " minute(s)" << endl;

    cout << "Number of trials: " << trialNum << endl;
    cout << "Estimated Variance (Antithetic): " << sampleVar << " minutes." << endl;
    cout << endl;

    return 0;
}

/* stosim/src/ch9_p24b.cpp */
