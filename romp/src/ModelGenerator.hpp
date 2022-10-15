/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file ModelGenerator.hpp
 * 
 * @brief generates the C++ code for the model itself
 * 
 * @date 2022/10/14
 * @version 0.2
 */

#pragma once

#include "CodeGenerator.hpp"
#include <cstddef>
#include <murphi/murphi.h>
#include <string>
#include <unordered_map>
// #include <set>
#include <unordered_set>
#include <vector>

namespace romp {

// generator for C-like code
class __attribute__((visibility("hidden"))) ModelGenerator
    : public romp::CodeGenerator,
      public murphi::ConstBaseTraversal {
protected:

  // TODO get rid of the need for enum_typedefs
  // // mapping of Enum unique_ids to the name of a TypeDecl to them
  // std::unordered_map<size_t, std::string> enum_typedefs;

  // mapping of an enum/scalar name to it's id in the model scalar/enum space
  std::unordered_set<std::string,size_t> enum_ids

  // TODO get rid of the need for is_pointer
  // // collection of unique_ids that were emitted as pointers instead of standard
  // // variables
  // std::unordered_set<size_t> is_pointer;

  // list of comments from the original source
  std::vector<murphi::Comment> comments;

  // whether each comment has been written to the output yet
  std::vector<bool> emitted;

public:
  ModelGenerator(const romp::CodeGenerator& cg_,
                 const std::unordered_set<std::string,size_t>& enum_ids_,
                 const std::vector<murphi::Comment> &comments_)
      : romp::CodeGenerator(cg_), enum_ids(enum_ids_),
        comments(comments_), emitted(comments_.size(), false) {}

  void visit_add(const murphi::Add &n) final;
  void visit_aliasdecl(const murphi::AliasDecl &n) final;
  void visit_aliasrule(const murphi::AliasRule &) final;
  void visit_aliasstmt(const murphi::AliasStmt &n) final;
  void visit_and(const murphi::And &n) final;
  void visit_array(const murphi::Array &n) final;
  void visit_assignment(const murphi::Assignment &n) final;
  void visit_band(const murphi::Band &n) final;
  void visit_bnot(const murphi::Bnot &n) final;
  void visit_bor(const murphi::Bor &n) final;
  void visit_chooserule(const murphi::ChooseRule &n) final;
  void visit_clear(const murphi::Clear &n) final;
  void visit_constdecl(const murphi::ConstDecl &n) final;
  void visit_div(const murphi::Div &n) final;
  void visit_element(const murphi::Element &n) final;
  void visit_enum(const murphi::Enum &n) final;
  void visit_eq(const murphi::Eq &n) final;
  void visit_errorstmt(const murphi::ErrorStmt &n) final;
  void visit_exists(const murphi::Exists &n) final;
  void visit_exprid(const murphi::ExprID &n) final;
  void visit_implication(const murphi::Implication &n) final;
  void visit_ismember(const murphi::IsMember &n) final;
  void visit_isundefined(const murphi::IsUndefined &n) final;
  void visit_field(const murphi::Field &n) final;
  void visit_for(const murphi::For &n) final;
  void visit_forall(const murphi::Forall &n) final;
  void visit_function(const murphi::Function &n) final;
  void visit_functioncall(const murphi::FunctionCall &n) final;
  void visit_geq(const murphi::Geq &n) final;
  void visit_gt(const murphi::Gt &n) final;
  void visit_if(const murphi::If &n) final;
  void visit_ifclause(const murphi::IfClause &n) final;
  void visit_leq(const murphi::Leq &n) final;
  void visit_lsh(const murphi::Lsh &n) final;
  void visit_lt(const murphi::Lt &n) final;
  void visit_mod(const murphi::Mod &n) final;
  void visit_model(const murphi::Model &n) final;
  void visit_mul(const murphi::Mul &n) final;
  void visit_multiset(const murphi::Multiset &n) final;
  void visit_multisetadd(const murphi::MultisetAdd &n) final;
  void visit_multisetcount(const murphi::MultisetCount &n) final;
  void visit_multisetelement(const murphi::MultisetElement &n) final;
  void visit_multisetremove(const murphi::MultisetRemove &n) final;
  void visit_multisetremovepred(const murphi::MultisetRemovePred &n) final;
  void visit_multisetquantifier(const murphi::MultisetQuantifier &n) final;
  void visit_negative(const murphi::Negative &n) final;
  void visit_neq(const murphi::Neq &n) final;
  void visit_not(const murphi::Not &n) final;
  void visit_number(const murphi::Number &n) final;
  void visit_or(const murphi::Or &n) final;
  void visit_procedurecall(const murphi::ProcedureCall &n) final;
  void visit_property(const murphi::Property &) final;
  void visit_propertyrule(const murphi::PropertyRule &n) final;
  void visit_propertystmt(const murphi::PropertyStmt &n) final;
  void visit_put(const murphi::Put &n) final;
  void visit_quantifier(const murphi::Quantifier &n) final;
  void visit_range(const murphi::Range &) final;
  void visit_record(const murphi::Record &n) final;
  void visit_return(const murphi::Return &n) final;
  void visit_rsh(const murphi::Rsh &n) final;
  void visit_ruleset(const murphi::Ruleset &) final;
  void visit_scalarset(const murphi::Scalarset &n) final;
  void visit_scalarsetunion(const murphi::ScalarsetUnion &n) final;
  void visit_sucast(const murphi::SUCast &n) final;
  void visit_sub(const murphi::Sub &n) final;
  void visit_simplerule(const murphi::SimpleRule &n) final;
  void visit_startstate(const murphi::StartState &n) final;
  void visit_switch(const murphi::Switch &n) final;
  void visit_switchcase(const murphi::SwitchCase &n) final;
  void visit_ternary(const murphi::Ternary &n) final;
  void visit_typedecl(const murphi::TypeDecl &n) final;
  void visit_typeexprid(const murphi::TypeExprID &n) final;
  void visit_undefine(const murphi::Undefine &n) final;
  void visit_while(const murphi::While &n) final;
  void visit_xor(const murphi::Xor &n) final;

  // helpers to make output more natural
  ModelGenerator &operator<<(const std::string &s);
  

  // make this class abstract
  virtual ~ModelGenerator() = 0;

private:
  // generate a print statement of the given expression and (possibly
  // not-terminal) type
  void print(const std::string &suffix, const murphi::TypeExpr &t,
             const murphi::Expr &e, size_t counter);

protected:
  // output comments preceding the given node
  size_t emit_leading_comments(const murphi::Node &n);

  // discard any un-emitted comments preceding the given position
  size_t drop_comments(const murphi::position &pos);

  // output single line comments following the given node
  size_t emit_trailing_comments(const murphi::Node &n);
};
  
} // namespace romp
