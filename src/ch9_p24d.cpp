/* stosim/src/ch9_p24d.cpp */

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

/* Using control variate. */
int main() {
    Uniform uniformGenerator = Uniform();

    /* Service times are exponential. */
    const double SERVICE_RATE = 1.0;
    Exponential serviceGenerator = Exponential(uniformGenerator, SERVICE_RATE);

    /* Arrival times are spanning Poi(2.0),
     * aka have delta with distribution Exp(2.0).
     */
    const double ARRIVAL_RATE = 2.0;
    Exponential arrivalGenerator = Exponential(uniformGenerator, ARRIVAL_RATE);

    /* Goal (theta) is estimating "raw" variance of first 10 wait times. */
    const uint64_t DEPARTURE_LIMIT = 10;

    const double Z = 3.0; // sure to within 0.27%
    double lastMean = 0.0;
    double lastControlMean = 0.0;
    double sampleMean = 0.0;
    double sampleControlMean = 0.0;
    double sampleVar = 0.0;
    double sampleControlVar = 0.0;
    double sampleCov = 0.0;
    double sampleSD = 0.0;
    double controlEstimator = 0.0;

    uint64_t trialNum = 0;
    double estimate = 1.0;
    const double TOLERANCE = 1.0; // within a minute
    while (trialNum <= 100 || estimate >= TOLERANCE) {
        ++trialNum;

        /* Counters */
        double currentTime = 0.0;
        uint64_t numArrivals = 0; // AKA Customer ID
        uint64_t numDepartures = 0;

        /* System State */
        uint64_t currentCustomers = 0;

        /* Event Variables */
        const double NIL = std::numeric_limits<double>::max();
        double nextArrivalT = arrivalGenerator.getValue();
        double nextDepartureT = NIL;

        /* Recordkeeping */
        const uint64_t PREALLOCATE_COUNT = 100;
        std::vector<double> arrivalTimes;
        std::vector<double> departureTimes;
        arrivalTimes.reserve(PREALLOCATE_COUNT);
        departureTimes.reserve(PREALLOCATE_COUNT);

        /* Simulation: M/M/1, single server, single queue. */
        while (numDepartures < DEPARTURE_LIMIT) {
            if (nextArrivalT <= nextDepartureT) {
                currentTime = nextArrivalT;
                ++numArrivals;
                ++currentCustomers;
                nextArrivalT = currentTime
                    + arrivalGenerator.next();                
                if (currentCustomers == 1) {
                    nextDepartureT = currentTime + serviceGenerator.next();
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
                else {
                    nextDepartureT = currentTime + serviceGenerator.next();
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
        double controlSample = 0.0;
        for (double& wt : waitTimes) {
            sample += wt;
        }

        /* Control variate in this case is now the sum of the
         * difference between total service time and total interarrival times.
         */
        for (double& d : departureTimes) {
            controlSample += d;
        }
        double tempSum = 0.0;
        for (uint64_t i = 0; i < DEPARTURE_LIMIT - 1; ++i) {
            tempSum += (arrivalTimes[i+1] - arrivalTimes[i]);
        }
        controlSample -= tempSum;

        /* Goal: estimate via fit with control variate (Ross pg. 161) */
        lastMean = sampleMean;
        sampleMean += (sample - sampleMean) / trialNum;

        lastControlMean = sampleControlMean;
        sampleControlMean += (controlSample - sampleControlMean) / trialNum;

        if (trialNum > 1) {
            /* Variances calculated using recursive scheme. */
            sampleVar = ( 1 - (1 / ((double) trialNum - 1)) )
            * sampleVar
            + (double) trialNum * pow((sampleMean - lastMean), 2);

            sampleControlVar = ( 1 - (1 / ((double) trialNum - 1)) )
            * sampleControlVar
            + (double) trialNum * pow((sampleControlMean - lastControlMean), 2);
    
            /* Online covariance calculation. */
            sampleCov = ( 1 - (1 / ((double) trialNum - 1)) )
            * sampleCov
            + (double) trialNum
            * (sampleMean - lastMean) * (sampleControlMean - lastControlMean);

            /* Standard Dev. of control estimator. */
            controlEstimator =
                (sampleVar - (sampleCov * sampleCov / sampleControlVar));
            sampleSD = sqrt(controlEstimator);
            estimate = Z * sampleSD / sqrt((double) trialNum);
        }
    } /* REALIZATION END */

    /* Printing to console. */
    cout << "Goal/Theta: Average total wait time of first ";
    cout << DEPARTURE_LIMIT << " customers." << endl;

    cout << "Percent Certainty (alpha): " << "99.73 (0.27)\%" << endl;
    cout << "Time Tolerance: " << TOLERANCE << " minute(s)" << endl;

    cout << "Number of trials: " << trialNum << endl;
    cout << "Estimated Variance (Service minus IAT Control): ";
    cout << controlEstimator << " minutes." << endl;
    cout << endl;

    return 0;
}

/* stosim/src/ch9_p24d.cpp */
