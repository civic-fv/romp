#pragma once

#include "location.hh"
#include <climits>
#include <cstddef>
#include <gmpxx.h>
#include <iostream>
#include <memory>
#include <murphi/Expr.h>
#include <murphi/Node.h>
#include <murphi/Ptr.h>
#include <string>
#include <utility>
#include <vector>
// #include <unordered_map>

#ifndef MURPHI_API_WITH_RTTI
#define MURPHI_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace murphi {

// Forward declare to avoid circular #include
struct TypeDecl;
struct VarDecl;

struct MURPHI_API_WITH_RTTI TypeExpr : public Node {

  id_t type_id;

  TypeExpr(const location &loc_);
  virtual ~TypeExpr() = default;

  // Whether this type is a primitive integer-like type.
  virtual bool is_simple() const;

  TypeExpr *clone() const override = 0;
  virtual mpz_class width() const;
  virtual mpz_class count() const = 0;
  virtual Ptr<TypeExpr> resolve() const;

  /* Numeric bounds of this type as valid C code. These are only valid to use on
   * TypeExprs for which is_simple() returns true.
   */
  virtual std::string lower_bound() const;  //TODO: get rid of these HACKY bounds things from rumur
  virtual std::string upper_bound() const;

  // Get a string representation of this type
  virtual std::string to_string() const = 0;

  /* Whether this type's bounds are constant. Only valid for TypeExprs for which
   * is_simple() returns true.
   */
  virtual bool constant() const;

  // can a value of this type can be assigned to or compared with a value of the
  // given type?
  bool coerces_to(const TypeExpr &other) const;
  // is the value of this type the same as the `other` type?
  bool equal_to(const TypeExpr &other) const;
  // inline bool operator == (const TypeExpr& other) const;
  // inline bool operator != (const TypeExpr& other) const;

  // Is this the type Boolean? Note that this only returns true for the actual
  // type Boolean, and not for TypeExprIDs that point at Boolean.
  virtual bool is_boolean() const;

  // Can this type possibly be used to aid with symmetry reduction?
  virtual bool is_useful() const;

protected:
  TypeExpr(id_t type_id_, const location &loc_);
  TypeExpr(const TypeExpr &) = default;
  TypeExpr &operator=(const TypeExpr &) = default;

  // static std::unordered_map<std::string,Ptr<TypeExpr>> type_mash;
  static id_t next_type_id;
  friend TypeDecl;
};

// << ------------------------------------------------------------------------------------------ >> 

struct MURPHI_API_WITH_RTTI Range : public TypeExpr {

  Ptr<Expr> min;
  Ptr<Expr> max;

  Range(const Ptr<Expr> &min_, const Ptr<Expr> &max_, const location &loc_);
  Range *clone() const;
  virtual ~Range() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  mpz_class count() const final;
  bool is_simple() const final;
  void validate() const final;

  std::string lower_bound() const final;
  std::string upper_bound() const final;
  std::string to_string() const final;
  bool constant() const final;
};

// << ------------------------------------------------------------------------------------------ >> 

struct MURPHI_API_WITH_RTTI Scalarset : public TypeExpr {

  Ptr<Expr> bound;
  std::string name; // added durring update of type decl, if ""/empty it is unnamed/un-declared

  Scalarset(const Ptr<Expr> &bound_, const location &loc_);
  Scalarset(const Ptr<Expr> &bound_, const std::string& name_, const location &loc_);
  Scalarset *clone() const;
  virtual ~Scalarset() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  mpz_class count() const final;
  bool is_simple() const final;
  void validate() const final;

  std::string lower_bound() const final;
  std::string upper_bound() const final;
  std::string to_string() const final;
  bool constant() const final;
  bool is_useful() const final;
};

// << ------------------------------------------------------------------------------------------ >> 

struct MURPHI_API_WITH_RTTI Enum : public TypeExpr {

  std::vector<std::pair<std::string, location>> members;

