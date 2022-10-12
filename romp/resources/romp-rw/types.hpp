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
    friend std::ostream& operator << (std::ostream& out, BaseType& val) {
      if (val.is_defined)
        return (out << val.value);
      return (out << "Undefined");
    }
    friend ostream_p& operator << (ostream_p& out, BaseType& val) { return (out << val.get()); }
  protected:
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

  template<range_t LB, range_t UB>
  class RangeType : public BaseType<range_t> {
  public:
    RangeType() : BaseType<range_t>() {}
    RangeType(range_t value_) : BaseType<range_t>(value_) {
      if (value_ < LB || value_ > UB)
        throw std::out_of_range("value " +
                                std::to_string(other) +
                                " being assigned is out of range (`"+ 
                                std::to_string(LB) +
                                ".."+
                                std::to_string(UB) +
                                "`)");
    }
    void Clear() { set(LB); }
    operator range_t () { return get(); }
    RangeType& operator = (range_t other) { 
      if (other < LB || other > UB)
        throw std::out_of_range("value " +
                                std::to_string(other) +
                                " being assigned is out of range (i.e. `"+ 
                                std::to_string(LB) +
                                ".."+
                                std::to_string(UB) +
                                "`)");
      return *((RangeType*)set(other));
    }
    size_t __get_index_val() const { return static_cast<size_t>(get()) - LB; }
    static constexpr range_t __LB() { return LB; } 
    static constexpr range_t __UB() { return UB; } 
    static constexpr range_t __STEP() { return static_cast<range_t>(1); }
    static constexpr size_t __COUNT() { return static_cast<size_t>((UB-LB)/__STEP); }
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
      out << "{\"$type\":\"value\",\"type\":{\"$type\":\"type-expr\",\"type\":\"range\","
            "\"lower-bound\":" << LB << ",\"upper-bound\":" << UB << "},"
            "\"value\":" << val.get() << '}';
    }
#   endif
  };

  // useful pre-decls
  template<size_t ENUM_ID, size_t BOUND> class EnumType;
  template<size_t NAME_ID, size_t ENUM_ID, size_t BOUND> class ScalarsetType;
  template<class... UNION_MEMBERS> class ScalarsetUnionType;

# ifndef __romp__GENERATED_CODE // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
  inline std::string to_str(const SCALAR_ENUM_t& val) { return "<UNDEFINED>"; } // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
# endif                         // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!

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
    inline void Clear() { value = static_cast<SCALAR_ENUM_t>(ENUM_ID); }
    
    static inline bool IsMember(const SCALAR_ENUM_t& v) { 
      return ((__LB() <= v) && (v <= __UB()));
    }
    
    static constexpr size_t __ENUM_ID() { return ENUM_ID; }
    static constexpr size_t __BOUND() { return BOUND; }
    static constexpr SCALAR_ENUM_t __LB() { return static_cast<SCALAR_ENUM_t>(ENUM_ID); }
    static constexpr SCALAR_ENUM_t __UB() { return static_cast<SCALAR_ENUM_t>(ENUM_ID+BOUND-1); }
    static constexpr SCALAR_ENUM_t __STEP() { return static_cast<SCALAR_ENUM_t>(1); }
    static constexpr SCALAR_ENUM_t __COUNT() { return BOUND; }

    // cast to index operator
    inline size_t __get_index_val() const {
      if (IsUndefined())
        throw std::logic_error("value was undefined");
      return static_cast<size_t>(value)-ENUM_ID; 
    }
    const SCALAR_ENUM_t& __get_value() const { return value; }

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
    
    friend ostream_p& operator << (ostream_p& out, const ScalarsetUnionType& val) { return (out << to_str(val.value)); }
    template<class O>
    static inline const std::string __json_type() { return "{\"$type\":\"enum-type\"}"; }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const EnumType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.IsUndefined() << "," << val.value)
#     else
        out << "{\"$type\":\"undefinable-value\",\"type\":" << __json_type() << ",\"value\":";
        if (val.IsUndefined())
          return (out << "null}");
        return (out << "\"" << to_str(val.value) << "\"}");
