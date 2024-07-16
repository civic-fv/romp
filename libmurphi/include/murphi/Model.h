#pragma once

#include "location.hh"
#include <cstddef>
#include <cstdint>
#include <gmpxx.h>
#include <iostream>
#include <memory>
#include <murphi/Decl.h>
#include <murphi/Function.h>
#include <murphi/Node.h>
#include <murphi/Ptr.h>
#include <murphi/Rule.h>
#include <vector>

#ifndef MURPHI_API_WITH_RTTI
#define MURPHI_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace murphi {

struct MURPHI_API_WITH_RTTI Model : public Node {

  // declarations, functions and rules in the order in which they appeared in
  // the source
  std::vector<Ptr<Node>> children;

  Model(const std::vector<Ptr<Node>> &children_, const location &loc_);
  virtual ~Model() = default;
  Model *clone() const;

  // Get the size of the state data in bits.
  mpz_class size_bits() const;

  void validate() const final;

  // dispatch to the appropriate traversal method (see traverse.h)
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  /* Get the number of global liveness properties in the model. Unlike
   * assumption_count, this considers the "flat" model. That is, a
   * ruleset-contained liveness property may count for more than one.
   */
  mpz_class liveness_count() const;

  /* Update the bit offset of each variable declaration in the model and reindex
   * all AST nodes.
   */
  void reindex();
};

} // namespace murphi
