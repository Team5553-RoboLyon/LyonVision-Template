﻿#include "Vision.h"

#include <iostream>

#ifndef RUNNING_FRC_TESTS
int main() {
#ifdef __DESKTOP__
  std::cout << "Running on Desktop - imshow enabled" << std::endl;
#else
  std::cout << "Running embedded - imshow disabled" << std::endl;
#endif

  std::cout << "Starting Vision Program" << std::endl;

  Vision vision;
  vision.Run();

  std::cout << "Vision Program Exited. Was that meant to happen?" << std::endl;
  return -1;
}
#endif