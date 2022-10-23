
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
#include <murphi/Expr.h>
#include <murphi/Boolean.h>
#include <murphi/Decl.h>
#include <murphi/Function.h>
#include <murphi/Ptr.h>
#include <murphi/except.h>
#include <murphi/traverse.h>
#include <string>
#include <utility>
#include <vector>
#include <map>

namespace murphi {


IsMember::IsMember(const Ptr<Expr>& designator_, const Ptr<TypeExpr>& type_value_, const location& loc_)
  : Expr(loc_), designator(designator_), type_value(type_value_) {}
IsMember* IsMember::clone() const { return new IsMember(*this); }

void IsMember::visit(BaseTraversal& visitor) { visitor.visit_ismember(*this); }
void IsMember::visit(ConstBaseTraversal& visitor) const { visitor.visit_ismember(*this); }

void IsMember::update() {
  // do nothing in current design
}

Ptr<TypeExpr> IsMember::type() const { return murphi::Boolean; }
mpz_class IsMember::constant_fold() const { throw Error("not a constant value", loc); }
bool IsMember::constant() const { return false; }
bool IsMember::is_pure() const { return true; }

void IsMember::validate_types() const {
  if (const auto _u = dynamic_cast<const ScalarsetUnion*>(designator->type().get())) {
    if (not _u->contains(*type_value))
      throw Error("IsMember will ALWAYS evaluate to false",loc);
  } else 
    throw Error("`" + designator->to_string() 
                + "` is not of type scalarset union, as IsMember expects", 
                designator->loc);
}
// this needs to be called after symbol resolution and a call to update()
void IsMember::validate() const {
  validate_types();
}

std::string IsMember::to_string() const {
  return "IsMember(" + designator->to_string() + ", " + type_value->to_string() + ')';
}


// << ------------------------------------------------------------------------------------------ >> 

SUCast::SUCast(const Ptr<TypeExpr>& target_, const Ptr<Expr>& cur_, const location& loc_)
  : UnaryExpr(cur_,loc_), target(target_) { update(); }
SUCast *SUCast::clone() const { return new SUCast(*this); }

void SUCast::visit(BaseTraversal& visitor) { visitor.visit_sucast(*this); } 
void SUCast::visit(ConstBaseTraversal& visitor) const { visitor.visit_sucast(*this); }

Ptr<TypeExpr> SUCast::type() const { return target; }
mpz_class SUCast::constant_fold() const { throw Error("not a constant value", loc); }
bool SUCast::constant() const { return false; };
// bool SUCast::is_pure() const { return true; }

void SUCast::validate() const {
  if (not rhs->type()->coerces_to(*target))
    throw Error("Can't cast/convert/coerce expr=`"
                + rhs->to_string() + "` --to-> type=`" + target->to_string() + "`", loc);
}

void SUCast::update() {
  // do nothing in current design
}

std::string SUCast::to_string() const { 
  return "(/*cast*/ " + rhs->to_string() 
          + "/* --to-> `"+ target->to_string() +"`*/)"; 
}


// << ------------------------------------------------------------------------------------------ >> 

MultisetElement::MultisetElement(const Ptr<Expr>& multiset_, const Ptr<ExprID> index_, const location& loc_)
  : Expr(loc_), index(index_), multiset(multiset_) {}
MultisetElement *MultisetElement::clone() const { return new MultisetElement(*this); }

void MultisetElement::visit(BaseTraversal& visitor) { visitor.visit_multisetelement(*this); }
void MultisetElement::visit(ConstBaseTraversal& visitor) const { visitor.visit_multisetelement(*this); }

bool MultisetElement::constant() const { return false; }

Ptr<TypeExpr> MultisetElement::type() const {
  const Ptr<TypeExpr> t = multiset->type()->resolve();
  // if we are called during symbol resolution on a malformed expression, our
  // left hand side may not be an array
  if (const auto m = dynamic_cast<const Multiset *>(t.get()))
    return m->element_type;

  throw Error("multiset element based on something that is not an multiset", loc);
}

mpz_class MultisetElement::constant_fold() const {
  throw Error("multiset element used in a constant expression", loc);
}

bool MultisetElement::is_lvalue() const { 
  // multiset element can't ever be used to change value internally
  return false;  // moved to a check in assignment
  // return multiset->is_lvalue();
}

bool MultisetElement::is_readonly() const {
  // multiset element can't ever be used to change value internally
  return true;
  // return multiset->is_readonly(); 
}

bool MultisetElement::is_pure() const { return true; }

void MultisetElement::validate() const {
  const Ptr<TypeExpr> t = multiset->type()->resolve();

  if (not isa<Multiset>(t))
    throw murphi::Error("multiset index on an expression that is not a multiset", loc);

  auto a = dynamic_cast<const Array &>(*t);

  if (!index->type()->coerces_to(*a.index_type))
    throw murphi::Error("multiset indexed using an expression of incorrect type", loc);
}
void MultisetElement::update() { 
  // do nothing but override the SUCast inserting behavior from element,
  //  since we should never allow any in-appropriate index types in the first place. 
}

std::string MultisetElement::to_string() const {
  return multiset->to_string() + "[" + index->to_string() + "]";
}


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
  if (const auto ms = dynamic_cast<const Multiset*>(multiset->type().get())) {
    decl->type = type = Ptr<Range>::make(Ptr<Number>::make(1_mpz,location()), ms->size, loc);
    decl->readonly = true;
  }
}

std::string MultisetQuantifier::to_string() const {
  return name + ":" + multiset->to_string();
}


// << ------------------------------------------------------------------------------------------ >> 

MultisetCount::MultisetCount(const MultisetQuantifier& ms_quantifier_, const Ptr<Expr>& condition_, const location& loc_)
  : Expr(loc_), ms_quantifier(ms_quantifier_), condition(condition_) 
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
                            ms->size, loc);
  // else
    assert(false && "DEV ERROR : MultisetQuantifier did not refer to a multiset!");
}
mpz_class MultisetCount::constant_fold() const { throw Error("not a constant value", loc); }
bool MultisetCount::constant() const { return false; }
bool MultisetCount::is_pure() const { return true; /* enforced by validate */ }

std::string MultisetCount::to_string() const {
  return "MultisetCount(" + ms_quantifier.to_string() + ", " + condition->to_string() + ")";
}


} //namespace murphi
