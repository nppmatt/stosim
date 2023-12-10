/* stosim/src/ch9_p5.cpp */

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
    
    /* Pre-allocate 100 words for storing samples for now. */
    std::vector<double> thetaVector;
    thetaVector.reserve(100);

    /* Generating pairs of normals and adding to vector as needed. */
    std::array<double, 2> generatedPair;

    double tolerance = 0.1;
    double test = 2.0;
    std::array<double, 2> normalResult;
    std::array<double, 2> antiResult;
    Uniform uniformGenerator = Uniform();
    uint64_t n = 0;

    while (n <= 100 && test >= tolerance) {
        /* Duplicating Box-Mueller with addition of antithetic variates. */
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
        
        S = 2.0;
        while (S > 1.0) {
            u1 = 1.0 - u1;
            u2 = 1.0 - u2;
            v1 = 2*u1 - 1;
            v2 = 2*u2 - 1;
            S = v1*v1 + v2*v2;
        }
        double anti_X = sqrt((-2 * log(S)) / S) * v1;
        double anti_Y = sqrt((-2 * log(S)) / S) * v2;

        normalResult = {X, Y};
        antiResult = {anti_X, anti_Y};

        /* According to scheme laid out in (9.5) */
        double Z_alpha = (normalResult[0] + antiResult[0]) / 2;
        double Z_beta = (normalResult[1] + antiResult[1]) / 2;
        thetaVector[n] = pow(Z_alpha, 3.0) * exp(Z_alpha);
        thetaVector[n+1] = pow(Z_beta, 3.0) * exp(Z_beta);
        n += 2;

        if (n % 100 == 0) {
            squaredSum = 0.0;
            for (uint64_t i = 0; i < n; ++i) {
                totalSum += thetaVector[i];
                squaredSum += (thetaVector[i] * thetaVector[i]);
            }
            sampleSD = sqrt(squaredSum / (n - 1));
            test = sampleSD / sqrt((double) n);
        }
    }

    cout << "Finished under tolerance. ";
    cout << "Generated " << n << " realizations." << endl;
    cout << "Sample Mean: " << totalSum / (double) n << endl;
    cout << "Sample Variance: " << squaredSum / (double) (n - 1) << endl;

    return 0;
}
/* stosim/src/ch9_p5.cpp */
 
