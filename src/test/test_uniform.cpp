#include "include/mc_random.hpp"

#include <iostream>

int main() {
    mcr::Uniform defaultUniform = mcr::Uniform();
    mcr::Uniform customUniform = mcr::Uniform(6911123111);
    
    int n = 4;
    for (int i = 0; i < n; ++i) {
        std::cout << defaultUniform.next() << std::endl;
        std::cout << customUniform.next() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
