/**
 * @defgroup BCG_Files BCG Files Module
 *
 * @brief commonly used functions when dealing with files
 */

#ifndef BCG_FILES_HPP
#define BCG_FILES_HPP

// ========================================================================= //
// dependencies

#include <stdexcept>

#include <string>
#include <fstream>

// ========================================================================== //

namespace BCG {
  //! @addtogroup BCG_Files
  //! @{

  /**
   * @brief returns a string of the form YYYY-MM-DD, HH:MM:SS
   */
  std::string generateTimestamp();

  /**
   * @brief returns a string that can be used as a header for logfiles.
   *
   * @param content a string that appears in a headline-like box
   *
   * The produced output looks like this:
   * \code
   * # ============================================================================ #
   * # dummy content
   * # timestamp: 2021-07-01, 19:46:13
   * # ============================================================================ #
   * \endcode
   */
  static inline std::string  generateFileComments(const std::string & content);

  // ........................................................................ //

  static inline std::fstream openThrow(const std::string & filename, std::ios_base::openmode mode = std::fstream::out);

  //! @}
}

// ========================================================================== //
// template implementations

#include "BCG/Files.tpp"

#endif
