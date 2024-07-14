#pragma once

#include "location.hh"
#include <cstddef>
#include <cstdint>
#include <gmpxx.h>
#include <iostream>
#include <murphi/Expr.h>
#include <murphi/Ptr.h>
#include <murphi/TypeExpr.h>
#include <string>

#ifndef MURPHI_API_WITH_RTTI
#define MURPHI_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace murphi {

struct MURPHI_API_WITH_RTTI Number : public Expr {

  mpz_class value;

  Number() = delete;
  Number(const std::string &value_, const location &loc_);
  Number(const mpz_class &value_, const location &loc_);
  Number(const Number &) = default;
  Number(Number &&) = default;
  Number &operator=(const Number &) = default;
  Number &operator=(Number &&) = default;
  virtual ~Number() = default;
  Number *clone() const;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  bool constant() const final;
  Ptr<TypeExpr> type() const final;
  mpz_class constant_fold() const final;
  std::string to_string() const final;
  bool is_pure() const final;
};

} // namespace murphi