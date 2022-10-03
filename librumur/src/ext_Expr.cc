
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
#include <rumur/Boolean.h>
#include <rumur/Decl.h>
#include <rumur/ext/Expr.h>
#include <rumur/Function.h>
#include <rumur/Ptr.h>
#include <rumur/ext/TypeExpr.h>
#include <rumur/except.h>
#include <rumur/ext/traverse.h>
#include <string>
#include <utility>
#include <vector>
#include <map>

namespace rumur {
namespace ext {

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
  struct MakeRanges : public ConstExtTypeTraversal {
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
  // - not necessary since the change to the IExtNode and make_legacy design
  // validate_types();
  // if (const auto _u = dynamic_cast<const ScalarsetUnion*>(designator.type().get())) {
  //   r = make_ranges(_u,*type);
  //   // build the Exprs
  //   auto _build [&](SubRangeSet::_Range* r, Or& p_expr) -> void {
  //     if (r == nullptr) // safety case: def end of expr
  //       return;
  //     p_expr.lhs = Ptr<And>::make(
  //       Ptr<Leq>::make(Ptr<Number>::make(r->min), designator, loc),
  //       Ptr<Leq>::make(designator, Ptr<Number>::make(r->max), loc),
  //       loc
  //     );
  //     if (r->next == nullptr) { // base case: end of expr
  //       p_expr.rhs = rumur::False;
  //       return;
  //     } // else  // case: more ranges to insert into check
  //     p_expr.rhs = Ptr<Or>::make(nullptr,nullptr,loc);
  //     _build(r->next,_rhs);
  //   };
  //   if (ranges.range_head == nullptr)
  //     throw Error("IsMember use error : `" + type->to_string() + "` "
  //                 "has no intersection with the type of `"
  //                 + designator->to_string() +"` !", 
  //                 loc);
  //   _build(r.ranges.range_head, *this);
  // } else 
  //   assert(false && "DEV ERROR : should be unreachable (work done in validate_types)");
}

Ptr<TypeExpr> IsMember::type() const { return rumur::Boolean; }
mpz_class SUCast::constant_fold() const { throw Error("not a constant value", loc); }
bool SUCast::constant() const { return false; };

void IsMember::validate_types() const {
  struct ValidateTypes : public ConstExtTypeTraversal {
    Ptr<ScalarsetUnion> _u;
    ValidateTypes(ScalarsetUnion*_u_) : _u(_u_) {}
    bool _contains(std::string name) {
      return (_u->members_exp.find(name) != _u->members_exp.end());
    }
    void visit_array(const Array& n) { throw Error("Arrays cant be members of scalarset unions!",n.loc); }
    void visit_enum(const Enum& n) {
      for (const auto mp : e.members)
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

Ptr<Or> IsMember::make_legacy() const {
  validate_types();
  if (const auto _u = dynamic_cast<const ScalarsetUnion*>(designator.type().get())) {
    auto _or = Ptr<Or>::make(nullptr,nullptr,loc);
    r = make_ranges(_u,*type);
    // build the Exprs
    auto _build [&](SubRangeSet::_Range* r, Or& p_expr) -> void {
      if (r == nullptr) // safety case: def end of expr
        return;
      p_expr.lhs = Ptr<And>::make(
        Ptr<Leq>::make(Ptr<Number>::make(r->min), designator, loc),
        Ptr<Leq>::make(designator, Ptr<Number>::make(r->max), loc),
        loc
      );
      if (r->next == nullptr) { // base case: end of expr
        p_expr.rhs = rumur::False;
        return;
      } // else  // case: more ranges to insert into check
      p_expr.rhs = Ptr<Or>::make(nullptr,nullptr,loc);
      _build(r->next,_rhs);
    };
    if (ranges.range_head == nullptr)
      throw Error("IsMember use error : `" + type->to_string() + "` "
                  "has no intersection with the type of `"
                  + designator->to_string() +"` !", 
                  loc);
    _build(r.ranges.range_head, *_or);
    return _or;
  } // else 
    assert(false && "DEV ERROR : should be unreachable (work done in validate_types)");
}

// << ------------------------------------------------------------------------------------------ >> 

SUCast::SUCast(const Ptr<TypeExpr> &target_, const Ptr<TypeExpr> &cur_, const location &loc_)
  : Add(cur_,nullptr,loc_), target(target_) { update(); }
SUCast *SUCast::clone() const { return new SUCast(*this); }

void SUCast::visit(BaseTraversal& visitor) { visitor.visit_sucast(*this); } 
void SUCast::visit(ConstBaseTraversal& visitor) const { visitor.visit_sucast(*this); }

Ptr<TypeExpr> SUCast::type() const { return target; }
// void SUCast::pre_validate() const {  
//   if (not lhs->type()->coerces_to(*target))
//     throw Error("Can't cast/convert/coerce expr=`"
//                 + rhs->to_string() + "` --to-> type=`" + target->to_string() "`", loc);
// }
mpz_class SUCast::constant_fold() const { throw Error("not a constant value", loc); }
bool SUCast::constant() const { return false; };
void SUCast::validate() const {
  if (not lhs->type()->coerces_to(*target))
    throw Error("Can't cast/convert/coerce expr=`"
                + rhs->to_string() + "` --to-> type=`" + target->to_string() "`", loc);
}

// mpz_class ScalarsetUnion::get_conv_modifier_su(const Scalarset& from, const ScalarsetUnion& to) {
//   assert(to.members_exp.find(from.name) != to.members_exp.end()
//          && "DEV ERROR : assert valid cast (should be checked with contains call before)");
//   return to.members_exp[from.name].min;
// }
// mpz_class ScalarsetUnion::get_conv_modifier_us(const ScalarsetUnion& from, const Scalarset& to) {
//   return -1_mpz * ScalarsetUnion::get_conv_modifier_su(to,from);
// }
// mpz_class ScalarsetUnion::get_conv_modifier_eu(const Enum& from, const ScalarsetUnion& to) {
//   assert(to.members_exp.find("_enum_"+from.members[0].first) != to.members_exp.end()
//          && "DEV ERROR : assert valid cast (should be checked with contains call before)");
//   return to.members_exp["_enum_"+from.members[0].first].min;
// }
// mpz_class ScalarsetUnion::get_conv_modifier_ue(const ScalarsetUnion& from, const Enum& to) {
//   return -1_mpz * ScalarsetUnion::get_conv_modifier_eu(to,from);
// }
// mpz_class ScalarsetUnion::get_conv_modifier(const TypeExpr& from, const TypeExpr& to) {
//   if (const auto to_u = dynamic_cast<const ScalarsetUnion*>(&to)) {
//     if (const auto from_s = dynamic_cast<const Scalarset*>(&from)) {
//       // thanks to the coercion check in pre_validate, 
//       //  we can treat scalarsets and unions the same for the from parameter,
//       //  when the to property is know to be a union type.
//       return ScalarsetUnion::get_conv_modifier_su(*from_s, *to_u);
//     } else if (const auto from_e = dynamic_cast<const Enum*>(&from)) {
//       return ScalarsetUnion::get_conv_modifier_eu(*from_e, *to_u);
//     } // else 
//       assert(false && "DEV ERROR : SUCast coming from incompatible type AND not caught earlier! (1)");
//   } else if (const auto to_s = dynamic_cast<const Scalarset*>(&to)) {
//     if (const auto from_u = dynamic_cast<const ScalarsetUnion*>(&from)) {
//       return ScalarsetUnion::get_conv_modifier_us(*from_u, *to_s);
//     } // else
//       assert(false && "DEV ERROR : SUCast coming from incompatible type AND not caught earlier! (2)")
//   } else if (const auto to_e = dynamic_cast<const Enum*>(&to)) {
//     if (const auto from_u = dynamic_cast<const ScalarsetUnion*>(&from)) {
//       return ScalarsetUnion::get_conv_modifier_ue(*from_u, *to_e);
//     } // else
//       assert(false && "DEV ERROR : SUCast coming from incompatible type AND not caught earlier! (3)")
//   }
// }

void SUCast::update() {
  // NOt necessary since change to ExtNode and make_legacy design
  // pre_validate();
  // rhs = Ptr<Number>::make(get_conv_modifier(
  //                           *rhs->type(), 
  //                           *target->resolve()
  //                         ), loc);
}

std::string SUCast::to_string() const { 
  return "(/*cast*/ " + lhs->to_string() 
          + "/* --to-> `" target->to_string() "`*/)"; 
}

Ptr<Expr> _get_bound(const TypeExpr& t) {
  struct Bound : ConstExtTypeTraversal {
    Ptr<Expr> res = nullptr;
    void visit_array(const Array& n) {}
    void visit_enum(const Enum& n) { res = Ptr<Number>::make(n.count(),location()); }
    void visit_multiset(const Multiset& n) {}
    void visit_range(const Range& n) {}
    void visit_record(const Record& n) {}
    void visit_scalarset(const Scalarset& n) { res = n.bound; }
    void visit_scalarsetunion(const ScalarsetUnion& n) {}
    void visit_typeexprid(const TypeExprID& n) { dispatch(*n.resolve()); }
  };
  Bound b;
  b.dispatch(t);
  return b.res;
}

Ptr<Expr> _get_modifier_uu(const ScalarsetUnion& from, const ScalarsetUnion& to, Ptr<Expr>& val) {
  if (from.abs_equal_to(to))
    return val;
  std::function<Ptr<Expr>(typeof(from.members.begin())&, Ptr<Expr>)> _gen;
  _gen = [&](typeof(from.members.begin())& i, Ptr<Expr> bound) -> Ptr<Expr> {
    if (i == from.members.end()) return Ptr<Number>(from.count()+1_mpz,loation()); // else make it out of range
    auto _bound = _get_bound(**i);
    return Ptr<Ternary>(/* complicated part */,
                        )
  }; 
  return _gen(from.begin(), Ptr<Number>::make(0_mpz,location()));
}
Ptr<Expr> _get_modifier_tu(const TypeExpr& from, const ScalarsetUnion& to, Ptr<Expr>& val) {}
Ptr<Expr> _get_modifier_fu(const ScalarsetUnion& from, const TypeExpr& to, Ptr<Expr>& val) {}

Ptr<Expr> _get_modifier(const TypeExpr& from, const TypeExpr& to, Ptr<Expr>& val) {
  if (const auto _fu = dynamic_cast<const ScalarsetUnion*>(&from)) {
    if (const auto _tu = dynamic_cast<const ScalarsetUnion*>(&to))
      return _get_modifier_uu(*_fu,*_tu, val);
    return _get_modifier_fu(*_fu,to, val);
  } else if (const auto _tu = dynamic_cast<const ScalarsetUnion*>(&to)) {
    return _get_modifier_tu(from,*_tu, val);
  }
  assert(false 
        && "DEV ERROR : SUCast neither type was a union "
           "(should be unreachable (caught by validate, or before injected into AST))");
}

Ptr<Ternary> SUCast::make_legacy() const {
  return Ptr<Ternary>::make(Ptr<IsUndefined>::make(lhs,loc),
                            Ptr<Number>::make(0_mpz,location()),
                            Ptr<Add>::make(lhs,
                                           _get_modifier(lhs->type(),target, lhs)
                                            loc), 
                            loc);
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
    throw rumur::Error("multiset index on an expression that is not a multiset", loc);

  auto a = dynamic_cast<const Array &>(*t);

  if (!index->type()->coerces_to(*a.index_type))
    throw rumur::Error("multiset indexed using an expression of incorrect type", loc);
}
void MultisetElement::update() { 
  // do nothing but override the SUCast inserting behavior from element,
  //  since we should never allow any in-appropriate index types in the first place. 
}

// std::string MultisetElement::to_string() const {
//   return array->to_string() + "[" + index->to_string() + "]";
// }

Ptr<Element> MultisetElement::make_legacy() const {
  return Ptr<Element>::make(array, index, loc);
}

// << ------------------------------------------------------------------------------------------ >> 

// /**
//  * Check to see if a MultisetElement swap is valid
//  */
// bool valid_ms_access(const MultisetQuantifier& mq, const Element& e) {
//   if (mq.designator->type()->equal_to(e->array->type())) { // if it's appropriate to convert at this time types will be equal
//     if (const auto _i = dynamic_cast<const ExprID*>(e->index.get())) {
//       return (_i->name == mq.name && mq.decl->type->equal_to(_i->type())
//           /* && mq.designator->to_string() == e->array->to_string() */); // <-- if nothing else works uncomment this
//       // this logic needs to be improved 
//       //  to ensure you don't access a multiset that hasn't been checked for a defined value 
//       //  at the specified location.
//     }
//     throw Error("you can only access a multiset element with a current scope specific location specifier", e->index->loc);
//   }
//   return false;
// }

// Ptr<Expr> MultisetElement::convert_elements(const MultisetQuantifier& mq, const Ptr<Expr>& expr) {
//   // would have loved to do this with a traverser but recursively rebuilding with a traverser is convoluted
//   //  therefore this solution is preferable. (this solution is to dynamic_cast for all direct descendents of Expr)
//   //  this operates blindly 
//   auto convert = [&](const Ptr<Expr>& _n) -> Ptr<Expr> {
//     if (_n == nullptr) return Ptr<Expr>(nullptr);
//     if (const auto _me = dynamic_cast<const MultisetElement*>(_n.get())) {
//       // if it's an already handled MultisetElement just convert internal elements as needed
//       return Ptr<MultisetElement>::make(convert(_me->array),
//                                         convert(_me->index),
//                                         _me->loc);
//     }
//     if (const auto _e = dynamic_cast<const Element*>(_n.get())) {
//       auto e = Ptr<Element>::make(convert(_e->array),
//                                   convert(_e->index),
//                                   _e->loc);
//       if (valid_ms_access(mq, *e))
//         return Ptr<MultisetElement>::make(e->array,e->index,_n->loc);
//       return e;
//     }
//     if (const auto _t = dynamic_cast<const Ternary*>(_n.get())) {
//       return Ptr<Ternary>::make(convert(_t->cond),
//                                 convert(_t->lhs),
//                                 convert(_t->rhs),
//                                 _t->loc);
//     }
//     if (const auto _b = dynamic_cast<const BinaryExpr*>(_n.get())) {
//       Ptr<BinaryExpr> b(_b->clone());
//       b->lhs = convert(_b->lhs);
//       b->rhs = convert(_b->rhs);
//       return b;
//     }
//     if (const auto _u = dynamic_cast<const UnaryExpr*>(_n.get())) {
//       Ptr<UnaryExpr> u(_u->clone());
//       u->lhs = convert(_u->lhs);
//       u->rhs = convert(_u->rhs);
//       return u;
//     }
//     if (const auto _id = dynamic_cast<const ExprID*>(_n.get())) {
//       //NOTE: might need to deal with alias decls here, but we can probs ignore
//       return Ptr<Expr>(_fid->clone());
//     }
//     if (const auto _fid = dynamic_cast<const Field*>(_n.get())) {
//       return Ptr<Expr>(_fid->clone());
//     }
//     if (const auto _fc = dynamic_cast<const FunctionCall*>(_n.get())) {
//       Ptr<FunctionCall> fc(_fc->clone());
//       for (size_t i=0; i<fc->arguments.size(); ++i)
//         fc->arguments[i] = convert(_fc->arguments[i]);
//       return fc;
//     }
//     if (const auto _ex = dynamic_cast<const Exists*>(_n.get())) {
//       Quantifier ex_q = *_ex->quantifier.clone();
//       ex_q.type = convert(ex_q.type);
//       ex_q.from = convert(ex_q.from);
//       ex_q.to = convert(ex_q.to);
//       ex_q.step = convert(ex_q.step);
//       return Ptr<Exists>::make(ex_q,
//                                convert(_ex->expr),
//                                _ex->loc);
//     }
//     if (const auto _fa = dynamic_cast<const Forall*>(_n.get())) {
//       Quantifier fa_q = *_fa->quantifier.clone();
//       fa_q.type = convert(fa_q.type);
//       fa_q.from = convert(fa_q.from);
//       fa_q.to = convert(fa_q.to);
//       fa_q.step = convert(fa_q.step);
//       return Ptr<Forall>::make(fa_q,
//                                convert(_fa->expr),
//                                _fa->loc);
//     }
//     if (const auto _mc = dynamic_cast<const MultisetCount*>(_n.get())) {
//       MultisetQuantifier mc_mq = *_mc->ms_quantifier.clone();
//       mc_mq.multiset = convert(mc_mq.multiset);
//       mc_mq.update();
//       return Ptr<MultisetCount>::make(mc_mq,
//                                       convert(_mc->condition),
//                                       _mc->loc);
//     }
//     if (const auto _im = dynamic_cast<const IsMember*>(_n.get())) {
//       return Ptr<IsMember>::make(convert(_im->designator),
//                                   _im->type,
//                                   _im->loc);
//     }
//     assert(false && "DEV ERROR : should be unreachable "
//                     "(if reachable then a direct decedent of Expr was added, but not handled)");
//   };
//   return convert(expr);
// }

// std::vector<Ptr<Stmt>> MultisetElement::convert_elements(const std::vector<MultisetQuantifier>& mq, const std::vector<Ptr<Stmt>>& body) {
//   struct StmtConverter : ConstExtStmtTraversal {
//     const std::vector<MultisetQuantifier>& mq;

//     void visit_aliasstmt(const AliasStmt &n) final {
//       for (auto &a : n.aliases)
//         dispatch(*a);
//       for (auto &s : n.body)
//         dispatch(*s);
//       n.validate();
//     }
//     void visit_assignment(const Assignment &n) final {
//       dispatch(*n.lhs);
//       dispatch(*n.rhs);
//       n.validate();
//     }
//     void visit_clear(const Clear &n) final {
//       dispatch(*n.rhs);
//       n.validate();
//     }

//     StmtConverter(const std::vector<MultisetQuantifier>& mq_) : mq(mq_) {}
//     void visit_multisetadd(const MultisetAdd& n) final {} 
//     void visit_multisetremove(const MultisetRemove& n) final {}
//     void visit_multisetremovepred(const MultisetRemovePred& n) final {}
//   };
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
    assert(ms->index_type != nullptr
            && "DEV ERROR : MultisetQuantifier's multiset has not been updated as expected yet");
    type = ms->index_type;
    decl->type = ms->index_type;
  }
}

std::string MultisetQuantifier::to_string() const {
  return name + ":" + multiset->to_string();
}

Ptr<Quantifier> MultisetQuantifier::make_legacy() const {
  assert(type != nullptr && "MultisetQuantifier was not ready to convert to Legacy!");
  return Ptr<Quantifier>(name,type,loc);
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
    throw Error("expresion does not evaluate to a boolean", pred->loc);
  if (not condition->is_pure())
    throw Error("expression is not pure", pred->loc);
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
bool MultisetCount::constant() const { return false; };

std::string MultisetCount::to_string() const {
  return "MultisetCount(" + ms_quantifier.to_string() + ", " + condition->to_string() + ")";
}

Ptr<Add> MultisetCount::make_legacy() const {
  // auto _condition = MultisetElement::convert_elements(ms_quantifier,condition);
  auto _convert = [&](Ptr<Add>& add, mpz_class i=1_mpz) -> void {
    if (i > ms_quantifier.type->count()) { // base case end of assets
      // add->rhs = Ptr<Number>::make(0_mpz,location());
      return;
    }
    add->rhs = Ptr<Add>::make(
                Ptr<Ternary>::make(
                    Ptr<IsUndefined>::make(
                      Ptr<MultisetElement>::make(
                        ms_quantifier.designator,
                        Ptr<Number>(i,location()),
                        loc),
                      loc),
                    Ptr<Number>::make(0_mpz,location()),
                    Ptr<Ternary>::make(
                      Ptr<Exists>::make(
                        *ms_quantifier.make_legacy(),
                        Ptr<And>::make(
                          Ptr<Eq>::make(
                            Ptr<ExprID>::make(
                              ms_quantifier.name, 
                              ms_quantifier.decl, 
                              ms_quantifier.loc),
                            Ptr<Number>::make(i,location()),
                            loc),
                          condition,
                          loc),
                        loc),
                      Ptr<Number>::make(1_mpz,location()),
                      Ptr<Number>::make(0_mpz,location()),
                      loc),
                    loc),
                  Ptr<Number>::make(0_mpz,location()),
                  loc);
    _convert(add->rhs,i+1);
  };
  auto res = Ptr<Add>::make(Ptr<Number>::make(0_mpz,location()),
                            Ptr<Number>::make(0_mpz,location()),
                            loc);
  _convert(res);
  return res; 
}


} //namespace ext
} //namespace rumur
