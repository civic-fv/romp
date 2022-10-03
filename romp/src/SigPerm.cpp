/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file SigPerm.cpp
 * 
 * @brief Implements a iterator class that can produce lists of the various permutations
 *        in the quantifiers of rumur's AST Rule's, so that we can call them in our output.
 * 
 * @date 2022/06/22
 * @version 0.1
 */

#include "SigPerm.hpp"
#include "ModelSplitter.hpp"
#include "type_traverse.hpp"
// #include "../../common/escape.h"
#include "nested_escape.hpp"

namespace romp {

  // << ========================================================================================== >> 
  // <<                                            SIG                                             >> 
  // << ========================================================================================== >> 

  // std::vector<const SigParam*>::iterator Sig::begin() const { return params.begin(); }
  // std::vector<const SigParam*>::iterator Sig::end() const { return params.end(); }
  // std::vector<const SigParam&>::iterator Sig::begin() const { return params.begin(); }
  // std::vector<const SigParam&>::iterator Sig::end() const { return params.end(); }

  // Sig::Sig(size_t index_, std::vector<const SigParam*> params_, const SigPerm& perm_)
  //   : index(index_), params(params_), perm(perm_) {}
  Sig::Sig(size_t index_, size_t params_size, const SigPerm& perm_)
    : index(index_), params(new const SigParam*[params_size+1]), perm(perm_) {}
  // Sig::Sig(size_t index_, std::vector<const SigParam&> params_, const SigPerm& perm_)
  //   : index(index_), params(params_), perm(perm_) {}

  Sig::Sig(const SigPerm& perm_) // copy constructor
    // : index(0), perm(perm_), params(nullptr) {} 
    : index(0), perm(perm_), params(0) {}

  Sig::Sig(const Sig& other)
    : index(other.index), params(new const SigParam*[other.size()]), perm(other.perm)
  {
    for (size_t i=0; i<other.size(); ++i)
      params[i] = other.params[i];
  }

  std::string Sig::to_string() const {
    if (perm.param_count > 0) {
    std::stringstream buf;
    // buf << "quantifiers(";
    std::string sep = "";
      for (int i=0; i<perm.param_count; ++i) 
        if (params[i] != nullptr) {
          buf << sep << perm.quantifiers[i].name << ":=" << nEscape(params[i]->value_str);
          // buf << sep << perm.quantifiers[i].name << ":=" << nEscape(params[i].value_str);
          sep = "; ";
        }
      // buf << ')';
    return buf.str(); 
    } else { return ""; }
  }

  std::string Sig::to_json() const {  
    if (perm.param_count > 0) {
    std::stringstream buf;
    // buf << "\"quantifiers\":";
    std::string sep = "";
      buf << '[';
      for (size_t i=0; i<perm.param_count; ++i) 
        if (params[i] != nullptr) {
          buf << sep << "{\"$type\":\"kv-pair\",\"key\":\"" << perm.quantifiers[i].name << "\",\"value\":"
                    << params[i]->to_json() << '}';
          sep = ",";
        }
      buf << ']';
      return buf.str(); 
    } else { return "[]"; /* "null"; */ }
  }

  std::string Sig::gen_call() const {
    std::stringstream out;
    out << perm.rule.name << "(";
    std::string sep;
    for (size_t i=0; i<size(); ++i) 
      if (params[i] != nullptr) {
        out << sep << *params[i];
        sep = ", ";
      }
    out << ")";
    return out.str();
  }

  size_t Sig::size() const { return perm.param_count; }

  Sig::~Sig() {
    if (params != nullptr) delete[] params;
    // while (not params.empty())
    //   params.pop_back();
  }

  /* friend */ bool operator == (const Sig& l, const Sig& r) { return  (l.perm.rule.name) ==  (r.perm.rule.name) && l.index == r.index; }
  /* friend */ bool operator != (const Sig& l, const Sig& r) { return  (l.perm.rule.name) !=  (r.perm.rule.name) || l.index != r.index; }


  // << ========================================================================================== >> 
  // <<                                         SigParam                                           >> 
  // << ========================================================================================== >> 

  const std::string& SigParam::to_string() const {return str_rep;}
  const std::string& SigParam::to_json() const {return json_rep;}

