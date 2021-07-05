// ========================================================================== //
// dependencies

// STL
#include <iostream>
// #include <iomanip>
//
#include <string>
using namespace std::string_literals;
#include <vector>

// own
#include "BCG.hpp"
#include "BCG_unittest.hpp"

// ========================================================================== //
// main


int main () {
  unittest_BCG_RANDOM();
  unittest_BCG_MATHS();
  unittest_BCG_VECTOR();
  unittest_BCG_STRING();
  //unittest_BCG_CONSOLE();
  unittest_BCG_FILES();
  unittest_BCG_ALL();
}
