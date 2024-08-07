#pragma once

#include "location.hh"
#include <cstddef>
#include <gmpxx.h>
#include <iostream>
#include <limits>
#include <memory>
#include <murphi/Expr.h>
#include <murphi/Node.h>
#include <murphi/Ptr.h>
#include <murphi/TypeExpr.h>
#include <string>

#ifndef MURPHI_API_WITH_RTTI
#define MURPHI_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace murphi {

struct MURPHI_API_WITH_RTTI Decl : public Node {

  std::string name;

  Decl(const std::string &name_, const location &loc_);
  virtual ~Decl() = 0;

  Decl *clone() const override = 0;

protected:
  Decl(const Decl &) = default;
  Decl &operator=(const Decl &) = default;
};

struct MURPHI_API_WITH_RTTI ExprDecl : public Decl {

  ExprDecl(const std::string &name_, const location &loc_);
  virtual ~ExprDecl() = default;

  // Return true if this declaration is usable as an lvalue
  virtual bool is_lvalue() const = 0;

  /* Return true if this declaration is to a resource cannot be modified. Note
   * that this is only relevant for declarations for which is_lvalue() returns
   * true. For non-lvalue declarations, this is always true.
   */
  virtual bool is_readonly() const = 0;

  virtual Ptr<TypeExpr> get_type() const = 0;

  ExprDecl *clone() const override = 0;

protected:
  ExprDecl(const ExprDecl &) = default;
  ExprDecl &operator=(const ExprDecl &) = default;
};

struct MURPHI_API_WITH_RTTI AliasDecl : public ExprDecl {

  Ptr<Expr> value;

  AliasDecl(const std::string &name_, const Ptr<Expr> &value_,
            const location &loc_);
  AliasDecl *clone() const;
  virtual ~AliasDecl() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  bool is_lvalue() const final;
  bool is_readonly() const final;
  Ptr<TypeExpr> get_type() const final;
};

struct MURPHI_API_WITH_RTTI ConstDecl : public ExprDecl {

  Ptr<Expr> value;

  /* The type of this constant. Typically this will be NULL (untyped), but in
   * the case of enum members it will have the enum declaration as its type.
   */
  Ptr<TypeExpr> type;

  ConstDecl(const std::string &name_, const Ptr<Expr> &value_,
            const location &loc_);
  ConstDecl(const std::string &name_, const Ptr<Expr> &value_,
            const Ptr<TypeExpr> &type_, const location &loc_);
  ConstDecl *clone() const;
  virtual ~ConstDecl() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  bool is_lvalue() const final;
  bool is_readonly() const final;
  void validate() const final;
  Ptr<TypeExpr> get_type() const final;
};

struct MURPHI_API_WITH_RTTI TypeDecl : public Decl {

  Ptr<TypeExpr> value;
  id_t type_id;

  TypeDecl(const std::string &name, const Ptr<TypeExpr> &value_,
           const location &loc);
  TypeDecl *clone() const override;
  virtual ~TypeDecl() = default;

  void visit(BaseTraversal &visitor) override;
  void visit(ConstBaseTraversal &visitor) const override;

  // void validate() const final;
  void update() override;
protected:
  static id_t next_type_id;
};

struct MURPHI_API_WITH_RTTI VarDecl : public ExprDecl {

  Ptr<TypeExpr> type;

  //TODO: remove legacy rumur code
  /* Offset within the model state. This is only relevant if this is a state
   * variable. We initially set it to an invalid value and rely on
   * Model::reindex setting this correctly later.
   */
  mpz_class offset = -1;

  /* Whether this variable is a read-only reference. E.g. a non-var parameter to
   * a function or procedure.
   */
  bool readonly = false;

  VarDecl(const std::string &name_, const Ptr<TypeExpr> &type_,
          const location &loc_);
  VarDecl *clone() const;
  virtual ~VarDecl() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  mpz_class count() const;
  mpz_class width() const;

  /* Whether this variable declaration is a global; part of the state. That is,
   * not a local declaration, function parameter, etc.
   */
  bool is_in_state() const;

  bool is_lvalue() const final;
  bool is_readonly() const final;
  Ptr<TypeExpr> get_type() const final;
};

} // namespace murphi
