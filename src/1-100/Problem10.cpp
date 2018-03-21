#include <cstdint>
#include <iostream>

#include "primes.hpp"

constexpr std::uint32_t goal{2'000'000};

void p10(std::ostream& os) {
    std::uint64_t sum{0};
    std::uint32_t currentPrime{2};
    while (currentPrime < goal) {
        sum += currentPrime;
        currentPrime = nextPrime(currentPrime);
    }

    os << sum << '\n';
}
