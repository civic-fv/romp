#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <exception>
#include <type_traits>
#include <cstring>
#include <tuple>
#include <random>

// << ------------------------------------------------------------------------------------------ >> 

class IRandWalker {
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
public:
  IRandWalker() : rd(std::random_device()), gen(rd) {}
  /**
   * @brief A handler to use to select a random number between [0, \c occupancy ) to use for choose rules.
   * @param occupancy the current occupancy of the calling multiset
   * @return \c size_t - the index in the multiset that has been choosen
   */
  virtual size_t choose_handler(size_t occupancy) {
    std::uniform_int_distribution<size_t> distribution(0, occupancy-1)
    return distribution(gen);
  }
};

// << ------------------------------------------------------------------------------------------ >> 

namespace __type__ {} // namespace __type__
namespace __model__ {} // namespace __model__
namespace __info__ {
  const std::string TYPE_IDS[] = {"_UNDEFINED_", "enum_test", "scalarset_1", "scalarset_2", "rand_enums", "union_test"};
} // namespace __info__


#define __INCLUDE_SCALAR__
#include "scalar_scratch.test.cpp"

// << ------------------------------------------------------------------------------------------ >> 


  template<typename T>
  class BaseType {
    T value;
    bool is_defined;
  protected:
    inline T& get() {
      if (not is_defined) 
        throw std::logic_error("value was undefined");
      return value;
    }
    inline BaseType& set(const T& value_) {
      value = value_;
      is_defined = true;
      return *this;
    }
    inline T& unsafe_get() { return value; }
  public:
    BaseType() { Undefine(); }
    BaseType(T value_) : is_defined(true), value(value_) {}
    inline void Undefine() { is_defined = false; std::memset(&value, 0u, sizeof(T)); }
    inline bool IsUndefined() const { return not is_defined; }

    operator T () { return get(); } // WARNING: do not include in production

    friend std::ostream& operator << (std::ostream& out, BaseType& val) {
      if (val.is_defined)
        return (out << val.value);
      return (out << "Undefined");
    }
//     friend ostream_p& operator << (ostream_p& out, BaseType& val) { return (out << val.get()); }
//   protected:
//     static inline const std::string __json_type() { return "null"; }
//     template<class O>
//     friend ojstream<O>& operator << (ojstream<O>& out, const BaseType& val) {
// #     ifdef __ROMP__SIMPLE_TRACE
//         return (out << val.IsUndefined() << "," << val.get())
// #     else
//         out << "{\"$type\":\"undefinable-value\",\"type\":null,\"value\":";
//         if (val.IsUndefined())
//           return (out << "null}");
//         return (out << val.get() << '}');
// #     endif 
//     }
  };

  template<size_t NAME_ID, typename T>
  class TypeIdType : public T {
  public:
    template<typename... Args>
    TypeIdType(Args &&... args) : T(std::forward<Args>(args)...) {}
    static inline const std::string __id() { return __info__::TYPE_IDS[NAME_ID]; }
    static inline const std::string __json_type() {
      return "{\"$type\":\"type-id\",\"id\":\"" + __id() + "\",\"referent\":" + T::__json_type() + '}';
    }
  };

