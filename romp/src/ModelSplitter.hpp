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
 * @version 0.1
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
#include <rumur/rumur.h>
#include <sstream>
#include "romp_def.hpp"


namespace romp {

// struct SplitModel { rumur::Model global_decls; rumur::Model state_var_decl;
//                     rumur::Model funct_decls; rumur::Model rule_decls; };


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
class ModelSplitter : public rumur::BaseTraversal {

  // << ===================================== Class Members ====================================== >> 
public: // ---- Public Class Members ---- //
  std::vector<rumur::Ptr<rumur::Decl>> global_decls;
  std::vector<rumur::Ptr<rumur::VarDecl>> state_var_decls;
  std::vector<rumur::Ptr<rumur::Function>> funct_decls;
  std::vector<rumur::Ptr<rumur::StartState>> startstate_decls;
  std::vector<rumur::Ptr<rumur::SimpleRule>> rule_decls;
  std::vector<rumur::Ptr<rumur::PropertyRule>> property_decls;
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

  // rumur::location loc;
  
  std::unordered_set<std::string> cTypeNames{ROMP_RESERVED_NAMES};
  // rumur::Symtab& symtab
  // std::unordered_map<size_t,std::string> cTypeName;  // might end up not needing this


  id_t anon_id = 0;


  // << ============================= Constructors & Deconstructor =============================== >> 
public:
  ModelSplitter(); // {}
  // ModelSplitter(rumur::Symtab& symtab_);
  ~ModelSplitter();


  // << ========================== Public/External Function Functions ============================ >> 
public:

  // SplitModel split_model(const rumur::Model &n);
  
  void sort_model(const std::vector<rumur::Ptr<rumur::Node>> &children);



  // << =========================== Internal/Private Helper Functions ============================ >> 
private:

  const std::string gen_new_anon_name();
  void make_name_unique(std::string &name);
  void insert_to_global_decls(rumur::Ptr<rumur::TypeDecl> n);
  void insert_to_global_decls(rumur::Ptr<rumur::ConstDecl> n);
  void visit_and_check_quantifier(rumur::Rule& r, rumur::Quantifier& q);
  // void sort_model(const std::vector<rumur::Ptr<rumur::Node>> &children);
  // void process_anon_complex_type(rumur::TypeExpr &children);

  void __throw_unreachable_error(const rumur::Node &n);


  // << =========================== Model Processing Helper Functions ============================ >> 
public:
  // - most useful ---- 
  // void visit_model(rumur::Model &n) final;
  void visit_array(rumur::Array &n) final;
  void visit_record(rumur::Record &n) final;
  void visit_function(rumur::Function &n) final;
  void visit_simplerule(rumur::SimpleRule &n) final;
  void visit_ruleset(rumur::Ruleset &n) final;
  void visit_aliasrule(rumur::AliasRule &n) final;
  void visit_startstate(rumur::StartState &n) final;
  void visit_propertyrule(rumur::PropertyRule &n) final;
  // void visit_quantifier(rumur::Quantifier& q) final;
  void _visit_quantifier(rumur::Quantifier& q);

  // - useful for debugging ---- 
  void visit_typedecl(rumur::TypeDecl &n) final;
  void visit_constdecl(rumur::ConstDecl &n) final;
  void visit_vardecl(rumur::VarDecl &n) final;
  void visit_enum(rumur::Enum &n) final;
  void visit_range(rumur::Range &) final;
  void visit_scalarset(rumur::Scalarset &) final;
  void visit_typeexprid(rumur::TypeExprID &n) final;

