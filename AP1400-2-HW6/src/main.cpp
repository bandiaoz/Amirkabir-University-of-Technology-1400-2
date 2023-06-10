#include <gtest/gtest.h>
#include <iostream>

#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"

int main(int argc, char** argv) {
  if (false) {  // make false to run unit-tests
    std::vector<q4::Sensor> sensors{{{0, 0.01}, 0.5}, {{0.5, 0.009}, 0.2}};
    auto kalman{q4::kalman_filter(sensors)};
    std::cout << "x: " << kalman.x << " y: " << kalman.y << std::endl;

  } else {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "RUNNING TESTS ..." << std::endl;
    int ret{RUN_ALL_TESTS()};
    if (!ret)
      std::cout << "<<<SUCCESS>>>" << std::endl;
    else
      std::cout << "FAILED" << std::endl;
  }
  return 0;
}