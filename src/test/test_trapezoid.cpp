#include "include/numeric.hpp"

#include <functional>
#include <cmath>
#include <iostream>

int main() {
    std::function<double(double)> myFunc;
    myFunc = [](double x) { return sqrt(x); };

    double a = 0;
    double b = 2;
    uint64_t n_1 = 2;
    uint64_t n_2 = 16;

    double approx_rough = num::trapezoidRule(myFunc, a, b, n_1);
    double approx_fine = num::trapezoidRule(myFunc, a, b, n_2);

    std::cout << "True integral of sqrt(x) over [0,2]: 1.885618083164127" << std::endl;
    std::cout << "Rough Approximation (n = 2): " << approx_rough << std::endl;
    std::cout << "Fine Approximation (n = 16): " << approx_fine << std::endl;

    return 0;
}
