#include "include/mc_random.hpp"

#include <iostream>

int main() {
    mcr::Uniform myUniform = mcr::Uniform();
    
    int n = 1000000;
    for (int i = 0; i < n; ++i) {
        std::cout << myUniform.next() << std::endl;
    }

    return 0;
}