  const std::string SigParam::to_string(const std::string& value_str, const QuantExpansion& qe) { 
    return "(::" ROMP_TYPE_NAMESPACE "::" + qe.type_id + ") " + value_str; 
  }

  const std::string SigParam::to_json(const std::string& value_str, const QuantExpansion& qe, const std::string json_val_type) {
    // if (auto _tid = dynamic_cast<const rumur::TypeExprID*>(qe.type.get())) {
    //   return "{\"type\":\"" + _tid->referent->name + ": " + _tid->referent->value->to_string() + "\","
    //                 "\"value\":""\"" + value_str +"\"}";
    return "{\"$type\":\""+ nEscape(json_val_type) + "\",\"type\":\"" + nEscape(ModelSplitter::get_pretty_rep(*qe.type)) + "\",\"value\":" + value_str +"}"; 
  }

  // << ========================================================================================== >> 
  // <<                                      QuantExpansion                                        >> 
  // << ========================================================================================== >> 

  // size_t QuantExpansion::size() const { return _size.get_ui() ; }
  size_t QuantExpansion::size() const { return _size; }

  std::vector<const SigParam*>::iterator QuantExpansion::begin() const { values.begin(); }
  std::vector<const SigParam*>::iterator QuantExpansion::end() const { values.end(); }
  // std::vector<const SigParam>::iterator QuantExpansion::begin() const { values.begin(); }
  // std::vector<const SigParam>::iterator QuantExpansion::end() const { values.end(); }

  QuantExpansion::QuantExpansion(const rumur::Quantifier& q) 
    : type(q.decl->type->clone())
  {
    if (auto _tid = dynamic_cast<const rumur::TypeExprID*>(q.decl->type.get()))
      type_id = _tid->name;
    else
      throw rumur::Error("Unprocessed anonymous type found in ruleset quantifier!!\t[dev-error]",q.type->loc);
    if (q.type == nullptr)
      resolve_quantifier_bounds(q);
    else
      resolve_quantifier_type(q);
    
  }

  void QuantExpansion::resolve_quantifier_bounds(const rumur::Quantifier& q) {
    // mpz_class start_mpz, stop_mpz, step_mpz;
    try { 
      start/* _mpz */ = q.from->constant_fold();
      stop/* _mpz */ = q.to->constant_fold();
      if (q.step != nullptr)
        step/* _mpz */ = q.step->constant_fold();
    } catch (rumur::Error& er) { 
      std::throw_with_nested(rumur::Error("You can't have a Ruleset's Quantifier dependent on a variable or a subset of an Enum !!", q.loc)); 
    }
    if (not start/* _mpz */.fits_slong_p())
      throw rumur::Error("Couldn't resolve the value of the Expression.", q.from->loc);
    if (not stop/* _mpz */.fits_slong_p())
      throw rumur::Error("Couldn't resolve the value of the Expression.", q.to->loc);
    if (q.step != nullptr && not step/* _mpz */.fits_slong_p())
      throw rumur::Error("Couldn't resolve the value of the Expression (step).", q.step->loc);
    // start = start_mpz.get_ui();
    // stop = stop_mpz.get_ui();
    // if (q.step != nullptr)
    //   step = step_mpz.get_ui();
    this->values = std::vector<const SigParam*>();
    for (mpz_class i = start; i<=stop; i += step)
      values.push_back(new SigParam{
                            i,
                            i.get_str(),
                            SigParam::to_string(i.get_str(), *this),
                            "{\"$type\":\"quantifier-value\","
                              "\"type\":\"" + nEscape(q.to_string()) + "\","
                              "\"value\":" + i.get_str() +"}",
                            *this
                          });
    try {
      mpz_class tmp = ((abs(stop-start)+1_mpz)/abs(step));
      _size = tmp.get_ui();
    } catch (...) {
      std::throw_with_nested(rumur::Error("Failed to extrapolate the size of the Quantifier \t[dev-error]",q.loc));
    }
  }

