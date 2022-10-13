#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <exception>
#include <type_traits>
#include <tuple>
#include <algorithm>

#ifndef __INCLUDE_SCALAR__
namespace __model__ {
  enum SCALAR {_UNDEFINED_=0, enum_test1, enum_test2, enum_test3, scalarset_1_1, scalarset_2_1, scalarset_2_2, other_enum, final_enum, anon_enum };
} // namespace __model__
namespace __info__ {
  const std::string TYPE_IDS[] = {"_UNDEFINED_", "enum_test", "scalarset_1", "scalarset_2", "rand_enums", "union_test"};
} // namespace __model__

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
#endif

  typedef ::__model__::SCALAR SCALAR_ENUM_t;
  inline SCALAR_ENUM_t make_SCALAR_ENUM_t(size_t val) { return static_cast<SCALAR_ENUM_t>(val); }

  // << ------------------------------------------------------------------------------------------ >> 


  template<size_t NAME_ID, typename T>
  class TypeIdType : public T {
  public:
    TypeIdType() : T() {}
    template<typename... Args>
    TypeIdType(Args &&... args) : T(std::forward<Args>(args)...) {}
    // inline operator T& () { return *((T*)this); }
    // inline operator T* () { return ((T*)this); }
    static inline const std::string __id() { return __info__::TYPE_IDS[NAME_ID]; }
    static inline const std::string __json_type() {
      return "{\"$type\":\"type-id\",\"id\":\"" + __id() + "\",\"referent\":" + T::__json_type() + '}';
    }
    // friend std::ostream& operator << (std::ostream& out, const T& val)
  };

  template<size_t ENUM_ID, size_t BOUND> class EnumType;
  template<size_t NAME_ID, size_t ENUM_ID, size_t BOUND> class ScalarsetType;
  template<class... UNION_MEMBERS> class ScalarsetUnionType;


  // << ------------------------------------------------------------------------------------------ >> 


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
    
    friend std::ostream& operator << (std::ostream& out, const EnumType& val) { return (out << to_str(val.value)); }
  };

  // << ------------------------------------------------------------------------------------------ >> 

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
  };



  // << ------------------------------------------------------------------------------------------ >> 

  // template<size_t I, class... U_M>
  // constexpr typename std::enable_if<(I>=sizeof...(U_M)), const size_t>::type __sum_bounds(const std::tuple<U_M...>& t) { return 0; }
  // template<size_t I, class... U_M>
  // constexpr typename std::enable_if<(I<sizeof...(U_M)), const size_t>::type __sum_bounds(const std::tuple<U_M...>& t) {
  //   return std::get<I>(t).__COUNT() + __sum_bounds<I+1,U_M...>(t);
  // }

  

  // << ------------------------------------------------------------------------------------------ >> 

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
    
    friend std::ostream& operator << (std::ostream& out, const ScalarsetUnionType& val) { return (out << to_str(val.value)); }
  };
  
  template<class... UNION_MEMBERS>
  const size_t ScalarsetUnionType<UNION_MEMBERS...>::ENUM_IDS[sizeof...(UNION_MEMBERS)+1] = {0,UNION_MEMBERS::__ENUM_ID()...};

  template<class... UNION_MEMBERS>
  const size_t ScalarsetUnionType<UNION_MEMBERS...>::BOUNDS[sizeof...(UNION_MEMBERS)+1] = {1,UNION_MEMBERS::__BOUND()...};


  // << ------------------------------------------------------------------------------------------ >> 

  // template<size_t ENUM_ID, size_t BOUND, size_t EID, size_t B>
  // EnumType<ENUM_ID,BOUND>::EnumType(const ENUM_TYPE<EID,B>& other) : value(other.__get_scalar_value()) {
  //   if ((ENUM_ID != EID || BOUND != B) && not other.IsUndefined())
  //     throw std::logic_error("value not member of this enum type");
  // }
  // template<size_t EID, size_t B, class... U_M>
  // EnumType<EID,B>::EnumType(const ScalarsetUnionType<U_M...>& other) : EnumType(other.__get_scalar_value()) {}
  // template<class... U_M, size_t EID, size_t B>
  // inline ScalarsetUnionType<U_M...> __convert(const EnumType<EID,B>& _this) {
  //   static_assert((ScalarsetUnionType<U_M...>::ContainsMember<EID,B>()),
  //                 "enum type must be a member of the union type to be cast to it");
  //   return ScalarsetUnionType<U_M...>(_this.value);
  // }
  // template<class... U_M, size_t NID, size_t EID, size_t B>
  // inline ScalarsetUnionType<U_M...> __convert(const ScalarsetType<NID, EID,B>& _this) {
  //   static_assert((ScalarsetUnionType<U_M...>::ContainsMember<EID,B>()),
  //                 "scalarset type must be a member of the union type to be cast to it");
  //   return ScalarsetUnionType<U_M...>(_this.value);
  // }

  template<size_t EID, size_t B, class... U_M>
  inline void __assign(EnumType<EID,B>& _this, const ScalarsetUnionType<U_M...>& other) { _this = other.__get_scalar_value(); }
  template<size_t NID, size_t EID, size_t B, class... U_M>
  inline void __assign(ScalarsetType<NID,EID,B>& _this, const ScalarsetUnionType<U_M...>& other) { _this = other.__get_scalar_value(); }

  template<size_t L_ID, size_t L_B, size_t R_ID, size_t R_B>
  inline bool operator == (const EnumType<L_ID,L_B>& l, const EnumType<R_ID,R_B> r) { 
    return ((L_ID == R_ID) // this static expr should help the compiler optimize this per type definition. 
            && (l.value == r.value)); 
  }
  template<size_t L_ID, size_t L_B, size_t R_ID, size_t R_B>
  inline bool operator != (const EnumType<L_ID,L_B>& l, const EnumType<R_ID,R_B> r) { 
    return ((L_ID != R_ID) // this should help the compiler optimize this per type definition. 
            || (l.value != r.value)); 
  }

  template<class... L_M, class... R_M>
  inline bool operator == (const ScalarsetUnionType<L_M...>& l, const ScalarsetUnionType<R_M...> r) { return l.value == r.value; }
  template<class... L_M, class... R_M>
  inline bool operator != (const ScalarsetUnionType<L_M...>& l, const ScalarsetUnionType<R_M...> r) { return l.value != r.value; }

  template<size_t EID, size_t B, class... U_M>
  inline bool operator == (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u) {
#   if __cplusplus >= 201703L
      return ((ScalarsetUnionType<U_M...>::ContainsMember<EID,B>()) // this should help the compiler optimize this per specific templated instance. [[requires c++17]] to be static
              && (e.value == u.value));
#   else
      return e.value == u.value;
#   endif
  }
  template<size_t EID, size_t B, class... U_M>
  inline bool operator != (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u) {
#   if __cplusplus >= 201703L
      return (not (ScalarsetUnionType<U_M...>::ContainsMember<EID,B>()) // this should help the compiler optimize this per specific templated instance. [[requires c++17]]
              || (e.value != u.value));
#   else
      return e.value != u.value;
#   endif
  }
  template<class... U_M, size_t EID, size_t B>
  inline bool operator == (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e) { return (e == u); }
  template<class... U_M, size_t EID, size_t B>
  inline bool operator != (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e) { return (e != u); }

  /* this IsMember is the one associated with the IsMember() Murphi language operator */
  template<class ET, class... U_M>
  inline bool IsMember(const ScalarsetUnionType<U_M...>& u) {
    return ET::IsMember(u.value);
  }
  template<size_t EID, size_t B, class... U_M>
  inline bool IsMember(const ScalarsetUnionType<U_M...>& u) {
    return EnumType<EID,B>::IsMember(u.value);
  }


