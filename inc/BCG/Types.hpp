/**
 * @defgroup BCG_Types BCG typeinfo support module
 *
 * @brief convenience functions to work with the std::any type
 */

#ifndef BCG_ANY_HPP
#define BCG_ANY_HPP

// ========================================================================= //
// dependencies

#include <string>
#include <typeinfo>

// ========================================================================== //

namespace BCG {
  //! @addtogroup BCG_Types
  //! @{

  // see
  // https://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname
  std::string demangle(const char* name);

  template <class T>
  std::string nameOfType(const T& t) {return demangle(typeid(t).name());}

  //! @}
}

#endif
