/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file SigPerm.hpp
 * 
 * @brief Implements a iterator class that can produce lists of the various permutations
 *        in the quantifiers of rumur's AST Rule's, so that we can call them in our output.
 * 
 *        Note: Note Optimized to be used in more than one file in a compilation (single file construction)
 * 
 * @date 2022/06/22
 * @version 0.1
 */

#pragma once


#include <rumur/rumur.h>
// #include "NestedError.hpp"
// #include "type_traverse.hpp"
#include "romp_def.hpp"
#include <cstddef>
#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include <sstream>

namespace romp {
class CGenerator;
class SigPerm;
struct Sig;
struct SigParam;
struct QuantExpansion;

//TODO fix this mess !!
// using vec_MTypeVals_t = ::std::vector<const ::romp::SigParam&>;
// using QuantExpansion_Iter_t = ::romp::vec_MTypeVals_t::iterator ;
// using SigParam_Iter_t = ::romp::vec_MTypeVals_t::iterator ;
// using quant_vals_cache_t = ::std::unordered_map<::std::string, const ::romp::QuantExpansion>> ;
// using quant_vals_cache_iter_t = ::romp::quant_vals_cache_t::iterator ;
// using vec_quant_vals_t = ::std::vector<const ::romp::quant_vals_cache_iter_t> ;
// using quant_vals_iter_t = ::romp::vec_quant_vals_t::iterator ;
// typedef ::std::vector<const ::romp::Sig::Param> vec_MTypeVals_t;
// typedef ::romp::vec_MTypeVals_t::iterator QuantExpansion_Iter_t;
// typedef ::romp::vec_MTypeVals_t::iterator SigParam_Iter_t;
// typedef ::std::unordered_map<::std::string, const ::romp::QuantExpansion>> quant_vals_cache_t;
// typedef ::romp::quant_vals_cache_t::iterator quant_vals_cache_iter_t;
// typedef ::std::vector<const ::romp::quant_vals_cache_iter_t> vec_quant_vals_t;
// typedef ::romp::vec_quant_vals_t::iterator quant_vals_iter_t;


// << ========================================================================================== >> 
// <<                                            Sig                                             >> 
// << ========================================================================================== >> 
#pragma region class_Sig
struct Sig {
  size_t index;
  // list/array/vector of the parameters in this signature
  const SigParam** params/* [] */;
  // std::vector<const SigParam*> params;
  // std::vector<const SigParam*>::iterator begin() const;
  // std::vector<const SigParam*>::iterator end() const;
  std::string to_string() const;
  std::string to_json() const;
  size_t size() const; // { return perm.size(); }
  std::string gen_call() const;
  // Sig(size_t index_, std::vector<const SigParam*> params_, const SigPerm& perm_);
  Sig(size_t index_, size_t params_size, const SigPerm& perm_);
  Sig(const SigPerm& perm_);
  Sig(const Sig& other); // copy constructor
  ~Sig(); // = default;
  friend bool operator == (const Sig& l, const Sig& r) ;
  friend bool operator != (const Sig& l, const Sig& r) ;
private:
  const SigPerm& perm;
  friend std::ostream& operator << (std::ostream& out, const Sig& sig);
  // friend CGenerator& CGenerator::operator << (const Sig& sig);
  // friend SigPerm::Iterator;
};
#pragma endregion class_Sig


// << ========================================================================================== >> 
// <<                                         SigParam                                           >> 
// << ========================================================================================== >> 
#pragma region class_SigParam
struct SigParam {
  const mpz_class value;
  const std::string value_str;
  const std::string str_rep;
  const std::string json_rep;
  const QuantExpansion& qe;
  const std::string& to_string() const;
  const std::string& to_json() const;
private:
  friend struct QuantExpansion;
  static const std::string to_string(const std::string& value_str, const QuantExpansion& qe);
  static const std::string to_json(const std::string& value_str, const QuantExpansion& qe, const std::string json_val_type);
  friend std::ostream& operator << (std::ostream& out, const SigParam& param);
  friend CGenerator& operator << (CGenerator& out, const SigParam& param);
};
#pragma endregion class_SigParam


// << ========================================================================================== >> 
// <<                                      QuantExpansion                                        >> 
// << ========================================================================================== >> 
#pragma region class_QuantExpansion
struct QuantExpansion {
  std::vector<const SigParam*> values;
  const rumur::Ptr<const rumur::TypeExpr> type;
  std::string type_id;
  mpz_class start;
  mpz_class stop;
  mpz_class step = 1_mpz;
  size_t size() const;
  std::vector<const SigParam*>::iterator begin() const;
  std::vector<const SigParam*>::iterator end() const;
  QuantExpansion(const rumur::Quantifier& q);
  ~QuantExpansion();
private:
  size_t _size = 0;
  void resolve_quantifier_bounds(const rumur::Quantifier& q);
  void resolve_quantifier_type(const rumur::Quantifier& q_);
};
#pragma endregion class_QuantExpansion

// << ========================================================================================== >> 
// <<                                          SigPerm                                           >> 
// << ========================================================================================== >> 
#pragma region class_SigPerm
class SigPerm {
private:

protected:
  static std::unordered_map<std::string,std::shared_ptr<const QuantExpansion>> quant_vals_cache;
  std::vector<std::shared_ptr<const QuantExpansion>> quant_vals;
  size_t _size = 1;
  

public:
  const rumur::Rule& rule; // the "ruleset" we are creating all the signatures for
  const std::string rule_type;
  const std::vector<rumur::Quantifier>& quantifiers;
  const size_t param_count;


// << ============================= Constructors & Deconstructor =============================== >> 
private:
protected:
  SigPerm(const rumur::Rule& rule_, const char* rule_type_);
public:
  SigPerm(const rumur::SimpleRule& rule_) : SigPerm(rule_, "Rule") {}
  SigPerm(const rumur::StartState& rule_) : SigPerm(rule_, "StartState") {}
  SigPerm(const rumur::PropertyRule& rule_) : SigPerm(rule_, "PropertyRule") {}
  ~SigPerm() = default;

// << =================================== Member Functions ===================================== >> 
private:
  void add_quants(const std::vector<rumur::Quantifier>& qs);

