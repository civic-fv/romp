#pragma once

#include <rumur/ext/make_legacy.h>
#include <rumur/TypeExpr.h>
#include <unordered_map>
#include <unordered_set>

#ifndef RUMUR_API_WITH_RTTI
#define RUMUR_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace rumur {
namespace ext {

//predecl
struct IsMember;
struct SUCast;


struct RUMUR_API_WITH_RTTI ScalarsetUnionMember {
  Ptr<TypeExpr> value;
  mpz_class min;
  mpz_class max;
};


struct RUMUR_API_WITH_RTTI ScalarsetUnion : public TypeExpr, public IExtNode<Scalarset> {

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

  mpz_class count() const override;
  std::string upper_bound() const override;
  std::string lower_bound() const override;

  void update() override;
  void validate() const override;
  bool is_useful() const override;
  bool contains(const TypeExpr &other) const;
  std::string to_string() const override;

  // unlike equal_to this returns true only if the other ScalarsetUnion are functionally the same
  //  (aka view the union as a flattened ordered set
  //    (flattened means enum groupings don't matter, just order of appearance in the union))
  bool abs_equal_to(const ScalarsetUnion& other) const;

  Ptr<Scalarset> make_legacy() const;

// private:
  /// map of the NAME of a scalarset or single Enum value in this union
  /// NOTE: this only has a value after symbol-resolution and a call to `update()`
  /// WARNING: meant for implementing legacy code adaptations and the contains method ONLY!
  ///          do not use in your implementation unless you know what you are doing,
  ///          it gets overwritten every time `update()` is called.
  // std::unordered_map<std::string,ScalarsetUnionMember> members_exp;
  // friend ::rumur::ext::SUCast;
  // friend ::rumur::ext::IsMember;
  // some helpful tools for converting to legacy AST
  // static mpz_class get_conv_modifier(const TypeExpr& from, const TypeExpr& to);
  // static mpz_class get_conv_modifier_su(const Scalarset& from, const ScalarsetUnion& to);
  // static mpz_class get_conv_modifier_us(const ScalarsetUnion& from, const Scalarset& to);
  // static mpz_class get_conv_modifier_eu(const Enum& from, const ScalarsetUnion& to);
  // static mpz_class get_conv_modifier_ue(const ScalarsetUnion& from, const Enum& to);
protected:
  Ptr<Add> gen_legacy_bound(std::unordered_set<std::string>& handled) const;
};


struct RUMUR_API_WITH_RTTI Multiset : public Array, IExtNode<Array> {

  Ptr<Expr>& size;
  //NOTE: Multiset's by default have nullptr as their index_type, 
  //      make_legacy will return an Array that has a proper index_type
  // Ptr<TypeExpr>& element_type;

  Multiset(const Ptr<Expr>& size_, const Ptr<TypeExpr>& element_type_, const location& loc_);
  Multiset *clone() const;
  ~Multiset() = default;

  void visit(BaseTraversal& visitor);
  void visit(ConstBaseTraversal& visitor) const;

  void validate() const override;
  void update() override;
  std::string to_string() const;

  Ptr<Array> make_legacy() const;
};

} //namespace ext
} //namespace rumur
