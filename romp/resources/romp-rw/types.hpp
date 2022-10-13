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
#endif

namespace romp {

  typedef ::__model__::SCALAR SCALAR_ENUM_t;  // typemask for the enum type holding all scalar and enum values

  // << ====================================== Base Types ======================================== >> 

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

    friend ostream_p& operator << (ostream_p& out, BaseType& val) { 
      if (val.IsUndefined())
        return (out << "<UNDEFINED>");
      return (out << val.get()); 
    }
    static inline const std::string __json_type() { return "null"; }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const BaseType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.IsUndefined() << "," << val.get())
#     else
        out << "{\"$type\":\"undefinable-value\",\"type\":null,\"value\":";
        if (val.IsUndefined())
          return (out << "null}");
        return (out << val.get() << '}');
#     endif 
    }
  };


  // << ===================================== Type ID Mask ======================================= >> 

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

    friend inline ostream_p& operator << (ostream_p& out, const BooleanType& val) {
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

    friend ostream_p& operator << (ostream_p& out, BaseType& val) { 
      return (out << get());
    }
    static const std::string __json_type() { 
      return "{\"$type\":\"range-type\","
                "\"bounds\":["+std::to_string(LB)+","+std::string(UB)+"]}";
    }
    template<class O>
#   ifndef __ROMP__SIMPLE_TRACE
    friend ojstream<O>& operator << (ojstream<O>& out, const RangeType& val) {
      out << "{\"$type\":\"undefinable-value\",\"type\":"<< __json_type() <<","
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
  template<size_t NAME_ID, size_t ENUM_ID, size_t BOUND> class ScalarsetType;
  template<class... UNION_MEMBERS> class ScalarsetUnionType;

# ifndef __romp__GENERATED_CODE // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
  inline std::string to_str(const SCALAR_ENUM_t& val) { return "<UNDEFINED>"; } // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
# endif                         // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
  inline std::ostream& operator << (std::ostream& out, const SCALAR_ENUM_t& val) { return (out << to_str(val)); }
  inline ostream_p& operator << (ostream_p& out, const SCALAR_ENUM_t& val) { return (out << to_str(val)); }
  template<class O>
  inline ojstream<O>& operator << (ojstream<O>& json, const SCALAR_ENUM_t& val) { return (json << '"' <<to_str(val))<< '"'; }

  template<size_t ENUM_ID, size_t BOUND>
  class EnumType {
  protected:
    SCALAR_ENUM_t value;
  public:
    EnumType() : value(SCALAR_ENUM_t::_UNDEFINED_) {}
    EnumType(const SCALAR_ENUM_t& value_) : value(value_) {
      if (not IsMember(value_))
        throw std::logic_error("`"+ to_str(value_) +"` is not a member of this enum type");
    }

    inline bool IsUndefined() const { return value == SCALAR_ENUM_t::_UNDEFINED_; }
    inline void Undefine() { value = SCALAR_ENUM_t::_UNDEFINED_; }
    inline void Clear() { value = make_SCALAR_ENUM_t(ENUM_ID); }
    
    static inline bool IsMember(const SCALAR_ENUM_t& v) { 
      return ((v == SCALAR_ENUM_t::_UNDEFINED_) || ((__LB() <= v) && (v <= __UB())));
    }
    
    static constexpr size_t __ENUM_ID() { return ENUM_ID; }
    static constexpr size_t __BOUND() { return BOUND; }
    static constexpr SCALAR_ENUM_t __LB() { return make_SCALAR_ENUM_t(ENUM_ID); }
    static constexpr SCALAR_ENUM_t __UB() { return make_SCALAR_ENUM_t(ENUM_ID+BOUND-1); }
    static constexpr SCALAR_ENUM_t __STEP() { return make_SCALAR_ENUM_t(1); }
    static constexpr size_t __COUNT() { return BOUND; }

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
      if (not IsMember(val))
        throw std::logic_error("`"+ to_str(value) +"` is not a member of this enum type");
      value = val;
      return *this;
    }

    template<class... U_M>
    explicit inline operator ScalarsetUnionType<U_M...> () { return __convert(*this); }
    template<class... U_M>
    ScalarsetUnionType<U_M...> __convert(const EnumType& _this);

    template<size_t L_ID, size_t L_B, size_t R_ID, size_t R_B>
    friend inline bool operator == (const EnumType<L_ID,L_B>& l, const EnumType<R_ID,R_B> r);
    template<size_t L_ID, size_t L_B, size_t R_ID, size_t R_B>
    friend inline bool operator != (const EnumType<L_ID,L_B>& l, const EnumType<R_ID,R_B> r);

    template<size_t EID, size_t B, class... U_M>
    friend inline bool operator == (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u);
    template<size_t EID, size_t B, class... U_M>
    friend inline bool operator != (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u);
    template<class... U_M, size_t EID, size_t B>
    friend inline bool operator == (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e);
    template<class... U_M, size_t EID, size_t B>
    friend inline bool operator != (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e);

    /* this IsMember is the one associated with the IsMember() Murphi language operator */
    template<size_t EID, size_t B, class... U_M>
    friend inline bool IsMember(const ScalarsetUnionType<U_M...> u);
    
    friend ostream_p& operator << (ostream_p& out, const ScalarsetUnionType& val) { return (out << val.value); }
    template<class O>
    static inline const std::string __json_type() { return "{\"$type\":\"enum-type\",\"bound\":"+std::to_string(BOUND)+'}'; }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const EnumType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.IsUndefined() << "," << val.value)
#     else
        out << "{\"$type\":\"undefinable-value\",\"type\":" << __json_type() << ",\"value\":";
        if (val.IsUndefined())
          return (out << "null}");
        return (out << "\"" << val.value << "\"}");
#     endif 
    }
  };

  template<size_t NAME_ID, size_t ENUM_ID, size_t BOUND>
  class ScalarsetType : public EnumType<ENUM_ID,BOUND> {
  public:
    ScalarsetType() : EnumType<ENUM_ID,BOUND>() {}
    ScalarsetType(const SCALAR_ENUM_t& value_) {
      if (not EnumType<ENUM_ID,BOUND>::IsMember(value_))
        throw std::logic_error("`"+ value_ +"` is not a member of this scalarset type");
      this->value = value_;
    }
    static inline const std::string __id() { return ::__info__::TYPE_IDS[NAME_ID]; }

    template<class... U_M>
    explicit inline operator ScalarsetUnionType<U_M...> () { return __convert(*this); }
    template<class... U_M>
    friend inline ScalarsetUnionType<U_M...> __convert(const ScalarsetType& _this);

    template<size_t EID, size_t B, class... U_M>
    friend inline void __assign(EnumType<EID,B>& _this, const ScalarsetUnionType<U_M...>& other);
    template<class... U_M>
    inline ScalarsetType& operator = (const ScalarsetUnionType<U_M...>& other) { __assign(*this,other); return *this; }
    inline ScalarsetType& operator = (const SCALAR_ENUM_t& val) {
      if (not EnumType<ENUM_ID,BOUND>::IsMember(val))
        throw std::logic_error("`"+ to_str(val) +"` is not a member of this scalarset type" 
                  + ((__id() != "") ? " (`"+ __id() +"`)" : std::string()));
      this->value = val;
      return *this;
    }
    friend ostream_p& operator << (ostream_p& out, const ScalarsetUnionType& val) { return (out << val.value); }
    static inline const std::string __json_type() { return "{\"$type\":\"scalarset-type\",\"id\":\""+__id()+"\",\"bound\":"+std::to_string(BOUND)+'}'; }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const ScalarsetType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.IsUndefined() << "," << val.value)
