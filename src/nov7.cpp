/* stosim/src/nov7.cpp */

#include "include/mc_random.hpp"

#include <cstdint>

void p7_8() {
    const double s1_rate = 4.0;
    const double s2_rate = 3.0;
    mcr::Exponential s1_service = mcr::Exponential(s1_rate);
    mcr::Exponential s2_service = mcr::Exponential(s2_rate);

    const double arrivalRate = 6.0;
    const uint64_t numArrivals = 1000;
}

int main() {
    p7_8();
    //p7_9;
    //p7_10;
    //p7_11;
    return 0;
}

/* stosim/src/nov7.cpp */

