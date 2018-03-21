#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

std::vector<int> divisorsOf(int /* n */);

void p12(std::ostream& os) {
    int n{2}, triangle{0};

    do {
        triangle = (n * (n - 1)) / 2;
        ++n;
    } while (divisorsOf(triangle).size() < 500);

    os << triangle << '\n';
}

std::vector<int> divisorsOf(int n) {
    const int max = sqrt(n);
    std::vector<int> divisors;

    for (int i = 1; i <= max; ++i) {
        if (n % i == 0) {
            divisors.push_back(n);
            if (i != max) divisors.push_back(n / i);
        }
    }
    return divisors;
}
