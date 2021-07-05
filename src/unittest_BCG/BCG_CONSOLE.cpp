// ========================================================================== //
// dependencies

// STL
#include <iostream>

#include <vector>

#include <chrono>
#include <thread>

// own
#define BCG_CONSOLE
#include "BCG.hpp"

// ========================================================================== //
// unittest

void unittest_BCG_CONSOLE () {
  BCG::init();

  BCG::writeBoxed("Testing the BCG console output functions", {BCG::ConsoleColors::FORE_YELLOW});
  BCG::writeWarning("not all output happens on STDOUT.");

  BCG::writeScale(80, 60);
  BCG::writeScale(80);
  BCG::writeScale(80, 10);

  for (auto p = 0.; p < 1; p += .01) {
    BCG::updateProgressBar(p);
    std::this_thread::sleep_for( std::chrono::milliseconds(5));
  }
  BCG::updateProgressBar(1);
  std::cout << std::endl;


  for (auto i = 0; i < 20; ++i) {
    BCG::idleAnimation("some text ");
    std::this_thread::sleep_for( std::chrono::milliseconds(50));
  }
  std::cout << std::endl;


  std::cout << "DONE." << std::endl;
}
