#include <iostream>
#include "base/add.h"

int main(int argc, char const *argv[]) {
  std::cout << "Hello World" << std::endl;

  std::cout << base::Add(10, 12) << std::endl;

  return 0;
}
