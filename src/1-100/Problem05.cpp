#include <iostream>
#include <numeric>

void p5(std::ostream& os) {
    std::uint64_t smallestMultiple{1};
    for (std::uint64_t i{1}; i <= 20; ++i)
        smallestMultiple = std::lcm(smallestMultiple, i);

    os << smallestMultiple << '\n';
}
