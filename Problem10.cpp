#include <cstdint>
#include <iostream>

#include "util/primes.hpp"

constexpr std::uint32_t goal{2'000'000};

int main() {
    std::uint64_t sum{0};
    std::uint32_t currentPrime{2};
    while (currentPrime < goal) {
        sum += currentPrime;
        currentPrime = nextPrime(currentPrime);
    }

    std::cout << sum << '\n';
}
