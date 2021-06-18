#ifndef UNITTEST_MOCK_USER2_H_
#define UNITTEST_MOCK_USER2_H_

#include "gmock/gmock.h"

class MockUser2 {
public:
  MOCK_METHOD(bool, Login, (const std::string& username, const std::string& password), ());

  MOCK_METHOD(bool, Pay, (int money), ());

  MOCK_METHOD(bool, Online, (), (const));
};

#endif  // UNITTEST_MOCK_USER2_H_
