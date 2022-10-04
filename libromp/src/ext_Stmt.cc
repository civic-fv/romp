
#include <romp/Stmt.h>
#include <romp/traverse.h>
#include <romp/except.h>


namespace romp {


MultisetAdd::MultisetAdd(const Ptr<Expr>& value_, const Ptr<Expr>& multiset_, const location& loc_)
  : Stmt(loc_), multiset(multiset_), value(value_) {}
MultisetAdd *MultisetAdd::clone() const { return new MultisetAdd(*this); }

void MultisetAdd::visit(BaseTraversal &visitor) { visitor.visit_multisetadd(*this); }
void MultisetAdd::visit(ConstBaseTraversal &visitor) const { visitor.visit_multisetadd(*this); }

void MultisetAdd::validate() const {
  if (const auto ms = dynamic_cast<const Multiset*>(multiset->type().get())) {
    if (not value->type()->coerces_to(*ms->element_type))
      throw Error("the type of expr=`" + value->to_string() +"` can't be coerced to type=`"
                  + ms->element_type->to_string() +"`", value->loc);
  } else
    throw Error("not of a multiset type as expected", multiset->loc);
}
void MultisetAdd::update() {
  // nothing to do here
}



// << ------------------------------------------------------------------------------------------ >> 

MultisetRemove::MultisetRemove(const Ptr<Expr>& index_, const Ptr<Expr>& multiset_, const location& loc_)
  : Stmt(loc_), index(index_), multiset(multiset_) {}
MultisetRemove *MultisetRemove::clone() const { return new MultisetRemove(*this); }

void MultisetRemove::visit(BaseTraversal &visitor) { visitor.visit_multisetremove(*this); }
void MultisetRemove::visit(ConstBaseTraversal &visitor) const { visitor.visit_multisetremove(*this); }

void MultisetRemove::validate() const {
  if (const auto ms = dynamic_cast<const Multiset*>(multiset->type().get())) {
    if (not index->type()->equal_to(*ms->index_type))
      throw Error("index not of valid type for specified multiset", index->loc);
  } else
    throw Error("not of a multiset type as expected", multiset->loc);
}
void MultisetRemove::update() {
  // nothing to do here with current design
}

// << ------------------------------------------------------------------------------------------ >> 


MultisetRemovePred::MultisetRemovePred(const MultisetQuantifier& ms_quantifier_, const Ptr<Expr>& pred_, const location& loc_)
  : Stmt(loc_), ms_quantifier(ms_quantifier_), pred(pred_) {}
MultisetRemovePred *MultisetRemovePred::clone() const { return new MultisetRemovePred(*this); }

void MultisetRemovePred::visit(BaseTraversal &visitor) { visitor.visit_multisetremovepred(*this); }
void MultisetRemovePred::visit(ConstBaseTraversal &visitor) const { visitor.visit_multisetremovepred(*this); }

void MultisetRemovePred::validate() const {
  if (not pred->is_boolean())
    throw Error("expresion does not evaluate to a boolean", pred->loc);
  if (not pred->is_pure())
    throw Error("expression is not pure", pred->loc);
}
void MultisetRemovePred::update() {
  // pred = MultisetElement::convert_elements(ms_quantifier,pred); // moved to symbol-resolver disambiguate
}



} //namespace romp
