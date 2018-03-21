#include <cstdint>
#include <iostream>

constexpr std::uint64_t x{100};

void p6(std::ostream& os) {
    // Comes from rewriting problem as a summation then expanding it out and
    // simplifying using algebra
    os << (x * (x - 1) * (x + 1) * (3 * x + 2)) / 12 << '\n';
}
