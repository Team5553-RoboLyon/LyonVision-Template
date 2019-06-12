#include "vision.h"

#include <iostream>

#ifndef RUNNING_FRC_TESTS
int main() {
  std::cout << "Starting Vision Program" << std::endl;
  curtin_frc_vision vision;
  vision.run();
  std::cout << "Vision Program Exited. Was that meant to happen? i doubt it lol." << std::endl;
  return -1;
}
#endif
