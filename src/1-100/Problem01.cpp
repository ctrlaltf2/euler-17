#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

constexpr int max{1000};

void p1(std::ostream& os) {
    std::vector<short> numbers(max - 1);
    std::iota(numbers.begin(), numbers.end(), 1);

    numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                                 [](const int& i) -> bool {
                                     return (i % 3 != 0) && (i % 5 != 0);
                                 }),
                  numbers.end());

    os << std::accumulate(numbers.begin(), numbers.end(), 0) << '\n';
}
