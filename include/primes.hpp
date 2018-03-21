#pragma once

#include <cmath>
#include <cstdint>
#include <type_traits>

template <typename Integral>
bool isPrime(Integral x) {
    static_assert(std::is_integral<Integral>::value,
                  "Can only check primes for integer type values");

    if ((x == 1) || (x == 0)) return false;

    if (x == 2) return true;

    // This check is quick because the compiler optimizes checking bit 0
    if (x % 2 == 0) return false;

    if (x < 0) x = -x;

    Integral max = std::floor(std::sqrt(x));
    for (std::uint64_t i = 3; i <= max; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

template <typename Integral>
Integral nextPrime(Integral x) {
    do {
        ++x;
    } while (!isPrime(x));
    return x;
}
