#include "include/numeric.hpp"
#include "include/mcrandom.hpp"

#include <functional>
#include <cmath>
#include <iostream>

void p5() {
    std::function<double(double)> myFunc;
    myFunc = [](double x) { return exp(x + x*x); };
    double a = -2;
    double b = 2;
    uint64_t trapezoid_count = 100;
    uint64_t mc_trials = 100;

    double approx_trapezoid = num::trapezoidRule(myFunc, a, b, trapezoid_count);
    double approx_mc = mcr::integrateMonteCarlo(myFunc, a, b, mc_trials);

    std::cout << "P5: True integral of exp^(x + x^2) over [-2,2]: 93.1628" << std::endl;
    std::cout << "Trapezoid Rule Approximation (n = 100): " << approx_trapezoid << std::endl;
    std::cout << "Monte Carlo Approximation (n = 100): " << approx_mc << std::endl;

    std::cout << std::endl;
}

void p7() {
    std::function<double(double)> myFunc;
    myFunc = [](double x) { return exp(-x*x); };
    uint64_t mc_trials = 100;

    double approx_mc = mcr::integrateMonteCarloInfUpper(myFunc, mc_trials);
    approx_mc *= 2; // Question integrates over (-inf., inf.), so multiply by 2.

    std::cout << "P7: True integral of exp^(-x^2) over [0,inf.): 1.77245" << std::endl;
    std::cout << "Monte Carlo Approximation (n = 100): " << approx_mc << std::endl;

    std::cout << std::endl;
}

void p12() {
    mcr::Uniform myUniform = mcr::Uniform();

    /* 12a */
    std::vector<double> uniform_expectation(3);
    std::vector<uint64_t> trials = {100, 1000, 10000};
    for (int i = 0; i < trials.size(); ++i) {
        for (int n = 0; n < trials[i]; ++n) {
            uniform_expectation[i] += myUniform.next();
        }
        uniform_expectation[i] /= trials[i];
    }

    std::cout << "P12: Expectations for U(0,1) for n = 100, 1000, 10000" << std::endl;
    for (auto & result : uniform_expectation) {
        std::cout << result << std::endl;
    }
 
    std::cout << "Human intuition says it's 0.5 or (1/2)." << std::endl;
    std::cout << std::endl;
}

int main() {
    p5();
    p7();
    //p9();
    //p10();
    p12();
    //p13();
    //p14();

    return 0;
}
