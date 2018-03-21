#include <cmath>
#include <iostream>
#include <numeric>

constexpr int goal{1000};

void p9(std::ostream& os) {
    for (std::uint64_t m = 1; m < 100; ++m) {
        for (std::uint64_t n = m; n < 100; ++n) {
            // Euclid's formula
            if ((m % 2) && (n % 2)) continue;
            if (std::gcd(m, n) != 1) continue;

            std::uint64_t a{(n * n) - (m * m)}, b{2 * m * n};

            if (a > goal || b > goal) break;

            // At this point we have a unique primitive pythagorean triple

            const std::uint64_t A = a, B = b, C = std::sqrt(a * a + b * b);

            // Check all the multiples of that primitive triple up until the sum
            // is too large
            int i{2};
            do {
                if (i * (A + B + C) == goal) {
                    os << A * i * B * i * C * i << '\n';
                    return;
                }
            } while (i++ * (A + B + C) < goal);
        }
    }
}