  // - useless (will only throw an error if called) ---- 
  virtual void visit_add(rumur::Add &n) { __throw_unreachable_error(n); }
  virtual void visit_aliasdecl(rumur::AliasDecl &n) { __throw_unreachable_error(n); }
  virtual void visit_aliasstmt(rumur::AliasStmt &n) { __throw_unreachable_error(n); }
  virtual void visit_and(rumur::And &n) { __throw_unreachable_error(n); }
  virtual void visit_assignment(rumur::Assignment &n) { __throw_unreachable_error(n); }
  virtual void visit_band(rumur::Band &n) { __throw_unreachable_error(n); }
  virtual void visit_bnot(rumur::Bnot &n) { __throw_unreachable_error(n); }
  virtual void visit_bor(rumur::Bor &n) { __throw_unreachable_error(n); }
  virtual void visit_clear(rumur::Clear &n) { __throw_unreachable_error(n); }
  virtual void visit_div(rumur::Div &n) { __throw_unreachable_error(n); }
  virtual void visit_element(rumur::Element &n) { __throw_unreachable_error(n); }
  virtual void visit_eq(rumur::Eq &n) { __throw_unreachable_error(n); }
  virtual void visit_errorstmt(rumur::ErrorStmt &n) { __throw_unreachable_error(n); }
  virtual void visit_exists(rumur::Exists &n) { __throw_unreachable_error(n); }
  virtual void visit_exprid(rumur::ExprID &n) { __throw_unreachable_error(n); }
  virtual void visit_field(rumur::Field &n) { __throw_unreachable_error(n); }
  virtual void visit_for(rumur::For &n) { __throw_unreachable_error(n); }
  virtual void visit_forall(rumur::Forall &n) { __throw_unreachable_error(n); }
  virtual void visit_functioncall(rumur::FunctionCall &n) { __throw_unreachable_error(n); }
  virtual void visit_geq(rumur::Geq &n) { __throw_unreachable_error(n); }
  virtual void visit_gt(rumur::Gt &n) { __throw_unreachable_error(n); }
  virtual void visit_if(rumur::If &n) { __throw_unreachable_error(n); }
  virtual void visit_ifclause(rumur::IfClause &n) { __throw_unreachable_error(n); }
  virtual void visit_implication(rumur::Implication &n) { __throw_unreachable_error(n); }
  virtual void visit_isundefined(rumur::IsUndefined &n) { __throw_unreachable_error(n); }
  virtual void visit_leq(rumur::Leq &n) { __throw_unreachable_error(n); }
  virtual void visit_lsh(rumur::Lsh &n) { __throw_unreachable_error(n); }
  virtual void visit_lt(rumur::Lt &n) { __throw_unreachable_error(n); }
  virtual void visit_model(rumur::Model &n) { __throw_unreachable_error(n); }
  virtual void visit_mod(rumur::Mod &n) { __throw_unreachable_error(n); }
  virtual void visit_mul(rumur::Mul &n) { __throw_unreachable_error(n); }
  virtual void visit_negative(rumur::Negative &n) { __throw_unreachable_error(n); }
  virtual void visit_neq(rumur::Neq &n) { __throw_unreachable_error(n); }
  virtual void visit_not(rumur::Not &n) { __throw_unreachable_error(n); }
  virtual void visit_number(rumur::Number &n) { __throw_unreachable_error(n); }
  virtual void visit_or(rumur::Or &n) { __throw_unreachable_error(n); }
  virtual void visit_procedurecall(rumur::ProcedureCall &n) { __throw_unreachable_error(n); }
  virtual void visit_property(rumur::Property &n) { __throw_unreachable_error(n); }
  virtual void visit_propertystmt(rumur::PropertyStmt &n) { __throw_unreachable_error(n); }
  virtual void visit_put(rumur::Put &n) { __throw_unreachable_error(n); }
  virtual void visit_quantifier(rumur::Quantifier &n) { __throw_unreachable_error(n); }
  virtual void visit_return(rumur::Return &n) { __throw_unreachable_error(n); }
  virtual void visit_rsh(rumur::Rsh &n) { __throw_unreachable_error(n); }
  virtual void visit_sub(rumur::Sub &n) { __throw_unreachable_error(n); }
  virtual void visit_switch(rumur::Switch &n) { __throw_unreachable_error(n); }
  virtual void visit_switchcase(rumur::SwitchCase &n) { __throw_unreachable_error(n); }
  virtual void visit_ternary(rumur::Ternary &n) { __throw_unreachable_error(n); }
  virtual void visit_undefine(rumur::Undefine &n) { __throw_unreachable_error(n); }
  virtual void visit_while(rumur::While &n) { __throw_unreachable_error(n); }
  virtual void visit_xor(rumur::Xor &n) { __throw_unreachable_error(n); }
  

protected:
  static void set_pretty_str_rep_type(const rumur::Node& t, int max_level=1);
public:
  static const std::string get_pretty_rep(const rumur::TypeExpr& t);

  // void visit_constdecl(ConstDecl &n) final; // pretty sure I don't need this!


  // ModelSplitter &operator<<(std::string &s);
  // ModelSplitter &operator<<(rumur::Node &n);

  // void dispatch(const rumur::Node &n);

};

} // namespace romp
