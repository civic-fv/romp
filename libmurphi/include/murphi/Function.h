#pragma once

#include "location.hh"
#include <cstddef>
#include <memory>
#include <murphi/Decl.h>
#include <murphi/Node.h>
#include <murphi/Ptr.h>
#include <murphi/Stmt.h>
#include <murphi/TypeExpr.h>
#include <string>
#include <vector>

#ifndef MURPHI_API_WITH_RTTI
#define MURPHI_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace murphi {

struct MURPHI_API_WITH_RTTI Function : public Node {

  std::string name;
  std::vector<Ptr<VarDecl>> parameters;
  Ptr<TypeExpr> return_type;
  std::vector<Ptr<Decl>> decls;
  std::vector<Ptr<Stmt>> body;

  Function(const std::string &name_,
           const std::vector<Ptr<VarDecl>> &parameters_,
           const Ptr<TypeExpr> &return_type_,
           const std::vector<Ptr<Decl>> &decls_,
           const std::vector<Ptr<Stmt>> &body_, const location &loc_);
  virtual ~Function() = default;
  Function *clone() const;
  void validate() const final;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  // is this function side effect free?
  bool is_pure() const;

  // does this function contain calls to itself?
  bool is_recursive() const;
};

} // namespace murphi
