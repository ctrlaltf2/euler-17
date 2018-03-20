#include <iostream>
#include <string>
#include <cstdint>

std::string bigAdd(std::string a, std::string b) {
    if(a.size() < b.size())
        a.swap(b);
    b.insert(0, a.size() - b.size(), '0');

    std::uint64_t carryOver{0};
    std::string sum;
    for(std::int64_t i = b.size() - 1; i >= 0; --i) {
        std::uint64_t workingSum = (a[i] - '0') + (b[i] - '0');
        workingSum += carryOver;
        sum.insert(0, 1, (workingSum % 10) + '0');
        carryOver = workingSum / 10;
    }
    if(carryOver != 0)
        sum.insert(0, std::to_string(carryOver));
    return sum;
}

int main() {
    std::string num = "2";
    for(int i = 1; i < 1000;++i)
        num = bigAdd(num, num);
        
    std::uint64_t sum{0};
    for(const auto& c : num)
        sum += c - '0';
    
    std::cout << sum << '\n';
}
