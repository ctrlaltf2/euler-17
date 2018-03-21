#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

void p2(std::ostream& os) {
    std::vector<int> fibs = []() -> std::vector<int> {
        std::vector<int> ret{1, 2};
        int i{1};

        while (true) {
            int next = ret[i] + ret[i - 1];

            if (next >= 4'000'000) break;

            ret.push_back(next);
            ++i;
        }
        return ret;
    }();

    fibs.erase(
        std::remove_if(fibs.begin(), fibs.end(),
                       [](const int& i) -> bool { return (i % 2) == 1; }),
        fibs.end());
    os << std::accumulate(fibs.begin(), fibs.end(), 0) << '\n';
}
