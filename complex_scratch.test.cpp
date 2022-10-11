#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <exception>
#include <type_traits>

namespace __model__ {} // namespace __model__

// << ------------------------------------------------------------------------------------------ >> 


  template<typename INDEX_t, typename ELEMENT_t>
  class ArrayType {
    ELEMENT_t data[INDEX_t::__count()];
  };


  // << ------------------------------------------------------------------------------------------ >> 

  template<size_t MAX, typename ELEMENT_t>
  class MultisetType {
    ELEMENT_t data[MAX];
  };




// << ------------------------------------------------------------------------------------------ >> 

const char* to_str(const bool val) { return ((val) ? "true" : "false"); }



auto main() -> int {
  using namespace __model__;


  try {

    std::cout <<
      "TODO\n\n"
      << std::flush;

  } catch (std::exception& ex) {
    std::cerr << "\nexception caught:\n  " << ex.what() << std::endl;
  }
  std::cout << "\n\n" << std::flush;
  return 0;
}
