// ========================================================================== //
// dependencies

// STL
#include <iostream>
#include <iomanip>

#include <vector>
#include <complex>
using namespace std::complex_literals;
#include <string>
using namespace std::string_literals;

// own
#define BCG_MATHS
#include "BCG.hpp"

// ========================================================================== //

#define THROWTEXT(msg) (std::string("RUNTIME EXCEPTION IN ") + (__PRETTY_FUNCTION__) + "\n" + msg)

// ========================================================================== //

template<typename Iterator>
void vd_test (Iterator beginA, Iterator endA,
              Iterator beginB, Iterator endB
) {
  auto N = std::distance(beginA, endA);
  if (N != std::distance(beginB, endB)) {
    throw std::invalid_argument("    vectors are not of same dimension!");
  }

  auto difffunc = std::minus<>();

  std::vector<typename std::iterator_traits<Iterator>::value_type> delta(N);
  std::transform(
    beginB, endB,
    beginA,
    delta.begin(),
    difffunc
  );

  std::vector<double> delta_d(N);
  std::transform(
    beginB, endB,
    beginA,
    delta_d.begin(),
    difffunc
  );

  std::cout << "int" << std::endl;
  for (auto & elm : delta) {
    std::cout << elm << std::endl;
  }
  std::cout << BCG::norm_Euclidean(delta  .begin(), delta  .end()) << std::endl;

  std::cout << "double" << std::endl;
  for (auto & elm : delta_d) {
    std::cout << elm << std::endl;
  }
  std::cout << BCG::norm_Euclidean(delta_d.begin(), delta_d.end()) << std::endl;

}


template<typename Iterator>
double vd_test_full(Iterator beginA, Iterator endA,
                    Iterator beginB, Iterator endB,
                    std::function<
                      double(
                      Iterator,
                      Iterator
                    )> normfunc = BCG::norm_Euclidean<Iterator>,
                    std::function<
                      typename std::iterator_traits<Iterator>::value_type(
                      typename std::iterator_traits<Iterator>::value_type,
                      typename std::iterator_traits<Iterator>::value_type
                    )> difffunc = std::minus<typename std::iterator_traits<Iterator>::value_type>()
) {
  // this is a copy of the vector_distance code in BCG.

  auto N = std::distance(beginA, endA);
  if (N != std::distance(beginB, endB)) {
    throw std::invalid_argument(THROWTEXT("    vectors are not of same dimension!"));
  }

  // and this is what causes the problem if you plug in anything other than a
  // std::vector for A and B:
  std::vector<typename std::iterator_traits<Iterator>::value_type> delta(N);
  std::transform(
    beginB, endB,
    beginA,
    delta.begin(),
    difffunc
  );

  /* while delta can be computed from any compatible containers, it will always
   * be a std::vector.
   * in the return statement, normfunc is invoked, which assumes its parameters
   * are of type Iterator, which is related to the container and might not be
   * a std::vector::iterator.
   *
   * There's two ways of fixing this issue:
   * A) demanding that normfunc has to be a templated in std::vector::iterator
   *    (probably the easier one)
   * B) dynamically deciding the type of delta to match that of A, B.
   */

  // ------------------------------------------------------------------------ //
  // type test system

  typename std::iterator_traits<Iterator>::value_type iteratorBase;

  const std::type_info& TI_iteratorBase = typeid(iteratorBase);
  const std::type_info& TI_iterator     = typeid(Iterator);
  const std::type_info& TI_normfunc     = typeid(normfunc);
  const std::type_info& TI_difffunc     = typeid(difffunc);
  const std::type_info& TI_aim          = typeid(BCG::norm_modSquareSum<Iterator>);
  const std::type_info& TI_delta_begin  = typeid(delta.begin());

  std::cout << "# ---- #" << std::endl;
  std::cout << "TI_iterator    : " << TI_iterator    .name() << std::endl;
  std::cout << "TI_iteratorBase: " << TI_iteratorBase.name() << std::endl;
  std::cout << "TI_difffunc    : " << TI_difffunc    .name() << std::endl;
  std::cout << "TI_normfunc    : " << TI_normfunc    .name() << std::endl;
  std::cout << "TI_aim         : " << TI_aim         .name() << std::endl;
  std::cout << "TI_delta_begin : " << TI_delta_begin .name() << std::endl;
  /* use c++filt -t in console to demangle the output of these.
   *
   * e.g.:
   * blue-chameleon@blue-chameleon-HP-250-G7-Notebook-PC:~/Codes/Parrot$ c++filt -t
   * St8functionIFdPKiS1_EE
   * std::function<double (int const*, int const*)>
   *
   * FdPKiS0_E
   * double (int const*, int const*)
   *
   *
   * With:
   * TI_iterator    : PKi                         int const*
   * TI_iteratorBase: i                           int
   * TI_difffunc    : St8functionIFiiiEE          std::function<int (int, int)>
   * TI_normfunc    : St8functionIFdPKiS1_EE      std::function<double (int const*, int const*)>
   * TI_aim         : FdPKiS0_E                                 double (int const*, int const*)
   * TI_delta_begin : N9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE
   *                                              __gnu_cxx::__normal_iterator<int*, std::vector<int, std::allocator<int> > >
   */
  std::cout << "# ---- #" << std::endl;
  // ------------------------------------------------------------------------ //


  return normfunc(delta.begin(), delta.end());
  //return BCG::norm_modSquareSum(delta.begin(), delta.end());
}