#     endif 
    }
  };

  template<size_t NAME_ID, size_t ENUM_ID, size_t BOUND>
  class ScalarsetType : public EnumType<ENUM_ID,BOUND> {
  public:
    ScalarsetType() : EnumType<ENUM_ID,BOUND>() {}
    ScalarsetType(const SCALAR_ENUM_t& value_) {
      if (not EnumType<ENUM_ID,BOUND>::IsMember(value_))
        throw std::logic_error("`"+ to_str(value_) +"` is not a member of this scalarset type");
      this->value = value_;
    }
    static inline const std::string __id() { return ::__info__::TYPE_IDS[NAME_ID]; }


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
    friend ostream_p& operator << (ostream_p& out, const ScalarsetUnionType& val) { return (out << to_str(val.value)); }
    template<class O>
    static inline const std::string __json_type() { return "{\"$type\":\"scalarset-type\",\"id\":\""+__id()+"\",\"bound\":"+std::to_string(BOUND)+'}'; }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const ScalarsetType& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.IsUndefined() << "," << val.value)
#     else
        out << "{\"$type\":\"undefinable-value\",\"type\":" << __json_type() << ",\"value\":";
        if (val.IsUndefined())
          return (out << "null}");
        return (out << "\"" << to_str(val.value) << "\"}");
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
      value = value_.__get_value();
    }

    static inline bool IsMember(const SCALAR_ENUM_t& val) { return MembersContain(val); }
    inline bool IsUndefined() const { return (value == SCALAR_ENUM_t::_UNDEFINED_); }
    inline void Undefine() { value = SCALAR_ENUM_t::_UNDEFINED_; }
    inline void Clear() { value = (((sizeof...(UNION_MEMBERS))<=0) ? SCALAR_ENUM_t::_UNDEFINED_ : static_cast<SCALAR_ENUM_t>(ENUM_IDS[1]) ); }
    
    // get index value
    inline size_t __get_index_value() const {
      if (IsUndefined())
        throw std::logic_error("value was undefined");
      size_t offset = 0ul;
      size_t i;
      for (i=0ul; i<(sizeof...(UNION_MEMBERS)+1); ++i) {
        if (ENUM_IDS[i] <= value && value <= (ENUM_IDS[i]+BOUNDS[i]-1)) 
          return offset + static_cast<size_t>(value) - ENUM_IDS[i];
        offset += BOUNDS[i];
        throw std::runtime_error("DEV ERROR : could not convert union to index value");
      }
      
    }
    const SCALAR_ENUM_t& __get_value() const { return value; }

    template<size_t E_ID, size_t B>
    inline ScalarsetUnionType& operator = (const EnumType<E_ID,B>& other) { return (*this = other.__get_value()); }
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
          u(static_cast<SCALAR_ENUM_t>(ScalarsetUnionType::ENUM_IDS[i_]+j_)) 
        {}
      ScalarsetUnionType& operator*() const { return u; }
      ScalarsetUnionType* operator->() { return &u; }
      iterator& operator += (int _) {
        if (++j > u.BOUNDS[i]) {
          ++u.value;
          return *this;
        }
        ++i; j=0;
        u.value = static_cast<SCALAR_ENUM_t>(ScalarsetUnionType::ENUM_IDS[i]+j);
        return *this;
      }
      friend bool operator <= (const iterator& l, const iterator& r) {
        return (l.i<=r.i && l.j <= r.j);
      }
      operator ScalarsetUnionType () { return ScalarsetUnionType(u); }
      iterator& operator = (const ScalarsetUnionType& other) {
        throw std::bad_cast("you cannot assign to a quantifier or for loop iterator")
      }
    };
    static constexpr iterator __LB() { return iterator(1, 0); }
    static constexpr iterator __UB() { return iterator(sizeof...(UNION_MEMBERS), BOUNDS[sizeof...(UNION_MEMBERS)]); }
    static constexpr int __STEP() { return 1; }
    static constexpr size_t __COUNT() {
      size_t res=0; 
      for (size_t i=1; i<=sizeof...(UNION_MEMBERS); ++i) 
        res += BOUNDS[i];
      return res;
    }
    
    friend ostream_p& operator << (ostream_p& out, const ScalarsetUnionType& val) { return (out << to_str(val.value)); }
    template<class O>
    static inline const std::string __json_type() { return "{\"$type\":\"scalarset-union-type\"}"; }
    template<class O>
    friend ojstream<O>& operator << (ojstream<O>& out, const ScalarsetUnion& val) {
#     ifdef __ROMP__SIMPLE_TRACE
        return (out << val.IsUndefined() << "," << val.value)
#     else
        out << "{\"$type\":\"undefinable-value\",\"type\":" << __json_type() << ",\"value\":";
        if (val.IsUndefined())
          return (out << "null}");
        return (out << "\"" << to_str(val.value) << "\"}");
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
  };


  template<size_t MAX, typename ELEMENT_t>
  class MultisetType {
    ELEMENT_t data[MAX];
  };


} // namespace romp
