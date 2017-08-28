#include "LazyArray.hpp"
#include <algorithm>
#include <numeric>

int main() {
    // LazyArray<std::string> LZ{"asdf", "qwerty"}; // Should fail to compile and raise a static assert error
    LazyArray<long> LZ{2, 3, 5, 12};
    std::cout << "Initializer list test: Should be '2 3 5 12'" << std::endl;
    LZ.print_coefficients(); // Should print out the contents of the LZ array above
    std::cout << "Max test: Should be the max value for whatever type is used for above" << std::endl;
    std::cout << LZ.getEnd() << std::endl; // Should print the std::numeric_limits::max() of the LazyArray type

    LazyArray<long> LZCopy(LZ);
    std::cout << "Copy constructor test: Should print '2 3 5 12'" << std::endl;
    LZCopy.print_coefficients(); // Should print the same as LZ.print_coefficients()

    LazyArray<long> LZSwapTest{1, 2, 3, 4, 5};
    LZSwapTest.swap(LZCopy);
    std::cout << "Swap test: Should print '2 3 5 12'" << std::endl;
    LZSwapTest.print_coefficients();
    std::cout << "Swap test: Should print '1 2 3 4 5'" << std::endl;
    LZCopy.print_coefficients();

    LazyArray<int> MoveTest( LazyArray<int> {1, 2, 3, 4} );
    std::cout << "Move test: Should print '1 2 3 4'" << std::endl;
    MoveTest.print_coefficients();

    LZCopy = {5, 4, 3, 2, 1};
    std::cout << "Operator= initializer list test: Should print '5 4 3 2 1'" << std::endl;
    LZCopy.print_coefficients();

    // LZCopy.end(); // Should throw a compile-time error saying that the container is infinite in size
    LazyArray<long> AccessTest{3, 7};
    std::cout << AccessTest.at(2) << std::endl;

    std::cout << AccessTest.size() << std::endl;

    int i = 0;
    AccessTest.setEnd(20);
    std::cout << "Catch out of bounds test: " << std::endl;
    while(true) {
        try {
            std::cout << AccessTest.at(i) << ' ';
        } catch(std::out_of_range&) {
            std::cout << std::endl;
            break;
        }
        ++i;
    }

    std::cout << "Index test: " << std::endl;
    for(int i = 0; i < AccessTest.size(); ++i) {
        std::cout << AccessTest[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "for(:) test: " << std::endl;
    AccessTest.setBegin(3);
    for(const auto i : AccessTest) {
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

    // Algorithms library test (Some will not work because the elements don't actually exist
    std::cout << "std::all_of testing if all numbers are greater than zero: "; 
    std::cout << std::all_of(AccessTest.begin(), AccessTest.end(), [](const long l)->bool { return l > 0; }) << std::endl; 

    std::cout << "std::any_of testing if any numbers are divisible by three: ";
    std::cout << std::any_of(AccessTest.begin(), AccessTest.end(), [](const long l)->bool { return l % 3 == 0; }) << std::endl;;

    std::cout << "std::none_of testing if none of the numbers are negative" << std::endl;
    std::cout << std::none_of(AccessTest.begin(), AccessTest.end(), [](const long l)->bool { return l < 0; }) << std::endl;

    std::cout << "std::for_each to print the squares of what's inside AccessTest: " << std::endl;
    std::for_each(AccessTest.begin(), AccessTest.end(), [](const auto num)->void { std::cout << num * num << std::endl; });

    std::cout << "std::count_if to see how many values are even" << std::endl;
    std::cout << std::count_if(AccessTest.begin(), AccessTest.end(), [](const auto num)->bool { return num % 2; }) << std::endl;

    std::cout << "std::mismatch would require conversion to a container with values to work" << std::endl;
    std::vector<long> V = AccessTest.toVector();

    for(const auto& i : V) std::cout << i << ' ';
    std::cout << std::endl;
    return 0;
}