// << ------------------------------------------------------------------------------------------ >> 

#ifndef __INCLUDE_SCALAR__

const char* to_str(const bool val) { return ((val) ? "true" : "false"); }



auto main() -> int {
  using namespace __model__;
  typedef TypeIdType<1,EnumType<enum_test1,3>> enum_test;
  typedef TypeIdType<2,ScalarsetType<2,scalarset_1_1,1>> scalarset_1;
  typedef TypeIdType<3,ScalarsetType<3,scalarset_2_1,2>> scalarset_2;
  typedef TypeIdType<4,EnumType<other_enum,2>> rand_enums;
  typedef TypeIdType<5,ScalarsetUnionType<enum_test,scalarset_1,scalarset_2,EnumType<anon_enum,1>>> union_test;
  try {
    enum_test e1 = _UNDEFINED_; // (enum_test1);
    scalarset_1 s1(_UNDEFINED_); // (scalarset_1_1);
    scalarset_2 s2; // = scalarset_2_2;
    rand_enums e2; // = final_enum;
    union_test u1 = _UNDEFINED_;

    std::cout << 
        "enum_test e1;\n"
        "rand_enums e2;\n"
        "scalarset_1 s1;\n"
        "scalarset_2 s2;\n"
        "union_test u1;\n\n"
      << std::flush <<
        "IsUndefined(e1)    -> " << to_str(e1.IsUndefined()) << "\n"
        "IsUndefined(e2)    -> " << to_str(e2.IsUndefined()) << "\n"
        "IsUndefined(s1)    -> " << to_str(s1.IsUndefined()) << "\n"
        "IsUndefined(s2)    -> " << to_str(s2.IsUndefined()) << "\n"
        "IsUndefined(u1)    -> " << to_str(u1.IsUndefined()) << "\n\n"
      << std::flush <<
        "Clear e1           -> " << ({e1.Clear(); e1;}) << "\n"
        "Clear e2           -> " << ({e2.Clear(); e2;}) << "\n"
        "Clear s1           -> " << ({s1.Clear(); s1;}) << "\n"
        "Clear s2           -> " << ({s2.Clear(); s2;}) << "\n"
        "Clear u1           -> " << ({u1.Clear(); u1;}) << "\n\n"
      << std::flush <<
        "e1 = enum_test3    -> " << (e1 = enum_test1) << "\n"
        "e1 = enum_test2    -> " << (e1 = enum_test2) << "\n"
        "e1 = enum_test1    -> " << (e1 = enum_test1) << "\n"
        "s2 = scalarset_2_2 -> " << (s2 = scalarset_2_2) << "\n"
        "s2 = scalarset_2_1 -> " << (s2 = scalarset_2_1) << "\n"
      << std::flush << 
        "IsMember(u1,union_test)  -> " << to_str(IsMember<union_test>(u1)) << "\n" 
        "IsMember(u1,scalarset_1) -> " << to_str(IsMember<scalarset_1>(u1)) << "\n\n"
      << std::flush <<
        "u1 = anon_enum     -> " << (u1 = anon_enum) << "\n"
        "u1 = scalarset_2_2 -> " << (u1 = scalarset_2_2) << "\n"
        "u1 = enum_test3    -> " << (u1 = enum_test3) << "\n"
        "u1 = enum_test1    -> " << (u1 = enum_test1) << "\n\n"
      << std::flush <<
        "e1 == enum_test1     -> " << to_str(e1 == enum_test(enum_test1)) << "\n"
        "e2 == other_enum     -> " << to_str(e2 == rand_enums(other_enum)) << "\n"
        "s1 == scalarset_1_1  -> " << to_str(s1 == scalarset_1(scalarset_1_1)) << "\n"
        "s2 == scalarset_2_1  -> " << to_str(s2 == scalarset_2(scalarset_2_1)) << "\n"
        "u1 == e1             -> " << to_str(u1 == e1) << "\n"
        "u1 == enum_test1     -> " << to_str(u1 == enum_test(enum_test1)) << "\n\n"
      << std::flush <<
        "e1 != enum_test2     -> " << to_str(e1 != enum_test(enum_test2)) << "\n"
        "e2 != final_enum     -> " << to_str(e1 != rand_enums(final_enum)) << "\n"
        "s2 != scalarset_2_2  -> " << to_str(e1 != scalarset_2(scalarset_2_2)) << "\n"
        "u1 != e2             -> " << to_str(u1 != e2) << "\n"
        "u1 != scalarset_1_1  -> " << to_str(u1 != scalarset_1(scalarset_1_1)) << "\n"
        "u1 != anon_enum      -> " << to_str(u1 != EnumType<anon_enum,1>(anon_enum)) << "\n\n"
      << std::flush;

  } catch (std::exception& ex) {
    std::cerr << "\nexception caught:\n  " << ex.what() << std::endl;
  }
  std::cout << "\n\n" << std::flush;
  return 0;
}

#endif