// << ------------------------------------------------------------------------------------------ >> 


  template<typename INDEX_t, typename ELEMENT_t>
  class ArrayType {
    ELEMENT_t data[INDEX_t::__COUNT()];
  public:
    ArrayType() { Undefine(); }
    ELEMENT_t operator [] (const INDEX_t& i) { return data[i.__get_index_val()]; }
    ELEMENT_t operator [] (const size_t i) {
      if ((0 > i) || (i >= INDEX_t::__COUNT()))
        throw std::out_of_range("`"+std::to_string(i)+"` is out of bounds of the array");
      return data[i]; 
    }

    bool IsUndefined() const {
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        if (not data[i].IsUndefined()) 
          return false;
      return true;
    }
    void Undefine() { std::memset(&data, 0u, sizeof(data)); } // for now design still allows for setting all to 0 to undefine 
    void Clear() {
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        data[i].Clear();
    }

    // template<typename LI, typename LE, typename RI, typename RE> 
    // friend bool operator == (const ArrayType<LI,LE>& l, const ArrayType<RI,RE> r) {
    friend bool operator == (const ArrayType& l, const ArrayType r) {
      // if (LI:__COUNT() != RI::__COUNT()) return false; // evaluate-able at compile time
      // for (size_t i=0; i<LI::__COUNT(); ++i)
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        if (l.data[i] != r.data[i])
          return false;
      return true;
    }
    template<typename LI, typename LE, typename RI, typename RE> 
    friend bool operator != (const ArrayType<LI,LE>& l, const ArrayType<RI,RE> r) {
      if (LI:__COUNT() != RI::__COUNT()) return true; // evaluate-able at compile time
      for (size_t i=0; i<LI::__COUNT(); ++i)
        if (l.data[i] == r.data[i])
          return false;
      return true;
    }

  };


  // << ------------------------------------------------------------------------------------------ >> 

  template<size_t MAX, typename ELEMENT_t>
  class MultisetType {
    ELEMENT_t data[MAX];
    size_t occupancy = 0;
  public:
    MultisetType() { Undefine(); }

    bool IsUndefined() const { return occupancy == 0; }
    void Undefine() { std::memset(&data, 0u, sizeof(data)); occupancy = 0; } // for now design still allows for setting all to 0 to undefine 
    // Do nothing, should never be called, just here for record & array templates
    void Clear() {}

    size_t MultisetCount(const std::function<bool(const size_t)>& cond) const {
      size_t count;
      for (size_t i=0; i<occupancy; ++i)
        if (cond(i)) count++;
      return count;
    }
    void MultisetAdd(const ELEMENT_t& val) {
      if (occupancy >= MAX) return;
      data[occupancy++] = val;
    }
    void MultisetRemove(const size_t i) {
      if (i != occupancy-1) {
        data[i] = data[occupancy-1];
      }
      data[--occupancy].Undefine();
    }
    void MultisetRemovePred(const std::function<bool(const size_t)>& pred) {
      for (size_t i=occupancy-1; i>=0; --i)
        if (pred(i)) MultisetRemove(i);
    }

    // always call IsUndefined() before using this, else exception thrown if empty/undefined
    const size_t Choose(IRandWalker* __rw__) const {
      if (occupancy == 0)
        throw std::logic_error("tried to choose from an empty/undefined multiset");
      return __rw__->choose_handler(occupancy);
    }

    friend const ELEMENT_t& __multiset_element(const MultisetType& ms, const size_t i) {
      return ms.data[i];
    }
    template<size_t LM, typename LE, size_t RM, typename RE>  
    friend bool operator == (const MultisetType<LI,LE>& l, const MultisetType<RI,RE> r) {
      // if (LM != RM) return false; // evaluate-able at compile time
      if (l.occupancy != r.occupancy) return false;
      for (size_t i=0; i<l.occupancy; ++i)
        if (l.data[i] != r.data[i])
          return false;
      return true;
    }
    template<size_t LM, typename LE, size_t RM, typename RE> 
    friend bool operator != (const MultisetType<LI,LE>& l, const MultisetType<RI,RE> r) {
      // if (LM != RM) return true; // evaluate-able at compile time
      if (l.occupancy != r.occupancy) return true;
      for (size_t i=0; i<l.occupancy; ++i)
        if (l.data[i] == r.data[i])
          return false;
      return true;
    }
  };


  // << ------------------------------------------------------------------------------------------ >> 

  template<size_t NAME_ID_START, typename... MEMBERS>
  class RecordType : public BaseType<RecT> {
    std::tuple<MEMBERS...> data;
  protected:
    static const std::string GET_MEMBER_NAME(size_t i) { return ::__info__::TYPE_IDS[NAME_ID_START+i]; }
    template<size_t I>
    bool _IsUndefined() const {
      if (I >= sizeof...(MEMBERS)) return true;
      if (not std::get<I>(data).IsUndefined()) return false;
      return _IsUndefined<I+1>();
    }
    template<size_t I>
    void _Clear() {
      if (I >= sizeof...(MEMBERS)) return;
      _Clear<I+1>();
    }
    template<size_t I>
    static bool _Equal(const RecordType& l, const RecordType& r) {
      if (I >= sizeof...(MEMBERS)) return true;
      if (std::get<I>(l.data) != std::get<I>(r.data)) return false;
      return _Equal<I+1>(l,r);
    }
    template<size_t I>
    static bool _NEqual(const RecordType& l, const RecordType& r) {
      if (I >= sizeof...(MEMBERS)) return true;
      if (std::get<I>(l.data) == std::get<I>(r.data)) return false;
      return _NEqual<I+1>(l,r);
    }
  public:
    RecordType() { Undefine(); }

    bool IsUndefined() const { return _IsUndefined<0>(); }
    void Undefine() { std::memset(&data, 0u, sizeof(data)); } // for now design still allows for setting all to 0 to undefine
    void Clear() { _Clear<0>(); }
    template<size_t I>
    typename std::tuple_element<I,std::tuple<MEMBERS...>>::type& get() { return std::get<I>(data); }

    friend bool operator == (const RecordType& l, const RecordType& r) { return RecordType::_Equal<0>(l,r); }
    friend bool operator != (const RecordType& l, const RecordType& r) { return RecordType::_NEqual<0>(l,r); }
  };


// << ------------------------------------------------------------------------------------------ >> 

const char* to_str(const bool val) { return ((val) ? "true" : "false"); }



auto main() -> int {
  using namespace __model__;

  try {
    IRandWalker __rw__;
    BaseType<int> v1 = 1;

    std::cout <<
      "TODO\n\n"
      << std::flush;

  } catch (std::exception& ex) {
    std::cerr << "\nexception caught:\n  " << ex.what() << std::endl;
  }
  std::cout << "\n\n" << std::flush;
  return 0;
}
