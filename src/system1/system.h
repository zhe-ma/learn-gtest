#ifndef SYSTEM1_SYSTEM_H_
#define SYSTEM1_SYSTEM_H_

#include "system1/user.h"

namespace system1 {

class System {
public:
  void Init() const;

  void set_user(User* user) {
    user_ = user;
  }

  std::string Pay(const std::string& username, const std::string& password, int money);

private:
  User* user_ = nullptr;
};

}  // namespace system1

#endif  // SYSTEM1_SYSTEM_H_
