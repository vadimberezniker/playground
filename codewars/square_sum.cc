#include <functional>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

// Straightforward implementation using a simple for loop.
class BasicSquareAndSum {
 public:
  int square_sum(const std::vector<int>& numbers) {
    int sum = 0;
    for (int n : numbers) {
      sum += (n * n);
    }
    return sum;
  }
};

// Slightly fancier version taking advantage of std::accumulate.
class AccumulateSquareAndSum {
 public:
  int square_sum(const std::vector<int>& numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0,
                           [](int acc, int n) { return acc + (n * n); });
  }
};

// Which version is better?
// I would personally prefer the first version because it's a simple for loop.
// Although std::accumulate is part of the standard library, it's a less 
// frequently used function and thus has more cognitive overhead for readers.

template <typename T>
class SquareAndSumTest : public ::testing::Test {
 protected:
  T impl_;
};

using Impls = ::testing::Types<BasicSquareAndSum, AccumulateSquareAndSum>;
TYPED_TEST_SUITE(SquareAndSumTest, Impls);

TYPED_TEST(SquareAndSumTest, Basic) {
  EXPECT_EQ(this->impl_.square_sum({}), 0);
  EXPECT_EQ(this->impl_.square_sum({1, 2, 3}), 14);
  EXPECT_EQ(this->impl_.square_sum({-1, -2, -3}), 14);
}