  void QuantExpansion::resolve_quantifier_type(const rumur::Quantifier& q_) {
    class type_trav : public rumur::ConstBaseTypeTraversal {
      const rumur::Quantifier& q;
      QuantExpansion& qe;
    public:
      type_trav(const rumur::Quantifier& q__, QuantExpansion& parent_) 
        : q(q__), qe(parent_),
          ConstBaseTypeTraversal("Not a supported TypeExpr for bounding a quantifier (it may be undefined or too complex) !!") 
      {}
      void visit_array(const rumur::Array& n) { unsupported_traversal(n,"rumur::Array"); }
      void visit_record(const rumur::Record& n) { unsupported_traversal(n,"rumur::Record"); }
      void visit_typeexprid(const rumur::TypeExprID& n) { unsupported_traversal(n,"undefined rumur::TypeExprID");; }
      void visit_enum(const rumur::Enum& n) { 
        qe.start = 0_mpz;
        qe.stop = mpz_class(n.members.size()) - 1_mpz;
        qe.step = 1_mpz;
        qe._size = n.members.size();
        qe.values = std::vector<const SigParam*>(qe.size());
        for (int i=0; i<n.members.size(); ++i) {
          std::string val = qe.type_id + "::" + n.members[i].first;
          qe.values.push_back(new SigParam{
                                mpz_class(i),
                                val,
                                "::" ROMP_TYPE_NAMESPACE "::" + val,
                                SigParam::to_json(nEscape("\""+n.members[i].first+"\""), qe, "enum-value"),
                                // "{\"type\":\"" + qe.type_id + "\","
                                //   "\"value\":\"" + n.members[i].first + "\"}",
                                qe
                              });
        }
      }
      void visit_range(const rumur::Range& n) {
        qe.start = n.min->constant_fold();
        qe.stop = n.max->constant_fold();
        qe.step = 1_mpz;
        qe.values = std::vector<const SigParam*>(/* qe.size() */);
        for (mpz_class i = qe.start; i<=qe.stop; i += qe.step)
          qe.values.push_back(new SigParam{
                                i,
                                i.get_str(),
                                SigParam::to_string(i.get_str(), qe),
                                SigParam::to_json(i.get_str(), qe, "range-value"),
                                qe
                              });
      }
      void visit_scalarset(const rumur::Scalarset& n) {
        qe.start = 0_mpz;
        qe.stop = n.bound->constant_fold();
        qe.step = 1_mpz;
        qe.values = std::vector<const SigParam*>(/* qe.size() */);
        for (mpz_class i = qe.start; i<qe.stop; i += qe.step)
          qe.values.push_back(new SigParam{
                                i,
                                i.get_str(),
                                SigParam::to_string(i.get_str(), qe),
                                SigParam::to_json(i.get_str(), qe, "scalarset-value"),
                                qe
                              });
      }
    };
    type_trav tt(q_, *this);
    try {
      tt.dispatch(*(q_.type->resolve()));
    } catch (...) {
      std::throw_with_nested(rumur::Error("Could not resolve the bounds of the Type based Quantifier !!", q_.loc));
    }
    try {
      _size = q_.type->count().get_ui() - 1;
    } catch (...) {
      std::throw_with_nested(rumur::Error("Could not extrapolate the size of the Quantifier !!",q_.loc));
    }
  }

  QuantExpansion::~QuantExpansion() {
    for (auto _v : values)
      if (_v != nullptr)
        delete _v;
  }


  // << ========================================================================================== >> 
  // <<                                          SigPerm                                           >> 
  // << ========================================================================================== >> 

  std::unordered_map<std::string,std::shared_ptr<const QuantExpansion>> SigPerm::quant_vals_cache{};

  SigPerm::SigPerm(const rumur::Rule& rule_, const char* rule_type_) 
    : rule_type(rule_type_), rule(rule_), 
      param_count(rule_.quantifiers.size()), quantifiers(rule_.quantifiers)
  {
    quant_vals = std::vector<std::shared_ptr<const QuantExpansion>>(param_count);
    if (param_count == 0) return;
    // if (quant_vals.size() == 0) throw rumur::Error("(SigPerm) array of quantifiers did not start empty !! \t[dev-error]", rule_.loc); 
    add_quants(rule.quantifiers);
    while (quant_vals[0] == nullptr) quant_vals.erase(quant_vals.begin()); // remove leading nullptr(s)
    if (quant_vals.size() != param_count) throw rumur::Error("(SigPerm) failed to properly add all quantifiers to permutation (possibly too many nulls added) !! \t[dev-error]",rule_.loc);
    for (int i=0; i<quant_vals.size(); ++i)
      if (quant_vals[i] == nullptr) throw rumur::Error("(SigPerm) a nullptr was added to the list of quantifiers !! \t[dev-error]", rule_.loc); 
  }

