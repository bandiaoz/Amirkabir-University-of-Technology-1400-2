#include <gtest/gtest.h>
#include <iostream>
#include "client.h"
#include "server.h"

int main(int argc, char **argv) {
  if (false) {
    std::string sender{}, receiver{};
    double value;
    Server::parse_trx("sarah-clay_0.5", sender, receiver, value);
    std::cout << sender << std::endl;
    std::cout << receiver << std::endl;
    std::cout << value << std::endl;
  } else {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "RUNNING TESTS ..." << std::endl;
    int ret{RUN_ALL_TESTS()};
    if (!ret) {
      std::cout << "<<<SUCCESS>>>" << std::endl;
    } else {
      std::cout << "FAILED" << std::endl;
    }
  }
  return 0;
}