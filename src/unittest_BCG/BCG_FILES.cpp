// ========================================================================== //
// dependencies

#include <iostream>
#include <filesystem>

#define BCG_FILES
#include "BCG.hpp"

// ========================================================================== //
// unittest

void unittest_BCG_FILES() {
  BCG::init();

  auto    existingfile = "./unittest/existingfile";
  auto nonexistingfile = "./unittest/non-existingfile";

  std::cout << ("\x1b[93m");
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << "| Testing BCG Files Module                                                     |" << std::endl;
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << ("\x1b[0m")  ;

  std::cout << "Timestamp:" << std::endl;
  std::cout << BCG::generateTimestamp() << std::endl << std::endl;

  std::cout << "Header:" << std::endl;
  std::cout << BCG::generateFileComments("dummy content") << std::endl << std::endl;

  std::fstream hFile;
  std::cout << "Attempting to open existing file, read mode ... " << std::flush;
  hFile = BCG::openThrow(existingfile, std::fstream::in);
  std::cout << "ok" << std::endl;

  std::cout << "Attempting to open non-existing file, read mode ... " << std::flush;
  try {hFile = BCG::openThrow(nonexistingfile, std::fstream::in);}
  catch (std::exception & e) {
    std::cout << "prevented by throwing:" << std::endl;
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Attempting to open non-existing file, write mode ... " << std::flush;
  hFile = BCG::openThrow(nonexistingfile);
  std::filesystem::remove(nonexistingfile);                                     // tidy up afterwards
  std::cout << "ok" << std::endl;

  std::cout << "Attempting to open existing file, write mode ... " << std::flush;
  try {hFile = BCG::openThrow(existingfile);}
  catch (std::exception & e) {
    std::cout << "prevented by throwing:" << std::endl;
    std::cout << e.what() << std::endl;
  }
  std::cout << std::endl;


  std::cout << std::endl << "DONE."<< std::endl << std::endl;
}
