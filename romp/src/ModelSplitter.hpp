/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file Model.hpp
 *
 * @brief   A Class that is a intermediary representation of the model,
 *        used to allow for generating the Cpp romp tools
 *        in a way that allows full context of the model.
 *
 * @date 2022/05/13
 * @version 0.2
 */

#pragma once

#include <string>
// #include <stack>
#include <vector>
#include <list>
// #include <iostream>
// #include <unordered_map>
#include <unordered_set>
#include <unordered_map>
#include <murphi/murphi.h>
#include <sstream>
#include "romp_def.hpp"


namespace romp {

// struct SplitModel { murphi::Model global_decls; murphi::Model state_var_decl;
//                     murphi::Model funct_decls; murphi::Model rule_decls; };


/**
 * @brief   A Class that is a intermediary representation of the model,
 *        used to allow for generating the Cpp romp tools
 *        in a way that allows full context of the model.
 *          It allows the following:
 *        \li Keeping track of all types (generating names for anonymous types)
 *        \li Keeping track of all "variables" respecting scope.
 *        \li Keeping track of all functions, procedures, & rules.
 *        \li allowing lookup of all above mentioned items.
 *        \li preserving a notion of scope.
 */
class ModelSplitter : public murphi::BaseTraversal {

  // << ===================================== Class Members ====================================== >> 
public: // ---- Public Class Members ---- //
  std::vector<murphi::Ptr<murphi::Decl>> global_decls;
  std::vector<murphi::Ptr<murphi::VarDecl>> state_var_decls;
  std::vector<murphi::Ptr<murphi::Function>> funct_decls;
  std::vector<murphi::Ptr<murphi::StartState>> startstate_decls;
  std::vector<murphi::Ptr<murphi::SimpleRule>> rule_decls;
  std::vector<murphi::Ptr<murphi::PropertyRule>> property_decls;
  static std::unordered_map<size_t,std::string> pretty_type_reprs;
  static size_t model_unique_id;
  std::stringstream funct_info_list;
  std::stringstream rule_info_list;
  std::stringstream startstate_info_list;
  std::stringstream prop_info_list;
  id_t next_property_id = 0u;
  id_t next_invar_id = 0u;
  id_t next_assume_id = 0u;
  id_t next_cover_id = 0u;
  id_t next_liveness_id = 0u;
  // friend class ::romp::CGenerator;


private: // ---- Private Class Members ---- //

  // murphi::location loc;
  
  std::unordered_set<std::string> cTypeNames{ROMP_RESERVED_NAMES};
  // murphi::Symtab& symtab
  // std::unordered_map<size_t,std::string> cTypeName;  // might end up not needing this


  id_t anon_id = 0;


  // << ============================= Constructors & Deconstructor =============================== >> 
public:
  ModelSplitter(); // {}
  // ModelSplitter(murphi::Symtab& symtab_);
  ~ModelSplitter();


  // << ========================== Public/External Function Functions ============================ >> 
public:

  // SplitModel split_model(const murphi::Model &n);
  
  void sort_model(const std::vector<murphi::Ptr<murphi::Node>> &children);



  // << =========================== Internal/Private Helper Functions ============================ >> 
private:

  const std::string gen_new_anon_name();
  void make_name_unique(std::string &name);
  void insert_to_global_decls(murphi::Ptr<murphi::TypeDecl> n);
  void insert_to_global_decls(murphi::Ptr<murphi::ConstDecl> n);
  void visit_and_check_quantifier(murphi::Rule& r, murphi::Quantifier& q);
  // void sort_model(const std::vector<murphi::Ptr<murphi::Node>> &children);
  // void process_anon_complex_type(murphi::TypeExpr &children);

  void __throw_unreachable_error(const murphi::Node &n);


  // << =========================== Model Processing Helper Functions ============================ >> 
public:
  // - most useful ---- 
  // void visit_model(murphi::Model &n) final;
  void visit_array(murphi::Array &n) final;
  void visit_record(murphi::Record &n) final;
  void visit_function(murphi::Function &n) final;
  void visit_simplerule(murphi::SimpleRule &n) final;
  void visit_ruleset(murphi::Ruleset &n) final;
  void visit_aliasrule(murphi::AliasRule &n) final;
  void visit_startstate(murphi::StartState &n) final;
  void visit_propertyrule(murphi::PropertyRule &n) final;
  // void visit_quantifier(murphi::Quantifier& q) final;
  void _visit_quantifier(murphi::Quantifier& q);

  // - useful for debugging ---- 
  void visit_typedecl(murphi::TypeDecl &n) final;
  void visit_constdecl(murphi::ConstDecl &n) final;
  void visit_vardecl(murphi::VarDecl &n) final;
  void visit_enum(murphi::Enum &n) final;
  void visit_range(murphi::Range &) final;
  void visit_scalarset(murphi::Scalarset &) final;
  void visit_typeexprid(murphi::TypeExprID &n) final;

