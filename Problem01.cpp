#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#define kMax 1000

int main() {
    std::vector<short> numbers(kMax - 1);
    std::iota(numbers.begin(), numbers.end(), 1);

    numbers.erase( std::remove_if( numbers.begin(), numbers.end(), [](const int& i) -> bool {
                    return (i % 3 != 0) &&
                           (i % 5 != 0);
                }),
                numbers.end());

    std::cout << std::accumulate(numbers.begin(), numbers.end(), 0) << std::endl;
    return 0;
}
