#include "LazyArray.hpp"

#include <vector>

#include <gtest/gtest.h>

namespace {

class LazyArrayTest : public testing::Test {};

TEST_F(LazyArrayTest, UnboundedAccess) {
    LazyArray<int> l([](const int x) { return x * x; });
    ASSERT_EQ(l[3], 9);
}

TEST_F(LazyArrayTest, FunctionConstructor) {
    LazyArray<int> l([](const int x) { return x * 2; });
    ASSERT_EQ(l[2], 4);
}

TEST_F(LazyArrayTest, RangedBasedFor) {
    std::vector<int> v;
    LazyArray<int> l([](const int x) { return x; });

    int loopCount{0};
    for (const int i : l) {
        if (loopCount == 10) break;
        ++loopCount;
    }

    ASSERT_EQ(loopCount, 10);
}
}  // namespace

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
