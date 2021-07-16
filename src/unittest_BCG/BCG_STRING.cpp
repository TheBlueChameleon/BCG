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

  std::string text1 = "$X text in between $X text in between $X";
  std::string text2 = "text in between $X text in between";
  std::string text3 = "no text to replace";

  std::cout << BCG::replaceAll(text1, "$X", "~ replacement okay ~") << std::endl;
  std::cout << BCG::replaceAll(text2, "$X", "~ replacement okay ~") << std::endl;
  std::cout << BCG::replaceAll(text3, "$X", "~ replacement okay ~") << std::endl;

  auto spots1 = BCG::findAll(text1, "$X");
  for (const auto & s : spots1) {std::cout << s << "\t";}
  std::cout << std::endl;
  auto spots2 = BCG::findAll(text2, "$X");
  for (const auto & s : spots2) {std::cout << s << "\t";}
  std::cout << std::endl;
  auto spots3 = BCG::findAll(text3, "$X");
  for (const auto & s : spots3) {std::cout << s << "\t";}
  std::cout << std::endl;

  std::cout << std::endl << "DONE."<< std::endl << std::endl;
}
