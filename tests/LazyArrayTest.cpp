#include <algorithm>
#include <numeric>
#include "LazyArray.hpp"

int main() {
    // LazyArray<std::string> LZ; // Should fail to compile and raise a static
    // assert error
    LazyArray<long> LZ([](const std::size_t i) -> long { return i * i; });
    std::cout << "Function test: Should be '4 16'" << std::endl;
    std::cout << LZ[2] << ' ' << LZ[4] << std::endl;
    std::cout << "Max test: Should be the max value for whatever type is used "
                 "for above"
              << std::endl;
    std::cout << LZ.getEnd() << std::endl;  // Should print the
                                            // std::numeric_limits::max() of the
                                            // LazyArray type

    LazyArray<long> LZCopy(LZ);
    std::cout << "Copy constructor test: Should print '4 16'" << std::endl;
    std::cout << LZCopy[2] << ' ' << LZCopy[4] << std::endl;

    LazyArray<long> LZSwapTest(
        [](const std::size_t i) -> long { return i + 1; });
    ;
    LZSwapTest.swap(LZCopy);
    std::cout << "Swap test: Should print '4 16'" << std::endl;
    std::cout << LZSwapTest[2] << ' ' << LZSwapTest[4] << std::endl;
    std::cout << "Swap test: Should print '1 2 3'" << std::endl;
    std::cout << LZCopy[0] << ' ' << LZCopy[1] << ' ' << LZCopy[2] << std::endl;

    LZCopy = [](const std::size_t i) -> long { return i + 2; };
    std::cout << "Operator= initializer list test: Should print '2 3'"
              << std::endl;
    std::cout << LZCopy[0] << ' ' << LZCopy[1] << ' ' << std::endl;

    // LZCopy.end(); // Should throw a compile-time error saying that the
    // container is infinite in size
    LazyArray<long> AccessTest([](const int x) -> long { return 3 * x + 7; });
    ;
    std::cout << AccessTest.at(2) << std::endl;

    std::cout << AccessTest.size() << std::endl;

    int i = 0;
    AccessTest.setEnd(20);
    std::cout << "Catch out of bounds test: " << std::endl;
    while (true) {
        try {
            std::cout << AccessTest.at(i) << ' ';
        } catch (std::out_of_range&) {
            std::cout << std::endl;
            break;
        }
        ++i;
    }

    std::cout << "Index test: " << std::endl;
    for (int i = 0; i < AccessTest.size(); ++i) {
        std::cout << AccessTest[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "for(:) test: " << std::endl;
    AccessTest.setBegin(3);
    for (const auto i : AccessTest) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    AccessTest.setBegin(0);

    auto itr = AccessTest.begin();
    auto itrend = AccessTest.end();
    std::cout << "begin == end: " << (itr == itrend) << std::endl;
    std::cout << "begin != end: " << (itr != itrend) << std::endl;
    std::cout << "begin < end: " << (itr < itrend) << std::endl;
    std::cout << "end < begin: " << (itrend < itr) << std::endl;
    std::cout << "end > begin: " << (itrend > itr) << std::endl;
    std::cout << "begin > end: " << (itr > itrend) << std::endl;

    // Algorithms library test (Some will not work because the elements don't
    // actually exist
    std::cout << "std::all_of testing if all numbers are greater than zero: ";
    std::cout << std::all_of(AccessTest.begin(), AccessTest.end(),
                             [](const long l) -> bool { return l > 0; })
              << std::endl;

    std::cout << "std::any_of testing if any numbers are divisible by three: ";
    std::cout << std::any_of(AccessTest.begin(), AccessTest.end(),
                             [](const long l) -> bool { return l % 3 == 0; })
              << std::endl;
    ;

    std::cout << "std::none_of testing if none of the numbers are negative"
              << std::endl;
    std::cout << std::none_of(AccessTest.begin(), AccessTest.end(),
                              [](const long l) -> bool { return l < 0; })
              << std::endl;

    std::cout
        << "std::for_each to print the squares of what's inside AccessTest: "
        << std::endl;
    std::for_each(
        AccessTest.begin(), AccessTest.end(),
        [](const auto num) -> void { std::cout << num * num << std::endl; });

    std::cout << "std::count_if to see how many values are even" << std::endl;
    std::cout << std::count_if(AccessTest.begin(), AccessTest.end(),
                               [](const auto num) -> bool { return num % 2; })
              << std::endl;

    std::cout << "std::mismatch would require conversion to a container with "
                 "values to work"
              << std::endl;
    std::vector<long> V = AccessTest.toVector();

    for (const auto& i : V) std::cout << i << ' ';
    std::cout << std::endl;

    {
        LazyArray<float> lz([](const float x) { return x; });
        lz.setEnd(9.5);
        lz.setIncrement(0.5);
        for (const float i : lz) std::cout << i << ' ';
        std::cout << '\n';
    }
    return 0;
}
