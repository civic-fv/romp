/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file hash.hpp
 * 
 * @brief where the hashing objects for the murphi types are defined
 * 
 * @date 2023/01/10
 * @version 0.2
 */


#ifndef __romp__GENERATED_CODE
#include "include.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#include "types.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#endif


namespace romp {
  /**
   * @brief Cascade a hash by adding a new value
   * @tparam T the type of the object being added to the hash
   * @param seed the starting value fo a hash or the hash at this stage (modified durring call)
   * @param v the value to hash using std::hash<T>
   */
  template <class T>
  inline void hash_combine(std::size_t& seed, const T& v) {
      seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

} //namespace romp

namespace std {

template<>
struct hash<::romp::SCALAR_ENUM_t> {
  inline size_t operator () (const ::romp::SCALAR_ENUM_t val) { return static_cast<size_t>(val); }
};


template<typename T>
struct hash<::romp::BaseUndefinableType<T>> {
  inline size_t operator () (const ::romp::BaseUndefinableType<T>& val) {
    return static_cast<size_t>(val.value) + 1ul * static_cast<size_t>(val.is_defined);
  }
};


template<size_t TID, class T>
struct hash<::romp::TypeIdType<TID,T>> {
  inline size_t operator () (const ::romp::TypeIdType<TID,T>& val) {
    return std::hash<T>{}(val);
  }
};


template<>
struct hash<::romp::BooleanType> {
  inline size_t operator () (const ::romp::BooleanType& val) {
    return ((val.IsUndefined()) ? 0ul : static_cast<size_t>(val==true)+1ul);
  }
};


template<::romp::range_t LB, ::romp::range_t UB, ::romp::range_t S=(::romp::range_t)((LB<=UB) ? 1 : -1)>
struct hash<::romp::RangeType<LB,UB,S>> {
  inline size_t operator () (const ::romp::RangeType<LB,UB,S>& val) {
    return ((val.IsUndefined()) ? 0ul : val.__get_index_val());
  }
};


template<size_t EID, size_t B>
struct hash<::romp::EnumType<EID,B>> {
  inline size_t operator () (const ::romp::EnumType<EID,B>& val) {
    return static_cast<size_t>(val.__get_scalar_value()); // same as SCALAR_ENUM_t that is it's only stored data
  }
};


template<class... MEM>
struct hash<::romp::ScalarsetUnionType<MEM...>> {
  inline size_t operator () (const ::romp::ScalarsetUnionType<MEM...>& val) {
    return static_cast<size_t>(val.__get_scalar_value()); // same as SCALAR_ENUM_t that is it's only stored data
  }
};


template<typename I_t, typename E_t>
struct hash<::romp::ArrayType<I_t,E_t>> {
  inline size_t operator () (const ::romp::ArrayType<I_t,E_t>& val) {
    size_t _hash = 0ul;
    for (size_t i=0; i<I_t::__COUNT(); ++i)
      ::romp::hash_combine(_hash,val.data[i]);
    return _hash;
  }
};


template<size_t M, typename E_t>
struct hash<::romp::MultisetType<M,E_t>> {
  inline size_t operator () (const ::romp::MultisetType<M,E_t>& val) {
    std::unordered_multiset<E_t> ms;
    for (size_t i=0; i<val.occupancy; ++i)
      ms.insert(val.data[i]);
    return std::hash<std::unordered_multiset<E_t>>()(ms);
  }
};


template<size_t FID, typename... FIELDS>
struct hash<::romp::RecordType<FID,FIELDS...>> {
  inline size_t operator () (const ::romp::RecordType<FID,FIELDS...>& val) {
    return std::hash<tuple<FIELDS...>>()(val);
  }
};


/* // defined in bfs.hpp for orderings sake
template<>
struct hash<::romp::State_t> {
  inline size_t operator () (const ::romp::State_t& state) { 
    return state.__romp__model_hash();
  }
};
*/


} //namespace std
