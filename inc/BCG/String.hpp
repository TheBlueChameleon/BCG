/**
 * @defgroup BCG_String BCG Strings Module
 *
 * @brief commonly used extensions to the STL string library, mostly in the form
 *   of static inline functions
 */

#ifndef BCG_STRING_HPP
#define BCG_STRING_HPP

// ========================================================================= //
// dependencies

#include <stdexcept>

#include <string>
#include <vector>

// ========================================================================== //

namespace BCG {
  //! @addtogroup BCG_String
  //! @{

  // ------------------------------------------------------------------------ //
  // Trim String

  //! @brief trim whitespaces from the start of the string, in place
  static inline void ltrim(std::string &s);

  //! @brief trim whitespaces from the end of the string, in place
  static inline void rtrim(std::string &s);

  //! @brief trim whitespaces from the start and end of the string, in place
  static inline void trim(std::string &s);

  //! @brief return a copy where whitespaces from the start of the string are trimmed
  static inline std::string ltrim_copy(std::string s);

  //! @brief return a copy where whitespaces from the end of the string are trimmed
  static inline std::string rtrim_copy(std::string s);

  //! @brief return a copy where whitespaces from the start and end of the string are trimmed
  static inline std::string trim_copy(std::string s);

  // ........................................................................ //
  //! @brief remove all whitespaces from a string, in place
  static inline void fullTrim(std::string &s);

  //! @brief return a copy of the string where all whitespaces are removed
  static inline std::string fullTrim_copy(std::string s);

  // ------------------------------------------------------------------------ //
  // case conversion

  //! @brief convert the entire string to uppercase characters
  static inline void     to_uppercase(std::string & s);

  //! @brief return a copy of the string where all characters are converted to uppercase
  static inline std::string uppercase(std::string   s);

  // ------------------------------------------------------------------------ //
  // split string

  /**
   * @brief split the string into a list of strings
   *
   * The separator character will be removed from the resulting list
   *
   * @param s the string to split into a list of strings
   * @param separator the character that indicates where to split the string
   */
  std::vector<std::string> splitString(const std::string & s, const char separator = ',');

  // ------------------------------------------------------------------------ //
  // substring matching and replacement

  /**
   * @brief searchs for a substring in a text and replaces all occurances
   *    thereof with a given replacement
   *
   * @param text the string to search in modify
   * @param searchFor the substring to search for and replace
   * @param replacement the string to replace \c searchFor with
   */
  void replaceAll(std::string & text, const std::string & searchFor, const std::string & replacement);

  /**
   * @brief searchs for a substring in a text and replaces all occurances
   *    thereof with a given replacement
   *
   * @param text the string to search in and return a modified copy
   * @param searchFor the substring to search for and replace
   * @param replacement the string to replace \c searchFor with
   *
   * @returns a copy of \c text where all instances of \c searchFor are replaced
   *    with \c replacement.
   */
  std::string replaceAll_copy(std::string text, const std::string & searchFor, const std::string & replacement);


  /**
   * @brief finds all instances of a substring in a given text and returns the
   *    positions where the substrings were found
   *
   * @param text the string to search in
   * @param searchFor the substring to search for
   *
   * @returns a vector of the positions where \c searchFor was found. If no
   *    instance if \c searchFor was found, the vector will have no elements.
   */
  std::vector<size_t> findAll(const std::string & text, const std::string & searchFor);

  // ........................................................................ //
  // wildcard matching

  /**
   * @brief check whether a string is matched by a pattern
   *
   * @param pattern a string to match against. All characters other than \c ?
   *  and \c * are matched verbatim.<br>
   *  * \c ? will be interpreted as a wildcard for an arbitrary \e single
   *    character<br>
   *  * \c * will be interpreted as a wildcard for an arbitrary \e sequence of
   *    characters<br>
   * @param toMatch is the string being analyzed.
   */
  bool wildcardmatch(const char        * pattern, const char        * toMatch);

  /**
   * @brief check whether a string is matched by a pattern
   *  see wildcardmatch(const char *, const char *) for details
   */
  bool wildcardmatch(const std::string & pattern, const std::string & toMatch);

  // ........................................................................ //
  // fancy formats

  /**
   * @brief returns a copy of a string, padded to both ends with a filler
   *  character such that the original string is centered.
   *
   * @param text the string to center
   * @param width the width of the resulting string
   * @param fillChar the char with which to pad the resulting string
   *
   * @throws std::invalid_argument if \c text has more characters than \c width
   */
  std::string center      (const std::string & text, int width = 80, const char fillChar = ' ');

  /**
   * @brief returns a copy of a string padded to be \c width characters wide.
   *
   * @param text the string to left-justify
   * @param width the width of the resulting string
   * @param fillChar the char with which to pad the resulting string
   *
   * @throws std::invalid_argument if \c text has more characters than \c width
   */
  std::string justifyLeft (const std::string & text, int width = 80, const char fillChar = ' ');

  /**
   * @brief returns a copy of a string padded from the left to be \c width
   *    characters wide.
   *
   * @param text the string to left-justify
   * @param width the width of the resulting string
   * @param fillChar the char with which to pad the resulting string
   *
   * @throws std::invalid_argument if \c text has more characters than \c width
   */
  std::string justifyRight (const std::string & text, int width = 80, const char fillChar = ' ');

  //! @}
}

// ========================================================================== //
// template implementations

#include "BCG/String.tpp"

#endif
