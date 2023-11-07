/* stosim/src/nov7.cpp */

#include "include/mc_random.hpp"

#include <cstdint>
#include <array>

using mcr::Exponential;

void p7_8() {
    /* Service times are exponential. */
    const double s1_rate = 4.0;
    const double s2_rate = 3.0;
    Exponential s1_serviceGenerator = Exponential(s1_rate);
    Exponential s2_serviceGenerator = Exponential(s2_rate);

    /* Arrival times are spanning Poi(6), aka have delta with distribution
     * Exp(6).
     */
    const double arrivalRate = 6.0;
    Exponential arrivalGenerator = Exponential(arrivalRate);
    const uint64_t arrivalLimit = 1000;

    const uint64_t numRealizations = 2;
    for (int n = 0; n < numRealizations; ++n) {
        /* Counters */
        double currentTime = 0.0;
        uint64_t numArrivals = 0;

        /* System State
         * May be expressed as the tuple: (n, s1, s2)
         */
        uint64_t currentCustomers = 0;
        uint64_t s1_customer = 0;
        uint64_t s2_customer = 0;

        /* Event Variables */
        double nextArrivalTime = 0.0;
        double s1_completionTime = 0.0;
        double s2_completionTime = 0.0;

        /* Recordkeeping */
        std::array<double, arrivalLimit> arrivalTimes;
        std::array<double, arrivalLimit> departureTimes;
        std::array<double, arrivalLimit> servicedBy;


        /* Simulation: 2 parallel servers, 1 shared queue */
        while (numArrivals < arrivalLimit) {

        }
    }
}

int main() {
    p7_8();
    //p7_9;
    //p7_10;
    //p7_11;
    return 0;
}

/* stosim/src/nov7.cpp */

