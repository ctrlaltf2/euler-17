#include <iostream>

#include "util/primes.hpp"

constexpr std::uint64_t n{10'001};

int main() {
    std::uint64_t currentPrime{2};
    for (std::uint64_t i{1}; i < n; ++i, currentPrime = nextPrime(currentPrime))
        ;
    std::cout << currentPrime << '\n';
}
