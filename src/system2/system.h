#ifndef SYSTEM2_SYSTEM_H_
#define SYSTEM2_SYSTEM_H_

#include "system2/user.h"
#include "unittest/mock_user2.h"

#ifdef ENABLE_UT
  #define User MockUser2
  #define private public
#endif  // ENABLE_UT

namespace system2 {

class System {
public:
  void Init() const;

  std::string Pay(const std::string& username, const std::string& password, int money);

  std::string GetUserStatus() const;

private:
  User user_;
};

}  // namespace system2

#endif  // SYSTEM2_SYSTEM_H_
