#include <iostream>

#include "primes.hpp"

constexpr std::uint64_t n{10'001};

void p7(std::ostream& os) {
    std::uint64_t currentPrime{2};
    for (std::uint64_t i{1}; i < n; ++i, currentPrime = nextPrime(currentPrime))
        ;
    os << currentPrime << '\n';
}
