#ifndef UNITTEST_MOCK_USER_H_
#define UNITTEST_MOCK_USER_H_

#include "system1/user.h"
#include "gmock/gmock.h"

namespace unittest {

class MockUser : public system1::User {
public:
  MOCK_METHOD(bool, Login, (const std::string& username, const std::string& password), (override));

  MOCK_METHOD(bool, Pay, (int money), (override));

  MOCK_METHOD(bool, Online, (), (const, override));
};

}  // namespace unittest

#endif  // UNITTEST_MOCK_USER_H_
