/* stosim/src/oct_10.cpp */
#include "include/mc_random.hpp"

#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <iostream>

using mcr::Uniform;
using std::cout;
using std::endl;

void p4_16() {
    constexpr int steps = 3;
    constexpr int N = 10;
    constexpr int values[steps][N] = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5, 6, 7, 9, 10}
    };
    Uniform u_gen = Uniform();

    constexpr int trials = 1000000;
    int results[trials];
    double U_1, U_2;
    int idx;
    for (int i = 0; i < trials; ++i) {
        U_1 = u_gen.next();
        U_2 = u_gen.next();
        if (U_1 < 0.5) {
            idx = (int) 5 * U_2;
            results[i] = values[1][idx];
        }
        else if (U_1 < 0.2) {
            idx = (int) 9 * U_2;
            results[i] = values[2][idx];
        }
        else {
            idx = (int) (10 * U_2) + 1;
            results[i] = idx;
        }
    }

    /* Get frequencies of each value. */
    int histo[N] = {};
    for (int n = 0; n < N; ++n) {
        for (int i = 0; i < trials; ++i) {
            if (results[i] == n + 1) {
                ++histo[n];
            }
        }
    }

    cout << "Value : Frequency" << endl;
    for (int n = 0; n < N; ++n) {
        cout << (n + 1) << " : " << ((double)histo[n] / trials) << endl;
    }

}

int main() {
    p4_16();
    //p4_17();
    //p5_2();
    //p5_4();
    //p5_5();
    //p5_7();
    //p5_8();
    //p5_10();

    return 0;
}
/* stosim/src/oct_10.cpp */

