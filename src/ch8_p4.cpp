/* stosim/src/ch8_p4.cpp */

#include "include/mc_random.hpp"

#include <cmath>
#include <array>
#include <vector>
#include <iostream>

using mcr::Uniform;
using std::cout;
using std::endl;

int main() {
    /* Statistics */
    double mean = 0.0;
    double variance = 1.0;
    double squaredSum = 0.0;
    double sampleSD = 0.0;
    double totalSum = 0.0;
    double sampleVar = 0.0;
    
    /* Pre-allocate 100 words for storing normal samples for now. */
    std::vector<double> normalVector;
    normalVector.reserve(100);

    /* Generating pairs of normals and adding to vector as needed. */
    std::array<double, 2> generatedPair;

    double tolerance = 0.1;
    double test = 2.0;
    std::array<double, 2> result;
    Uniform uniformGenerator = Uniform();
    uint64_t n = 0;
    while (n <= 100 && test >= tolerance) {
        cout << " "; // dirty hack to fix a buffer overflow
        
        /* Quick Box-Mueller */
        double u1, u2, v1, v2;
        double S = 2.0;
        while (S > 1.0) {
            u1 = uniformGenerator.next();
            u2 = uniformGenerator.next();
            v1 = 2*u1 - 1;
            v2 = 2*u2 - 1;
            S = v1*v1 + v2*v2;
        }
        
        double X = sqrt((-2 * log(S)) / S) * v1;
        double Y = sqrt((-2 * log(S)) / S) * v2;
        
        result = {X, Y};

        /* Naively adding whole pairs. */
        normalVector[n] = result[0];
        normalVector[n+1] = result[1];
        n += 2;

        squaredSum = 0.0;
        for (int i = 0; i < n; ++i) {
            totalSum += normalVector[i];
            squaredSum += (normalVector[i] * normalVector[i]);
        }
        sampleSD = sqrt(squaredSum / (n - 1));
        test = sampleSD / sqrt((double) n);
    }

    cout << "Finished. Generated " << n << " normals." << endl;
    cout << "Sample Mean: " << totalSum / (double) n << endl;
    cout << "Sample Variance: " << squaredSum / (double) (n - 1) << endl;

    return 0;
}
/* stosim/src/ch8_p4.cpp */
 