// ========================================================================== //
// unittest

void unittest_BCG_MATHS() {
  BCG::init();

  std::cout << ("\x1b[93m");
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << "| Testing BCG Maths Module                                                     |" << std::endl;
  std::cout << "+------------------------------------------------------------------------------+" << std::endl;
  std::cout << ("\x1b[0m")  ;
  std::cout << std::setw(8) << std::fixed;

  std::cout << "the value of π: " << BCG::PI << std::endl;

  BCG::complex_d_t z = std::exp( 1i * BCG::PI );
  std::cout << "exp(iπ) = " << z << std::endl;
  std::cout << "string prefix and complex number: "s + BCG::complex_to_string(z) << std::endl;

  std::cout << "4! = " << BCG::factorial(4) << std::endl;
  std::cout << "(4.0)! = " << BCG::factorial( 4.0 ) << std::endl;

  auto        x = {-1, 2, 3};
  auto        y = {-4, 5, 6};

  std::vector<double> v(y.begin(), y.end());
  std::vector<double> w(x.begin(), x.end());

  std::cout << "modsquare norm of x       : "  << BCG::norm_modSquareSum(x.begin(), x.end()) << std::endl;
  std::cout << "   absSum-norm of x       :  " << BCG::norm_absSum      (x.begin(), x.end()) << std::endl;
  std::cout << "      norm_max of x       :  " << BCG::norm_max         (x.begin(), x.end()) << std::endl;

  std::cout << "modsquare_real norm of x  : "  << BCG::norm_modSquareSum_real(x.begin(), x.end()) << std::endl;
  std::cout << "   absSum_real-norm of x  :  " << BCG::norm_absSum_real      (x.begin(), x.end()) << std::endl;

  std::cout << "euclidean norm of y       :  " << BCG::norm_Euclidean(v.begin(), v.end()) << std::endl;
  std::cout << "difference between v and w:  " << BCG::vector_distance(v.begin(), v.end(),
                                                                       w.begin(), w.end() ) << std::endl;

  // this code will give an compile time error
//   std::cout << "difference between x and y:  " << BCG::vector_distance(x.begin(), x.end(),
//                                                                        y.begin(), y.end() ) << std::endl;

  // use this as a basis if you want to fix the issue
//   std::cout << std::endl;
//   std::cout << vd_test_full(v.begin(), v.end(),
//                             w.begin(), w.end() ) << std::endl;
//
//   std::cout << std::defaultfloat;
  std::cout << std::endl << "DONE."<< std::endl << std::endl;
}
