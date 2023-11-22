#include "include/mc_random.hpp"

#include <iostream>

int main() {
    mcr::Uniform defaultUniform = mcr::Uniform();
    mcr::Uniform customUniform = mcr::Uniform(11111111111111);
    
    int n = 3;
    for (int i = 0; i < n; ++i) {
        std::cout << defaultUniform.next() << std::endl;
        std::cout << customUniform.next() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
