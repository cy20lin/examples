#include <fmt/core.h>
#include <iostream>

int main() {
  std::cout << fmt::format("hello {}", "fmt") << std::endl;
  fmt::print("The answer is {}.\n", 42);
}