#include "gtest/gtest.h"
#include "gmock/gmock.h"

class NewEnvironment : public testing::Environment {
public:
  void SetUp() override {
    std::cout << "================所有用例前================" << std::endl;
  }

  void TearDown() override {
    std::cout << "================所有用例后================" << std::endl;
  }
};

int main(int argc, char **argv) {
  testing::AddGlobalTestEnvironment(new NewEnvironment);

  // Since Google Mock depends on Google Test, InitGoogleMock() is
  // also responsible for initializing Google Test.  Therefore there's
  // no need for calling testing::InitGoogleTest() separately.
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}