#include "system2/system.h"

#include <iostream>

namespace system2 {

void System::Init() const {
  std::cout << "System Init" << std::endl;
}

std::string System::Pay(const std::string& username, const std::string& password, int money) {
  if (!user_.Online() && !user_.Login(username, password)) {
    return "login error";
  }

  if (!user_.Pay(money)) {
    return "pay error";
  }

  return "pay success";
}

std::string System::GetUserStatus() const {
  std::string msg;
  int status = user_.GetStatus(&msg);
  if (status == 0) {
    return "normal";
  }

  return msg;
}

}  // namespace system2
