#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

int hailstoneBouncesOf(int /* num */, std::unordered_map<int, int>& /* previousBounces */);

int main() {
    std::unordered_map<int, int> memoizedBounces;
    memoizedBounces.reserve(3'721'303); // Reserve just the right amount of buckets to prevent rehashing. Magic number comes from the number of buckets in the map after this is run. This shaves off ~0.95 seconds on my 4 core 3.1GHz

    int highest{0}, num{0};
    for(int i = 2; i < 1'000'000; ++i) {
        int currentBounces = hailstoneBouncesOf(i, memoizedBounces);

        if(currentBounces > highest) {
            highest = currentBounces;
            num = i;
        }
    }
    std::cout << num << std::endl;
    return 0;
}

int hailstoneBouncesOf(const int num, std::unordered_map<int, int>& previousBounces) {
    long bounces{1}, current{num};
    std::vector<int> cache;
    while(true) {
        if(current == 1) break;

        if( previousBounces.find(current) != previousBounces.end() ) {
            bounces += previousBounces.at(current);
            break;
        }

        cache.push_back(current);

        if(current % 2 == 0)
            current /= 2;
        else
            current = current * 3 + 1;

        ++bounces;
    }

    // Add cached items bounce amounts
    for(const auto& i : cache)
        previousBounces[i] = bounces--;

    return previousBounces[num];
}
