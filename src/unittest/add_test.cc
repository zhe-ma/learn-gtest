#include <complex>
#include "gtest/gtest.h"
#include "base/add.h"

TEST(AddTest, case1) {
  EXPECT_EQ(base::Add(10, 9), 19);
}

TEST(AddTest, case2) {
  EXPECT_DOUBLE_EQ(base::Add(2.3, 1.4), 3.7);
}

TEST(AddTest, case3) {
  std::complex<int> a{1, 1};
  std::complex<int> b{2, 2};
  auto c = base::Add(a, b);
  EXPECT_EQ(c, std::complex<int>(3, 3));
}