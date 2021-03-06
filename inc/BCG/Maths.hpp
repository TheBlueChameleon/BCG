/**
 * @defgroup BCG_Maths BCG Maths Module
 *
 * @brief commonly used extensions to the STL maths library
 *
 * @todo include multinomial
 *
 */

#ifndef BCG_MATHS_HPP
#define BCG_MATHS_HPP

// ========================================================================= //
// dependencies

#include <stdexcept>

#include <sstream>
#include <complex>
#include <vector>
#include <iterator>

#include <functional>

#include <cmath>
#include <numeric>

// ========================================================================== //

namespace BCG {
  //! @addtogroup BCG_Maths
  //! @{

  // ------------------------------------------------------------------------ //
  // globals

  //! an alias for \c std::complex<double>
  typedef std::complex<double> complex_d_t;

  //! @brief the numerical value of @f$\pi@f$
  constexpr double PI = std::atan(1.0) * 4;

  // ------------------------------------------------------------------------ //
  // type conversion

  /**
   * @brief returns a string representation of a std::complex<double> alias complex_d_t
   * @todo complex_to_string: add more format params
   */
  template<class T>
  static inline const std::string complex_to_string(const std::complex<T> & z);

  // ------------------------------------------------------------------------ //
  // vector norm and distance

  /**
   * @brief compute the Euclidean norm of a vector, given by an arbitrary STL
   *  container
   *
   * Recall: The Euclidean norm of a complex valued vector @f$x@f$ is defined
   * as:
   * @f[
   *  || x || = \sqrt{ \sum_i x_i \cdot x_i^*}
   * @f]
   *
   * @attention this function is implemented in terms of \c BCG::complex_d_t and
   *  will implicitly cast its operands to that type. While the result is
   *  mathematically correct when used with reals or integers, the type
   *  conversion can take considerable time. Use norm_Euclidean_real() when
   *  handling a \c double vector or implement your own version based on
   *  \c std::transform_reduce.
   */
  template<class Iterator>
  double norm_Euclidean(Iterator begin, Iterator end);

  /**
   * @brief computes the square of the Euclidean norm of a vector, given by an
   *  arbitrary STL container
   *
   * Since no square root is computed, this is slightly faster than
   * norm_Euclidean(). The computed value is given by:
   * @f[
   *  || x || = \sum_i x_i \cdot x_i^*
   * @f]
   *
   * @attention this function is implemented in terms of \c BCG::complex_d_t and
   *  will implicitly cast its operands to that type. While the result is
   *  mathematically correct when used with reals or integers, the type
   *  conversion can take considerable time. Use norm_modSquareSum_real() when
   *  handling a \c double vector or implement your own version based on
   *  \c std::transform_reduce.
   */
  template<class Iterator>
  double norm_modSquareSum(Iterator begin, Iterator end);

  /**
   * @brief computes the taxicab norm of a vector, given by an arbitrary STL
   *  container
   *
   * Remember: the taxicab norm is given by
   * @f[
   *  || x || = \sum_i |x_i|
   * @f]
   *
   * @attention this function is implemented in terms of \c BCG::complex_d_t and
   *  will implicitly cast its operands to that type. While the result is
   *  mathematically correct when used with reals or integers, the type
   *  conversion can take considerable time. Use norm_absSum_real() when
   *  handling a \c double vector or implement your own version based on
   *  \c std::transform_reduce.
   */
  template<class Iterator>
  double norm_absSum(Iterator begin, Iterator end);

  /**
   * @brief computes the maximum norm of a vector, given by an arbitrary STL
   *  container
   *
   * Remember: the maximum norm is given by
   * @f[
   *  || x || = \max |x_i|
   * @f]
   *
   * @attention this function is implemented in terms of \c BCG::complex_d_t and
   *  will implicitly cast its operands to that type. While the result is
   *  mathematically correct when used with reals or integers, the type
   *  conversion can take considerable time. Use std::max_element() when
   *  handling real valued vectors.
   */
  template<class Iterator>
  double norm_max(Iterator begin, Iterator end);


