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
#include <filesystem>

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
   \verbatim
   # ============================================================================ #
   # dummy content
   # timestamp: 2021-07-01, 19:46:13
   # ============================================================================ #
   \endverbatim
   */
  static inline std::string  generateFileComments(const std::string & content);

  // ........................................................................ //


  /**
   * @brief attempts to open a file but throws an exception in common cases
   *
   * @param filename the file to be opened
   * @param mode     the file mode, usually either \c std::fstream::in or
   *    \c std::fstream::out.
   * @param noOverwrite whether or not to throw an error if the file already
   *    exists. Ignored when \c mode is \c std::fstream::in.
   *
   * @throws std::runtime_error if \c mode is *not* \c std::fstream::in and
   *    \c noOverwrite is \c true.
   * @throws std::invalid_argument if the file could not be opened.
   */
  static inline std::fstream openThrow(const std::string & filename,
                                       const std::ios_base::openmode mode = std::fstream::out,
                                       bool noOverwrite = true);


  /**
   * @brief returns a list of all files that match a given pattern.
   *
   * @todo implement getAllFiles. Note that BCG::String is already available.
   */
  std::vector<std::string> getAllFiles(const std::string & pattern);
  //! @}
}

// ========================================================================== //
// template implementations

#include "BCG/Files.tpp"

#endif
