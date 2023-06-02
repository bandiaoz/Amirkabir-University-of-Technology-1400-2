#include "hw1.h"

#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char **argv) {
  bool debug = false;
  if (debug) {  // make false to run unit-tests
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