  // - useless (will only throw an error if called) ---- 
  virtual void visit_add(murphi::Add &n) { __throw_unreachable_error(n); }
  virtual void visit_aliasdecl(murphi::AliasDecl &n) { __throw_unreachable_error(n); }
  virtual void visit_aliasstmt(murphi::AliasStmt &n) { __throw_unreachable_error(n); }
  virtual void visit_and(murphi::And &n) { __throw_unreachable_error(n); }
  virtual void visit_assignment(murphi::Assignment &n) { __throw_unreachable_error(n); }
  virtual void visit_band(murphi::Band &n) { __throw_unreachable_error(n); }
  virtual void visit_bnot(murphi::Bnot &n) { __throw_unreachable_error(n); }
  virtual void visit_bor(murphi::Bor &n) { __throw_unreachable_error(n); }
  virtual void visit_clear(murphi::Clear &n) { __throw_unreachable_error(n); }
  virtual void visit_div(murphi::Div &n) { __throw_unreachable_error(n); }
  virtual void visit_element(murphi::Element &n) { __throw_unreachable_error(n); }
  virtual void visit_eq(murphi::Eq &n) { __throw_unreachable_error(n); }
  virtual void visit_errorstmt(murphi::ErrorStmt &n) { __throw_unreachable_error(n); }
  virtual void visit_exists(murphi::Exists &n) { __throw_unreachable_error(n); }
  virtual void visit_exprid(murphi::ExprID &n) { __throw_unreachable_error(n); }
  virtual void visit_field(murphi::Field &n) { __throw_unreachable_error(n); }
  virtual void visit_for(murphi::For &n) { __throw_unreachable_error(n); }
  virtual void visit_forall(murphi::Forall &n) { __throw_unreachable_error(n); }
  virtual void visit_functioncall(murphi::FunctionCall &n) { __throw_unreachable_error(n); }
  virtual void visit_geq(murphi::Geq &n) { __throw_unreachable_error(n); }
  virtual void visit_gt(murphi::Gt &n) { __throw_unreachable_error(n); }
  virtual void visit_if(murphi::If &n) { __throw_unreachable_error(n); }
  virtual void visit_ifclause(murphi::IfClause &n) { __throw_unreachable_error(n); }
  virtual void visit_implication(murphi::Implication &n) { __throw_unreachable_error(n); }
  virtual void visit_isundefined(murphi::IsUndefined &n) { __throw_unreachable_error(n); }
  virtual void visit_leq(murphi::Leq &n) { __throw_unreachable_error(n); }
  virtual void visit_lsh(murphi::Lsh &n) { __throw_unreachable_error(n); }
  virtual void visit_lt(murphi::Lt &n) { __throw_unreachable_error(n); }
  virtual void visit_model(murphi::Model &n) { __throw_unreachable_error(n); }
  virtual void visit_mod(murphi::Mod &n) { __throw_unreachable_error(n); }
  virtual void visit_mul(murphi::Mul &n) { __throw_unreachable_error(n); }
  virtual void visit_negative(murphi::Negative &n) { __throw_unreachable_error(n); }
  virtual void visit_neq(murphi::Neq &n) { __throw_unreachable_error(n); }
  virtual void visit_not(murphi::Not &n) { __throw_unreachable_error(n); }
  virtual void visit_number(murphi::Number &n) { __throw_unreachable_error(n); }
  virtual void visit_or(murphi::Or &n) { __throw_unreachable_error(n); }
  virtual void visit_procedurecall(murphi::ProcedureCall &n) { __throw_unreachable_error(n); }
  virtual void visit_property(murphi::Property &n) { __throw_unreachable_error(n); }
  virtual void visit_propertystmt(murphi::PropertyStmt &n) { __throw_unreachable_error(n); }
  virtual void visit_put(murphi::Put &n) { __throw_unreachable_error(n); }
  virtual void visit_quantifier(murphi::Quantifier &n) { __throw_unreachable_error(n); }
  virtual void visit_return(murphi::Return &n) { __throw_unreachable_error(n); }
  virtual void visit_rsh(murphi::Rsh &n) { __throw_unreachable_error(n); }
  virtual void visit_sub(murphi::Sub &n) { __throw_unreachable_error(n); }
  virtual void visit_switch(murphi::Switch &n) { __throw_unreachable_error(n); }
  virtual void visit_switchcase(murphi::SwitchCase &n) { __throw_unreachable_error(n); }
  virtual void visit_ternary(murphi::Ternary &n) { __throw_unreachable_error(n); }
  virtual void visit_undefine(murphi::Undefine &n) { __throw_unreachable_error(n); }
  virtual void visit_while(murphi::While &n) { __throw_unreachable_error(n); }
  virtual void visit_xor(murphi::Xor &n) { __throw_unreachable_error(n); }
  

protected:
  static void set_pretty_str_rep_type(const murphi::Node& t, int max_level=1);
public:
  static const std::string get_pretty_rep(const murphi::TypeExpr& t);

  // void visit_constdecl(ConstDecl &n) final; // pretty sure I don't need this!


  // ModelSplitter &operator<<(std::string &s);
  // ModelSplitter &operator<<(murphi::Node &n);

  // void dispatch(const murphi::Node &n);

};

} // namespace romp
