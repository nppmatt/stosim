/* stosim/src/oct_17.cpp */
#include "include/mc_random.hpp"

#include <iostream>

using std::cout;
using std::endl;

void p5_27() {
    double rate = 1.0;
    double timeLimit = 10.0;
    mcr::Exponential expGenerator = mcr::Exponential(rate);

    double timeElapsed = 0.0;
    while (timeElapsed < timeLimit) {
        cout << timeElapsed << endl;
        timeElapsed += expGenerator.next();
    }

}

void p5_29() {
    double busHourlyRate = 5.0;
    double timeLimit = 1.0;
    mcr::Exponential expGenerator = mcr::Exponential(busHourlyRate);

    double timeElapsed = 0.0;
    double totalFans = 0.0;
}

int main() {
    p5_27();
    p5_29(); // Simulate avg. number of people at event arriving by bus.
    //p5_30();

    return 0;
}
/* stosim/src/oct_17.cpp */

