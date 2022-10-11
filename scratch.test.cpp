#include <iostream>
#include <exception>
#include <string>
#include <utility>
#include <cstring>


typedef long range_t;
typedef struct{int a; char* b;} comp_t;

namespace __info__ {
  const std::string TYPE_IDS[] = {"SmallRange"};
} // namespace __info__

template<size_t NAME_ID, typename T>
class TypeIdType : public T {
public:
  template<typename... Args>
  TypeIdType(Args &&... args) : T(std::forward<Args>(args)...) {}
  const std::string __id() { return ::__info__::TYPE_IDS[NAME_ID]; }
  const std::string __json_type() {
    return "{\"$type\":\"type-id\",\"id\":\"" + __id() + "\",\"referent\":" + ((T*)this)->__json_type() + '}';
  }
};
template<typename T> 
class ValueType {
  T value;
  bool is_defined;
protected:
  T& get() {
    if (not is_defined) 
      throw std::logic_error("value was undefined");
    return value;
  }
  ValueType& set(const T& value_) {
    value = value_;
    is_defined = true;
    return *this;
  }
  T& unsafe_get() { return value; }
public:
  ValueType() { Undefine(); }
  ValueType(T value_) : is_defined(true), value(value_) {}
  void Undefine() { is_defined = false; std::memset(&value, 0u, sizeof(T)); }
  bool IsUndefined() { return not is_defined; }
  // virtual void Clear() = 0;
  operator T () { return get(); }
  // ValueType& operator = (const ValueType& other) { 
  //   value = other.value;
  //   is_defined = other.is_defined;
  //   return *this; 
  // }
  ValueType& operator = (T other) { return *set(other); }
  const std::string __json_type() { return "null"; }
  friend std::ostream& operator << (std::ostream& out, ValueType& val) {
    if (val.is_defined)
      return (out << val.value);
    return (out << "Undefined");
  }
//   friend ostream_p& operator << (ostream_p& out, ValueType& val) { return (out << val.get()); }
//   template<class O>
//   friend ojstream<O>& operator << (ojstream<O>& out, ValueType& val) {
// #   ifdef __ROMP__SIMPLE_TRACE
//       return (out << val.IsUndefined() << "," << val.get())
// #   else
//       out << "{\"$type\":\"value\",\"type\":null,\"value\":";
//       if (val.IsUndefined())
//         return (out << "null}");
//       return (out << val.get() << '}');
// #  endif 
//   }
};

template<range_t LB, range_t UB>
class RangeType : public ValueType<range_t> {
public:
  RangeType() : ValueType<range_t>() {}
  RangeType(range_t value_) : ValueType<range_t>(value_) {}
  void Clear() { set(LB); }
  RangeType& operator = (range_t other) { 
    if (other < LB || other > UB)
      throw std::out_of_range("value " +
                              std::to_string(other) +
                              " being assigned is out of range (`"+ 
                              std::to_string(LB) +
                              ".."+
                              std::to_string(UB) +
                              "`)");
    return *((RangeType*)set(other));
  }
  const std::string __json_type() { 
    return (std::string() + "{\"$type\":\"range-type\","
              "\"bounds\":["+std::to_string(LB)+","+std::to_string(UB)+"]}").c_str();
  }
//   friend ostream_p& operator << (ostream_p& out, ValueType& val) { 
//     return (out << get());
//   }
//   template<class O>
// #ifndef __ROMP__SIMPLE_TRACE
//   friend ojstream<O>& operator << (ojstream<O>& out, RangeType& val) {
//     out << "{\"$type\":\"value\",\"type\":{\"$type\":\"type-expr\",\"type\":\"range\","
//            "\"lower-bound\":" << LB << ",\"upper-bound\":" << UB << "},"
//            "\"value\":"; 
//     if (val.IsUndefined())
//       return (out << "null}");
//     return (out << val.get() << '}');
//   }
// #endif
};



constexpr const char* to_str(const bool val) { return ((val) ? "true" : "false"); }

const char sr_name[] = "SmallRange";

