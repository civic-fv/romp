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
  IRandWalker() { gen = std::mt19937(rd()); }
  /**
   * @brief A handler to use to select a random number between [0, \c occupancy ) to use for choose rules.
   * @param occupancy the current occupancy of the calling multiset
   * @return \c size_t - the index in the multiset that has been choosen
   */
  virtual size_t choose_handler(size_t occupancy) {
    std::uniform_int_distribution<size_t> distribution(0, occupancy-1);
    return distribution(gen);
  }
};

// << ------------------------------------------------------------------------------------------ >> 

namespace __type__ {} // namespace __type__
namespace __model__ {
  enum SCALAR { _UNDEFINED_=0, enum_test1, enum_test2, enum_test3, scalarset_1_1, scalarset_2_1, scalarset_2_2, other_enum, final_enum, anon_enum };
} // namespace __model__
namespace __info__ {            //     0               1          2               3             4             5             6             7         8     9         10
  const std::string TYPE_IDS[] = {"_UNDEFINED_", "enum_test", "scalarset_1", "scalarset_2", "rand_enums", "union_test", "array_test", "ms_test", "foo", "bar", "rec_test",
                                //  11        12      13          14      15      16          17
                                  "arr3d", "arr3d", "ms_comp", "nArr",  "nMs", "rec_comp", "union_arr"};
} // namespace __info__

  std::string to_str(const ::__model__::SCALAR& val) {
    using namespace __model__;
    switch (val) {
      case _UNDEFINED_: return "<UNDEFINED>";
      case enum_test1: return "enum_test1";
      case enum_test2: return "enum_test2";
      case enum_test3: return "enum_test3";
      case scalarset_1_1: return "scalarset_1_1";
      case scalarset_2_1: return "scalarset_2_1";
      case scalarset_2_2: return "scalarset_2_2";
      case other_enum: return "other_enum";
      case final_enum: return "final_enum";
      case anon_enum: return "anon_enum";
      default: return "<UNKNOWN_ENUM>";
    }
    return "<UNKNOWN_ENUM>";
  }

#define __INCLUDE_SCALAR__
#include "scalar_scratch.test.cpp"
#define __INCLUDE_SIMPLE__
#include "scratch.test.cpp"



