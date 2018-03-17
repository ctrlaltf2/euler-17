#include <cmath>
#include <cstdint>
#include <iostream>

#include "util/primes.hpp"

constexpr std::uint64_t goal{600'851'475'143};

int main() {
    std::uint64_t workingNumber = goal;
    while (!isPrime(workingNumber)) {
        std::uint64_t i{2};
        do {
            if (workingNumber % i == 0) {
                workingNumber /= i;
                break;
            }
        } while (++i);
    }
    std::cout << workingNumber << '\n';
}
