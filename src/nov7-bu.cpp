/* stosim/src/nov7.cpp */

#include "include/mc_random.hpp"

#include <cstdint>
#include <array>
#include <limits>
#include <iostream>

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
        uint64_t numArrivals = 0; // AKA Customer ID

        /* System State
         * May be expressed as the tuple: (n, s1, s2)
         */
        uint64_t currentCustomers = 0;
        uint64_t s1_customer = 0;
        uint64_t s2_customer = 0;

        /* Event Variables */
        const double NIL = std::numeric_limits<double>::max();
        double nextArrivalT = arrivalGenerator.getValue();
        double s1_finishT = NIL;
        double s2_finishT = NIL;

        /* Recordkeeping */
        std::array<double, arrivalLimit> arrivalTimes = {};
        std::array<double, arrivalLimit> departureTimes = {};
        std::array<uint64_t, arrivalLimit> servedBy = {};

        /* Simulation: 2 parallel servers, 1 shared queue */
        uint64_t laterCustomer = 0;
        while (numArrivals < arrivalLimit) {
            if (nextArrivalT < s1_finishT && nextArrivalT < s2_finishT) {
                currentTime = nextArrivalT;
                ++numArrivals;
                nextArrivalT = currentTime + arrivalGenerator.next();
                arrivalTimes[numArrivals] = currentTime;

                if (currentCustomers > 1) {
                    ++currentCustomers;
                }
                else if (currentCustomers == 1) {
                    ++currentCustomers;
                    if (s1_customer != 0) {
                        s2_customer = numArrivals;
                        s2_finishT = currentTime + s2_serviceGenerator.next();
                        servedBy[numArrivals] = 2;
                    }
                    else if (s2_customer != 0) {
                        s1_customer = numArrivals;
                        s1_finishT = currentTime + s1_serviceGenerator.next();
                        servedBy[numArrivals] = 1;
                    }
                }
                /* DEFAULT PATH IF NO CUSTOMERS PRESENT */
                else {
                    ++currentCustomers;
                    s2_customer = 0;
                    s1_customer = numArrivals;
                    s1_finishT = currentTime + s1_serviceGenerator.next();
                    servedBy[numArrivals] = 1;
                }
            }
            else if (s1_finishT < nextArrivalT && s1_finishT <= s2_finishT) {
                currentTime = s1_finishT;
                departureTimes[s1_customer] = currentTime;

                if (currentCustomers > 2) {
                    laterCustomer = s1_customer;
                    if (s2_customer > s1_customer) {
                        laterCustomer = s2_customer;
                    }
                    --currentCustomers;
                    s1_customer = laterCustomer + 1;
                    s1_finishT = currentTime + s1_serviceGenerator.next();
                    servedBy[s1_customer] = 1;
                }
                else if (currentCustomers == 2) {
                    --currentCustomers;
                    s1_customer = 0;
                    s1_finishT = NIL;
                }
                else if (currentCustomers == 1) {
                    --currentCustomers;
                    s1_customer = 0;
                    s2_customer = 0;
                    s1_finishT = NIL;
                }
            }
            else if (s2_finishT < nextArrivalT && s2_finishT <= s1_finishT) {
                currentTime = s2_finishT;
                departureTimes[s2_customer] = currentTime;

                if (currentCustomers > 2) {
                    laterCustomer = s1_customer;
                    if (s2_customer > s1_customer) {
                        laterCustomer = s2_customer;
                    }
                    --currentCustomers;
                    s2_customer = laterCustomer + 1;
                    s2_finishT = currentTime + s2_serviceGenerator.next();
                    servedBy[s2_customer] = 2;
                }
                else if (currentCustomers == 2) {
                    --currentCustomers;
                    s2_customer = 0;
                    s2_finishT = NIL;
                }
                else if (currentCustomers == 1) {
                    --currentCustomers;
                    s1_customer = 0;
                    s2_customer = 0;
                    s2_finishT = NIL;
                }
            }
        } /* SIM END */

        double avgWait = 0.0;
        double totalWait = 0.0;
        for (int i = 0; i < arrivalLimit; ++i) {
            std::cout << "departureT: " << departureTimes[i] << " | arrivalT: " << arrivalTimes[i] << std::endl;
            totalWait += (departureTimes[i] - arrivalTimes[i]);
        }
        avgWait = totalWait / (double) arrivalLimit;

        double s1_ratio = 0.0;
        uint64_t s1_hits = 0;
        for (int i = 0; i < arrivalLimit; ++i) {
            s1_hits += (servedBy[i] & 1);
        }
        s1_ratio = (double) s1_hits / (double) arrivalLimit;

        std::cout << "Realization #" << (n+1) << std::endl;
        std::cout << "a) Average time in system: " << avgWait << std::endl;
        std::cout << "b) Server 1 Service Ratio: " << s1_ratio << std::endl;
        std::cout << std::endl;
    } /* REALIZE END */
}

int main() {
    p7_8();
    //p7_9;
    //p7_10;
    //p7_11;
    return 0;
}

/* stosim/src/nov7.cpp */

