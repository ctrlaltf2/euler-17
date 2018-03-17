#include <iostream>
#include <numeric>

int main() {
    std::uint64_t smallestMultiple{1};
    for (std::uint64_t i{1}; i <= 20; ++i)
        smallestMultiple = std::lcm(smallestMultiple, i);

    std::cout << smallestMultiple << '\n';
}
