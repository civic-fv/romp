#pragma once

#include "CodeGenerator.hpp"
#include <cstddef>
#include <iostream>
#include <romp/romp.h>
#include <string>
#include <unordered_map>
// #include <set>
#include <unordered_set>
#include <vector>


// generator for C-like code
class __attribute__((visibility("hidden"))) CLikeGenerator
    : public romp::CodeGenerator,
      public romp::ConstBaseTraversal {

  static id_t anon_id;

protected:
  std::ostream &out;
  bool pack;
  
  std::unordered_set<std::string> reserved_type_names{ROMP_RESERVED_NAMES};
  

public:
  // mapping of Enum unique_ids to the name of a TypeDecl to them
  std::unordered_map<size_t, std::string> enum_typedefs;

  // track what types have been defined so that you can
  // ensure to emit types in a C/C++ safe way
  std::unordered_set<std::string> emitted_tDecls{ROMP_PREDEFINED_TYPES};

  // collection of unique_ids that were emitted as pointers instead of standard
  // variables
  std::unordered_set<size_t> is_pointer;

  // list of comments from the original source
  std::vector<romp::Comment> comments;

  // whether each comment has been written to the output yet
  std::vector<bool> emitted;

public:
  CLikeGenerator(const std::vector<romp::Comment> &comments_,
                 std::ostream &out_, bool pack_)
      : out(out_), pack(pack_), comments(comments_),
        emitted(comments_.size(), false) {}

  // CLikeGenerator(std::unordered_set<size_t> emitted_tDecls_,
  //                const std::vector<romp::Comment> &comments_,
  //                std::vector<bool> emitted_comments_,
  //                std::unordered_map<size_t, std::string> enum_typedefs_,
  //                std::ostream &out_, bool pack_)
  //     : out(out_), pack(pack_), comments(comments_),
  //       emitted(emitted_comments_),
  //       emitted_tDecls(emitted_tDecls_),
  //       enum_typedefs(enum_typedefs_) 
  //        {}

  void visit_add(const romp::Add &n) final;
  void visit_aliasdecl(const romp::AliasDecl &n) final;
  void visit_aliasrule(const romp::AliasRule &); // final;
  void visit_aliasstmt(const romp::AliasStmt &n) final;
  void visit_and(const romp::And &n) final;
  void visit_array(const romp::Array &n); // final;
  void visit_assignment(const romp::Assignment &n) final;
  void visit_band(const romp::Band &n) final;
  void visit_bnot(const romp::Bnot &n) final;
  void visit_bor(const romp::Bor &n) final;
  void visit_clear(const romp::Clear &n) final;
  void visit_div(const romp::Div &n) final;
  void visit_element(const romp::Element &n) final;
  void visit_enum(const romp::Enum &n); // final;
  void visit_eq(const romp::Eq &n) final;
  void visit_errorstmt(const romp::ErrorStmt &n); // final;
  void visit_exists(const romp::Exists &n) final;
  void visit_exprid(const romp::ExprID &n) final;
  void visit_field(const romp::Field &n) final;
  void visit_implication(const romp::Implication &n) final;
  void visit_isundefined(const romp::IsUndefined &) final;
  void visit_for(const romp::For &n) final;
  void visit_forall(const romp::Forall &n) final;
  void visit_functioncall(const romp::FunctionCall &n) final;
  void visit_geq(const romp::Geq &n) final;
  void visit_gt(const romp::Gt &n) final;
  void visit_if(const romp::If &n) final;
  void visit_ifclause(const romp::IfClause &n) final;
  void visit_leq(const romp::Leq &n) final;
  void visit_lsh(const romp::Lsh &n) final;
  void visit_lt(const romp::Lt &n) final;
  void visit_mod(const romp::Mod &n) final;
  void visit_model(const romp::Model &n); // final;
  void visit_mul(const romp::Mul &n) final;
  void visit_negative(const romp::Negative &n) final;
  void visit_neq(const romp::Neq &n) final;
  void visit_not(const romp::Not &n) final;
  void visit_number(const romp::Number &n) final;
  void visit_or(const romp::Or &n) final;
  void visit_procedurecall(const romp::ProcedureCall &n) final;
  void visit_property(const romp::Property &) final;
  void visit_propertystmt(const romp::PropertyStmt &n); // final;
  void visit_put(const romp::Put &n) final;
  void visit_quantifier(const romp::Quantifier &n) ; //final;
  void visit_range(const romp::Range &); // final;
  void visit_record(const romp::Record &n); // final;
  void visit_return(const romp::Return &n) final;
  void visit_rsh(const romp::Rsh &n) final;
  void visit_ruleset(const romp::Ruleset &) final;
  void visit_scalarset(const romp::Scalarset &); // final;
  void visit_sub(const romp::Sub &n) final;
  void visit_switch(const romp::Switch &n) final;
  void visit_switchcase(const romp::SwitchCase &n) final;
  void visit_ternary(const romp::Ternary &n) final;
  void visit_typedecl(const romp::TypeDecl &n); // final;
  void visit_typeexprid(const romp::TypeExprID &n) final;
  void visit_undefine(const romp::Undefine &n) final;
  void visit_while(const romp::While &n) final;
  void visit_xor(const romp::Xor &n) final;

  // helpers to make output more natural
  CLikeGenerator &operator<<(const std::string &s);
  CLikeGenerator &operator<<(const romp::Node &n);

  // make this class abstract
  virtual ~CLikeGenerator() = 0;

private:
  // generate a print statement of the given expression and (possibly
  // not-terminal) type
  void print(const std::string &suffix, const romp::TypeExpr &t,
             const romp::Expr &e, size_t counter);

protected:
  // output comments preceding the given node
  size_t emit_leading_comments(const romp::Node &n);

  // discard any un-emitted comments preceding the given position
  size_t drop_comments(const romp::position &pos);

  // output single line comments following the given node
  size_t emit_trailing_comments(const romp::Node &n);

  // ensure all internal references to TypeExpressions are ID's referencing 
  // type declarations that have already been emitted.
  // Throws romp::Error if this is not the case.
  void check_type_ref(const romp::Node &p, const romp::Ptr<romp::TypeExpr> &t) const;

};
