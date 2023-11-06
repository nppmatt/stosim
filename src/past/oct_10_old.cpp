/* stosim/src/oct_10.cpp */
#include "include/mc_random.hpp"

#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <iostream>

void p4_16() {
    const int N = 10;
    const int values[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const double probability[N] = {0.06, 0.06, 0.06, 0.06, 0.06, 0.15, 0.13, 0.14, 0.15, 0.13};

    /* Step 1: Same probabilities get grouped into buckets.
     * Map is used with each entry having the form: <probability, {bucket set members}>
     */
    std::map<double, std::set<int>> bucketMap;
    for (int i = 0; i < N; ++i) {
        bucketMap[probability[i]].insert(values[i]);
    }

    /* Step 2: Associate the membership proportion with each bucket ("pretend" prior probability).
     * Stored as vectors first, then appended to the final result when we merge.
     */
    std::vector<double> priorVec;
    std::vector<std::set<int>> bucketVec;
    auto it_prior = priorVec.begin();
    auto it_bucket = bucketVec.begin();
    for (auto const& [prob, bucket] : bucketMap) {
        it_prior = priorVec.insert( it_prior, (double)bucket.size() / N );
        it_bucket = bucketVec.insert( it_bucket, bucket );
    }

    /* Step 3: Merging the buckets based on similar probability, then sorting them. */

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

