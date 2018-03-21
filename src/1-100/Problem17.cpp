#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

namespace count {
const static std::array<unsigned int, 19> belowNineteen = {
    3,  // one
    3,  // two
    5,  // three
    4,  // four
    4,  // five
    3,  // six
    5,  // seven
    5,  // eight
    4,  // nine
    3,  // ten
    6,  // eleven
    6,  // twelve
    8,  // thirteen
    8,  // fourteen
    7,  // fifteen
    7,  // sixteen
    9,  // seventeen
    8,  // eighteen
    8,  // nineteen
};

const static std::array<unsigned int, 8> tens = {
    6,  // twenty
    6,  // thirty
    5,  // forty
    5,  // fifty
    5,  // sixty
    7,  // seventy
    6,  // eighty
    6,  // ninety
};
}  // namespace count

std::uint32_t letterCount(std::uint32_t n) {
    assert(n <= 1000);
    assert(n > 0);

    try {
        if (n <= 19) return count::belowNineteen.at(n - 1);

        if (n == 1000) return std::string("onethousand").size();

        std::uint32_t letterCount{0};

        if (n >= 100) {
            // Get hundreds, add to letterCount
            // make n equal to n - 100s place
            const std::uint32_t hundredsDigit = (n / 1000.0) * 10;
            letterCount += count::belowNineteen.at(hundredsDigit - 1);
            letterCount += std::string("hundred").size();
            n -= hundredsDigit * 100;

            // n was something like 100, 400, 900, 700, etc
            if (n == 0) return letterCount;

            letterCount += std::string("and").size();
        }

        // Now n is now less than 100
        if (n <= 19) return letterCount + count::belowNineteen.at(n - 1);

        // n is now less than 100 and greater than 19

        const std::uint32_t tensDigit = (n / 100.0) * 10;

        letterCount += count::tens.at(tensDigit - 2);

        // Now the ones place
        const std::uint32_t onesDigit = n % 10;

        if (onesDigit == 0) return letterCount;

        letterCount += count::belowNineteen.at(onesDigit - 1);
        return letterCount;
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << '\n';
        std::cout << "Errored at n = " << n << '\n';
        return 0;
    }
}

void p17(std::ostream& os) {
    std::uint64_t letterCountSum{0};
    for (auto i = 1u; i <= 1000; ++i) letterCountSum += letterCount(i);
    os << letterCountSum << '\n';
}
