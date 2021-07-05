// ========================================================================== //
// dependencies

// STL
#include <iostream>
#include <iomanip>

#define BCG_VECTOR
#include "BCG.hpp"

// ========================================================================== //
// unittest

// template <typename T>
// void vecout (const std::vector<T> & data) {
//   for (auto & e : data) {std::cout << e << ",";}
//   std::cout << "\b " << std::endl;
// }

// -------------------------------------------------------------------------- //

void unittest_BCG_VECTOR() {
  BCG::init();

  std::cout << ("\x1b[93m");
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << "| Testing the BCG Vector utility functions                                     |" << std::endl;
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << ("\x1b[0m")  ;
  std::cout << std::setw(8) << std::fixed;

  auto        x = {-1, 2, 3};
  auto        y = {-4, 5, 6};
  std::vector a = x;
  std::vector b = y;

  std::cout << "source data:" << std::endl;
  std::cout << "a: " << BCG::vector_to_string(a) << std::endl;
  std::cout << "b: " << BCG::vector_to_string(y.begin(), y.end()) << std::endl;

  std::cout << "vector specific concatenate: " << BCG::vector_to_string(BCG::concatenate(a, b)) << std::endl;
  std::cout << "type generic concatenate   : " << BCG::vector_to_string(BCG::concatenate(
    x.begin(), x.end(),
    y.begin(), y.end())
  ) << std::endl;

  std::cout << "value closest to 2.2 in a:" << std::endl;
  std::cout << *BCG::findNearby(a.begin(), a.end(), 2.2, 0.5);
  std::cout << " at index " << BCG::findNearbyIdx(a.begin(), a.end(), 2.2, 0.5) << std::endl;

  std::cout << "21 values between -5 and +5                    : " << BCG::vector_to_string( BCG::linspace(-5, 5, 21) ) << std::endl;
  std::cout << "values between -5 and +5 with an increment of 2: " << BCG::vector_to_string( BCG::arange  (-5, 5, 2 ) ) << std::endl;

  std::cout << std::defaultfloat;
  std::cout << std::endl << "DONE."<< std::endl << std::endl;
}
