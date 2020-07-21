#include <fmt/format.h>

namespace hello {

std::string getGreeting(const std::string &name) {
  return fmt::format("Hello {}!", name);
}

void sayHello(const std::string &name) {
  fmt::print("{}\n", getGreeting(name));
}

} // namespace hello