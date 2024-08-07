#include "location.hh"
#include "../../common/isa.h"
#include <cstddef>
#include <gmpxx.h>
#include <iostream>
#include <memory>
#include <murphi/Decl.h>
#include <murphi/Expr.h>
#include <murphi/Node.h>
#include <murphi/Ptr.h>
#include <murphi/except.h>
#include <murphi/traverse.h>
#include <string>

namespace murphi {

Decl::Decl(const std::string &name_, const location &loc_)
    : Node(loc_), name(name_) {}

Decl::~Decl() {}

// << ------------------------------------------------------------------------------------------ >>

ExprDecl::ExprDecl(const std::string &name_, const location &loc_)
    : Decl(name_, loc_) {}

AliasDecl::AliasDecl(const std::string &name_, const Ptr<Expr> &value_,
                     const location &loc_)
    : ExprDecl(name_, loc_), value(value_) {}

AliasDecl *AliasDecl::clone() const { return new AliasDecl(*this); }

void AliasDecl::visit(BaseTraversal &visitor) {
  visitor.visit_aliasdecl(*this);
}

void AliasDecl::visit(ConstBaseTraversal &visitor) const {
  visitor.visit_aliasdecl(*this);
}

bool AliasDecl::is_lvalue() const { return value->is_lvalue(); }

bool AliasDecl::is_readonly() const { return value->is_readonly(); }

Ptr<TypeExpr> AliasDecl::get_type() const { return value->type(); }

// << ------------------------------------------------------------------------------------------ >>

ConstDecl::ConstDecl(const std::string &name_, const Ptr<Expr> &value_,
                     const location &loc_)
    : ExprDecl(name_, loc_), value(value_) {}

ConstDecl::ConstDecl(const std::string &name_, const Ptr<Expr> &value_,
                     const Ptr<TypeExpr> &type_, const location &loc_)
    : ExprDecl(name_, loc_), value(value_), type(type_) {}

ConstDecl *ConstDecl::clone() const { return new ConstDecl(*this); }

void ConstDecl::visit(BaseTraversal &visitor) {
  visitor.visit_constdecl(*this);
}

void ConstDecl::visit(ConstBaseTraversal &visitor) const {
  visitor.visit_constdecl(*this);
}

bool ConstDecl::is_lvalue() const { return false; }

bool ConstDecl::is_readonly() const { return true; }

Ptr<TypeExpr> ConstDecl::get_type() const {

  // If this constant has an explicit type (e.g. it's an enum member), use that.
  if (type != nullptr)
    return type;

  /* If this doesn't have an explicit type, fall back on the type of the value
   * it points at. This is irrelevant for numerical constants, but important for
   * boolean constants.
   */
  return value->type();
}

void ConstDecl::validate() const {
  if (!value->constant())
    throw Error("const definition is not a constant", value->loc);
}

// << ------------------------------------------------------------------------------------------ >>

id_t TypeDecl::next_type_id = 0;

TypeDecl::TypeDecl(const std::string &name_, const Ptr<TypeExpr> &value_,
                   const location &loc_)
    : Decl(name_, loc_), value(value_), type_id(next_type_id++) {}

TypeDecl *TypeDecl::clone() const { return new TypeDecl(*this); }

void TypeDecl::visit(BaseTraversal &visitor) { visitor.visit_typedecl(*this); }

void TypeDecl::visit(ConstBaseTraversal &visitor) const {
  visitor.visit_typedecl(*this);
}

// void TypeDecl::validate() const {
//   if (isa<TypeExprID>(value) && isa<Scalarset>(value->resolve()))
//     throw Error("``Type masking'' a Scalarset or scalarset union is not supported !", loc);
// }

void TypeDecl::update() {
  // mark scalarset as a named scalarset by giving it the decl name
  if (auto _s = dynamic_cast<Scalarset*>(value.get())) {
    _s->name = name;
  } else if (auto _u = dynamic_cast<ScalarsetUnion*>(value.get())) {
    _u->name = name;
  }
}

// << ------------------------------------------------------------------------------------------ >>

VarDecl::VarDecl(const std::string &name_, const Ptr<TypeExpr> &type_,
                 const location &loc_)
    : ExprDecl(name_, loc_), type(type_) {}

VarDecl *VarDecl::clone() const { return new VarDecl(*this); }

void VarDecl::visit(BaseTraversal &visitor) { visitor.visit_vardecl(*this); }

void VarDecl::visit(ConstBaseTraversal &visitor) const {
  visitor.visit_vardecl(*this);
}

bool VarDecl::is_lvalue() const { return true; }

bool VarDecl::is_readonly() const { return readonly; }

bool VarDecl::is_in_state() const { return offset >= 0; }

mpz_class VarDecl::width() const { return type->width(); }

mpz_class VarDecl::count() const { return type->count(); }

Ptr<TypeExpr> VarDecl::get_type() const { return type; }

} // namespace murphi
