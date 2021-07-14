/**
 * @defgroup BCG_Types BCG Typeinfo Support Module
 *
 * @brief convenience functions to work with the typeid operator
 *
 * C++ specifies a typeid operator which returns a std::type_info object. This
 * object in turn has a method name() which returns a const char* identifying
 * the type of the object, even at runtime, which can be used to deduce
 * properties of derived class instances.
 *
 * Compilers will return a *mangled* name, i.e. some string thatincorporates
 * information about namespaces and data needed for correct linkage.
 *
 * Different compilers (gcc, clang, msvc, ...) act according to different
 * mangling rules. Hence this module should be an aid using the provided
 * features while maintaining portability
 */

#ifndef BCG_ANY_HPP
#define BCG_ANY_HPP

// ========================================================================= //
// dependencies

#include <string>
#include <typeinfo>
#include <functional>

// ========================================================================== //

namespace BCG {
  //! @addtogroup BCG_Types
  //! @{

  //! @brief returns the mangled type name of an object
  template <class T>
  std::string getTypeIDName(const T& t) {return typeid(t).name();}

  // these codes are copied from or based upon this stackoverflow thread:
  // https://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname

  //! @brief returns the demangled type name from a c-string
  std::string demangle(const char* name);

  //! @brief returns the demangled type name of an arbitrary object
  template <class T>
  std::string getTypeName(const T& t) {return demangle(typeid(t).name());}

  //! @}
}

#endif
