#ifndef SYSTEM2_USER_H_
#define SYSTEM2_USER_H_

#include <string>

namespace system2 {

class User {
public:
  bool Login(const std::string& username, const std::string& password);

  bool Pay(int money);

  bool Online() const;

  int GetStatus(std::string* error_msg) const;
};

}  // namespace system2

#endif  // SYSTEM2_USER_H_
