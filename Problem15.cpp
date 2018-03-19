#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

constexpr std::uint32_t goal{20};

int main() {
    // Use binomial coefficient to solve problem, get answer through pascal's triangle
    std::vector<std::uint64_t> prev{1, 1};
    for(std::uint64_t i = 1; i < goal * 2;++i) {
        std::vector<std::uint64_t> next;
        std::transform(prev.begin() + 1, prev.end(), prev.begin(), std::back_inserter(next), std::plus<std::uint64_t>());
        next.insert(next.begin(), 1);
        next.push_back(1);
        prev = std::move(next);
    }
    std::cout << *(std::max_element(prev.begin(), prev.end())) << '\n';
}
