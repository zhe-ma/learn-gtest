#include "system2/user.h"

namespace system2 {

bool User::Login(const std::string& username, const std::string& password) {
  return true;
}

bool User::Pay(int money) {
  return true;
}

bool User::Online() const {
  return true;
}

int User::GetStatus(std::string* error_msg) const {
  return 0;
}

}  // namespace system2