#     else
        out << "{\"$type\":\"undefinable-value\",\"type\":" << __json_type() << ",\"value\":";
        if (val.IsUndefined())
          return (out << "null}");
        return (out << "\"" << val.value << "\"}");
#     endif 
    }
  };


  template<class... UNION_MEMBERS>
  class ScalarsetUnionType {
    SCALAR_ENUM_t value;
  protected:
    static const size_t MEMBER_COUNT;
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

    static inline bool IsMember(const SCALAR_ENUM_t& val) { return MembersContain(val); }
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
          return offset + static_cast<size_t>(value) - ENUM_IDS[i];
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
    template<size_t NID, size_t EID, size_t B>
    explicit inline operator ScalarsetType<NID,EID,B> () {
      static_assert(ScalarsetUnionType::ContainsMember<EID,B>(), 
                    "union must contain scalarset member type to cast to it!");
      return ScalarsetType<NID,EID,B>(value);
    }
    template<size_t NID, size_t EID, size_t B>
    friend inline ScalarsetUnionType __convert(const EnumType<EID,B>& _this) {
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
    
    template<class... L_M, class... R_M>
    friend inline bool operator == (const ScalarsetUnionType<L_M...>& l, const ScalarsetUnionType<R_M...> r);
    template<class... L_M, class... R_M>
    friend inline bool operator != (const ScalarsetUnionType<L_M...>& l, const ScalarsetUnionType<R_M...> r);

    bool operator == (const SCALAR_ENUM_t& other) const { return value == other; }
    bool operator != (const SCALAR_ENUM_t& other) const { return value != other; }

    template<size_t EID, size_t B, class... U_M>
    friend inline bool operator == (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u);
    template<size_t EID, size_t B, class... U_M>
    friend inline bool operator != (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u);
    template<class... U_M, size_t EID, size_t B>
    friend inline bool operator == (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e);
    template<class... U_M, size_t EID, size_t B>
    friend inline bool operator != (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e);

    /* this IsMember is the one associated with the IsMember() Murphi language operator */
    template<class ET, class... U_M>
    friend inline bool IsMember(const ScalarsetUnionType<U_M...>& u);
    template<size_t EID, size_t B, class... U_M>
    friend inline bool IsMember(const ScalarsetUnionType<U_M...>& u);

    class iterator {
      ScalarsetUnionType u;
      size_t i;
      size_t j;
    public:
      iterator(size_t i_, size_t j_) 
        : i(i_), j(j_), 
          u(make_SCALAR_ENUM_t(ScalarsetUnionType::ENUM_IDS[i_]+j_)) 
        {}
      ScalarsetUnionType& operator*() const { return u; }
      ScalarsetUnionType* operator->() { return &u; }
      iterator& operator += (int _) {
        if (++j > u.BOUNDS[i]) {
          ++u.value;
          return *this;
        }
        ++i; j=0;
        u.value = make_SCALAR_ENUM_t(ScalarsetUnionType::ENUM_IDS[i]+j);
        return *this;
      }
      friend bool operator <= (const iterator& l, const iterator& r) {
        return (l.i<=r.i && l.j <= r.j);
      }
      operator ScalarsetUnionType () { return ScalarsetUnionType(u); }
      iterator& operator = (const ScalarsetUnionType& other) {
        throw std::logic_error("you cannot assign to a quantifier or for-loop iterator");
      }
    };
    static constexpr iterator __LB() { return iterator(1, 0); }
    static constexpr iterator __UB() { return iterator(sizeof...(UNION_MEMBERS), BOUNDS[sizeof...(UNION_MEMBERS)]); }
    static constexpr int __STEP() { return 1; }

    static constexpr size_t __COUNT() {
#     if __cplusplus >= 201703L
        return ((UNION_MEMBERS::__COUNT() == E_ID) + ...); // [[requires C++17]]
#     else
        size_t counts[sizeof...(UNION_MEMBERS)] = {(UNION_MEMBERS::__COUNT())...};
        size_t res=0; 
        for (size_t i=0; i<sizeof...(UNION_MEMBERS); ++i) 
          res += counts[i];
        return res;
#     endif
    }
    
    friend ostream_p& operator << (ostream_p& out, const ScalarsetUnionType& val) { return (out << val.value); }
    static inline const std::string __json_type() { 
      return "{\"$type\":\"scalarset-union-type\","
                "\"member-count\":"+std::to_string(sizeof...(UNION_MEMBERS))+","
                "\"\"bound\":"+ std::to_string(__COUNT()) +'}';
    }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const ScalarsetUnion& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.IsUndefined() << "," << val.value)
#     else
        out << "{\"$type\":\"undefinable-value\",\"type\":" << __json_type() << ",\"value\":";
        if (val.IsUndefined())
          return (out << "null}");
        return (out << "\"" << val.value << "\"}");
#     endif 
    }
  };
  
  template<class... UNION_MEMBERS>
  const size_t ScalarsetUnionType<UNION_MEMBERS...>::ENUM_IDS[sizeof...(UNION_MEMBERS)+1] = {0,UNION_MEMBERS::__ENUM_ID()...};

  template<class... UNION_MEMBERS>
  const size_t ScalarsetUnionType<UNION_MEMBERS...>::BOUNDS[sizeof...(UNION_MEMBERS)+1] = {1,UNION_MEMBERS::__BOUND()...};


  // << ===================================== Complex Types ====================================== >> 

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

  protected:
    // write split line if there is a lot of info in the data structure 
    inline typename std::enable_if<(sizeof(ELEMENT_t)*INDEX_t::__COUNT()>sizeof(RangeType<0,1>)*6),void>::type _pWrite(ostream_p& out) {
      std::string sep;
      out.indent(); out.indent();
      { const auto __LB__ = INDEX_t::__LB();
        const auto __UB__ = INDEX_t::__UB();
        const auto __STEP__ = INDEX_t::__STEP();
        const auto __COND__ = ((__STEP__>0) 
                                ? [](i)->bool { return i<=__UB__; }
                                : [](i)->bool { return i>=__LB__; });
        for (auto i=__LB__; __COND__(i); i+=__STEP__) {
          out << sep << out.nl() << i << ": " << val[i]; sep = ",";
        }
      }
      out.dedent(); out.dedent();
    }
    // write single line if there is NOT a lot of info in the data structure
    inline typename std::enable_if<(sizeof(ELEMENT_t)*INDEX_t::__COUNT()<=sizeof(RangeType<0,1>)*6),void>::type _pWrite(ostream_p& out) {
      std::string sep;
      for (size_t i=0; i<INDEX_t::__COUNT(); ++i) {
        out << sep << data[i]; sep = ", ";
      }
    }
  public:
    // template<typename It, typename Et>
    // friend inline ostream_p& operator << (ostream_p& out, const ArrayType<It,Et>& val) {
    friend inline ostream_p& operator << (ostream_p& out, const ArrayType& val) {
      if (val.IsUndefined()) return (out << "<UNDEFINED>");
      out << '(' << val.occupancy << "/" << MAX << "){";
      val._pWrite(out);
      return (out << '}');
    }
    // template<size_t EID, size_t B, typename Et>
    // friend inline ostream_p& operator << (ostream_p& out, const ArrayType<EnumType<EID,B>,Et>& val) {/* might need latter */}
    // template<class... U_M, typename Et>
    // friend inline ostream_p& operator << (ostream_p& out, const ArrayType<ScalarsetUnionType<U_M...>,Et>& val) {/* might need latter */}
    static constexpr std::string __json_type() { 
      return "{\"$type\":\"array-type\",\"length\":"+ std::to_string(INDEX_t::__COUNT())+'}';
    }
    template<class O>
    friend inline ojstream<O>& operator << (ojstream<O>& json, const ArrayType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        json << '['; std::string sep;
        for (size_t i=0; i<INDEX_t::__COUNT(); ++i) {
          out << sep << val.data[i]; sep = ", ";
        }
        return (json << ']');
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
  };
 

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

  protected:
    // write split line if there is a lot of info in data structure 
    inline typename std::enable_if<(sizeof(ELEMENT_t)*MAX>sizeof(RangeType<0,1>)*8),void>::type _pWrite(ostream_p& out) {
      std::string sep;
      out.indent(); out.indent();
      for (size_t i=0; i<val.occupancy; ++i) {
        out << sep << out.nl() << val.data[i]; sep = ",";
      }
      out.dedent(); out.dedent();
    }
    // write single line if there is NOT a lot of info in data structure
    inline typename std::enable_if<(sizeof(ELEMENT_t)*MAX<=sizeof(RangeType<0,1>)*8),void>::type _pWrite(ostream_p& out) {
      std::string sep;
      for (size_t i=0; i<val.occupancy; ++i) {
        out << sep << data[i]; sep = ", ";
      }
    }
  public:
    friend inline ostream_p& operator << (ostream_p& out, const MultisetType& val) {
      if (val.IsUndefined()) return (out << "<UNDEFINED>");
      out << '(' << val.occupancy << "/" << MAX << "){";
      val._pWrite(out);
      return (out << '}');
    }
    static constexpr std::string __json_type() { 
      return "{\"$type\":\"multiset-type\",\"max\":"+std::to_string(MAX)+'}';
    }
    template<class O>
    friend inline ojstream<O>& operator << (ojstream<O>& json, const MultisetType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        json << '['; std::string sep;
        for (size_t i=0; i<val.occupancy; ++i) {
          json << sep << val.data[i]; sep = ", ";
        }
        return (json << ']');
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
  };


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
    typename std::enable_if<(I>=sizeof...(MEMBERS)),void>::type _pWrite(ostream_p& out, const std::string& sep) const { return; }
    template<size_t I>
    typename std::enable_if<(I<sizeof...(MEMBERS)),void>::type _pWrite(ostream_p& out, const std::string& sep) const {
      if (I > 0) out << sep;
      if ((sizeof(std::tuple<MEMBERS...>)>sizeof(RangeType<0,1>)*8) || (sizeof...(MEMBERS)>3)) out.nl();
      out << '`' << _GET_MEMBER_NAME(I) << "`: " << std::get<I>(data);
      _pWrite<I+1>(out,sep);
    }
    template<class O, size_t I>
    typename std::enable_if<(I>=sizeof...(MEMBERS)),void>::type _jWrite(ojstream<O>& json) const { return; }
    template<class O, size_t I>
    typename std::enable_if<(I<sizeof...(MEMBERS)),void>::type _jWrite(ojstream<O>& json) const {
#     ifdef __ROMP__SIMPLE_TRACE
        if (I > 0) json << ',';
        json << std::get<I>(data);
        _jWrite<I+1>(json);
#     else
        if (I > 0) json << ',';
        json << "{\"$type\":\"kv-pair\",\"key\":" << _GET_MEMBER_NAME(I) << ","
                  "\"value\":" << std::get<I>(data) << '}';
        _jWrite<I+1>(json);
#     endif
    }
  public:
    friend ostream_p& operator << (ostream_p& out, const RecordType& val) {
      if (val.IsUndefined()) return (out << "<UNDEFINED>");
      out << "{";
      if ((sizeof(std::tuple<MEMBERS...>)>sizeof(RangeType<0,1>)*8) || (sizeof...(MEMBERS)>3)) {
        out.indent(); out.indent();
        val._pWrite<0>(out, ";");
        out << out._dedent() << '}'; out.dedent(); 
      } else {
        val._pWrite<0>(out, "; ");
        return (out << '}');
      }
    }
    static constexpr std::string __json_type() {
      return "{\"$type\":\"record-type\",\"member-count\":"+std::to_string(sizeof...(MEMBERS))+'}';
    }
    template<class O>
    friend inline ojstream<O>& operator << (ojstream<O>& json, const RecordType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        json << '['; 
        val._jWrite(json);
        return (json << ']');
#     else
        json << "{\"$type\":\"complex-value\",\"type\":" << RecordType::__json_type() << ","
                  "\"value\":";
        if (val.IsUndefined())
          return (json << "null}");
        json << "[";
        val._jWrite(json);
        return (json << "]}");
#     endif
    }
  };


} // namespace romp