  //! @brief Optimized version of norm_Euclidean() for \c double valued vectors
  template<class Iterator>
  double norm_Euclidean_real(Iterator begin, Iterator end);

  //! @brief Optimized version of norm_modSquareSum() for \c double valued vectors
  template<class Iterator>
  double norm_modSquareSum_real(Iterator begin, Iterator end);

  //! @brief Optimized version of norm_absSum() for \c double valued vectors
  template<class Iterator>
  double norm_absSum_real(Iterator begin, Iterator end);


  /**
   * @brief computes the Euclidean distance between two STL vectors
   *
   * @param beginA iterator to the first value of the first vector
   * @param endA iterator to the last value of the first vector
   * @param beginB iterator to the first value of the second vector
   * @param endB iterator to the last value of the second vector
   * @param normfunc is a function that computes the norm of the difference
   *    between \c A and \c B
   * @param difffunc is a function that computes the difference between two
   *    elements of \c A and \c B
   *
   * The computed value is given by:
   * @f[
   *  ||B - A|| = \mbox{normfunc}( \{\mbox{difffunc}(B_i - A_i)\}_{i=1..N} )
   * @f]
   *
   * @attention in its current form, this function can only be called if \c A
   *  and B are instances of \c std::vector<T>. Otherwise you'll get an ugly
   *  errormessage like:<br>
   @verbatim
   In instantiation of ???double BCG::vector_distance(...)
   error: no match for call to ???(std::function<double(...)>
   @endverbatim
   * See the comments in the \c .tpl for details on why this is, if you want to fix
   * this -- or simply convert your input to an std::vector...
   *
   * @todo fix the normfunc issue
   */
  template<typename Iterator>
  double vector_distance( Iterator beginA, Iterator endA,
                          Iterator beginB, Iterator endB,
                          std::function<double(Iterator, Iterator)> normfunc = norm_Euclidean<Iterator>,
                          std::function<
                            typename std::iterator_traits<Iterator>::value_type(
                              typename std::iterator_traits<Iterator>::value_type,
                              typename std::iterator_traits<Iterator>::value_type
                            )> difffunc = std::minus<typename std::iterator_traits<Iterator>::value_type>()
                         );

//   //! @brief stuff
//   //! @todo include optional norm function, take from findNearby, but use <functional>
  template<class T>
  double vector_distance(const std::vector<T> & A, const std::vector<T> & B);

  // ------------------------------------------------------------------------ //
  // misc

  /**
   * @brief returns the signum of a value
   *
   * @param val the value for which to compute the signum.<br>
   *    \c val must have the comparison operators &lt; and &gt; implemented and
   *    must be constructible from the argument \c 0.
   *
   * @return either \c +1 if \c val is positive, \c -1 if \c val is negative or
   *    \c 0 if \c val is \c 0.
   */
  template <typename T>
  constexpr static inline int sgn(T val);

  /**
   * @brief computes the factorial of an integer n.
   *
   * @attention This is a template implementation that works with arbibrary
   *  types T. If the argument n is non-integral, this will go into an infinite
   *  loop
   *
   * * type unsigned <tt>long long int</tt> yields correct results up to n = 20
   *    and then goes into overload (returns zero)
   * * type \c double yields good results up to n = 22
   *    reaches computation limit after n = 170 and will yield <tt>nan:inf</tt>
   *    beyond (nothrow)
   * * type <tt>long double</tt> yields good results up to n = 25
   * * use at own risk with non-integral types, rounding errors will accumulate
   *
   * Can be used with GMP types and works just fine. However, GMP classes have
   * their proper methods for this.
   */
  template <typename T>
  static inline T factorial (T n);

  //! @}
}

// ========================================================================== //
// template implementations

#include "BCG/Maths.tpp"

#endif
