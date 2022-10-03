
#include <rumur/ext/Stmt.h>
#include <rumur/traverse.h>
#include <rumur/except.h>


namespace rumur {
namespace ext {

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
Ptr<AliasStmt> MultisetAdd::make_legacy() const {
  std::vector<IfClause> clauses;
  if (const auto _m = dynamic_cast<const Multiset*>(multiset->type().get())) {
    auto msq_mc = MultisetQuantifier("__ms_i__", multiset, loc);
    msq_mc.update();
    mpz_class max = _m->size->constant_fold();
    for (mpz_class i=1_mpz; i<=max; ++i) {
      auto ms_el = Ptr<MultisetElement>::make(msq_mc, multiset, Ptr<Number>::make(i,location()), loc);
      clauses.push_back(
        IfClause(
          Ptr<IsUndefined>::make(ms_el, loc),
          std::vector<Ptr<Stmt>>{
            Ptr<Assignment>::make(
              ms_el,
              value,
              loc)
            },
          loc)
        );
    }
    return Ptr<AliasStmt>::make(
      std::vector<Ptr<AliasDecl>>{},
      std::vector<Ptr<Stmt>>{
        Ptr<If>::make(
          std::vector<IfClause>{
            IfClause(
              Ptr<Not>::make(
                Ptr<IsUndefined>::make(
                  value,
                  loc)
                loc),
              std::vector<Ptr<Stmt>>{
                Ptr<If>::make(
                  clauses,
                  loc)},
              loc),},
          loc)}, 
      loc);
  }
  throw Error("not a multiset", multiset->loc);
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

Ptr<AliasStmt> MultisetRemove::make_legacy() const {
  throw Error("`MultisetRemove` is not supported in legacy model-checkers! (try MultisetRemovePred instead)", loc);
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

Ptr<AliasStmt> MultisetRemovePred::make_legacy() const {
  // auto _pred = MultisetElement::convert_elements(ms_quantifier,pred);
  auto ms_el = Ptr<MultisetElement>::make(ms_quantifier,
                                          ms_quantifier.multiset,
                                          Ptr<ExprID>::make(ms_quantifier.name, 
                                                            ms_quantifier.decl, 
                                                            loc),
                                          loc);
  return Ptr<AliasStmt>::make(
    std::vector<Ptr<AliasDecl>>{},
    std::vector<Ptr<Stmt>>{
      Ptr<For>::make(
        *ms_quantifier.make_legacy(),
        std::vector<Ptr<Stmt>>{
          Ptr<If>::make(
            std::vector<IfClause>{
              IfClause(
                Ptr<And>::make(
                  Ptr<Not>::make(
                    Ptr<IsUndefined>::make(
                      ms_el,
                      loc),
                    loc),
                  pred,
                  loc),
              std::vector<Ptr<Stmt>>{
                Ptr<Undefine>::make(
                  ms_el
                  loc)
                }, loc)
            }, loc)
          }, 
        loc)
      }
    loc);
}


} //namespace ext
} //namespace rumur
