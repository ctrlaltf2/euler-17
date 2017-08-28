#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

std::vector<int> divisorsOf(int /* n */);

int main() {
    int n{2}, triangle{0};

    do {
        triangle = (n * (n - 1)) / 2;
        ++n;
    } while( divisorsOf(triangle).size() < 500);

    std::cout << triangle << std::endl;
}

std::vector<int> divisorsOf(int n) {
    const int max = sqrt(n);
    std::vector<int> divisors;

    for(int i = 1; i <= max; ++i) {
        if(n % i == 0) {
            divisors.push_back(n);
            if(i != max)
                divisors.push_back(n / i);
        }
    }
    return divisors;
}
