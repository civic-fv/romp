#pragma once

#include "location.hh"
#include <cstddef>
#include <iostream>
#include <memory>
#include <romp/Expr.h>
#include <romp/Node.h>
#include <romp/Ptr.h>

#ifndef ROMP_API_WITH_RTTI
#define ROMP_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace romp {

struct ROMP_API_WITH_RTTI Property : public Node {

  enum Category {
    ASSERTION,
    ASSUMPTION,
    COVER,
    LIVENESS,
  };

  Category category;
  Ptr<Expr> expr;

  Property(Category category_, const Ptr<Expr> &expr_, const location &loc_);
  Property *clone() const;
  virtual ~Property() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

} // namespace romp
