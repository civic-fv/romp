
#include <murphi/Stmt.h>
#include <murphi/traverse.h>
#include <murphi/except.h>


namespace murphi {


MultisetAdd::MultisetAdd(const Ptr<Expr>& value_, const Ptr<Expr>& multiset_, const location& loc_)
  : Stmt(loc_), value(value_), multiset(multiset_) {}
MultisetAdd *MultisetAdd::clone() const { return new MultisetAdd(*this); }

void MultisetAdd::visit(BaseTraversal &visitor) { visitor.visit_multisetadd(*this); }
void MultisetAdd::visit(ConstBaseTraversal &visitor) const { visitor.visit_multisetadd(*this); }

void MultisetAdd::validate() const {
  const auto t = multiset->type()->resolve();
  if (const auto ms = dynamic_cast<const Multiset*>(t.get())) {
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

MultisetRemove::MultisetRemove(const Ptr<ExprID>& index_, const Ptr<Expr>& multiset_, const location& loc_)
  : Stmt(loc_), index(index_), multiset(multiset_) {}
MultisetRemove *MultisetRemove::clone() const { return new MultisetRemove(*this); }

void MultisetRemove::visit(BaseTraversal &visitor) { visitor.visit_multisetremove(*this); }
void MultisetRemove::visit(ConstBaseTraversal &visitor) const { visitor.visit_multisetremove(*this); }

void MultisetRemove::validate() const {
  const auto t = multiset->type()->resolve();
  if (const auto ms = dynamic_cast<const Multiset*>(t.get())) {
    if (const auto eid = dynamic_cast<const ExprID*>(index.get())) {
      if (ms_quantifier == nullptr || not eid->is_readonly() || eid->id != ms_quantifier->name)
        throw Error("index value of the MultisetRemove operation could not be associated with a Choose rule", index->loc);
      if (not index->type()->equal_to(*ms_quantifier->type))
        throw Error("index not of valid type for specified multiset", index->loc);
    } else
      throw Error("MultisetRemove requires that the index value be an unmodified variable reference to a Choose rule", index->loc);
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



} //namespace murphi
