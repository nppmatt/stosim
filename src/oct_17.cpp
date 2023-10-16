/* stosim/src/oct_17.cpp */
#include "include/mc_random.hpp"

#include <vector>
#include <map>
#include <set>
#include <functional>
#include <cmath>
#include <iostream>

using mcr::Uniform;
using std::cout;
using std::endl;

void p5_17() {
    std::function<double(double)> densityFunction = [](double x) {
        return 0.25 + 2 * pow(x, 3) + 1.25 * pow(x, 4);
    };
}

int main() {
    p5_17();
    //p5_19();
    //p5_20();
    //p5_23();
    //p5_27();
    //p5_29(); // Simulate avg. number of people at event arriving by bus.
    //p5_30();

    return 0;
}
/* stosim/src/oct_17.cpp */