  void add_quant(const rumur::Quantifier& q) ;

  static void add_quant(const std::string& name, const rumur::Quantifier& q);
  
  // std::vector<std::vector<const SigParam&>::iterator> get_init_param_iters() const;
  std::vector<size_t> get_init_param_iters() const;

protected:
  


protected:

public:

  std::string to_string() const;
  std::string to_json() const;
  
  // << ========================================================================================== >> 
  // <<                                     SigPerm::Iterator                                      >> 
  // << ========================================================================================== >> 

  struct Iterator {
    const Sig& operator*() const ;
    const Sig* operator->() const ;
    // prefix iterator
    friend Iterator& operator ++ (Iterator&) ;
    // postfix iterator
    friend Iterator operator ++ (Iterator&, int) ;
    friend bool operator == (const Iterator& l, const Iterator& r) ;
    friend bool operator != (const Iterator& l, const Iterator& r) ;
    std::string to_string() const;
  protected:
    void increment_item();
    void increment_param_iters();
    void increment_param_iters(signed long level);
  private:
    size_t index;
    // Sig* sig_ptr;
    Sig sig;
    const SigPerm& perm;
    // std::vector<std::vector<const SigParam&>::iterator> param_iters;
    // std::vector<size_t> param_iters;
    size_t* param_iters; // dynamic array of index values for the various quantifiers for a 
  // public:
    // construct a "begin" iterator (ONLY)
    // Iterator(const SigPerm& perm_, std::vector<std::vector<const SigParam&>::iterator> param_iters_);
    // Iterator(const SigPerm& perm_, std::vector<size_t> param_iters_);
    Iterator(const SigPerm& perm_, size_t index_);
    // construct an "end" iterator (ONLY)
    Iterator(const SigPerm& perm_); // : index(perm_.size), perm(perm_) {}
  public:
    Iterator(const Iterator& other); // copy constructor
    friend SigPerm;
    friend Sig;
  public:
    // ~Iterator();
    ~Iterator(); // = default;
  };

  friend Iterator;
  friend Sig;

public:
  size_t size() const;
  Iterator begin() const;
  Iterator end() const;
};
#pragma endregion class_SigPerm


}
