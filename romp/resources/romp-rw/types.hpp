/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw/types.hpp
 * 
 * @brief The Template Type decls used to represent Murphi Types.
 * 
 * @date 2022/10/05
 * @version 0.2
 */

#ifndef __romp__GENERATED_CODE  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#pragma once                // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "pregen-fix.hpp"  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "include.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
#include "decl.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
#include "writers.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
namespace __model__ { // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
  enum SCALAR {_UNDEFINED_=0}; // useful pre-decl // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
} // namespace __model__  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
namespace __info__ { // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
  const std::string SCALAR_IDS[1] {"<UNDEFINED>"}; // useful pre-decl // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
} // namespace __model__  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
namespace romp { // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
  typedef ::__model__::SCALAR SCALAR_ENUM_t;  // typemask for the enum type holding all scalar and enum values // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
} // namespace __model__  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
#endif

namespace romp {

  // << ================================== Scalar Enum Helpers =================================== >> 
  template<typename T>
  inline SCALAR_ENUM_t make_SCALAR_ENUM_t(T val) { return static_cast<SCALAR_ENUM_t>(val); }
  inline std::string to_str(const SCALAR_ENUM_t& scalar) { return ::__info__::SCALAR_IDS[static_cast<size_t>(scalar)]; }
  inline std::ostream& operator << (std::ostream& out, const SCALAR_ENUM_t& val) { return (out << to_str(val)); }
  // inline ostream_p& operator << (ostream_p& out, const SCALAR_ENUM_t& val) { return (out << to_str(val)); }
  template<class O>
  inline ojstream<O>& operator << (ojstream<O>& json, const SCALAR_ENUM_t& val) {
      if (val == SCALAR_ENUM_t::_UNDEFINED_) return (json << "null");
#   ifdef __ROMP__SIMPLE_TRACE
      return (json << static_cast<size_t>(val));
#   else
      return (json << '"' <<to_str(val)<< '"');
#   endif
  }


  // << ====================================== Base Types ======================================== >> 

  // template<typename T>
  // inline void Assignment(T& container, const T& value, const location& loc) {
  //   try {
  //     container = value;
  //   } catch (...) {
  //     throw ModelTypeError("error durring assignment", loc);
  //   }
  // }
  template<typename T>
  inline void Assignment(T& container, const T value, const location& loc) {
    try {
      container = value;
    } catch (...) {
      throw ModelTypeError("error durring assignment", loc);
    }
  }

  /**
   * @brief A 0 width type to ensure all types have access to the metadata generated for them
   * @tparam TID the location in \c ::__info__::TYPE_INFOS that this type's metadata is stored.
   */
  // template<size_t TID>
  // class BaseType {
  // public:
  //   static inline constexpr const TypeInfo& __INFO() { return ::__info__::TYPE_INFOS[0]; }
  //   static inline const std::string __json_type() { return std::to_string(TID); }
  // protected:
  //   template<typename T, typename ET>
  //   static inline void throw_(std::string msg);
  // };

  template<typename T>
  class BaseUndefinableType {
    T value;
    bool is_defined;
  public: // NOTE: I was lazy and just made this section public instead of protected
    inline T get() const {
      if (not is_defined) 
        throw std::logic_error("value was undefined");
      return value;
    }
    inline BaseUndefinableType& set(const T& value_) {
      value = value_;
      is_defined = true;
      return *this;
    }
    inline T unsafe_get() const { return value; }
  public:
    BaseUndefinableType() { Undefine(); }
    // BaseUndefinableType(T value_) : is_defined(true), value(value_) {}
    BaseUndefinableType(const T& value_) : is_defined(true), value(value_) {}
    inline void Undefine() { is_defined = false; std::memset(&value, 0u, sizeof(T)); }
    inline bool IsUndefined() const { return not is_defined; }

    static constexpr bool __IS_SIMPLE() { return true; }
    static constexpr bool __IS_RECORD() { return false; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() { return false; }

    explicit inline operator T () { return value; }

    // friend ostream_p& operator << (ostream_p& out, const BaseUndefinableType& val) { 
    friend std::ostream& operator << (std::ostream& out, const BaseUndefinableType& val) { 
      if (val.IsUndefined())
        return (out << SCALAR_ENUM_t::_UNDEFINED_);
      return (out << val.get()); 
    }
    static inline const std::string __json_type() { return "null"; }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& json, const BaseUndefinableType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        if (val.IsUndefined()) return (json << "null"); 
        return (json << val.get());
#     else
        json << "{\"$type\":\"undefinable-value\",\"type-id\":null,\"value\":";
        if (val.IsUndefined())
          return (json << "null}");
        return (json << val.get() << '}');
#     endif 
    }
    friend class std::hash<BaseUndefinableType>;
  };


  // << ===================================== Type ID Mask ======================================= >> 

  template<size_t TID, class T>
  class TypeIdType : public T {
  public:
    template<typename... Args>
    TypeIdType(Args &&... args) : T(std::forward<Args>(args)...) {}
    // template<typename... Args>
    // TypeIdType(const Args &&... args) : T(std::forward<Args>(args)...) {}
    operator T& () { return *((T*)this); }
    // operator T& () const { return T(*this); }
    // static inline constexpr const TypeInfo& __INFO() { return ::__info__::TYPE_INFOS[0]; }
    static inline constexpr bool __IS_TYPEID() { return true; }
    static inline const std::string& __id() { return ::__info__::TYPE_IDS[TID]; }
    static inline constexpr const std::string __json_type() {
      // return std::to_string(TID);
      return "{\"$type\":\"type-id\",\"tid\":"+std::to_string(TID)+",\"id\":\"" + __id() + "\",\"referent\":" + T::__json_type() + '}';
    }
    static inline constexpr const std::string __p_type() { return __id(); }
    template<template<size_t,class>class TId_t>
    friend 
    typename std::enable_if<std::is_base_of<TypeIdType<TID,T>,
                                            TId_t<TID,T>>::value,
                            ostream_p>::type& operator << (ostream_p& out, TId_t<TID,T> val) { 
      return (out << *((T*)&val)); 
    }
  };


  // << ===================================== Simple Types ======================================= >>

  class BooleanType : public BaseUndefinableType<bool>/* , public BaseType<0ul> */ {
  public:
    BooleanType() : BaseUndefinableType<bool>() {}
    BooleanType(bool val) : BaseUndefinableType<bool>(val) {}

    void Clear() { set(false); }
    inline operator bool () const { return get(); }
    // inline operator int () const { return static_cast<int>(get()); }
    inline operator range_t () const { return static_cast<range_t>(get()); }
    inline BooleanType operator = (bool val) { return ((BooleanType&)set(val)); }

    // static inline constexpr const TypeInfo& __INFO() { return ::__info__::TYPE_INFOS[0]; }
    // static inline constexpr BooleanType __LB() { return false; } 
    // static inline constexpr BooleanType __UB() { return true; } 
    // BooleanType& __step() { set(true); return *this; }
    static inline constexpr size_t __COUNT() { return 2u; }

    static inline const std::string __p_type() { return "Boolean"; }

