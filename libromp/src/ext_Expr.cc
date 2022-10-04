
#include "../../common/isa.h"
#include "location.hh"
#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <gmpxx.h>
#include <iostream>
#include <limits>
#include <memory>
#include <romp/Expr.h>
#include <romp/Boolean.h>
#include <romp/Decl.h>
#include <romp/Function.h>
#include <romp/Ptr.h>
#include <romp/except.h>
#include <string>
#include <utility>
#include <vector>
#include <map>

namespace romp {


struct SubRangeSet {
  struct _Range {
    _Range* prev;
    mpz_class min;
    mpz_class max;
    _Range* next;
  };
  SubRangeSet(const mpz_class& abs_min_,const mpz_class& abs_max_)
    : abs_min(abs_min_), abs_max(abs_max_), range_head(nullptr) {}
  mpz_class abs_min;
  mpz_class abs_max;
  _Range* range_head = nullptr;
  void insert(mpz_class min, mpz_class max) {
    min = ((min <= abs_min) ? abs_min : min);
    max = ((max >= abs_max) ? abs_max : max);
    if (range_head == nullptr) {  // base case: empty
      range_head = new _Range{nullptr, min, max, nullptr};
      return;
    }
    _Range* range = _insert(range_head, min,max);
    _span(range->next, min,max, range);  // never call with a node you don't want to loose!!
  }
  struct iterator {
    _Range* iter;
    _Range& operator*() const { return *iter; }
    _Range* operator->() const { return iter; }
    friend iterator& operator ++ (iterator& i) { i.iter = i.iter->next; return i; }
    friend iterator operator ++ (iterator& i, int v) { iterator cpy{i.iter}; ++i; return cpy; }
    friend bool operator == (const iterator& l, const iterator& r) { return l.iter == r.iter; }
    friend bool operator != (const iterator& l, const iterator& r) { return l.iter != r.iter; }
  };
  iterator begin() { return iterator{range_head}; }
  iterator end() { return iterator{nullptr}; }
protected:
  _Range* _insert(_Range* r, mpz_class& min, mpz_class& max) { // forward (r never null)
    if (min > r->max) { // case: r comes before range
      auto _r = new _Range{r,min,max,r->next};
      r->next = _r;
      return _r;
    }
    if (min >= r->min) {  // case: r overlaps with range // also case: r->max == min
      if (r->max >= max) // sub-case: r contains all of our range
        max = r->max;   // update max
      return r;
    }
    if (r->next == nullptr)
      return new _Range{r,min,max,nullptr};
    return _insert(r->next, min,max);
  }
  void _span(_Range* r, mpz_class& min, mpz_class& max, _Range* range) { // forward (r can be null); !! trims ALL nodes it explores !!
    if (r == nullptr) // base case: END OF RANGE LIST
      return;
    if (max < r->min) // base case: NO OVERLAP
      return;  // do not trim r
    if (max >= r->min) { // case: r overlaps with range
      range->max = r->max; // update with current range with values from this overlapping range
      range->next = r->next;
    }
    if (max > r->max) // case: range completely overlaps with r
      _span(r->next, min,max, range);  // check next range for overlap
    delete r; // trim r
  }
};

SubRangeSet make_ranges(const ScalarsetUnion* u, const TypeExpr& type) {
  struct MakeRanges : public ConstTypeTraversal {
    SubRangeSet ranges;
    const Ptr<ScalarsetUnion> _u;
    MakeRanges(const ScalarsetUnion& _u_) : _u(_u_), ranges(0_mpz,_u->count()) {}
    bool _try_insert(std::string name) {
      auto _m = _u->members_exp.find(name);
      if (_m != _u->members_exp.end()) {
        ranges.insert(_m->second.min,_m->second.max);
        return true;
      }
      return false;
    }
    void visit_array(const Array& n) { assert(false && "Array should be unreachable"); }
    void visit_enum(const Enum& n) {
      for (const auto mp : n.members)
          _try_insert("_enum_"+mp.first);
    }
    void visit_multiset(const Multiset& n) { assert(false && "Multiset should be unreachable"); }
    void visit_range(const Range& n) { assert(false && "Range should be unreachable"); }
    void visit_record(const Record& n) { assert(false && "Record should be unreachable"); }
    void visit_scalarset(const Scalarset& n) { 
      throw Error("scalarsets must be defined with a name to be a member of a union!",n.loc); 
    }
    void visit_scalarsetunion(const ScalarsetUnion& n) {
      for (const auto m : n.members)
        dispatch(*m);
    }
    void visit_typeexprid(const TypeExprID& n) {
      if (not _try_insert(n.referent->name))
        dispatch(*n.resolve());
    }
  };
  MakeRanges r(*u);
  r.dispatch(type);
  return r.ranges;
}


// << ------------------------------------------------------------------------------------------ >> 


IsMember::IsMember(Ptr<Expr> designator_, Ptr<TypeExpr> type_value_, location loc_)
  : Node(loc_), designator(designator_), type_value(type_value_) {}
IsMember* IsMember::clone() { return new IsMember(*this); }

void IsMember::visit(BaseTraversal& visitor) { visitor.visit_ismember(*this); }
void IsMember::visit(ConstBaseTraversal& visitor) const { visitor.visit_ismember(*this); }

void IsMember::update() {
  // do nothing in current design
}

Ptr<TypeExpr> IsMember::type() const { return romp::Boolean; }
mpz_class IsMember::constant_fold() const { throw Error("not a constant value", loc); }
bool IsMember::constant() const { return false; };

void IsMember::validate_types() const {
  struct ValidateTypes : public ConstTypeTraversal {
    Ptr<ScalarsetUnion> _u;
    ValidateTypes(ScalarsetUnion*_u_) : _u(_u_) {}
    bool _contains(std::string name) {
      return (_u->members_exp.find(name) != _u->members_exp.end());
    }
    void visit_array(const Array& n) { throw Error("Arrays cant be members of scalarset unions!",n.loc); }
    void visit_enum(const Enum& n) {
      for (const auto mp : n.members)
          _contains("_enum_"+mp.first);
    }
    void visit_multiset(const Multiset& n) { throw Error("Multisets cant be members of scalarset unions!",n.loc); }
    void visit_range(const Range& n) { throw Error("Ranges's cant be members of scalarset unions!",n.loc); }
    void visit_record(const Record& n) { throw Error("Records's cant be members of scalarset unions!",n.loc); }
    void visit_scalarset(const Scalarset& n) { throw Error("scalarsets must be defined with a name to be a member of a union!",n.loc); }
    void visit_scalarsetunion(const ScalarsetUnion& n) {
      for (const auto m : n.members)
        dispatch(*m);
    }
    void visit_typeexprid(const TypeExprID& n) {
      if (n.referent == nullptr)
        throw Error(n.name+" was not resolved \t[dev-error]",n.loc)
      if (not _contains(n.referent->name))
        dispatch(*n.resolve());
    }
  };
  if (const auto _u = dynamic_cast<const ScalarsetUnion*>(designator.type().get())) {
    ValidateTypes _vt(_u);
    _vt.dispatch(*type_value);
  } else 
    throw Error("IsMember use error : `" + designator->to_string() 
                + "` is not of type scalarset union, as IsMember expects", 
                designator.loc)
}
// this needs to be called after symbol resolution and a call to update()
void IsMember::validate() const {
  validate_types();
}

std::string IsMember::to_string() const {
  return "IsMember(" + designator->to_string() + ", " + type->to_string() + ')';
}


// << ------------------------------------------------------------------------------------------ >> 

SUCast::SUCast(const Ptr<TypeExpr> &target_, const Ptr<TypeExpr> &cur_, const location &loc_)
  : Add(cur_,nullptr,loc_), target(target_) { update(); }
SUCast *SUCast::clone() const { return new SUCast(*this); }

void SUCast::visit(BaseTraversal& visitor) { visitor.visit_sucast(*this); } 
void SUCast::visit(ConstBaseTraversal& visitor) const { visitor.visit_sucast(*this); }

Ptr<TypeExpr> SUCast::type() const { return target; }
mpz_class SUCast::constant_fold() const { throw Error("not a constant value", loc); }
bool SUCast::constant() const { return false; };
void SUCast::validate() const {
  if (not lhs->type()->coerces_to(*target))
    throw Error("Can't cast/convert/coerce expr=`"
                + rhs->to_string() + "` --to-> type=`" + target->to_string() "`", loc);
}

void SUCast::update() {
  // do nothing in current design
}

std::string SUCast::to_string() const { 
  return "(/*cast*/ " + lhs->to_string() 
          + "/* --to-> `" target->to_string() "`*/)"; 
}


// << ------------------------------------------------------------------------------------------ >> 

MultisetElement::MultisetElement(const Ptr<Expr>& designator_, const Ptr<Expr> index_, const location& loc_)
  : Element(designator_,index_,loc_) {}
MultisetElement *MultisetElement::clone() const { return new MultisetElement(*this); }

void MultisetElement::visit(BaseTraversal& visitor) { visitor.visit_multisetelement(*this); }
void MultisetElement::visit(ConstBaseTraversal& visitor) const { visitor.visit_multisetelement(*this); }

void MultisetElement::validate() const {
  const Ptr<TypeExpr> t = array->type()->resolve();

  if (not isa<Multiset>(t))
    throw romp::Error("multiset index on an expression that is not a multiset", loc);

  auto a = dynamic_cast<const Array &>(*t);

  if (!index->type()->coerces_to(*a.index_type))
    throw romp::Error("multiset indexed using an expression of incorrect type", loc);
}
void MultisetElement::update() { 
  // do nothing but override the SUCast inserting behavior from element,
  //  since we should never allow any in-appropriate index types in the first place. 
}

// std::string MultisetElement::to_string() const {
//   return array->to_string() + "[" + index->to_string() + "]";
// }


// << ------------------------------------------------------------------------------------------ >> 

MultisetQuantifier::MultisetQuantifier(const std::string& name_, const Ptr<Expr> multiset_, const location& loc_)
  : Quantifier(name_,nullptr,loc_), multiset(multiset_) {}
MultisetQuantifier *MultisetQuantifier::clone() const { new MultisetQuantifier(*this); }

void MultisetQuantifier::visit(BaseTraversal& visitor) { visitor.visit_multisetquantifier(*this); }
void MultisetQuantifier::visit(ConstBaseTraversal& visitor) const { visitor.visit_multisetquantifier(*this); }

void MultisetQuantifier::validate() const {
  if (not isa<Multiset>(multiset->type()))
    throw Error("expected a multiset", multiset->loc);
}
void MultisetQuantifier::update() {
  if (const auto ms = dynamic_cast<const Multiset*>(multiset->type())) {
    type = ms->index_type;
    decl->type = ms->index_type;
  }
}

std::string MultisetQuantifier::to_string() const {
  return name + ":" + multiset->to_string();
}


// << ------------------------------------------------------------------------------------------ >> 

MultisetCount::MultisetCount(const MultisetQuantifier& ms_quantifier_, const Ptr<Expr>& condition_, const location& loc_)
  : Add(nullptr, nullptr, loc_), 
    ms_quantifier(ms_quantifier_), condition(condition_) 
  {}
MultisetCount *MultisetCount::clone() const { new MultisetCount(*this); }

void MultisetCount::visit(BaseTraversal& visitor) { visitor.visit_multisetcount(*this); }
void MultisetCount::visit(ConstBaseTraversal& visitor) const { visitor.visit_multisetcount(*this); }

void MultisetCount::validate() const {
  if (not condition->is_boolean())
    throw Error("expresion does not evaluate to a boolean", condition->loc);
  if (not condition->is_pure())
    throw Error("expression is not pure", condition->loc);
}
void MultisetCount::update() {
  // condition = MultisetElement::convert_elements(ms_quantifier,condition);  // moved to symbol-resolver disambiguate
}
Ptr<TypeExpr> MultisetCount::type() const {
  if (const auto ms = dynamic_cast<const Multiset*>(ms_quantifier.multiset->type().get()))
    return Ptr<Range>::make(Ptr<Number>::make(0_mpz,location()),
                            ms->size(), location());
  // else
    assert(false && "DEV ERROR : MultisetQuantifier did not refer to a multiset!");
}
mpz_class MultisetCount::constant_fold() const { throw Error("not a constant value", loc); }
bool MultisetCount::constant() const { return false; }
bool MultisetCount::is_pure() const { return true; /* enforced by validate */ }

std::string MultisetCount::to_string() const {
  return "MultisetCount(" + ms_quantifier.to_string() + ", " + condition->to_string() + ")";
}


} //namespace romp
