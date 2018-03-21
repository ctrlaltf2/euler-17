#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

void p4(std::ostream& os) {
    int max{0};
    for (int a = 999; a > 99; --a) {
        for (int b = a; b > 99; --b) {
            std::string product = std::to_string(a * b),
                        reversed_product = product;
            std::reverse(reversed_product.begin(), reversed_product.end());

            if (reversed_product == product) max = std::max(max, a * b);
        }
    }
    os << max << '\n';
}
