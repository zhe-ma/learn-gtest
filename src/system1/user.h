#ifndef SYSTEM1_USER_H_
#define SYSTEM1_USER_H_

#include <string>

namespace system1 {

class User {
public:
  virtual bool Login(const std::string& username, const std::string& password) = 0;

  virtual bool Pay(int money) = 0;

  virtual bool Online() const = 0;
};

}  // namespace system1

#endif  // SYSTEM1_USER_H_
