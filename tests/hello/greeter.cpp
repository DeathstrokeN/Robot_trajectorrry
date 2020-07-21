#include <catch2/catch.hpp>

#include <hello/hello.h>

TEST_CASE("Greeter") {
  auto names = {"John", "Jack", "Paul"};

  for (auto name : names) {
    REQUIRE(hello::getGreeting(name) == "Hello " + std::string{name} + "!");
  }
}