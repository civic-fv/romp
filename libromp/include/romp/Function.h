#pragma once

#include "location.hh"
#include <cstddef>
#include <memory>
#include <romp/Decl.h>
#include <romp/Node.h>
#include <romp/Ptr.h>
#include <romp/Stmt.h>
#include <romp/TypeExpr.h>
#include <string>
#include <vector>

#ifndef ROMP_API_WITH_RTTI
#define ROMP_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace romp {

struct ROMP_API_WITH_RTTI Function : public Node {

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

} // namespace romp
