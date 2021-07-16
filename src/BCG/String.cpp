// ========================================================================= //
// dependencies

// STL
#include <stdexcept>

#include <iostream>

#include <string>

// own
#include "BCG.hpp"

// ========================================================================== //
// local macro

#define THROWTEXT(msg) (std::string("RUNTIME EXCEPTION IN ") + (__PRETTY_FUNCTION__) + "\n" + msg)

// ========================================================================== //
// procs

using namespace BCG;

std::vector<std::string> BCG::splitString(const std::string & s, const char separator) {
  std::vector<std::string> reVal;
  if ( s.empty() ) {return reVal;}

  auto posSeparator = s.find(separator);
  auto last = 0u;

  while (posSeparator != std::string::npos) {
    reVal.push_back( s.substr(last, posSeparator - last) );

    last = posSeparator + 1;
    posSeparator = s.find(separator, posSeparator + 1);
  }

  if (last != s.size()) {
    reVal.push_back( s.substr(last, s.size() - last) );
  }

  return reVal;
}
// .......................................................................... //
std::string BCG::replaceAll(std::string text, const std::string & searchFor, const std::string & replacement) {
  constexpr auto npos = std::string::npos;

  size_t spot = 0u;
  while (true) {
    spot = text.find(searchFor);
    if (spot == npos) {break;}

    text.replace(spot, searchFor.size(), replacement);
  }

  return text;
}
// .......................................................................... //
std::vector<size_t> BCG::findAll(const std::string & text, const std::string & searchFor) {
  constexpr auto npos = std::string::npos;
  std::vector<size_t> reVal;

  size_t spot = 0u;
  while (true) {
    spot = text.find(searchFor, spot);
    if (spot == npos) {break;}

    reVal.push_back(spot);
    ++spot;
  }

  return reVal;
}
// .......................................................................... //
bool BCG::wildcardmatch(const char *first, const char * second) {
  // https://www.geeksforgeeks.org/wildcard-character-matching/

  if (*first == '\0' && *second == '\0')                        { return true ; }
  if (*first == '*'  && *(first+1) != '\0' && *second == '\0')  { return false; }
  if (*first == '?'  || *first == *second)                      { return wildcardmatch(first+1, second+1); }
  if (*first == '*')                                            { return wildcardmatch(first+1, second) || wildcardmatch(first, second+1); }
  return false;
}
bool BCG::wildcardmatch(const std::string & pattern, const std::string & searchstring) {return wildcardmatch(pattern.c_str(), searchstring.c_str());}
// .......................................................................... //
std::string BCG::center(const std::string & text, int width, const char fillChar) {
  int core = text.size();

  if (core > width) {
    throw std::invalid_argument(THROWTEXT("   text length exceeds width"));
  }

  int padding = width - core;
  bool oddLength = padding & 1;
  padding >>= 1;

  std::string reVal(padding, fillChar);
  reVal += text + reVal;
  if (oddLength) {reVal += fillChar;}

  return reVal;
}
// .......................................................................... //
std::string BCG::justifyLeft(const std::string & text, int width, const char fillChar) {
  int core = text.size();
  if (core > width) {throw std::invalid_argument(THROWTEXT("   text length exceeds width"));}
  return text + std::string(width - core, fillChar);
}
// .......................................................................... //
std::string BCG::justifyRight(const std::string & text, int width, const char fillChar) {
  int core = text.size();
  if (core > width) {throw std::invalid_argument(THROWTEXT("   text length exceeds width"));}
  return std::string(width - core, fillChar) + text;
}