    friend inline bool operator == (const BooleanType& l, const BooleanType& r) {
      return !(l.IsUndefined() || r.IsUndefined()) && (l.unsafe_get() == r.unsafe_get());
    }
    friend inline bool operator == (const BooleanType& l, const bool& r) {
      return (not l.IsUndefined()) && (l.unsafe_get() == r);
    }
    friend inline bool operator == (const bool& l, const BooleanType& r) {
      return (not r.IsUndefined()) && (l == r.unsafe_get());
    }

    // friend inline ostream_p& operator << (ostream_p& out, const BooleanType& val) {
    friend inline std::ostream& operator << (std::ostream& out, const BooleanType& val) {
      if (val.IsUndefined())
        return (out << SCALAR_ENUM_t::_UNDEFINED_);
      return (out << ((val.get()) ? "true" : "false"));
    }
    static inline const std::string __json_type() { return "{\"$type\":\"boolean-type\"}"; }
#   ifndef __ROMP__SIMPLE_TRACE
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const BooleanType& val) {
      out << "{\"$type\":\"undefinable-value\",\"type-id\":"<< __json_type() <<","
            "\"value\":";
      if (val.IsUndefined())
        return (out << "null}");
      return (out << val.get() << '}');
    }
#   endif
  };

  template<range_t LB, range_t UB, range_t STEP=(range_t)((LB<=UB) ? 1 : -1)>
  class RangeType : public BaseUndefinableType<range_t> {
    static_assert(not ((LB<=UB) xor (STEP>0)), "step must go in the same direction as bounds");
    static_assert((not (STEP==0) || (LB==UB)), "if STEP is 0, then LB must equal UB");
  protected:
    static void _check(range_t value_) {
      if (LB<=UB) { // compiler should optimize this top level if-else out
        if (LB <= value_ && value_ <= UB) return;
      } else {
        if (UB <= value_ && value_ <= LB) return;
      }
      throw std::out_of_range("value (`" +
                              std::to_string(value_) +
                              "`) is out of range (`"+ 
                              std::to_string(LB) +
                              ".."+
                              std::to_string(UB) +
                              "`)");
    }
  public:
    RangeType() : BaseUndefinableType<range_t>() {}
    RangeType(range_t value_) : BaseUndefinableType<range_t>(value_) { _check(value_); }
    template<range_t O_LB, range_t O_UB, range_t O_STEP>
    RangeType(const RangeType<O_LB,O_UB,O_STEP>& range_) {
      if (range_.IsUndefined()) Undefine();
      else { RangeType::_check(range_.__unsafe_get()); this->set(range_.__unsafe_get()); }
    }
    inline range_t __unsafe_get() const { return unsafe_get(); }
    void Clear() { set(LB); }
    inline operator range_t () { return get(); }
    inline RangeType& operator = (range_t other) { 
      _check(other);
      return ((RangeType&)set(other));
    }
    template<range_t N_LB, range_t N_UB, range_t N_STEP>
    inline RangeType& operator = (const RangeType<N_LB,N_UB,N_STEP>& other) { 
      if (other.IsUndefined()) {
        Undefine();
        return *this;
      }
      return (*this = other);
    }
    size_t __get_index_val() const { return static_cast<size_t>(get() - LB); }
    static constexpr RangeType __LB() { return RangeType(LB); }
    static constexpr RangeType __UB() { RangeType tmp(UB); tmp.set(UB+STEP); return tmp; } 
    static constexpr size_t __COUNT() { return (((UB-LB)+1)/STEP); }
    RangeType& __step() {
      // step needs to account for uneven ranges or modifying values in model between steps
      range_t val = get() + STEP;
      if (LB<=UB) { // compiler should optimize this top level if-else out
        set((val <= UB) ? val : UB+STEP); 
      } else {
        set((val >= UB) ? val : UB+STEP);
      }
      return *this;
    }

    inline range_t __get_value() const { return get(); }

    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator + (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() + r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator - (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() - r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator * (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() * r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator / (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() / r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator % (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() % r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator & (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() & r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator | (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() | r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline range_t operator ^ (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() ^ r.__get_value(); }

    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator < (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return r.get() < r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator <= (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() <= r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator == (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return !(l.IsUndefined() || r.IsUndefined()) && l.get() == r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator != (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return !(l.IsUndefined() || r.IsUndefined()) && l.unsafe_get() != r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator >= (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.unsafe_get() >= r.__get_value(); }
    template<range_t RLB, range_t RUB, range_t RST>
    friend inline bool operator > (const RangeType& l, const RangeType<RLB,RUB,RST>& r) { return l.get() > r.__get_value(); }
    
    friend inline range_t operator + (const RangeType& l, const range_t& r) { return l.get() + r; }
    friend inline range_t operator - (const RangeType& l, const range_t& r) { return l.get() - r; }
    friend inline range_t operator * (const RangeType& l, const range_t& r) { return l.get() * r; }
    friend inline range_t operator / (const RangeType& l, const range_t& r) { return l.get() / r; }
    friend inline range_t operator % (const RangeType& l, const range_t& r) { return l.get() % r; }
    friend inline range_t operator & (const RangeType& l, const range_t& r) { return l.get() & r; }
    friend inline range_t operator | (const RangeType& l, const range_t& r) { return l.get() | r; }
    friend inline range_t operator ^ (const RangeType& l, const range_t& r) { return l.get() ^ r; }
    friend inline bool operator < (const RangeType& l, const range_t& r) { return l.get() < r; }
    friend inline bool operator <= (const RangeType& l, const range_t& r) { return l.get() <= r; }
    friend inline bool operator == (const RangeType& l, const range_t& r) { return (not l.IsUndefined()) && l.unsafe_get() == r; }
    friend inline bool operator != (const RangeType& l, const range_t& r) { return (not l.IsUndefined()) && l.unsafe_get() != r; }
    friend inline bool operator >= (const RangeType& l, const range_t& r) { return l.get() >= r; }
    friend inline bool operator > (const RangeType& l, const range_t& r) { return l.get() > r; }
    friend inline range_t operator + (const range_t& l, const RangeType& r) { return l + r.get(); }
    friend inline range_t operator - (const range_t& l, const RangeType& r) { return l - r.get(); }
    friend inline range_t operator * (const range_t& l, const RangeType& r) { return l * r.get(); }
    friend inline range_t operator / (const range_t& l, const RangeType& r) { return l / r.get(); }
    friend inline range_t operator % (const range_t& l, const RangeType& r) { return l % r.get(); }
    friend inline range_t operator & (const range_t& l, const RangeType& r) { return l & r.get(); }
    friend inline range_t operator | (const range_t& l, const RangeType& r) { return l | r.get(); }
    friend inline range_t operator ^ (const range_t& l, const RangeType& r) { return l ^ r.get(); }
    friend inline bool operator < (const range_t& l, const RangeType& r) { return l < r.get(); }
    friend inline bool operator <= (const range_t& l, const RangeType& r) { return l <= r.get(); }
    friend inline bool operator == (const range_t& l, const RangeType& r) { return (not r.IsUndefined()) && l == r.unsafe_get(); }
    friend inline bool operator != (const range_t& l, const RangeType& r) { return (not r.IsUndefined()) && l != r.unsafe_get(); }
    friend inline bool operator >= (const range_t& l, const RangeType& r) { return l >= r.get(); }
    friend inline bool operator > (const range_t& l, const RangeType& r) { return l > r.get(); }


    static constexpr const std::string __p_type() { 
      if (-1 <= STEP && STEP <= 1) // compiler should optimize this out
        return std::to_string(LB) + ".." + std::to_string(UB);
      return std::to_string(LB) + " to " + std::to_string(UB) + " by " + std::to_string(STEP);
    }
    // friend ostream_p& operator << (ostream_p& out, RangeType& val) { 
    //   return (out << get());
    // }
    static constexpr const std::string __json_type() { 
      return "{\"$type\":\"range-type\","
                "\"bounds\":["+std::to_string(LB)+","+std::to_string(UB)+"]}";
    }
#   ifndef __ROMP__SIMPLE_TRACE
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const RangeType& val) {
      out << "{\"$type\":\"undefinable-value\",\"type-id\":"<< __json_type() <<","
            "\"value\":";
      if (val.IsUndefined())
        return (out << "null}");
      return (out << val.get() << '}');
    }
#   endif
  };



  // << =================================== Scalar/Enum Types ==================================== >> 

  // useful pre-decls
  template<size_t ENUM_ID, size_t BOUND> class EnumType;
  template<size_t ENUM_ID, size_t BOUND> class ScalarsetType;
  template<class... UNION_MEMBERS> class ScalarsetUnionType;

  template<size_t ENUM_ID, size_t BOUND>
  class EnumType {
  protected:
    SCALAR_ENUM_t value;
  public:
    EnumType() : value(SCALAR_ENUM_t::_UNDEFINED_) {}
    EnumType(const SCALAR_ENUM_t& value_) : value(value_) {
      if (value_ != SCALAR_ENUM_t::_UNDEFINED_ && not IsMember(value_))
        throw std::logic_error("`"+ to_str(value_) +"` is not a member of this enum type");
    }
    template<class... UM>
    EnumType(const ScalarsetUnionType<UM...>& union_) : EnumType(union_.__get_scalar_value()) {}

    inline bool IsUndefined() const { return value == SCALAR_ENUM_t::_UNDEFINED_; }
    inline void Undefine() { value = SCALAR_ENUM_t::_UNDEFINED_; }
    inline void Clear() { value = make_SCALAR_ENUM_t(ENUM_ID); }
    
    static inline bool IsMember(const SCALAR_ENUM_t& v) {
      //NOTE: IsMember does not recognise Undefined as a Member of this type
      return (((make_SCALAR_ENUM_t(ENUM_ID) <= v) 
                    && (v <= make_SCALAR_ENUM_t(ENUM_ID+BOUND))));
    }
    
    static constexpr size_t __ENUM_ID() { return ENUM_ID; }
    static constexpr size_t __BOUND() { return BOUND; }
    static constexpr EnumType __LB() { return make_SCALAR_ENUM_t(ENUM_ID); }
    static constexpr EnumType __UB() { return make_SCALAR_ENUM_t(ENUM_ID+BOUND); }
    EnumType& __step() { value = make_SCALAR_ENUM_t(static_cast<size_t>(value)+1); return *this; }
    static constexpr size_t __COUNT() { return BOUND; }
    static constexpr bool __IS_SIMPLE() { return true; }
    static constexpr bool __IS_RECORD() { return false; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() { return false; }

    // cast to index operator
    inline size_t __get_index_val() const {
      if (IsUndefined())
        throw std::logic_error("value was undefined");
      return static_cast<size_t>(value)-ENUM_ID; 
    }
    const SCALAR_ENUM_t& __get_scalar_value() const { return value; }

    template<size_t EID, size_t B, class... U_M>
    friend inline void __assign(EnumType<EID,B>& _this, const ScalarsetUnionType<U_M...>& other);

    template<class... U_M>
    inline EnumType& operator = (const ScalarsetUnionType<U_M...>& other) { __assign(*this,other); return *this; }
    inline EnumType& operator = (const SCALAR_ENUM_t& val) {
      if (val != SCALAR_ENUM_t::_UNDEFINED_ && not IsMember(val))
        throw std::logic_error("`"+ to_str(value) +"` is not a member of this enum type");
      value = val;
      return *this;
    }

    template<class... U_M>
    explicit inline operator ScalarsetUnionType<U_M...> () { return __convert(*this); }
    template<class... U_M>
    friend ScalarsetUnionType<U_M...> __convert(const EnumType& _this);

    template<size_t R_EID, size_t R_B>
    friend inline bool operator == (const EnumType& l, const EnumType<R_EID,R_B> r) { 
      return l.value == r.value;
    }
    template<size_t R_EID, size_t R_B>
    friend inline bool operator != (const EnumType& l, const EnumType<R_EID,R_B> r) {
      return l.value != r.value;
    }
    friend inline bool operator == (const EnumType& l, const SCALAR_ENUM_t& r) { 
      return l.value == r;
    }
    friend inline bool operator != (const EnumType& l, const SCALAR_ENUM_t& r) {
      return l.value != r;
    }
    friend inline bool operator == (const SCALAR_ENUM_t& l, const EnumType& r) {
      return l == r.value;
    }
    friend inline bool operator != (const SCALAR_ENUM_t& l, const EnumType& r) {
      return l != r.value;
    }

    /* this IsMember is the one associated with the IsMember() Murphi language operator */
    template<typename T, class... U_M>
    friend inline bool IsMember(const ScalarsetUnionType<U_M...> u);
    
    static constexpr const std::string __p_type() { 
      std::string res = "enum {";
      std::string sep;
      for (auto i=__LB(); i!=__UB(); i.__step()) {
        res += sep + to_str(make_SCALAR_ENUM_t(i.__get_scalar_value()));
        sep = ",";
      }
      return res + "}";
    }
    // friend ostream_p& operator << (ostream_p& out, const EnumType& val) { return (out << val.value); }
    friend std::ostream& operator << (std::ostream& out, const EnumType& val) { return (out << val.value); }
    static inline constexpr const std::string __json_type() { 
      return "{\"$type\":\"enum-type\",\"first-member\":\""+to_str(make_SCALAR_ENUM_t(ENUM_ID))+"\",""\"member-count\":"+std::to_string(BOUND)+'}';
    }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const EnumType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.value);
#     else
        out << "{\"$type\":\"undefinable-value\",\"type-id\":" << EnumType::__json_type() << ",\"value\":";
        // if (val.IsUndefined())
        //   return (out << "null}");
        return (out << val.value << '}');
#     endif 
    }
  };

  template<size_t ENUM_ID, size_t BOUND>
  class ScalarsetType : public EnumType<ENUM_ID,BOUND> {
  public:
    ScalarsetType() : EnumType<ENUM_ID,BOUND>() {}
    ScalarsetType(const SCALAR_ENUM_t& value_) {
      if (value_ != SCALAR_ENUM_t::_UNDEFINED_ && not EnumType<ENUM_ID,BOUND>::IsMember(value_))
        throw std::logic_error("`"+ to_str(value_) +"` is not a member of this scalarset type");
      this->value = value_;
    }
    template<class... UM>
    ScalarsetType(const ScalarsetUnionType<UM...>& union_) : ScalarsetType(union_.__get_scalar_value()) {}
    // static inline const std::string __id() { return ::__info__::TYPE_INFOS[TID].label; }

    
    static constexpr ScalarsetType __LB() { return make_SCALAR_ENUM_t(ENUM_ID); }
    static constexpr ScalarsetType __UB() { return make_SCALAR_ENUM_t(ENUM_ID+BOUND); }
    ScalarsetType& __step() { EnumType<ENUM_ID,BOUND>::__step(); return *this; }

    template<class... U_M>
    explicit inline operator ScalarsetUnionType<U_M...> () { return __convert(*this); }
    template<class... U_M>
    friend ScalarsetUnionType<U_M...> __convert(const ScalarsetType& _this);

    template<class... U_M>
    friend inline void __assign(ScalarsetType& _this, const ScalarsetUnionType<U_M...>& other);
    template<class... U_M>
    inline ScalarsetType& operator = (const ScalarsetUnionType<U_M...>& other) { __assign(*this,other); return *this; }
    inline ScalarsetType& operator = (const SCALAR_ENUM_t& val) {
      if (val != SCALAR_ENUM_t::_UNDEFINED_ && not EnumType<ENUM_ID,BOUND>::IsMember(val))
        throw std::logic_error("`"+ to_str(val) +"` is not a member of this scalarset type");
      this->value = val;
      return *this;
    }

    static constexpr const std::string __p_type() { return "scalarset("+std::to_string(BOUND)+')'; }
    // friend ostream_p& operator << (ostream_p& out, const ScalarsetType& val) { return (out << val.value); }
    friend std::ostream& operator << (std::ostream& out, const ScalarsetType& val) { return (out << val.value); }
    static constexpr const std::string __json_type() { return "{\"$type\":\"scalarset-type\",\"bound\":"+std::to_string(BOUND)+'}'; }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const ScalarsetType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.value);
#     else
        out << "{\"$type\":\"undefinable-value\",\"type-id\":" << ScalarsetType::__json_type() << ",\"value\":";
        // if (val.IsUndefined())
        //   return (out << "null}");
        return (out << val.value << '}');
#     endif 
    }
  };


  template<class... UNION_MEMBERS>
  class ScalarsetUnionType {
    SCALAR_ENUM_t value;
  protected:
    // static const size_t MEMBER_COUNT;
    static const size_t ENUM_IDS[sizeof...(UNION_MEMBERS)+1];
    static const size_t BOUNDS[sizeof...(UNION_MEMBERS)+1];
    
    template<size_t E_ID, size_t B>
    static constexpr bool ContainsMember() {
#     if __cplusplus >= 201703L
        return (((UNION_MEMBERS::__ENUM_ID() == E_ID) || ...) && ((UNION_MEMBERS::__BOUND() == B) || ...)); // [[requires C++17]]
#     else
        bool res = false;
        for (size_t i=1; i<(sizeof...(UNION_MEMBERS)+1); ++i)
          res |= ((ENUM_IDS[i] == E_ID) && (BOUNDS[i] == B));
        return res;
#     endif
    }
    static inline bool MembersContain(const SCALAR_ENUM_t& v) {
      if (v == SCALAR_ENUM_t::_UNDEFINED_) return true;
#     if __cplusplus >= 201703L
        return (UNION_MEMBERS::IsMember(v) || ...); // [[requires C++17]]
#     else
        bool res = false;
        for (size_t i=1; i<(sizeof...(UNION_MEMBERS)+1); ++i)
          res |= ((ENUM_IDS[i] <= v) && (v <= ENUM_IDS[i]+BOUNDS[i]-1));
        return res;
#     endif
    }

    public:
    ScalarsetUnionType() : value(SCALAR_ENUM_t::_UNDEFINED_) {}
    ScalarsetUnionType(const SCALAR_ENUM_t& value_) : value(value_) {
      if (not MembersContain(value_)) // this is NOT evaluate-able at compile time
        throw std::out_of_range("`"+ to_str(value) +"` is not a member of the union (scalarset union)");
    }
    template<size_t E_ID, size_t B>
    ScalarsetUnionType(const EnumType<E_ID,B>& value_) { 
      if (not ContainsMember<E_ID,B>()) // this is evaluate-able at compile time (if c++17)
        throw std::out_of_range("`"+ to_str(value) +"` is not a member of the union (scalarset union)");
      value = value_.__get_scalar_value();
    }
    template<class... UM>
    ScalarsetUnionType(const ScalarsetUnionType<UM...>& u_) : ScalarsetUnionType(u_.value) {}

    static inline bool IsMember(const SCALAR_ENUM_t& val) { return (val != SCALAR_ENUM_t::_UNDEFINED_ && MembersContain(val)); }
    inline bool IsUndefined() const { return (value == SCALAR_ENUM_t::_UNDEFINED_); }
    inline void Undefine() { value = SCALAR_ENUM_t::_UNDEFINED_; }
    inline void Clear() { value = (((sizeof...(UNION_MEMBERS))<=0) ? SCALAR_ENUM_t::_UNDEFINED_ : make_SCALAR_ENUM_t(ENUM_IDS[1]) ); }
    
    // get index value
    inline const size_t __get_index_val() const {
      if (IsUndefined())
        throw std::logic_error("value was undefined");
      size_t offset = 0ul;
      size_t i;
      for (i=0ul; i<(sizeof...(UNION_MEMBERS)+1); ++i) {
        if (ENUM_IDS[i] <= value && value <= (ENUM_IDS[i]+BOUNDS[i]-1)) 
          return offset + static_cast<size_t>(value) - ENUM_IDS[i] -1; // modified for dbg
        offset += BOUNDS[i];
      }
      throw std::runtime_error("DEV ERROR : could not convert union to index value");
    }
    const SCALAR_ENUM_t& __get_scalar_value() const { return value; }

    template<size_t EID, size_t B>
    explicit inline operator EnumType<EID,B> () {
      static_assert(ScalarsetUnionType::ContainsMember<EID,B>(), 
                    "union must contain enum member type to cast to it!");
      return EnumType<EID,B>(value);
    }
    template<size_t EID, size_t B>
    friend inline ScalarsetUnionType __convert(const EnumType<EID,B>& _this) {
      static_assert((ScalarsetUnionType::ContainsMember<EID,B>()),
                  "enum type must be a member of the union type to be cast to it");
      return ScalarsetUnionType(_this.value);
    }
    template<size_t EID, size_t B>
    explicit inline operator ScalarsetType<EID,B> () {
      static_assert(ScalarsetUnionType::ContainsMember<EID,B>(), 
                    "union must contain scalarset member type to cast to it!");
      return ScalarsetType<EID,B>(value);
    }
    template<size_t EID, size_t B>
    friend inline ScalarsetUnionType __convert(const ScalarsetType<EID,B>& _this) {
      static_assert((ScalarsetUnionType::ContainsMember<EID,B>()),
                  "scalarset type must be a member of the union type to be cast to it");
      return ScalarsetUnionType(_this.value);
    }

    template<size_t E_ID, size_t B>
    inline ScalarsetUnionType& operator = (const EnumType<E_ID,B>& other) { return (*this = other.__get_scalar_value()); }
    inline ScalarsetUnionType& operator = (const SCALAR_ENUM_t& val) {
      if (not MembersContain(val)) // this is evaluate-able at compile time
        throw std::out_of_range("`"+ to_str(value) +"` is not a member of the union (scalarset union)");
      value = val;
    }
    
    template<class... R_M>
    friend inline bool operator == (const ScalarsetUnionType& l, const ScalarsetUnionType<R_M...> r) {
      return l.value == r.value;
    }
    template<class... R_M>
    friend inline bool operator != (const ScalarsetUnionType& l, const ScalarsetUnionType<R_M...> r) {
      return l.value != r.value;
    }

    bool operator == (const SCALAR_ENUM_t& other) const { return value == other; }
    bool operator != (const SCALAR_ENUM_t& other) const { return value != other; }
    template<size_t EID, size_t B>
    bool operator == (const EnumType<EID,B>& other) const { return value == other.__get_scalar_value(); }
    template<size_t EID, size_t B>
    bool operator != (const EnumType<EID,B>& other) const { return value != other.__get_scalar_value(); }

    template<size_t EID, size_t B>
    friend inline bool operator == (const EnumType<EID,B>& e, const ScalarsetUnionType& u) { return u == e; }
    template<size_t EID, size_t B>
    friend inline bool operator != (const EnumType<EID,B>& e, const ScalarsetUnionType& u) { return u == e; }

    /* this IsMember is the one associated with the IsMember() Murphi language operator */
    // template<class ET, class... U_M>
    // friend inline bool IsMember(const ScalarsetUnionType<U_M...>& u);
    // template<size_t EID, size_t B, class... U_M>
    // friend inline bool IsMember(const ScalarsetUnionType<U_M...>& u);

    class iterator {
      ScalarsetUnionType u;
      size_t i;
      size_t j;
    public:
      iterator(size_t i_, size_t j_) 
        : i(i_), j(j_)
        {
          if (i>sizeof...(UNION_MEMBERS)) {
            j = 0; u.value = SCALAR_ENUM_t::_UNDEFINED_;
          } else u.value = make_SCALAR_ENUM_t(ScalarsetUnionType::ENUM_IDS[i_]+j_);
        }
      ScalarsetUnionType& operator*() const { return u; }
      ScalarsetUnionType* operator->() { return &u; }
      iterator& operator += (int) { return (__step()); }
      iterator& __step() {
        // if (i>=sizeof...(UNION_MEMBERS)+1) {
        //   j = 0; u.value = SCALAR_ENUM_t::_UNDEFINED_;
        //   return *this;
        // } 
        if (++j < ScalarsetUnionType::BOUNDS[i]) {
          u.value = make_SCALAR_ENUM_t(static_cast<size_t>(u.value)+1);
          return *this;
        }
        ++i; j=0;
        if (i>=sizeof...(UNION_MEMBERS)+1) {
          u.value = SCALAR_ENUM_t::_UNDEFINED_;
          return *this;
        }
        u.value = make_SCALAR_ENUM_t(ScalarsetUnionType::ENUM_IDS[i]+j);
        return *this;
      }
      friend bool operator <= (const iterator& l, const iterator& r) {
        return (l.i<=r.i && l.j <= r.j);
      }
      operator ScalarsetUnionType () { return ScalarsetUnionType(u); }
      operator SCALAR_ENUM_t () { return u.value; }
      iterator& operator = (const ScalarsetUnionType& other) {
        throw std::logic_error("you cannot assign to a quantifier or for-loop iterator");
      }
      inline SCALAR_ENUM_t __get_scalar_value() const { return u.value; }
      friend inline bool operator == (const iterator& l, const iterator& r) { return (l.i==r.i && l.j==r.j); }
      friend inline bool operator != (const iterator& l, const iterator& r) { return (l.i!=r.i || l.j!=r.j); }
      friend inline bool operator == (const ScalarsetUnionType& l, const iterator& r) { return l == r.u; }
      friend inline bool operator != (const ScalarsetUnionType& l, const iterator& r) { return l != r.u; }
      friend inline bool operator == (const iterator& l, const ScalarsetUnionType& r) { return l.u == r; }
      friend inline bool operator != (const iterator& l, const ScalarsetUnionType& r) { return l.u != r; }
      template<size_t EID, size_t B>
      friend inline bool operator == (const EnumType<EID,B>& e, const ScalarsetUnionType::iterator& ui) { return ui.u == e; }
      template<size_t EID, size_t B>
      friend inline bool operator != (const EnumType<EID,B>& e, const ScalarsetUnionType::iterator& ui) { return ui.u == e; }
      template<size_t EID, size_t B>
      friend inline bool operator == (const ScalarsetUnionType::iterator& ui, const EnumType<EID,B>& e) { return ui.u == e; }
      template<size_t EID, size_t B>
      friend inline bool operator != (const ScalarsetUnionType::iterator& ui, const EnumType<EID,B>& e) { return ui.u == e; }
      friend std::ostream& operator << (std::ostream& out, const iterator& val) { return (out << val.u); }
    };

    ScalarsetUnionType(const iterator& it_) 
      : ScalarsetUnionType(it_.__get_scalar_value()) {}
    template<class... UM>
    ScalarsetUnionType(const typename ScalarsetUnionType<UM...>::iterator& it_) 
      : ScalarsetUnionType(it_.__get_scalar_value()) {}

    static constexpr iterator __LB() { return iterator(1, 0); }
    static constexpr iterator __UB() { return iterator(sizeof...(UNION_MEMBERS)+1, 0); }
    // static constexpr int __STEP() { return 1; }

    static constexpr size_t __COUNT() {
#     if __cplusplus >= 201703L
        return ((UNION_MEMBERS::__COUNT()) + ...); // [[requires C++17]]
#     else
        size_t counts[sizeof...(UNION_MEMBERS)] = {(UNION_MEMBERS::__COUNT())...};
        size_t res=0; 
        for (size_t i=0; i<sizeof...(UNION_MEMBERS); ++i) 
          res += counts[i];
        return res;
#     endif
    }
    static constexpr bool __IS_SIMPLE() { return true; }
    static constexpr bool __IS_RECORD() { return false; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() { return false; }
    
    static constexpr const std::string __p_type() {
#     if __cplusplus >= 201703L
        return "union {" + ((UNION_MEMBERS::__p_type()) + ...) + "}"; // [[requires C++17]]
#     else
        const std::string member_types[sizeof...(UNION_MEMBERS)] = {(UNION_MEMBERS::__p_type())...};
        std::string res = "union {";
        std::string sep;
        for (size_t i=0; i<sizeof...(UNION_MEMBERS); ++i) {
          res += sep + member_types[i];
          sep = ", ";
        }
        return res + "}";
#     endif
    }
    // friend ostream_p& operator << (ostream_p& out, const ScalarsetUnionType& val) { return (out << val.value); }
    friend std::ostream& operator << (std::ostream& out, const ScalarsetUnionType& val) { return (out << val.value); }
    static constexpr const std::string __json_type() { 
      return "{\"$type\":\"scalarset-union-type\","
                "\"member-count\":"+std::to_string(sizeof...(UNION_MEMBERS))+","
                "\"\"bound\":"+ std::to_string(__COUNT()) +'}';
    }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const ScalarsetUnionType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.value);
#     else
        out << "{\"$type\":\"undefinable-value\",\"type-id\":" << ScalarsetUnionType::__json_type() << ",\"value\":";
        // if (val.IsUndefined())
        //   return (out << "null}");
        return (out << val.value << '}');
#     endif 
    }
  };
  
  template<class... UNION_MEMBERS>
  const size_t ScalarsetUnionType<UNION_MEMBERS...>::ENUM_IDS[sizeof...(UNION_MEMBERS)+1] = {0,UNION_MEMBERS::__ENUM_ID()...};

  template<class... UNION_MEMBERS>
  const size_t ScalarsetUnionType<UNION_MEMBERS...>::BOUNDS[sizeof...(UNION_MEMBERS)+1] = {1,UNION_MEMBERS::__BOUND()...};


  /* this IsMember is the one associated with the IsMember() Murphi language operator */
  template<class ET, typename VT>
  inline bool IsMember(const VT& u) {
    return ET::IsMember(u.__get_scalar_value());
  }


  // << ===================================== Complex Types ====================================== >> 
  template<typename INDEX_t, typename ELEMENT_t>
  class ArrayType;

  template<typename INDEX_t, typename ELEMENT_t>
  inline ELEMENT_t& Element(ArrayType<INDEX_t,ELEMENT_t>& array, const INDEX_t& index, const location& loc);
  template<typename INDEX_t, typename ELEMENT_t>
  inline const ELEMENT_t& Element(const ArrayType<INDEX_t,ELEMENT_t>& array, const INDEX_t& index, const location& loc);
  // template<template<typename INDEX_t, typename ELEMENT_t>class ARRAY_t>
  // inline ELEMENT_t& Element(ARRAY_t& array, const INDEX_t& index, const location& loc);

  template<typename INDEX_t, typename ELEMENT_t>
  class ArrayType {
    ELEMENT_t data[INDEX_t::__COUNT()];
  public:
    ArrayType() { Undefine(); }
    ELEMENT_t& operator [] (const INDEX_t& i) { return data[i.__get_index_val()]; }
    const ELEMENT_t& operator [] (const INDEX_t& i) const { return data[i.__get_index_val()]; }
    // typename std::enable_if<(not std::is_convertible<INDEX_t,size_t>::value), ELEMENT_t>::type
    // ELEMENT_t operator [] (const size_t i) {
    //   if ((0 > i) || (i >= INDEX_t::__COUNT()))
    //     throw std::out_of_range("`"+std::to_string(i)+"` is out of bounds of the array");
    //   return data[i]; 
    // }
    // friend inline ELEMENT_t& Element(ArrayType& array, const INDEX_t& index, const location& loc) {
    //   try {
    //     return (array[index]);
    //   } catch (...) {
    //     throw ModelTypeError("error durring array element access", loc);
    //   }
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

    static constexpr bool __IS_SIMPLE() { return false; }
    static constexpr bool __IS_RECORD() { return false; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() { 
      return ((ELEMENT_t::__DO_P_SEP()) || ((INDEX_t::__COUNT()>4)) 
              || (sizeof(ELEMENT_t)>(sizeof(BooleanType)*((ELEMENT_t::__IS_RECORD()) ? 2 : 3))));
    }
 
    template<typename RI, typename RE> 
    friend bool operator == (const ArrayType& l, const ArrayType<RI,RE>& r) {
      if (INDEX_t::__COUNT() != RI::__COUNT()) return false; // evaluate-able at compile time
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        if (l.data[i] != r.data[i])
          return false;
      return true;
    }
    template<typename RI, typename RE> 
    friend bool operator != (const ArrayType& l, const ArrayType<RI,RE>& r) {
      if (INDEX_t::__COUNT() != RI::__COUNT()) return true; // evaluate-able at compile time
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i)
        if (l.data[i] == r.data[i])
          return false;
      return true;
    }

  protected:
    // write split line if there is a lot of info in the data structure
    inline void _pWrite_comp(ostream_p& out) const {
      std::string sep;
      out.indent();
      for (auto i=INDEX_t::__LB(); i!=INDEX_t::__UB(); i.__step()) {
        out << sep << out.nl() << '[' << i << "]: " << (*this)[i]; sep = ",";
      }
      out.dedent();
    }
    // write single line if there is NOT a lot of info in the data structure
    inline void _pWrite_simp(ostream_p& out) const {
      std::string sep;
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i) {
        out << sep << data[i]; sep = ", ";
      }
    }
  public:
    static constexpr const std::string __p_type() { 
      return "Array["+INDEX_t::__p_type()+"] of " + ELEMENT_t::__p_type(); 
    }
    // template<typename It, typename Et>
    // friend inline ostream_p& operator << (ostream_p& out, const ArrayType& val) {
    template<template<typename,typename>class Arr_t>
    friend 
    typename std::enable_if<std::is_base_of<ArrayType<INDEX_t,ELEMENT_t>,
                                            Arr_t<INDEX_t,ELEMENT_t>>::value,
                            ostream_p>::type& operator << (ostream_p& out, const Arr_t<INDEX_t,ELEMENT_t>& val) {
      if (val.IsUndefined()) return (out << SCALAR_ENUM_t::_UNDEFINED_);
      out << '[';
      if (ArrayType::__DO_P_SEP()) {
        val._pWrite_comp(out);
        out.nl();
      } else
        val._pWrite_simp(out);
      return (out << ']');
    }
    static constexpr const std::string __json_type() { 
      return "{\"$type\":\"array-type\",\"size\":"+ std::to_string(INDEX_t::__COUNT())+'}';
    }
    template<class O>
    friend inline ojstream<O>& operator << (ojstream<O>& json, const ArrayType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        // json << '[';
        std::string sep;
        for (size_t i=0; i<INDEX_t::__COUNT(); ++i) {
          json << sep << val.data[i]; sep = ",";
        }
        return (json /*<< ']'*/);
#     else
        json << "{\"$type\":\"complex-value\",\"type\":" << ArrayType::__json_type() << ","
                  "\"value\":";
        if (val.IsUndefined())
          return (json << "null}");
        json << '['; std::string sep;
        for (size_t i=0; i<INDEX_t::__COUNT(); ++i) {
          json << sep << val.data[i]; sep = ",";
        }
        return (json << "]}");
#     endif
    }
    friend std::hash<ArrayType>;
  };

  template<typename INDEX_t, typename ELEMENT_t>
  inline ELEMENT_t& Element(ArrayType<INDEX_t,ELEMENT_t>& array, const INDEX_t& index, const location& loc) {
    try {
      return (array[index]);
    } catch (...) {
      throw ModelTypeError("error durring array element access", loc);
    }
  }
  template<typename INDEX_t, typename ELEMENT_t>
  inline const ELEMENT_t& Element(const ArrayType<INDEX_t,ELEMENT_t>& array, const INDEX_t& index, const location& loc) {
    try {
      return (array[index]);
    } catch (...) {
      throw ModelTypeError("error durring array element access", loc);
    }
  }
 


  template<size_t MAX, typename ELEMENT_t> class MultisetType;

  template<size_t MAX, typename ELEMENT_t>
  inline const ELEMENT_t& MultisetElement(const MultisetType<MAX,ELEMENT_t>& ms, const size_t i, const location& loc);



  template<size_t MAX, typename ELEMENT_t>
  class MultisetType {
    static_assert(MAX != ~((size_t)0u), "multiset is not the same size as the empty option");
    static_assert(MAX != 0, "multiset is not of zero size");
    ELEMENT_t data[MAX];
    size_t occupancy = 0;
    bool is_defined = false;
  public:
    MultisetType() { Undefine(); }

    bool IsUndefined() const { return ((not is_defined) && (occupancy == 0)); }
    void Undefine() { std::memset(&data, 0u, sizeof(data)); occupancy = 0; is_defined = false; } // for now design still allows for setting all to 0 to undefine 
    // Do nothing, should never be called, just here for record & array templates
    void Clear() { Undefine(); is_defined = true; }

    static constexpr bool __IS_SIMPLE() { return false; }
    static constexpr bool __IS_RECORD() { return false; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() { 
      return ((ELEMENT_t::__DO_P_SEP()) || (MAX>3) 
             || (sizeof(ELEMENT_t)>(sizeof(BooleanType)*((ELEMENT_t::__IS_RECORD()) ? 2 : 3))));
    }

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
  protected:
    void MultisetRemove(const size_t i) {
      if (i != occupancy-1) {
        data[i] = data[occupancy-1];
      }
      data[--occupancy].Undefine();
    }
  public:
    void MultisetRemovePred(const std::function<bool(const size_t)>& pred) {
      for (long i=occupancy; i>0; --i)
        if (pred(i-1)) MultisetRemove(i-1);
    }

    // size_t Choose(IRandWalker* __rw__) const {
    //   if (not is_defined || occupancy == 0)
    //     return ~((size_t)0u); // no choice possible value
    //   return __rw__->choose_handler(occupancy);
    // }

    // friend inline const ELEMENT_t& MultisetElement(const MultisetType& ms, const size_t i, const location& loc);
    const ELEMENT_t& operator [] (size_t index) const { return data[index]; }

    template<size_t RM, typename RE>  
    friend bool operator == (const MultisetType& l, const MultisetType<RM,RE>& r) {
      if (l.occupancy != r.occupancy) return false; // makes multiplicity matter
      bool res = true;
      size_t found = 0;
      bool matched[MAX];
      for (size_t j=0; j<l.occupancy; ++j) matched[j] = false;
      for (size_t i=0; i<r.occupancy; ++i) {
        for (size_t j=0; j<l.occupancy; ++j) {
          if (r.data[i] == l.data[j] && not matched[j]) {
            matched[j] = true; ++found;
          }
        }
        if (found!=i) return false;
      }
      for (size_t j=0; j<l.occupancy; ++j) res &= matched[j];
      return res;
      /* // rewriting to make multiplicity matter and order not matter
      // if (MAX != RM) return false; // evaluate-able at compile time
      if (l.occupancy != r.occupancy) return false;
      for (size_t i=0; i<l.occupancy; ++i)
        if (l.data[i] != r.data[i])
          return false;
      return true; */
    }
    template< size_t RM, typename RE> 
    friend bool operator != (const MultisetType& l, const MultisetType<RM,RE>& r) {
      return not (l == r);
      /* // rewriting to make multiplicity matter and order not matter
      // if (LM != RM) return true; // evaluate-able at compile time
      if (l.occupancy != r.occupancy) return true;
      for (size_t i=0; i<l.occupancy; ++i)
        if (l.data[i] == r.data[i])
          return false;
      return true; */
    }

  protected:
    // write split line if there is a lot of info in data structure 
    inline void _pWrite_comp(ostream_p& out) const {
      std::string sep;
      out.indent();
      for (size_t i=0; i<occupancy; ++i) {
        out << sep << out.nl() << data[i]; sep = ",";
      }
      out.dedent();
    }
    // write single line if there is NOT a lot of info in data structure
    inline void _pWrite_simp(ostream_p& out) const {
      std::string sep;
      for (size_t i=0; i<occupancy; ++i) {
        out << sep << data[i]; sep = ", ";
      }
    }
  public:
    static constexpr const std::string __p_type() { 
      return "Multiset["+std::to_string(MAX)+"] of " + ELEMENT_t::__p_type();
    }
    // friend inline ostream_p& operator << (ostream_p& out, const MultisetType& val) {
    template<template<size_t,typename>class MS_t>
    friend 
    typename std::enable_if<std::is_base_of<MultisetType<MAX,ELEMENT_t>,
                                            MS_t<MAX,ELEMENT_t>>::value,
                            ostream_p>::type& operator << (ostream_p& out, const MS_t<MAX,ELEMENT_t>& val) {
      if (val.IsUndefined()) return (out << SCALAR_ENUM_t::_UNDEFINED_);
      out << '(' << val.occupancy;
      if (ELEMENT_t::__DO_P_SEP() || sizeof(ELEMENT_t)*val.occupancy > sizeof(RangeType<0,1>)*4) {
        val._pWrite_comp(out << "/" << MAX << "){");
        out.nl();
      } else
        val._pWrite_simp(out << "){");
      return (out << '}');
    }
    // template<>
    // friend inline ostream_p& operator << <MultisetType>(ostream_p& out, const MultisetType& val); // {
    static constexpr const std::string __json_type() { 
      return "{\"$type\":\"multiset-type\",\"max\":"+std::to_string(MAX)+'}';
    }
    template<class O>
    friend inline ojstream<O>& operator << (ojstream<O>& json, const MultisetType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        if (val.occupancy<=0) return (json << "null");
        json << "{\"multiset\":["; std::string sep;
        for (size_t i=0; i<val.occupancy; ++i) {
          json << sep << '[' << val.data[i] << ']'; sep = ", ";
        }
        return (json << "]}");
#     else
        json << "{\"$type\":\"complex-value\",\"type\":" << MultisetType::__json_type() << ","
              "\"value\":";
        if (val.IsUndefined())
          return (json << "null}");
        json << '['; std::string sep;
        for (size_t i=0; i<val.occupancy; ++i) {
          json << sep << val.data[i]; sep = ",";
        }
        return (json << "]}");
#     endif
    }
    friend std::hash<MultisetType>;
  };

  template<size_t MAX, typename ELEMENT_t>
  inline const ELEMENT_t& MultisetElement(const MultisetType<MAX,ELEMENT_t>& ms, const size_t i, const location& loc) {
    try {
      return ms[i];
    } catch (...) {
      throw ModelTypeError("error during multiset element access", loc);
    }
  }



  template<size_t FID_START, typename... FIELDS>
  class RecordType {
    std::tuple<FIELDS...> data;
  protected:
    template<size_t I>
    static inline constexpr const std::string& _GET_FIELD_NAME() { return ::__info__::RECORD_FIELD_LABELS[FID_START+I]; }
    template<size_t I>
    inline typename std::enable_if<(I>=sizeof...(FIELDS)),bool>::type _IsUndefined() const { return true; }
    template<size_t I>
    inline typename std::enable_if<(I<sizeof...(FIELDS)),bool>::type _IsUndefined() const {
      if (not std::get<I>(data).IsUndefined()) return false;
      return _IsUndefined<I+1>();
    }
    template<size_t I>
    inline typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type _Clear() { return; }
    template<size_t I>
    inline typename std::enable_if<(I<sizeof...(FIELDS)),void>::type _Clear() {
      std::get<I>(data).Clear();
      _Clear<I+1>();
    }
    template<size_t I>
    static inline typename std::enable_if<(I>=sizeof...(FIELDS)),bool>::type _Equal(const RecordType& l, const RecordType& r) { return true; }
    template<size_t I>
    static inline typename std::enable_if<(I<sizeof...(FIELDS)),bool>::type _Equal(const RecordType& l, const RecordType& r) {
      if (std::get<I>(l.data) != std::get<I>(r.data)) return false;
      return _Equal<I+1>(l,r);
    }
    template<size_t I>
    static inline typename std::enable_if<(I>=sizeof...(FIELDS)),bool>::type _NEqual(const RecordType& l, const RecordType& r) { return true; }
    template<size_t I>
    static inline typename std::enable_if<(I<sizeof...(FIELDS)),bool>::type _NEqual(const RecordType& l, const RecordType& r) {
      if (std::get<I>(l.data) == std::get<I>(r.data)) return false;
      return _NEqual<I+1>(l,r);
    }
  public:
    RecordType() { Undefine(); }

    bool IsUndefined() const { return _IsUndefined<0>(); }
    void Undefine() { std::memset(&data, 0u, sizeof(data)); } // for now design still allows for setting all to 0 to undefine
    void Clear() { _Clear<0>(); }

    static constexpr bool __IS_SIMPLE() { return false; }
    static constexpr bool __IS_RECORD() { return true; }
    static constexpr bool __IS_TYPEID() { return false; }
    static constexpr bool __DO_P_SEP() {
// #     if __cplusplus >= 201703L
//         return ((sizeof...(FIELDS)>3) || (FIELDS::__DO_P_SEP() || ...)); // [[requires C++17]]
// #     else
        bool f_p_seps[] = {FIELDS::__DO_P_SEP()...}; 
        bool res = false;
        for (size_t i=0; i<(sizeof...(FIELDS)); ++i)
          res |= f_p_seps[i];
        return res || (sizeof...(FIELDS)>3);
// #     endif
    }

    template<size_t I>
    typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type& get() { 
      throw std::out_of_range("field does not exist in record"); 
    }
    template<size_t I>
    typename std::enable_if<(I<sizeof...(FIELDS)),typename std::tuple_element<I,std::tuple<FIELDS...>>::type>::type& get() { 
      return std::get<I>(data); 
    }
    template<size_t I>
    const typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type& get() const { 
      throw std::out_of_range("field does not exist in record"); 
    }
    template<size_t I>
    const typename std::enable_if<(I<sizeof...(FIELDS)),typename std::tuple_element<I,std::tuple<FIELDS...>>::type>::type& get() const { 
      return std::get<I>(data); 
    }

    // template<size_t O_FID>
    // friend bool operator == (const RecordType& l, const RecordType<O_FID,FIELDS...>& r) { return RecordType::_Equal<0>(l,r); }
    // template<size_t O_FID>
    // friend bool operator != (const RecordType& l, const RecordType<O_FID,FIELDS...>& r) { return RecordType::_NEqual<0>(l,r); }
    template<size_t O_FID>
    friend bool operator == (const RecordType& l, const RecordType<O_FID,FIELDS...>& r) { return l.data == r.data; }
    template<size_t O_FID>
    friend bool operator != (const RecordType& l, const RecordType<O_FID,FIELDS...>& r) { return l.data != r.data; }

  protected:
    template<size_t I>
    typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type _pWrite_comp(ostream_p& out) const { return; }
    template<size_t I=0>
    typename std::enable_if<(I<sizeof...(FIELDS)),void>::type _pWrite_comp(ostream_p& out) const {
      // if (I > 0) out << sep;
      if (__DO_P_SEP() || out.OPTIONS.report_show_type) out.nl();
      if ((not (std::get<I>(data).__IS_RECORD()) || std::get<I>(data).__IS_TYPEID())
          && out.OPTIONS.report_show_type)
        out << _GET_FIELD_NAME<I>() << ": " << std::get<I>(data).__p_type() << " = " << std::get<I>(data) << ';';
      else
        out << _GET_FIELD_NAME<I>() << " := " << std::get<I>(data) << ';';
      _pWrite_comp<I+1>(out);
    }
    template<size_t I>
    typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type _pWrite_simp(ostream_p& out) const { return; }
    template<size_t I=0>
    typename std::enable_if<(I<sizeof...(FIELDS)),void>::type _pWrite_simp(ostream_p& out) const {
      out << _GET_FIELD_NAME<I>() << ": " << std::get<I>(data);
      if (I+1<sizeof...(FIELDS)) out << "; ";
      _pWrite_simp<I+1>(out);
    }
    template<class O, size_t I>
    typename std::enable_if<(I>=sizeof...(FIELDS)),void>::type _jWrite(ojstream<O>& json) const { return; }
    template<class O, size_t I>
    typename std::enable_if<(I<sizeof...(FIELDS)),void>::type _jWrite(ojstream<O>& json) const {
#     ifdef __ROMP__SIMPLE_TRACE
        if (I > 0) json << ',';
        json << std::get<I>(data);
        _jWrite<O,I+1>(json);
#     else
        if (I > 0) json << ',';
        json << "{\"$type\":\"kv-pair\",\"key\":\"" << _GET_FIELD_NAME<I>() << "\","
                  "\"value\":" << std::get<I>(data) << '}';
        _jWrite<O,I+1>(json);
#     endif
    }
  public:
    static constexpr const std::string __p_type() { return "Record"; }
    // friend ostream_p& operator << (ostream_p& out, const RecordType& val) {
    template<template<size_t,typename...>class Rec_t>
    friend 
    typename std::enable_if<std::is_base_of<RecordType<FID_START,FIELDS...>,
                                            Rec_t<FID_START,FIELDS...>>::value,
                            ostream_p>::type& operator << (ostream_p& out, const Rec_t<FID_START,FIELDS...>& val) {
      if (val.IsUndefined()) return (out << SCALAR_ENUM_t::_UNDEFINED_);
      if (RecordType::__DO_P_SEP()) {
        out << '{'; // "Record";
        out.indent(); out.indent();
        val._pWrite_comp(out);
        // val._pWrite_comp<0>(out);
        return (out << out.dedent() << out.nl() << '}' /* "EndRecord" */ << out.dedent());
      } else {
        out << "{";
        val._pWrite_simp(out);
        // val._pWrite_simp<0>(out);
        return (out << "}");
      }
    }
    static constexpr std::string __json_type() {
      return "{\"$type\":\"record-type\",\"field-count\":"+std::to_string(sizeof...(FIELDS))+'}';
    }
    template<class O>
    friend inline ojstream<O>& operator << (ojstream<O>& json, const RecordType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        // json << '['; 
        val._jWrite<O,0>(json);
        return (json /* << ']' */);
#     else
        json << "{\"$type\":\"complex-value\",\"type-id\":" << RecordType::__json_type() << ","
                  "\"value\":";
        if (val.IsUndefined())
          return (json << "null}");
        json << "[";
        val._jWrite<O,0>(json);
        return (json << "]}");
#     endif
    }
    friend std::hash<RecordType>;
  };





} // namespace romp

namespace __model__ {
  // typedef ::romp::BooleanType Boolean;
  typedef ::romp::BooleanType boolean;
  // typedef ::romp::BooleanType BOOLEAN;
} // namespace __model__