int main() {
  ValueType<int> v1(5);
  ValueType<range_t> v2 = (5l);
  UndefinableType<int> v1(5);
  UndefinableType<range_t> v2 = (5l);
  RangeType<0,12> r1 = (5l);
  RangeType<-12,12> r2(-2l);
  try {
    std::cout <<
      "sizeof(int)                -> "
        << sizeof(int) << " B\n"
      "sizeof(ValueType<int>)     -> "
        << sizeof(ValueType<int>) << " B\n"
      "sizeof(range_t)            -> "
        << sizeof(range_t) << " B\n"
      "sizeof(ValueType<range_t>) -> "
        << sizeof(ValueType<range_t>) << " B\n"
      "sizeof(RangeType<0,12>)    -> " 
        << sizeof(RangeType<0,12>) << " B\n"
      // "sizeof(comp_t)             -> "
      //   << sizeof(comp_t) << "B\n"
    << std::endl << 
      "ValueType<int>     v1(5);\n"
      "ValueType<range_t> v2 = (5l);\n"
      "RangeType<0,12>    r1 = (5l);\n"
      "RangeType<-12,12>  r2(-2l);\n"
    << std::endl <<
      "v1       -> " << v1 << "\n"
      "v2       -> " << v2 << "\n"
      "r1       -> " << r1 << "\n"
      "r2       -> " << r2 << "\n"
      "(int)v1  -> " << ((int)v1) << "\n"
      "20 + v1  -> " << (10+v1) << "\n"
      "v1 + 20  -> " << (v1+10) << "\n"
      "20 + r1  -> " << (10+r1) << "\n"
      "r1 + 20  -> " << (r1+10l) << "\n"
      "v1 + v2  -> " << (v1+v2) << "\n"
      "v1 + r1  -> " << (v1 + r1) << "\n"
      "r2 + v2  -> " << (r2 + v2) << "\n"
      "r1 + r2  -> " << (r1 + r2) << "\n"
      "((range_t)r1) + r2 -> " << ((range_t)r1 + r2) << "\n"
      "v1 == v2 -> " << to_str(v1 == v2) << "\n"
      "r1 != r2 -> " << to_str(r1 != r2) << "\n"
      "v1 >= v2 -> " << to_str(v1 >= v2) << "\n"
      "r1 > r2  -> " << to_str(r1 > r2) << "\n"
      "-v1      -> " << (-v1) << "\n"
      "-r1      -> " << (-r1) << "\n"
      "~v1      -> " << (~v1) << "\n"
      "~r1      -> " << (~r1) << "\n"
      "v1 = 1  -> " << (v1 = 1) << "\n"
      "r1 = 10 -> " << (r1 = 10) << "\n"
      "v1 = Value<int>() -> " << (v1 = ValueType<int>()) << "\n"
      "IsUndefined(v1) -> " << to_str(v1.IsUndefined()) << "\n"
      "r1 = Range<0,12>() -> " << (r1 = RangeType<0,12>()) << "\n"
      "IsUndefined(r1) -> " << to_str(r1.IsUndefined()) << "\n"
      "Clear r1;\n"
      "r1       -> " << ({r1.Clear(); r1;}) << "\n"
      "Clear r2;\n"
      "r2       -> " << ({r2.Clear(); r2;}) // << "\n"
    << std::endl;
    try { std::cout << "r1 = 13  -> " << std::flush << (r1 = 13) << std::endl; } 
    catch (std::out_of_range& ex) { std::cout << "std::out_of_range(\"" << ex.what() << "\")\n" << std::flush; }
    std::cout <<
      "v1 = r2  -> " << (v1 = r2) << "\n"
      "v1       -> " << (v1 = r2) << "\n"
      "v2 = r2  -> " << (v2 = r2) << "\n"
      "v2       -> " << (v2 = r2) << "\n"
      "Undefine v1;\n"
      "IsUndefined(v1) -> " << ({v1.Undefine(); to_str(v1.IsUndefined());})
    << std::endl;
    try { std::cout << "v1 + v2 -> " << std::flush << (v1 + v2) << std::endl; } 
    catch (std::logic_error& ex) { std::cout << "std::logic_error(\"" << ex.what() << "\")\n" << std::flush; }
    try { std::cout << "v2 + v1 -> " << std::flush << (v2 + v1) << std::endl; } 
    catch (std::logic_error& ex) { std::cout << "std::logic_error(\"" << ex.what() << "\")\n" << std::flush; }
    typedef TypeIdType<0,RangeType<1,2>> SmallRange;
    SmallRange t1(1);
    std::cout << "\n\n" 
      "TypeIdType<\"SmallRange\",RangeType<1,2>> t1(1);\n"
      "t1     -> " << t1 << "\n"
      "v1.__json_type() -> \"" << v1.__json_type() << "\"\n"
      "r1.__json_type() -> \"" << r1.__json_type() << "\"\n"
      "t1.__json_type() -> \"" << t1.__json_type() << "\"\n"
      << "\n\n" 
      << std::flush;
  } catch (std::exception& ex) {
    std::cerr << "\nexception caught:\n  " << ex.what() << std::endl;
  }
   
    return 0;
}