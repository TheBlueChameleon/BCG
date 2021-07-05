// ========================================================================== //
// dependencies

#include <iostream>

#include <string>

#define BCG_STRING
#include "BCG.hpp"

// ========================================================================== //
// unittest

void unittest_BCG_STRING() {
  BCG::init();

  std::cout << ("\x1b[93m");
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << "| Testing BCG String Module                                                    |" << std::endl;
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << ("\x1b[0m")  ;

  std::cout << BCG::center(" centered text ", 80, '~') << std::endl << std::endl;


  std::cout << std::endl << "DONE."<< std::endl << std::endl;
}