// << ------------------------------------------------------------------------------------------ >> 


  template<typename INDEX_t, typename ELEMENT_t>
  class ArrayType {
    ELEMENT_t data[INDEX_t::__COUNT()];
  public:
    ArrayType() { Undefine(); }
    ELEMENT_t& operator [] (const INDEX_t& i) { return data[i.__get_index_val()]; }
    // typename std::enable_if<(not std::is_convertible<INDEX_t,size_t>::value), ELEMENT_t>::type
    // ELEMENT_t operator [] (const size_t i) {
    //   if ((0 > i) || (i >= INDEX_t::__COUNT()))
    //     throw std::out_of_range("`"+std::to_string(i)+"` is out of bounds of the array");
    //   return data[i]; 
    // }

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
 
    template<typename RI, typename RE> 
    friend bool operator == (const ArrayType& l, const ArrayType<RI,RE>& r) {
      if (INDEX_t::__COUNT() != RI::__COUNT()) return false; // evaluate-able at compile time
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        if (l.data[i] != r.data[i])
          return false;
      return true;
    }
    template<typename LI, typename LE, typename RI, typename RE> 
    friend bool operator != (const ArrayType& l, const ArrayType<RI,RE>& r) {
      if (INDEX_t::__COUNT() != RI::__COUNT()) return true; // evaluate-able at compile time
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        if (l.data[i] == r.data[i])
          return false;
      return true;
    }

    friend inline std::ostream& operator << (std::ostream& out, const ArrayType& val) {
      if (val.IsUndefined()) return (out << "<UNDEFINED>");
      out << '['; std::string sep;
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i) {
        out << sep << val.data[i]; sep = ", ";
      }
      return (out << ']');
    }
  };


  // << ------------------------------------------------------------------------------------------ >> 

  template<size_t MAX, typename ELEMENT_t>
  class MultisetType {
    ELEMENT_t data[MAX];
    size_t occupancy = 0;
    bool is_defined = false;
  public:
    MultisetType() { Undefine(); }

    bool IsUndefined() const { return ((not is_defined) && (occupancy == 0)); }
    void Undefine() { std::memset(&data, 0u, sizeof(data)); occupancy = 0; is_defined = false; } // for now design still allows for setting all to 0 to undefine 
    // Do nothing, should never be called, just here for record & array templates
    void Clear() { Undefine(); is_defined = true; }

    size_t MultisetCount(const std::function<bool(const size_t)>& cond) const {
      size_t count = 0;
      for (size_t i=0; i<occupancy; ++i)
        if (cond(i)) count++;
      return count;
    }
    void MultisetAdd(const ELEMENT_t& val) {
      if (occupancy >= MAX || val.IsUndefined()) 
        return;
      is_defined = true;
      data[occupancy++] = val;
    }
    void MultisetRemove(const size_t i) {
      if (i != occupancy-1) {
        data[i] = data[occupancy-1];
      }
      data[--occupancy].Undefine();
    }
    void MultisetRemovePred(const std::function<bool(const size_t)>& pred) {
      for (long i=occupancy; i>0; --i)
        if (pred(i-1)) MultisetRemove(i-1);
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
    template<size_t RM, typename RE>  
    friend bool operator == (const MultisetType& l, const MultisetType<RM,RE>& r) {
      // if (MAX != RM) return false; // evaluate-able at compile time
      if (l.occupancy != r.occupancy) return false;
      for (size_t i=0; i<l.occupancy; ++i)
        if (l.data[i] != r.data[i])
          return false;
      return true;
    }
    template< size_t RM, typename RE> 
    friend bool operator != (const MultisetType& l, const MultisetType<RM,RE>& r) {
      // if (LM != RM) return true; // evaluate-able at compile time
      if (l.occupancy != r.occupancy) return true;
      for (size_t i=0; i<l.occupancy; ++i)
        if (l.data[i] == r.data[i])
          return false;
      return true;
    }

    friend std::ostream& operator << (std::ostream& out, const MultisetType& val) {
      if (val.IsUndefined()) return (out << "<UNDEFINED>");
      out << '[' << val.occupancy << "]{"; std::string sep;
      for (size_t i=0; i<val.occupancy; ++i) {
        out << sep << val.data[i]; sep = ", ";
      }
      return (out << '}');
    }
  };


  // << ------------------------------------------------------------------------------------------ >> 

  template<size_t NAME_ID_START, typename... MEMBERS>
  class RecordType {
    std::tuple<MEMBERS...> data;
  protected:
    static const std::string& _GET_MEMBER_NAME(size_t i) { return ::__info__::TYPE_IDS[NAME_ID_START+i]; }
    template<size_t I>
    inline typename std::enable_if<(I>=sizeof...(MEMBERS)),bool>::type _IsUndefined() const { return true; }
    template<size_t I>
    inline typename std::enable_if<(I<sizeof...(MEMBERS)),bool>::type _IsUndefined() const {
      if (not std::get<I>(data).IsUndefined()) return false;
      return _IsUndefined<I+1>();
    }
    template<size_t I>
    inline typename std::enable_if<(I>=sizeof...(MEMBERS)),void>::type _Clear() { return; }
    template<size_t I>
    inline typename std::enable_if<(I<sizeof...(MEMBERS)),void>::type _Clear() {
      std::get<I>(data).Clear();
      _Clear<I+1>();
    }
    template<size_t I>
    static inline typename std::enable_if<(I>=sizeof...(MEMBERS)),bool>::type _Equal(const RecordType& l, const RecordType& r) { return true; }
    template<size_t I>
    static inline typename std::enable_if<(I<sizeof...(MEMBERS)),bool>::type _Equal(const RecordType& l, const RecordType& r) {
      if (std::get<I>(l.data) != std::get<I>(r.data)) return false;
      return _Equal<I+1>(l,r);
    }
    template<size_t I>
    static inline typename std::enable_if<(I>=sizeof...(MEMBERS)),bool>::type _NEqual(const RecordType& l, const RecordType& r) { return true; }
    template<size_t I>
    static inline typename std::enable_if<(I<sizeof...(MEMBERS)),bool>::type _NEqual(const RecordType& l, const RecordType& r) {
      if (std::get<I>(l.data) == std::get<I>(r.data)) return false;
      return _NEqual<I+1>(l,r);
    }
  public:
    RecordType() { Undefine(); }

    bool IsUndefined() const { return _IsUndefined<0>(); }
    void Undefine() { std::memset(&data, 0u, sizeof(data)); } // for now design still allows for setting all to 0 to undefine
    void Clear() { _Clear<0>(); }
    template<size_t I>
    typename std::enable_if<(I>=sizeof...(MEMBERS)),typename std::tuple_element<I,std::tuple<MEMBERS...>>::type>::type& get() { 
      throw std::out_of_range("member does not exist in record"); 
    }
    template<size_t I>
    typename std::enable_if<(I<sizeof...(MEMBERS)),typename std::tuple_element<I,std::tuple<MEMBERS...>>::type>::type& get() { 
      return std::get<I>(data); 
    }

    friend bool operator == (const RecordType& l, const RecordType& r) { return RecordType::_Equal<0>(l,r); }
    friend bool operator != (const RecordType& l, const RecordType& r) { return RecordType::_NEqual<0>(l,r); }

  protected:
    template<size_t I>
    typename std::enable_if<(I>=sizeof...(MEMBERS)),void>::type _write(std::ostream& out) const { return; }
    template<size_t I>
    typename std::enable_if<(I<sizeof...(MEMBERS)),void>::type _write(std::ostream& out) const {
      if (I > 0) out << ", ";
      out << '`' << _GET_MEMBER_NAME(I) << "`: " << std::get<I>(data);
      if (I < sizeof...(MEMBERS)) _write<I+1>(out);
    }
  public:
    friend std::ostream& operator << (std::ostream& out, const RecordType& val) {
      if (val.IsUndefined()) return (out << "<UNDEFINED>");
      out << "{"; val._write<0>(out); return (out << '}');
    }
  };


// << ------------------------------------------------------------------------------------------ >> 

const char* to_str(const bool val) { return ((val) ? "true" : "false"); }



auto main() -> int {
  using namespace __model__;
  typedef TypeIdType<1,EnumType<enum_test1,3>> enum_test;
  typedef TypeIdType<2,ScalarsetType<2,scalarset_1_1,1>> scalarset_1;
  typedef TypeIdType<3,ScalarsetType<3,scalarset_2_1,2>> scalarset_2;
  typedef TypeIdType<4,EnumType<other_enum,2>> rand_enums;
  typedef TypeIdType<5,ScalarsetUnionType<enum_test,scalarset_1,scalarset_2,EnumType<anon_enum,1>>> union_test;

  typedef TypeIdType<6,ArrayType<enum_test,scalarset_2>> array_test;
  typedef TypeIdType<7,MultisetType<4,scalarset_2>> ms_test;
  typedef TypeIdType<10,RecordType<8,RangeType<4,8>,union_test>> rec_test;
  typedef TypeIdType<11,ArrayType<RangeType<4,8>,ArrayType<scalarset_2,BooleanType>>> arr2d;
  typedef TypeIdType<12,ArrayType<RangeType<4,8>,ArrayType<scalarset_2,ArrayType<scalarset_1,BooleanType>>>> arr3d;
  typedef TypeIdType<13,MultisetType<4,rec_test>> ms_comp;
  typedef TypeIdType<16,RecordType<14,array_test,ms_test>> rec_comp;
  typedef TypeIdType<17,ArrayType<union_test,ms_test>> union_arr;

  try {
    IRandWalker __rw__;
    
    enum_test e1 = _UNDEFINED_; // (enum_test1);
    scalarset_1 s1(_UNDEFINED_); // (scalarset_1_1);
    scalarset_2 s2; // = scalarset_2_2;
    rand_enums e2; // = final_enum;
    union_test u1 = _UNDEFINED_;

    e1.Clear();
    s1.Clear();
    s2.Clear();
    e2.Clear();
    u1.Clear();

    array_test a1;
    ms_test m1;
    rec_test r1;
    arr2d a2;
    arr3d a3;
    ms_comp m2;
    rec_comp r2;
    union_arr a4;

    std::cout << "\n"
        "array_test a1;           -> " << a1 << "\n"
        "ms_test m1;              -> " << m1 << "\n"
        "rec_test r1;             -> " << r1 << "\n"
        "arr2d a2;                -> " << a2 << "\n"
        "arr3d a3;                -> " << a3 << "\n"
        "ms_comp m2;              -> " << m2 << "\n"
        "rec_comp r2;             -> " << r2 << "\n"
        "union_arr a4;            -> " << a4 << "\n"
      << std::flush << "\n"
        "IsUndefined(a1)          -> " << to_str(a1.IsUndefined()) << "\n"
        "IsUndefined(m1)          -> " << to_str(m1.IsUndefined()) << "\n"
        "IsUndefined(r1)          -> " << to_str(r1.IsUndefined()) << "\n"
        "IsUndefined(a2)          -> " << to_str(a2.IsUndefined()) << "\n"
        "IsUndefined(a3)          -> " << to_str(a3.IsUndefined()) << "\n"
        "IsUndefined(m2)          -> " << to_str(m2.IsUndefined()) << "\n"
        "IsUndefined(r2)          -> " << to_str(r2.IsUndefined()) << "\n"
        "IsUndefined(a4)          -> " << to_str(a4.IsUndefined()) << "\n"
      << std::flush << "\n"
        "Clear a1                 -> " << ({a1.Clear(); a1;}) << "\n"
        "Clear m1                 -> " << ({m1.Clear(); m1;}) << "\n"
        "Clear r1                 -> " << ({r1.Clear(); r1;}) << "\n"
        "Clear a2                 -> " << ({a2.Clear(); a2;}) << "\n"
        "Clear a3                 -> " << ({a3.Clear(); a3;}) << "\n"
        "Clear m2                 -> " << ({m2.Clear(); m2;}) << "\n"
        "Clear r2                 -> " << ({r2.Clear(); r2;}) << "\n"
        "Clear a4                 -> " << ({a4.Clear(); a4;}) << "\n"
      << std::flush << "\n"
        // "a1[0]                    -> " << a1[0] << "\n"
        "a1[enum_test1]           -> " << a1[enum_test1] << "\n"
        "a2[5][scalarset_2_1]     -> " << a2[5][scalarset_2_1] << "\n"
        "a2[6r][scalarset_2_2]    -> " << a2[RangeType<4,8>(6)][scalarset_2_2] << "\n"
        "a3[6r][scalarset_2_1][scalarset_1_1] -> " << a3[RangeType<4,8>(6)][scalarset_2_1][scalarset_1_1] << "\n"
        "a4[enum_test1]           -> " << a4[enum_test1] << "\n"
        "a4[scalarset_2_1]        -> " << a4[scalarset_2_1] << "\n"
        "a4[s2]                   -> " << a4[s2] << "\n"
        "a4[anon_enum]            -> " << a4[anon_enum] << "\n"
        // "a3[6r][0][scalarset_1_1] -> " << a3[RangeType<4,8>(6)][0][scalarset_1_1] << "\n"
      << std::flush << "\n"
        "a1[enum_test2] = scalarset_2_2       -> " << (a1[enum_test2] = scalarset_2_2) << "\n"
        "a1;                      -> " << (a1) << "\n"
      << std::flush << "\n"
        "a2[8][scalarset_2_1] = true          -> " << (a2[8][scalarset_2_1] = true) << "\n"
        "a2;                      -> " << (a2) << "\n"
      << std::flush << "\n"
        "MultisetAdd(scalarset_2_1,m1);       -> " << ({m1.MultisetAdd(scalarset_2_1); m1;}) << "\n"
        "MultisetAdd(scalarset_2_2,m1);       -> " << ({m1.MultisetAdd(scalarset_2_2); m1;}) << "\n"
        "MultisetAdd(scalarset_2_1,m1);       -> " << ({m1.MultisetAdd(scalarset_2_1); m1;}) << "\n"
        "MultisetAdd(scalarset_2_2,m1);       -> " << ({m1.MultisetAdd(scalarset_2_2); m1;}) << "\n"
        "MultisetAdd(scalarset_2_1,m1);       -> " << ({m1.MultisetAdd(scalarset_2_1); m1;}) << "\n"
        "MultisetAdd(scalarset_2_2,m1);       -> " << ({m1.MultisetAdd(scalarset_2_2); m1;}) << "\n"
        "MultisetAdd(r1,m2);                  -> " << ({m2.MultisetAdd(r1); m2;}) << "\n"
      << std::flush << "\n"
        "r1.foo = 5               -> " << (r1.get<0/*foo*/>() = 5) << "\n"
        "r1.bar = enum_test3      -> " << (r1.get<1/*bar*/>() = enum_test3) << "\n"
        "r1;                      -> " << (r1) << "\n"
      << std::flush << "\n"
        "MultisetAdd(r1,m2);                  -> " << ({m2.MultisetAdd(r1); m2;}) << "\n"
      << std::flush << "\n"
        "MultisetCount(i:m1, m1[i]==s2)       -> " << (m1.MultisetCount([&](size_t i) -> bool { return (__multiset_element(m1, i)==s2); })) << "\n"
        "MultisetCount(i:m2, m2[i]==r1)       -> " << (m2.MultisetCount([&](size_t i) -> bool { return (__multiset_element(m2, i)==r1); })) << "\n"
      << std::flush << "\n"
        "MultisetRemove(1, m1)                -> " << ({m1.MultisetRemove(1); m1;}) << "\n"
        "MultisetRemovePred(i:m1, m1[i]==s2)  -> " << ({m1.MultisetRemovePred([&](const size_t i) -> bool { return (__multiset_element(m1, i)==s2); }); m1;}) << "\n"
        "MultisetRemove(0, m2)                -> " << ({m2.MultisetRemove(0); m2;}) << "\n"
        "MultisetRemovePred(i:m2, m2[i]==r1)  -> " << ({m2.MultisetRemovePred([&](const size_t i) -> bool { return (__multiset_element(m2, i)==r1); }); m2;}) << "\n"
      << std::flush << "\n"
      << std::flush;

  } catch (std::exception& ex) {
    std::cerr << "\nexception caught:\n  " << ex.what() << std::endl;
  }
  std::cout << "\n\n" << std::flush;
  return 0;
}
