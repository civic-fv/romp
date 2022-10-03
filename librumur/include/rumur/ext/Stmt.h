#pragma once

#include <rumur/Stmt.h>
#include <rumur/ext/TypeExpr.h>
#include <rumur/ext/Expr.h>
#include <rumur/ext/make_legacy.h>

#ifndef RUMUR_API_WITH_RTTI
#define RUMUR_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace rumur {
namespace ext {

struct RUMUR_API_WITH_RTTI MultisetAdd : public Stmt, public IExtNode<AliasStmt> {

  Ptr<Expr> value;
  Ptr<Expr> multiset;

  MultisetAdd(const Ptr<Expr>& value_, const Ptr<Expr>& multiset_, const location& loc_);
  MultisetAdd *clone() const override;
  ~MultisetAdd() = default;

  void visit(BaseTraversal &visitor) override;
  void visit(ConstBaseTraversal &visitor) const override;

  void validate() const final;
  void update() final;

  Ptr<AliasStmt> make_legacy() const;
};


struct RUMUR_API_WITH_RTTI MultisetRemove : public Stmt, public IExtNode<AliasStmt> {

  Ptr<Expr> index;
  Ptr<Expr> multiset;

  MultisetRemove(const Ptr<Expr>& index_, const Ptr<Expr>& multiset_, const location& loc_);
  MultisetRemove *clone() const override;
  ~MultisetRemove() = default;

  void visit(BaseTraversal &visitor) override;
  void visit(ConstBaseTraversal &visitor) const override;

  void validate() const final;
  void update() final;

  Ptr<AliasStmt> make_legacy() const final;
};


struct RUMUR_API_WITH_RTTI MultisetRemovePred : public Stmt, public IExtNode<AliasStmt> {

  MultisetQuantifier ms_quantifier;
  Ptr<Expr> pred;

  MultisetRemovePred(const MultisetQuantifier& ms_quantifier_, const Ptr<Expr>& pred_, const location& loc_);
  MultisetRemovePred *clone() const override;
  ~MultisetRemovePred() = default;

  void visit(BaseTraversal &visitor) override;
  void visit(ConstBaseTraversal &visitor) const override;

  void validate() const final;
  void update() final;

  Ptr<AliasStmt> make_legacy() const final;
};


}//namespace ext
}//namespace rumur