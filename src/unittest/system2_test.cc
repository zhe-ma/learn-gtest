#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "system2/system.h"

class System2Test : public testing::Test {
protected:
  void SetUp() override {
    std::cout << "================每个用例前================" << std::endl;
    system_.Init();
  }

  void TearDown() override{
    std::cout << "================每个用例后================" << std::endl;
  }

  static void SetUpTestCase() {
    std::cout << "================该Suite用例前================" << std::endl;
  }

  static void TearDownTestCase() {
    std::cout << "================该Suite用例后================" << std::endl;
  }

  system2::System system_;
};

TEST_F(System2Test, case1) {
  MockUser2& user = system_.user_;
  EXPECT_CALL(user, Online()).WillOnce(testing::Return(true)).WillRepeatedly(testing::Return(false));  // 第一次返回true，后面返回false
  EXPECT_CALL(user, Login(testing::_, testing::_)).WillRepeatedly(testing::Return(false));  // “_”为通配符，表示任何输入参数。总返回false。
  EXPECT_CALL(user, Pay(testing::_)).WillRepeatedly(testing::Return(true));

  std::string ret = system_.Pay("user1", "123", 10);
  EXPECT_STREQ(ret.c_str(), "pay success");

  ret = system_.Pay("user2", "123", 11);
  EXPECT_STREQ(ret.c_str(), "login error");
}

TEST_F(System2Test, case2) {
  // admin用户不能登陆支付
  MockUser2& user = system_.user_;
  EXPECT_CALL(user, Online()).WillRepeatedly(testing::Return(false));
  EXPECT_CALL(user, Login("admin", testing::_)).WillRepeatedly(testing::Return(false));

  std::string ret = system_.Pay("admin", "123", 10);
  EXPECT_STREQ(ret.c_str(), "login error");

  ret = system_.Pay("admin", "abc", 10);
  EXPECT_STREQ(ret.c_str(), "login error");
}

TEST_F(System2Test, case3) {
  // 非admin用户只能支付两次，后面支付均失败
  MockUser2& user = system_.user_;
  EXPECT_CALL(user, Online()).WillRepeatedly(testing::Return(true));
  EXPECT_CALL(user, Login(testing::StrNe("admin"), testing::_)).WillRepeatedly(testing::Return(true));  // testing::StrNe比较函数，不是某个值
  EXPECT_CALL(user, Pay(testing::_)).WillOnce(testing::Return(true)).WillOnce(testing::Return(true)).WillRepeatedly(testing::Return(false));

  std::string ret = system_.Pay("user1", "123", 10);
  EXPECT_STREQ(ret.c_str(), "pay success");

  ret = system_.Pay("user1", "123", 10);
  EXPECT_STREQ(ret.c_str(), "pay success");

  ret = system_.Pay("user1", "123", 10);
  EXPECT_STREQ(ret.c_str(), "pay error");
}

TEST_F(System2Test, case4) {
  // 非admin用户只能支付两次，后面支付均失败
  MockUser2& user = system_.user_;
  EXPECT_CALL(user, GetStatus(testing::_)).WillOnce(
    testing::DoAll(
      testing::SetArgPointee<0>("good"),
      testing::Return(0)
    )
  ).WillOnce(
    testing::DoAll(
      testing::SetArgPointee<0>("Offline"),
      testing::Return(-1)
    )
  );

  EXPECT_EQ(system_.GetUserStatus(), "normal");
  EXPECT_EQ(system_.GetUserStatus(), "Offline");
}
