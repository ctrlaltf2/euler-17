#include "lib/LazyArray.hpp"

#include <cmath>

constexpr double sqrt5{2.2360679774997896964091736};

int main() {
    LazyArray<long> fibs([](const long x) {
        double a = (1 + sqrt5) / 2.0;
        double b = (1 - sqrt5) / 2.0;

        return std::floor((std::pow(a, x) - std::pow(b, x)) / sqrt5);
    });

    long sum{0};
    for (const long i : fibs) {
        if (i > 4'000'000) break;

        if (i % 2 == 0) sum += i;
    }

    std::cout << sum << '\n';
}
