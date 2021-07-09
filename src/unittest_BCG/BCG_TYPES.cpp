// ========================================================================== //
// dependencies

// STL
#include <iostream>

#include <vector>
#include <string>
using namespace std::string_literals;

#define BCG_TYPES
#include "BCG.hpp"

// ========================================================================== //
// dummy classes

struct AStruct {};
class  AClass  {};
class  Derived : public AClass {};

// ========================================================================== //
// unittest

void unittest_BCG_TYPES() {
  BCG::init();

  std::cout << ("\x1b[93m");
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << "| Testing the BCG Typeinfo Support System                                      |" << std::endl;
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << ("\x1b[0m")  ;

  auto i = 0;
  auto s = "some string"s;

  std::cout << "int        : " << BCG::nameOfType(i)         << std::endl;
  std::cout << "std::string: " << BCG::nameOfType(s)         << std::endl;
  std::cout << "AStruct()  : " << BCG::nameOfType(AStruct()) << std::endl;
  std::cout << "AClass()   : " << BCG::nameOfType(AClass ()) << std::endl;
  std::cout << "Derived()  : " << BCG::nameOfType(Derived()) << std::endl;
  std::cout << std::endl;

  std::cout << "GCC explicit types" << std::endl;
  std::cout << "'i' is " << BCG::demangle("i") << std::endl;

}