  void SigPerm::add_quants(const std::vector<rumur::Quantifier>& qs) {
    for (const auto& q : qs)
      add_quant(q);
  }

  void SigPerm::add_quant(const rumur::Quantifier& q) {
    if (auto _tid = dynamic_cast<const rumur::TypeExprID*>(q.decl->type.get())) {
      auto qe_i = SigPerm::quant_vals_cache.find(_tid->referent->name);
      // const QuantExpansion& qe = qe_i->second;
      if (qe_i == SigPerm::quant_vals_cache.end()) {
        SigPerm::add_quant(_tid->name, q);
        auto tmp = SigPerm::quant_vals_cache[_tid->referent->name];
        if (tmp == nullptr) return; // avoid adding a null to the list
        quant_vals.push_back(tmp);
        this->_size *= tmp->size();
      } else {
        if (qe_i->second == nullptr) return; // avoid adding a null to the list
        quant_vals.push_back(qe_i->second);
        this->_size *= qe_i->second->size();
      }
      // quant_vals.push_back(qe);
    } else
      throw rumur::Error("Unprocessed anonymous type found in ruleset quantifier!!\t[dev-error]", q.type->loc);
  }

  void SigPerm::add_quant(const std::string& name, const rumur::Quantifier& q) {
    SigPerm::quant_vals_cache.emplace(name, new QuantExpansion(q));
    // SigPerm::quant_vals_cache.insert(std::make_pair(name, std::shared_ptr<const QuantExpansion>(new QuantExpansion(q))));
  }

  std::vector<size_t> SigPerm::get_init_param_iters() const {
    std::vector<size_t> param_iters(param_count);
    for (size_t i=0; i<param_count; ++i)
      param_iters.push_back(0);
    return param_iters;
  }
  // std::vector<std::vector<const SigParam>::iterator> SigPerm::get_init_param_iters() const {
  //   std::vector<std::vector<const SigParam>::iterator> param_iters(param_count);
  //   for (auto quant_val : quant_vals)
  //     param_iters.push_back(quant_val->begin());
  //   return param_iters;
  // }

  // size_t SigPerm::size() const { return _size.get_ui(); }
  size_t SigPerm::size() const { return _size; }
  // SigPerm::Iterator SigPerm::begin() const { return (param_count > 0) ? Iterator(*this/* , get_init_param_iters() */) : this->end(); }
  SigPerm::Iterator SigPerm::begin() const { return Iterator(*this/* , get_init_param_iters() */); }
  SigPerm::Iterator SigPerm::end() const { return Iterator(*this, _size); }

  // std::string SigPerm::to_string() const {
  // 
  // }
  


  // << ========================================================================================== >> 
  // <<                                     SigPerm::Iterator                                      >> 
  // << ========================================================================================== >> 

  // const Sig SigPerm::Iterator::operator * () const { return *sig_ptr; }
  // const Sig* SigPerm::Iterator::operator -> () const { return sig_ptr; }
  const Sig& SigPerm::Iterator::operator * () const { return sig; }
  const Sig* SigPerm::Iterator::operator -> () const { return &sig; }
  
  // prefix iterator
  SigPerm::Iterator& operator ++ (SigPerm::Iterator& it) { it.increment_item(); return it; } 
  // postfix iterator
  SigPerm::Iterator operator ++ (SigPerm::Iterator& it, int n) { SigPerm::Iterator cpy(it); ++it; return cpy; }
  /* friend */ bool operator == (const SigPerm::Iterator& l, const SigPerm::Iterator& r) { return  (l.perm.rule.name) ==  (r.perm.rule.name) && l.index == r.index; }
  /* friend */ bool operator != (const SigPerm::Iterator& l, const SigPerm::Iterator& r) { return  (l.perm.rule.name) !=  (r.perm.rule.name) || l.index != r.index; }
  
