// ========================================================================== //
// dependencies

// STL
#include <iostream>
#include <iomanip>

// own
#define BCG_RANDOM
#include "BCG.hpp"

// ========================================================================== //
// unittest

void unittest_BCG_RANDOM() {
  BCG::init();

  std::cout << ("\x1b[93m");
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << "| Testing BCG Random Module                                                    |" << std::endl;
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << ("\x1b[0m")  ;
  std::cout << std::setw(8) << std::fixed;

  std::cout << "truely random int           : " << BCG::trueRNG() << std::endl;
  std::cout << "seed, obtainted from trueRNG: " << BCG::seedRNG << std::endl;
  std::cout << "pseudorandom int            : " << BCG::PRNG() << std::endl;
  std::cout << std::endl;

  std::cout << "left column : random values between 0 and 1" << std::endl;
  std::cout << "right column: random values between 0 and 2pi" << std::endl;
  for (int i = 0; i < 10; ++i) {
    std::cout << BCG::get_randPercentage() << "\t" << BCG::get_randPhase() << std::endl;
  }

  std::cout << "seed reset" << std::endl;
  std::cout << "repeat same pseudorandom numbers:" << std::endl;
  BCG::reset_PRNG( BCG::seedRNG );
  std::cout << "pseudorandom int            : " << BCG::PRNG() << std::endl;
  std::cout << "0..1 and 0..2pi:" << std::endl;

  for (int i = 0; i < 10; ++i) {
    std::cout << BCG::get_randPercentage() << "\t" << BCG::get_randPhase() << std::endl;
  }

  std::cout << std::defaultfloat;
  std::cout << std::endl << "DONE."<< std::endl << std::endl;
}
