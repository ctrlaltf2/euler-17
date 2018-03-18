#include <iostream>
#include <numeric>

#include "lib/LazyArray.hpp"

int main() {
    LazyArray<short> numbers(
        [](const short x) -> short { return x + 1; });  // 1x + 1
    numbers.setEnd(1000);

    std::cout << std::accumulate(numbers.begin(), numbers.end(), 0,
                                 [](int current, const short val) {
                                     if ((val % 3 == 0) || (val % 5 == 0))
                                         return current + val;
                                     else
                                         return current;
                                 })
              << std::endl;
}
