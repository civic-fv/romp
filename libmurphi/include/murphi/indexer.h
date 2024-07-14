#pragma once

#include <cstddef>
#include <murphi/Expr.h>
#include <murphi/Model.h>
#include <murphi/Number.h>
#include <murphi/Rule.h>
#include <murphi/Stmt.h>
#include <murphi/TypeExpr.h>
#include <murphi/traverse.h>

#ifndef MURPHI_API_WITH_RTTI
#define MURPHI_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace murphi {

class MURPHI_API_WITH_RTTI Indexer : public BaseTraversal {

private:
  size_t next = 0u;
  id_t next_record_field_id = 0u;
  id_t next_type_id = 0u;

public:
  void visit_add(Add &n) final;
  void visit_aliasdecl(AliasDecl &n) final;
  void visit_aliasrule(AliasRule &n) final;
  void visit_aliasstmt(AliasStmt &n) final;
  void visit_ambiguousamp(AmbiguousAmp &n) final;
  void visit_ambiguouspipe(AmbiguousPipe &n) final;
  void visit_and(And &n) final;
  void visit_array(Array &n) final;
  void visit_assignment(Assignment &n) final;
  void visit_band(Band &n) final;
  void visit_bnot(Bnot &n) final;
  void visit_bor(Bor &n) final;
  void visit_clear(Clear &n) final;
  void visit_constdecl(ConstDecl &n) final;
  void visit_div(Div &n) final;
  void visit_element(Element &n) final;
  void visit_enum(Enum &n) final;
  void visit_eq(Eq &n) final;
  void visit_errorstmt(ErrorStmt &n) final;
  void visit_exists(Exists &n) final;
  void visit_exprid(ExprID &n) final;
  void visit_field(Field &n) final;
  void visit_for(For &n) final;
  void visit_forall(Forall &n) final;
  void visit_function(Function &n) final;
  void visit_functioncall(FunctionCall &n) final;
  void visit_geq(Geq &n) final;
  void visit_gt(Gt &n) final;
  void visit_if(If &n) final;
  void visit_ifclause(IfClause &n) final;
  void visit_implication(Implication &n) final;
  void visit_isundefined(IsUndefined &n) final;
  void visit_leq(Leq &n) final;
  void visit_lsh(Lsh &n) final;
  void visit_lt(Lt &n) final;
  void visit_model(Model &n) final;
  void visit_mod(Mod &n) final;
  void visit_mul(Mul &n) final;
  void visit_negative(Negative &n) final;
  void visit_neq(Neq &n) final;
  void visit_not(Not &n) final;
  void visit_number(Number &n) final;
  void visit_or(Or &n) final;
  void visit_procedurecall(ProcedureCall &n) final;
  void visit_property(Property &n) final;
  void visit_propertyrule(PropertyRule &n) final;
  void visit_propertystmt(PropertyStmt &n) final;
  void visit_put(Put &n) final;
  void visit_quantifier(Quantifier &n) final;
  void visit_range(Range &n) final;
  void visit_record(Record &n) final;
  void visit_return(Return &n) final;
  void visit_rsh(Rsh &n) final;
  void visit_ruleset(Ruleset &n) final;
  void visit_scalarset(Scalarset &n) final;
  void visit_simplerule(SimpleRule &n) final;
  void visit_startstate(StartState &n) final;
  void visit_sub(Sub &n) final;
  void visit_switch(Switch &n) final;
  void visit_switchcase(SwitchCase &n) final;
  void visit_ternary(Ternary &n) final;
  void visit_typedecl(TypeDecl &n) final;
  void visit_typeexprid(TypeExprID &n) final;
  void visit_undefine(Undefine &n) final;
  void visit_vardecl(VarDecl &n) final;
  void visit_while(While &n) final;
  void visit_xor(Xor &n) final;

  // added syntax nodes
  void visit_chooserule(ChooseRule& n) final;
  void visit_ismember(IsMember& n) final;
  void visit_multiset(Multiset& n) final;
  void visit_multisetadd(MultisetAdd& n) final;
  void visit_multisetcount(MultisetCount& n) final;
  void visit_multisetelement(MultisetElement& n) final;
  void visit_multisetremove(MultisetRemove& n) final;
  void visit_multisetremovepred(MultisetRemovePred& n) final;
  void visit_multisetquantifier(MultisetQuantifier& n) final;
  void visit_scalarsetunion(ScalarsetUnion& n) final;
  void visit_sucast(SUCast& n) final;

  void dispatch(Node& n);

  virtual ~Indexer() = default;

private:
  void visit_bexpr(BinaryExpr &n);
  void visit_uexpr(UnaryExpr &n);
};

} // namespace murphi