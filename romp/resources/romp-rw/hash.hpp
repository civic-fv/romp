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
 * @version 0.3
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
    // credit: geeks4geeks.com
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

} //namespace romp

namespace std {

template<>
struct hash<::romp::SCALAR_ENUM_t> {
  inline size_t operator () (const ::romp::SCALAR_ENUM_t val) const { return static_cast<size_t>(val); }
};


template<typename T>
struct hash<::romp::BaseUndefinableType<T>> {
  inline size_t operator () (const ::romp::BaseUndefinableType<T>& val) const {
    return static_cast<size_t>(val.value) + 1ul * static_cast<size_t>(val.is_defined);
  }
};


template<size_t TID, class T>
struct hash<::romp::TypeIdType<TID,T>> {
  inline size_t operator () (const ::romp::TypeIdType<TID,T>& val) const {
    return std::hash<T>()(val);
  }
};


template<>
struct hash<::romp::BooleanType> {
  inline size_t operator () (const ::romp::BooleanType& val) const {
    return ((val.IsUndefined()) ? 0ul : static_cast<size_t>(val==true)+1ul);
  }
};


template<::romp::range_t LB, ::romp::range_t UB, ::romp::range_t S>
struct hash<::romp::RangeType<LB,UB,S>> {
  inline size_t operator () (const ::romp::RangeType<LB,UB,S>& val) const {
    return ((val.IsUndefined()) ? 0ul : val.__get_index_val());
  }
};


template<size_t EID, size_t B>
struct hash<::romp::EnumType<EID,B>> {
  inline size_t operator () (const ::romp::EnumType<EID,B>& val) const {
    return static_cast<size_t>(val.__get_scalar_value()); // same as SCALAR_ENUM_t that is it's only stored data
  }
};

template<size_t EID, size_t B>
struct hash<::romp::ScalarsetType<EID,B>> {
  inline size_t operator () (const ::romp::ScalarsetType<EID,B>& val) const {
    return static_cast<size_t>(val.__get_scalar_value()); // same as SCALAR_ENUM_t that is it's only stored data
  }
};


template<class... MEM>
struct hash<::romp::ScalarsetUnionType<MEM...>> {
  inline size_t operator () (const ::romp::ScalarsetUnionType<MEM...>& val) const {
    return static_cast<size_t>(val.__get_scalar_value()); // same as SCALAR_ENUM_t that is it's only stored data
  }
};


template<typename I_t, typename E_t>
struct hash<::romp::ArrayType<I_t,E_t>> {
  inline size_t operator () (const ::romp::ArrayType<I_t,E_t>& val) const {
    size_t _hash = 0ul;
    for (size_t i=0; i<I_t::__COUNT(); ++i)
      ::romp::hash_combine(_hash,val.data[i]);
    return _hash;
  }
};


template<size_t M, typename E_t>
struct hash<::romp::MultisetType<M,E_t>> {
  // credit: Alex Reinking (https://stackoverflow.com/users/2137996/alex-reinking)
  // from: https://stackoverflow.com/questions/36520235/algorithm-for-hash-crc-of-unordered-multiset
  inline size_t operator () (const ::romp::MultisetType<M,E_t>& val) const {
    size_t _h = 0ul;
    std::hash<E_t> _hash;
    for (size_t i=0; i<val.occupancy; ++i)
      _h += log_pow(_hash(val.data[i]));
    return _h % UINT64_MAX;
  }
  size_t log_pow(size_t ex) const {
    size_t res = 1;
    size_t base = 0xA67; // set base to a reasonably large prime
    while (ex > 0) {
        if (ex % 2)
            res = res * base;
        base *= base;
        ex /= 2;
    }
    return res;
   }
};


template<size_t FID, typename... FIELDS>
struct hash<::romp::RecordType<FID,FIELDS...>> {
  inline size_t operator () (const ::romp::RecordType<FID,FIELDS...>& val) const {
    // return std::hash<tuple<FIELDS...>>()(val);
    size_t _h = 0ul; return _hash(val,_h);
  }
protected:
  template<size_t I>
  typename std::enable_if<(I>=sizeof...(FIELDS)),size_t>::type _hash(const ::romp::RecordType<FID,FIELDS...>& val, size_t _h) const { return _h; }
  template<size_t I=0>
  typename std::enable_if<(I<sizeof...(FIELDS)),size_t>::type _hash(const ::romp::RecordType<FID,FIELDS...>& val, size_t _h) const {
    ::romp::hash_combine(_h,std::get<I>(val.data));
    return _hash<I+1>(val,_h);
  }
};


/* // defined in bfs.hpp for orderings sake
template<>
struct hash<::romp::State_t> {
  inline size_t operator () (const ::romp::State_t& state) const {
    return state.__romp__model_hash();
  }
};
*/


} //namespace std