/* stosim/src/oct_17.cpp */
#include "include/mc_random.hpp"

#include <iostream>
#include <functional>

using std::cout;
using std::endl;

void p5_27() {
    double rate = 1.0;
    double timeLimit = 10.0;
    mcr::Exponential expGenerator = mcr::Exponential(rate);

    cout << "Problem 5.27: Generating arbitrary Poisson path." << endl;

    double timeElapsed = 0.0;
    while (timeElapsed < timeLimit) {
        cout << "t = " << timeElapsed << endl;
        timeElapsed += expGenerator.next();
    }

    cout << endl;
}

void p5_29() {
    double busHourlyRate = 5.0;
    double timeLimit = 1.0;
    mcr::Exponential expGenerator = mcr::Exponential(busHourlyRate);
    mcr::Uniform uniformGenerator = mcr::Uniform();

    cout << "Problem 5.29: Simulating arrival of bussed fans." << endl;
    cout << "Time (hours) | Total Fans" << endl;

    double timeElapsed = 0.0;
    uint64_t totalFans = 0;
    uint64_t totalEvents = 0;
    while (timeElapsed < timeLimit) {
        cout << "t = " << timeElapsed << " | n = " << totalFans << endl;
        totalFans += (uint64_t)(21 * uniformGenerator.next()) + 20;
        ++totalEvents;
        timeElapsed += expGenerator.next();
    }

    double averageFans = (double)totalFans / (double)totalEvents;
    cout << "This realization's average Fans per Bus: " << averageFans << endl;

    cout << endl;
}

/* Incomplete */
void p5_30() {
    std::function<double(double)> poissonRate = [](double t){ return 3 + 4 / (t + 1); };
    //mcr::Exponential expGenerator = mcr::Exponential(rate);
    mcr::Uniform uniformGenerator = mcr::Uniform();

    uint64_t eventLimit = 10;
    uint64_t totalEvents = 0;
    while (totalEvents < eventLimit) {
        ++totalEvents;
    }

}

int main() {
    p5_27();
    p5_29(); // Simulate avg. number of people at event arriving by bus.
    p5_30();

    return 0;
}
/* stosim/src/oct_17.cpp */

