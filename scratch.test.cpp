#include <iostream>
#include <exception>
#include <string>
#include <utility>
#include <cstring>


typedef long range_t;

#ifndef __INCLUDE_SIMPLE__
typedef struct{int a; char* b;} comp_t;

namespace __info__ {
  const std::string TYPE_IDS[] = {"SmallRange"};
} // namespace __info__
#endif

template<typename T>
  class BaseType {
    T value;
    bool is_defined;
  protected:
    inline T get() const {
      if (not is_defined) 
        throw std::logic_error("value was undefined");
      return value;
    }
    inline BaseType& set(const T& value_) {
      value = value_;
      is_defined = true;
      return *this;
    }
    inline T unsafe_get() { return value; }
  public:
    BaseType() { Undefine(); }
    BaseType(T value_) : is_defined(true), value(value_) {}
    inline void Undefine() { is_defined = false; std::memset(&value, 0u, sizeof(T)); }
    inline bool IsUndefined() const { return not is_defined; }

    explicit inline operator T () { return value; }

    friend inline std::ostream& operator << (std::ostream& out, BaseType& val) {
      if (val.is_defined)
        return (out << val.value);
      return (out << "<UNDEFINED>");
    }
    static inline const std::string __json_type() { return "null"; }
  };


  // << ===================================== Simple Types ======================================= >> 

  class BooleanType : public BaseType<bool> {
  public:
    void Clear() { set(false); }
    inline operator bool () { return get(); }
    inline BooleanType operator = (const bool val) { return ((BooleanType&)set(val)); }
    static constexpr bool __LB() { return false; } 
    static constexpr bool __UB() { return true; } 
    static constexpr bool __STEP() { return static_cast<bool>(1); }
    static constexpr size_t __COUNT() { return 2u; }

    static inline const std::string __json_type() { return "{\"$type\":\"boolean-type\"}"; }

    friend inline std::ostream& operator << (std::ostream& out, const BooleanType& val) {
      if (val.IsUndefined())
        return (out << "<UNDEFINED>");
      return (out << ((val.get()) ? "true" : "false"));
    }
  };

  template<range_t LB, range_t UB>
  class RangeType : public BaseType<range_t> {
  public:
    RangeType() : BaseType<range_t>() {}
    RangeType(range_t value_) : BaseType<range_t>(value_) {
      if (value_ < LB || value_ > UB)
        throw std::out_of_range("value " +
                                std::to_string(value_) +
                                " being assigned is out of range (`"+ 
                                std::to_string(LB) +
                                ".."+
                                std::to_string(UB) +
                                "`)");
    }
    void Clear() { set(LB); }
    inline operator range_t () { return get(); }
    inline RangeType& operator = (range_t other) { 
      if (other < LB || other > UB)
        throw std::out_of_range("value " +
                                std::to_string(other) +
                                " being assigned is out of range (i.e. `"+ 
                                std::to_string(LB) +
                                ".."+
                                std::to_string(UB) +
                                "`)");
      return ((RangeType&)set(other));
    }
    size_t __get_index_val() const { return static_cast<size_t>(get() - LB); }
    static constexpr range_t __LB() { return LB; } 
    static constexpr range_t __UB() { return UB; } 
    static constexpr range_t __STEP() { return static_cast<range_t>(1); }
    static constexpr size_t __COUNT() { return static_cast<size_t>((UB-LB+1)/__STEP()); }

    // friend inline range_t operator - (const RangeType& l) { return -l.get(); }
    // friend inline range_t operator ~ (const RangeType& l) { return ~l.get(); }

    // friend inline range_t operator + (const RangeType& l, const range_t& r) { return l.get() + r; }
    // friend inline range_t operator - (const RangeType& l, const range_t& r) { return l.get() - r; }
    // friend inline range_t operator * (const RangeType& l, const range_t& r) { return l.get() * r; }
    // friend inline range_t operator / (const RangeType& l, const range_t& r) { return l.get() / r; }
    // friend inline range_t operator % (const RangeType& l, const range_t& r) { return l.get() % r; }
    // friend inline range_t operator & (const RangeType& l, const range_t& r) { return l.get() & r; }
    // friend inline range_t operator | (const RangeType& l, const range_t& r) { return l.get() | r; }
    // friend inline range_t operator ^ (const RangeType& l, const range_t& r) { return l.get() ^ r; }

    // friend inline bool operator < (const RangeType& l, const range_t& r) { return l.get() < r; }
    // friend inline bool operator <= (const RangeType& l, const range_t& r) { return l.get() <= r; }
    // friend inline bool operator == (const RangeType& l, const range_t& r) { return l.get() == r; }
    // friend inline bool operator != (const RangeType& l, const range_t& r) { return l.get() != r; }
    // friend inline bool operator >= (const RangeType& l, const range_t& r) { return l.get() >= r; }
    // friend inline bool operator > (const RangeType& l, const range_t& r) { return l.get() > r; }


    // friend inline range_t operator + (const range_t& l, const RangeType& r) { return l + r.get(); }
    // friend inline range_t operator - (const range_t& l, const RangeType& r) { return l - r.get(); }
    // friend inline range_t operator * (const range_t& l, const RangeType& r) { return l * r.get(); }
    // friend inline range_t operator / (const range_t& l, const RangeType& r) { return l / r.get(); }
    // friend inline range_t operator % (const range_t& l, const RangeType& r) { return l % r.get(); }
    // friend inline range_t operator & (const range_t& l, const RangeType& r) { return l & r.get(); }
    // friend inline range_t operator | (const range_t& l, const RangeType& r) { return l | r.get(); }
    // friend inline range_t operator ^ (const range_t& l, const RangeType& r) { return l ^ r.get(); }

    // friend inline bool operator < (const range_t& l, const RangeType& r) { return l < r.get(); }
    // friend inline bool operator <= (const range_t& l, const RangeType& r) { return l <= r.get(); }
    // friend inline bool operator == (const range_t& l, const RangeType& r) { return l == r.get(); }
    // friend inline bool operator != (const range_t& l, const RangeType& r) { return l != r.get(); }
    // friend inline bool operator >= (const range_t& l, const RangeType& r) { return l >= r.get(); }
    // friend inline bool operator > (const range_t& l, const RangeType& r) { return l > r.get(); }


    template<range_t RLB, range_t RUB>
    friend inline range_t operator + (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() + r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline range_t operator - (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() - r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline range_t operator * (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() * r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline range_t operator / (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() / r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline range_t operator % (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() % r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline range_t operator & (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() & r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline range_t operator | (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() | r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline range_t operator ^ (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() ^ r.get(); }

    template<range_t RLB, range_t RUB>
    friend inline bool operator < (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() < r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline bool operator <= (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() <= r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline bool operator == (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() == r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline bool operator != (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() != r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline bool operator >= (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() >= r.get(); }
    template<range_t RLB, range_t RUB>
    friend inline bool operator > (const RangeType& l, const RangeType<RLB,RUB>& r) { return l.get() > r.get(); }




    static const std::string __json_type() { 
      return "{\"$type\":\"range-type\","
                "\"bounds\":["+std::to_string(LB)+","+std::to_string(UB)+"]}";
    }

    friend inline std::ostream& operator << (std::ostream& out, const RangeType& val) {
      if (val.IsUndefined())
        return (out << "<UNDEFINED>");
      return (out << val.get());
    }
  };


#ifndef __INCLUDE_SIMPLE__ 
constexpr const char* to_str(const bool val) { return ((val) ? "true" : "false"); }


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


int main() {
  BaseType<int> v1(5);
  BaseType<range_t> v2 = (5l);
  RangeType<0,12> r1 = (5l);
  RangeType<-12,12> r2(-2l);
  try {
    std::cout <<
      "sizeof(int)                -> "
        << sizeof(int) << " B\n"
      "sizeof(BaseType<int>)     -> "
        << sizeof(BaseType<int>) << " B\n"
      "sizeof(range_t)            -> "
        << sizeof(range_t) << " B\n"
      "sizeof(BaseType<range_t>) -> "
        << sizeof(BaseType<range_t>) << " B\n"
      "sizeof(RangeType<0,12>)    -> " 
        << sizeof(RangeType<0,12>) << " B\n"
      // "sizeof(comp_t)             -> "
      //   << sizeof(comp_t) << "B\n"
    << std::endl << 
      "BaseType<int>     v1(5);\n"
      "BaseType<range_t> v2 = (5l);\n"
      "RangeType<0,12>    r1 = (5l);\n"
      "RangeType<-12,12>  r2(-2l);\n"
    << std::endl <<
      "v1       -> " << v1 << "\n"
      "v2       -> " << v2 << "\n"
      "r1       -> " << r1 << "\n"
      "r2       -> " << r2 << "\n"
      "(int)v1  -> " << ((int)v1) << "\n"
      // "20 + v1  -> " << (10+v1) << "\n"
      // "v1 + 20  -> " << (v1+10) << "\n"
      "20 + r1  -> " << (10+r1) << "\n"
      "r1 + 20  -> " << (r1+10l) << "\n"
      // "v1 + v2  -> " << (v1+v2) << "\n"
      // "v1 + r1  -> " << (v1 + r1) << "\n"
      // "r2 + v2  -> " << (r2 + v2) << "\n"
      "r1 + r2  -> " << (r1 + r2) << "\n"
      "((range_t)r1) + r2 -> " << (((range_t)r1) + r2) << "\n"
      // "v1 == v2 -> " << to_str(v1 == v2) << "\n"
      "r1 != r2 -> " << to_str(r1 != r2) << "\n"
      // "v1 >= v2 -> " << to_str(v1 >= v2) << "\n"
      "r1 > r2  -> " << to_str(r1 > r2) << "\n"
      // "-v1      -> " << (-v1) << "\n"
      "-r1      -> " << (-r1) << "\n"
      // "~v1      -> " << (~v1) << "\n"
      "~r1      -> " << (~r1) << "\n"
      "v1 = 1  -> " << (v1 = 1) << "\n"
      "r1 = 10 -> " << (r1 = 10) << "\n"
      "v1 = Value<int>() -> " << (v1 = BaseType<int>()) << "\n"
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
    // std::cout <<
    //   "v1 = r2  -> " << (v1 = r2) << "\n"
    //   "v1       -> " << (v1 = r2) << "\n"
    //   "v2 = r2  -> " << (v2 = r2) << "\n"
    //   "v2       -> " << (v2 = r2) << "\n"
    //   "Undefine v1;\n"
    //   "IsUndefined(v1) -> " << ({v1.Undefine(); to_str(v1.IsUndefined());})
    // << std::endl;
    // try { std::cout << "v1 + v2 -> " << std::flush << (v1 + v2) << std::endl; } 
    // catch (std::logic_error& ex) { std::cout << "std::logic_error(\"" << ex.what() << "\")\n" << std::flush; }
    // try { std::cout << "v2 + v1 -> " << std::flush << (v2 + v1) << std::endl; } 
    // catch (std::logic_error& ex) { std::cout << "std::logic_error(\"" << ex.what() << "\")\n" << std::flush; }
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
#endif
