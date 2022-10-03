#pragma once

#include <rumur/ext/make_legacy.h>
#include <rumur/Expr.h>
#include <functional>

#ifndef RUMUR_API_WITH_RTTI
#define RUMUR_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace rumur {
namespace ext {

struct RUMUR_API_WITH_RTTI IsMember : public Expr, public IExtNode<Or> {

  Ptr<Expr> designator;
  Ptr<TypeExpr> type_value;

  IsMember(const Ptr<Expr>& designator_, const Ptr<TypeExpr>& type_value_, const location& loc_);
  IsMember* clone() const override;
  ~IsMember() = default;

  void visit(BaseTraversal& visitor) override;
  void visit(ConstBaseTraversal& visitor) const override;

  Ptr<TypeExpr> type() const override;
  mpz_class constant_fold() const override;
  bool constant() const override;
  void validate() const override;
  void update() override;

  std::string to_string() const override;

  Ptr<Or> make_legacy() const;
protected:
  void validate_types() const;
};


/**
 * @brief A built in AST element, that should never be inserted by the parser,
 *        but should be inserted by the Assignment operator when assigning into
 *        a scalarset union from a scalarset or vise versa.
 *        It is mostly used as a wrapper for an existing AST node to wrap a child in.
 *        WARNING: This is a internal AST tool only & is pretty HACKY, 
 *                 therefore it is not included directly in any traversal tool,
 *                  and will just register as an (UN-validated) Add Expr!
 *        NOTE: does NOT guarantee bounds validity when casting OUT of a union into
 *              a scalarset, enum, or even sub-union.
 *              Therefore, your implementation must perform check after operations
 *              (this can also be done without extending your implementation to support
 *                all extended syntax by: bounds checking rhs of an Assignment Stmt,
 *                and the index value in an Element Expr).
 */
struct RUMUR_API_WITH_RTTI SUCast : public UnaryExpr, public IExtNode<Ternary> {

  Ptr<TypeExpr> target; // expected to have it's symbols resolved already (HACKY)

  /**
   * @brief \b Constructor: \n Construct a new \c SUCast object.
   *        \b NOTE: all parameters are expected have their symbols resolved before construction (HACKY)
   * @param target_ The SCALARSET UNION type you wish to get to 
   * @param cur_ The expression that will have its value cast to target
   * @param loc_ The location of the parent AST that creates this as a wrapper for an expression.
   */
  SUCast(const Ptr<TypeExpr>& target_, const Ptr<Expr>& cur_, const location& loc_);
  virtual ~SUCast() = default;
  SUCast *clone() const override;
  
  void visit(BaseTraversal& visitor) override;
  void visit(ConstBaseTraversal& visitor) const override;

  Ptr<TypeExpr> type() const final;
  void validate() const final;
  void update() final;  // update is also called from constructor
  mpz_class constant_fold() const final;
  bool constant() const final;
  std::string to_string() const final;

  Ptr<Ternary> make_legacy() const final;
// protected:
//   void pre_validate() const;
};


struct RUMUR_API_WITH_RTTI MultisetQuantifier : public Quantifier, public IExtNode<Quantifier> {

  Ptr<Expr> multiset;

  MultisetQuantifier(const std::string& name_, const Ptr<Expr> multiset_, const location& loc_);
  MultisetQuantifier *clone() const override;
  ~MultisetQuantifier() = default;

  void visit(BaseTraversal& visitor) override;
  void visit(ConstBaseTraversal& visitor) const override;

  void validate() const final;
  void update() final;
  std::string to_string() const final;

  Ptr<Quantifier> make_legacy() const final;
};


/**
 * @brief The only way to access an element of a multiset.
 *        NOTE: this AST node can't produced by parsing an Murphi file, only by code after the fact
 *              (currently in the disambiguate function of the symbol-resolver)  
 */
struct RUMUR_API_WITH_RTTI MultisetElement : public Element, IExtNode<Element> {

  MultisetElement(const Ptr<Expr>& multiset_, 
                  const Ptr<Expr> index_, const location& loc_);
  MultisetElement *clone() const override;
  ~MultisetElement() = default;

  void visit(BaseTraversal& visitor) override;
  void visit(ConstBaseTraversal& visitor) const override;

  Ptr<TypeExpr> type() const final;
  void validate() const final;
  void update() final;

  std::string to_string() const final;

  Ptr<Element> make_legacy() const final;
  // static Ptr<Expr> convert_elements(const MultisetQuantifier& mq, const Ptr<Expr>& expr);
  // static std::vector<Ptr<Stmt>> convert_elements(const std::vector<MultisetQuantifier>& mq, const std::vector<Ptr<Stmt>>& body);
};


struct RUMUR_API_WITH_RTTI MultisetCount : public Expr, public IExtNode<Add> {

  MultisetQuantifier ms_quantifier;
  Ptr<Expr> condition;

  MultisetCount(const MultisetQuantifier& ms_quantifier_, const Ptr<Expr>& condition_, const location& loc_);
  MultisetCount *clone() const override;
  ~MultisetCount() = default;

  void visit(BaseTraversal& visitor) override;
  void visit(ConstBaseTraversal& visitor) const override;

  void validate() const override;
  void update() override;
  Ptr<TypeExpr> type() const override;
  mpz_class constant_fold() const override;
  bool constant() const override;

  std::string to_string() const override;

  Ptr<Add> make_legacy() const;
};

} //namespace ext
} //namespace rumur
