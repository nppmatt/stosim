/* stosim/src/ch7_p18.cpp */

#include "include/mc_random.hpp"

#include <cstdint>
#include <limits>
#include <iostream>

using mcr::Exponential;
using mcr::Uniform;
using std::cout;
using std::endl;

/*
Toy Store Specification:
Simulate with LAMBDA = 5 and T = 100
Customer arrivals span Poisson(5), so arrivals are distributed over Exp(5).
Customers buy according to all-or-nothing/fill-or-kill rule.
Customers buy maximum of 3 units according to PMF.
Inventory is replenished instantly, only when current stock is empty.
Initial stock of 4 units.
10 units ordered per replenishment.

Loosely modeled on Ross Ex. 7.5, with no ordering time.

Quantity of interest is EV of customers who depart without making a purchase
in first T units of time.
*/

int main() {
    const double TIME_LIMIT = 100.0;
    const double ARRIVAL_RATE = 5.0;
    Exponential arrivalGenerator = Exponential(ARRIVAL_RATE);
    Uniform uniformGenerator = Uniform();

    uint64_t totalAngryCustomers = 0;
    const uint64_t REALIZE_TOTAL = 1000;
    for (uint64_t realizeNum = 1; realizeNum <= REALIZE_TOTAL; ++realizeNum) {
        /* System State */
        double currentTime = 0.0;
        uint64_t currentInventory = 4;

        /* Internal Counters */
        uint64_t customerDemand = 0;

        /* Events */
        const double NIL = std::numeric_limits<double>::max();
        double nextArrivalT = arrivalGenerator.getValue();
        double replenishT = NIL;

        /* Record Keeping */
        uint64_t sampleAngryCustomers = 0;

        while (currentTime < TIME_LIMIT) {
            /* Evaluate rules.
            Replenishment treated as discrete despite it being instant in
            this case, just to maintain structure.
            */
            bool arrivalIsNext = (nextArrivalT < replenishT);
            bool replenishIsNext = (replenishT <= nextArrivalT);

            /* Simulate after rule evaluation. */
            if (arrivalIsNext) {
                currentTime = nextArrivalT;

                /* Determine demand of this arrived customer based on
                specified PMF.
                */
                if (uniformGenerator.next() < 0.5) { customerDemand = 1; }
                else if (uniformGenerator.next() < (2/3)) { customerDemand = 2; }
                else { customerDemand = 3; }

                /* Adjust inventory if customer is served, else customer
                instantly leaves angry. Generate next arrival in the meantime.
                */
                if (customerDemand <= currentInventory) {
                    currentInventory -= customerDemand;
                }
                else {
                    ++sampleAngryCustomers;
                }
                nextArrivalT = currentTime + arrivalGenerator.next();

                /* If empty, ensure next event is replenishment. */
                if (currentInventory == 0) { replenishT = currentTime; }
            }
            else if (replenishIsNext) {
                currentInventory = 10;
                replenishT = NIL;
            }
        } /* END SIMULATION */

        totalAngryCustomers += sampleAngryCustomers;
        if (realizeNum % 100 == 0) {
            cout << "Realization #: " << realizeNum << " | ";
            cout << "Angry Cust. Expected Value (N = " << realizeNum << "): ";
            cout << (double) totalAngryCustomers / (double) realizeNum << endl;
        }
    } /* END REALIZATION */

    return 0;
}

/* stosim/src/ch7_p18.cpp */