  // The range [unique_id, unique_id_limit) is usable by this node as
  // identifiers. Enum types need this specialization due to the way references
  // to their members are resolved (see updateASTs()).
  size_t unique_id_limit = SIZE_MAX;

  Enum(const std::vector<std::pair<std::string, location>> &members_,
       const location &loc_);
  Enum *clone() const;
  virtual ~Enum() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  mpz_class count() const final;
  bool is_simple() const final;
  void validate() const final;

  std::string lower_bound() const final;
  std::string upper_bound() const final;
  std::string to_string() const final;
  bool constant() const final;
  bool is_boolean() const final;
};

// << ------------------------------------------------------------------------------------------ >> 

struct MURPHI_API_WITH_RTTI Record : public TypeExpr {

  std::vector<Ptr<VarDecl>> fields;

  Record(const std::vector<Ptr<VarDecl>> &fields_, const location &loc_);
  Record *clone() const;
  virtual ~Record() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  mpz_class width() const final;
  mpz_class count() const final;
  std::string to_string() const final;
};

// << ------------------------------------------------------------------------------------------ >> 

struct MURPHI_API_WITH_RTTI Array : public TypeExpr {

  Ptr<TypeExpr> index_type;
  Ptr<TypeExpr> element_type;

  Array(const Ptr<TypeExpr> &index_type_, const Ptr<TypeExpr> &element_type_,
        const location &loc_);
  Array *clone() const;
  virtual ~Array() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  mpz_class width() const final;
  mpz_class count() const final;
  void validate() const;
  std::string to_string() const;
  bool is_useful() const;
};

// << ------------------------------------------------------------------------------------------ >> 

struct MURPHI_API_WITH_RTTI TypeExprID : public TypeExpr {

  std::string name;
  Ptr<TypeDecl> referent;

  TypeExprID(const std::string &name_, const Ptr<TypeDecl> &referent_,
             const location &loc_);
  TypeExprID *clone() const;
  virtual ~TypeExprID() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  mpz_class width() const final;
  mpz_class count() const final;
  bool is_simple() const final;
  Ptr<TypeExpr> resolve() const final;
  void validate() const final;
  bool is_useful() const final;

  void update() final;

  std::string lower_bound() const final;
  std::string upper_bound() const final;
  std::string to_string() const final;
  bool constant() const final;
};


// << ------------------------------------------------------------------------------------------ >> 
// everything below here is implemented in src/ext_TypeExpr.h 
// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI ScalarsetUnion : public TypeExpr {

  // the list of types to union
  std::vector<Ptr<TypeExpr>> members;
  std::string name; // added durring update of type decl, if ""/empty it is unnamed/un-declared

  ScalarsetUnion(const std::vector<Ptr<TypeExpr>>& members_, const location& loc_);
  ScalarsetUnion(const std::vector<Ptr<TypeExpr>>& members_, 
                 const std::string& name_, const location& loc_);
  ScalarsetUnion *clone() const;
  virtual ~ScalarsetUnion() = default;

  void visit(BaseTraversal& visitor);
  void visit(ConstBaseTraversal& visitor) const;

  std::string lower_bound() const final;
  std::string upper_bound() const final;

  mpz_class count() const final;
  void update() final;
  void validate() const final;
  bool is_useful() const final;
  std::string to_string() const final;

  // return true if this union contains the specified type
  bool contains(const TypeExpr &other) const;
};

// << ------------------------------------------------------------------------------------------ >> 

struct MURPHI_API_WITH_RTTI Multiset : public TypeExpr {

  Ptr<Expr> size;
  Ptr<TypeExpr> element_type;

  Multiset(const Ptr<Expr>& size_, const Ptr<TypeExpr>& element_type_, const location& loc_);
  Multiset *clone() const;
  ~Multiset() = default;

  void visit(BaseTraversal& visitor);
  void visit(ConstBaseTraversal& visitor) const;

  mpz_class width() const final;
  mpz_class count() const final;
  void validate() const;
  std::string to_string() const;
  bool is_useful() const;

  void update() final;
};

} // namespace murphi