  // std::string SigPerm::Iterator::to_string() const { sig_ptr->to_string(); }
  std::string SigPerm::Iterator::to_string() const { sig.to_string(); }

  void SigPerm::Iterator::increment_item() {
    if (perm.param_count == 0) { sig.index = index = perm.size(); return; } // edge case of no quantifiers
    if (index >= perm.size() || perm.param_count == 0) return;  // we are at the end
    increment_param_iters(); 
    sig.index = ++index;
    // Sig* old = sig_ptr;
    // std::vector<const SigParam*> params(perm.param_count);
    // sig.params.clear();
    // for (size_t i=0; i<perm.param_count; ++i) {  // merged with increment_param_iters into for-loop below (manual tail recursion optimization)
    //   // params.push_back(perm.quant_vals[i]->values[param_iters[i]]);
    //   sig.params[i] = perm.quant_vals[i]->values[param_iters[i]];
    // }
    // for (auto param_i : param_iters)
    //   params.push_back(*param_i);
    // sig_ptr = new Sig(++index, params, perm);
    // delete old;
  }
  void SigPerm::Iterator::increment_param_iters() { increment_param_iters(perm.param_count-1); }
  void SigPerm::Iterator::increment_param_iters(signed long level) {
    if (level < 0) return; // base case
    auto& quant = *perm.quant_vals[level];
    size_t& ii = param_iters[level];
    if ((++ii) >= quant.size()) { // roll-over/cary or end if necessary 
      increment_param_iters(level-1);
      ii = 0ul;
    } 
#ifdef DEBUG
    auto _param = quant.values[ii];
    sig.params[level] = _param;
#else
    sig.params[level] = quant.values[ii];
#endif
    // if (level > perm.param_count) throw rumur::Error("SigPerm::Iterator tried to iterate too far \t[dev-error]",perm.rule.loc);
    // if (level <= 0) { index = perm.size(); return; }
    // param_iters[level-1]++;
    // if (param_iters[level-1] < perm.quant_vals[level-1]->size()) return;
    // increment_param_iters(--level);
    // param_iters[level-1] = 0;
  }

  SigPerm::Iterator::Iterator(const SigPerm& perm_/* , std::vector<size_t> param_iters_ */) 
      // : index(0ul), perm(perm_), param_iters(param_iters_.size()), sig(0,perm_.param_count,perm_)
      : index(0ul), perm(perm_), param_iters(new size_t[perm_.param_count+1]), sig(0,perm_.param_count,perm_)
    {
      // std::vector<const SigParam*> params(perm.param_count);
      for (size_t i=0; i<perm.param_count; ++i) {
        // params.push_back(perm.quant_vals[i]->values[0]);
        // sig.params.push_back(perm.quant_vals[i]->values[0]);
        sig.params[i] = perm.quant_vals[i]->values[0];
        // param_iters.push_back(0ul);
        param_iters[i] = 0ul;
      }
      return;  // <- for dbg breakpoint only
      // for (auto param_i : param_iters)
      //   params.push_back(*param_i);
      // sig_ptr = new Sig(++index, params, perm);
    }
  // SigPerm::Iterator::Iterator(const SigPerm& perm_, std::vector<std::vector<const SigParam&>::iterator> param_iters_) 
  //     : index(0ul), perm(perm_), param_iters(param_iters_)
  //   {}
  SigPerm::Iterator::Iterator(const SigPerm& perm_, size_t index_) 
    // : index(perm_.size()), perm(perm_), sig(perm_.size(), 1, perm_) {}
    : index(perm_.size()), perm(perm_), sig(perm_.size(), 1, perm_), param_iters(nullptr) {}
    // : index(perm_.size()), perm(perm_), sig(perm_.size(),std::vector<const SigParam*>(),perm_) {}
  // SigPerm::Iterator::~Iterator() { delete sig_ptr; }

  SigPerm::Iterator::Iterator(const SigPerm::Iterator& other)
    : perm(other.perm), index(other.index), sig(other.sig), param_iters(new size_t[other.perm.param_count+1])
  {
    for (size_t i=0; i<other.perm.param_count; ++i)
      param_iters[i] = other.param_iters[i];
  }

  SigPerm::Iterator::~Iterator() { if (param_iters != nullptr) delete[] param_iters; }

}
