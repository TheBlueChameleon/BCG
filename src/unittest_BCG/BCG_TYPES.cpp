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

// tests where g++/clang++ show difference:
// https://jplehr.de/2019/10/25/name-mangling-in-c-with-clang-and-gcc/

class CTorMangleTestClass {
  private:
    int dimX, dimY, gridA, gridB;

  public:
    CTorMangleTestClass(int numX, int numY) : dimX(numX),
                                     dimY(numY),
                                     gridA(dimX*dimY),
                                     gridB(dimX*dimY)
                                     {}
};

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

  std::cout << "int        : " << BCG::getTypeName(i)         << std::endl;
  std::cout << "std::string: " << BCG::getTypeName(s)         << std::endl;
  std::cout << "AStruct()  : " << BCG::getTypeName(AStruct()) << std::endl;
  std::cout << "AClass()   : " << BCG::getTypeName(AClass ()) << std::endl;
  std::cout << "Derived()  : " << BCG::getTypeName(Derived()) << std::endl;
  std::cout << std::endl;

  std::cout << "GCC explicit types" << std::endl;
  std::cout << "'i' is " << BCG::demangle("i") << std::endl;

  std::cout << "CTor of class    : " << BCG::getTypeIDName( CTorMangleTestClass(0,0) ) << std::endl;
  // g++      : CTor of class    : 19CTorMangleTestClass
  // clang++  : CTor of class    : 19CTorMangleTestClass

  auto obj = CTorMangleTestClass(0,0);
  std::cout << "instance of class: " << BCG::getTypeIDName( obj ) << std::endl;
  std::cout << "demangle         : " << BCG::getTypeName  ( obj ) << std::endl;



}
