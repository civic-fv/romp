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
#include <romp/romp.h>
#include <sstream>
#include "romp_def.hpp"


namespace romp {

// struct SplitModel { romp::Model global_decls; romp::Model state_var_decl;
//                     romp::Model funct_decls; romp::Model rule_decls; };


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
class ModelSplitter : public romp::BaseTraversal {

  // << ===================================== Class Members ====================================== >> 
public: // ---- Public Class Members ---- //
  std::vector<romp::Ptr<romp::Decl>> global_decls;
  std::vector<romp::Ptr<romp::VarDecl>> state_var_decls;
  std::vector<romp::Ptr<romp::Function>> funct_decls;
  std::vector<romp::Ptr<romp::StartState>> startstate_decls;
  std::vector<romp::Ptr<romp::SimpleRule>> rule_decls;
  std::vector<romp::Ptr<romp::PropertyRule>> property_decls;
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

  // romp::location loc;
  
  std::unordered_set<std::string> cTypeNames{ROMP_RESERVED_NAMES};
  // romp::Symtab& symtab
  // std::unordered_map<size_t,std::string> cTypeName;  // might end up not needing this


  id_t anon_id = 0;


  // << ============================= Constructors & Deconstructor =============================== >> 
public:
  ModelSplitter(); // {}
  // ModelSplitter(romp::Symtab& symtab_);
  ~ModelSplitter();


  // << ========================== Public/External Function Functions ============================ >> 
public:

  // SplitModel split_model(const romp::Model &n);
  
  void sort_model(const std::vector<romp::Ptr<romp::Node>> &children);



  // << =========================== Internal/Private Helper Functions ============================ >> 
private:

  const std::string gen_new_anon_name();
  void make_name_unique(std::string &name);
  void insert_to_global_decls(romp::Ptr<romp::TypeDecl> n);
  void insert_to_global_decls(romp::Ptr<romp::ConstDecl> n);
  void visit_and_check_quantifier(romp::Rule& r, romp::Quantifier& q);
  // void sort_model(const std::vector<romp::Ptr<romp::Node>> &children);
  // void process_anon_complex_type(romp::TypeExpr &children);

  void __throw_unreachable_error(const romp::Node &n);


  // << =========================== Model Processing Helper Functions ============================ >> 
public:
  // - most useful ---- 
  // void visit_model(romp::Model &n) final;
  void visit_array(romp::Array &n) final;
  void visit_record(romp::Record &n) final;
  void visit_function(romp::Function &n) final;
  void visit_simplerule(romp::SimpleRule &n) final;
  void visit_ruleset(romp::Ruleset &n) final;
  void visit_aliasrule(romp::AliasRule &n) final;
  void visit_startstate(romp::StartState &n) final;
  void visit_propertyrule(romp::PropertyRule &n) final;
  // void visit_quantifier(romp::Quantifier& q) final;
  void _visit_quantifier(romp::Quantifier& q);

  // - useful for debugging ---- 
  void visit_typedecl(romp::TypeDecl &n) final;
  void visit_constdecl(romp::ConstDecl &n) final;
  void visit_vardecl(romp::VarDecl &n) final;
  void visit_enum(romp::Enum &n) final;
  void visit_range(romp::Range &) final;
  void visit_scalarset(romp::Scalarset &) final;
  void visit_typeexprid(romp::TypeExprID &n) final;

  // - useless (will only throw an error if called) ---- 
  virtual void visit_add(romp::Add &n) { __throw_unreachable_error(n); }
  virtual void visit_aliasdecl(romp::AliasDecl &n) { __throw_unreachable_error(n); }
  virtual void visit_aliasstmt(romp::AliasStmt &n) { __throw_unreachable_error(n); }
  virtual void visit_and(romp::And &n) { __throw_unreachable_error(n); }
  virtual void visit_assignment(romp::Assignment &n) { __throw_unreachable_error(n); }
  virtual void visit_band(romp::Band &n) { __throw_unreachable_error(n); }
  virtual void visit_bnot(romp::Bnot &n) { __throw_unreachable_error(n); }
  virtual void visit_bor(romp::Bor &n) { __throw_unreachable_error(n); }
  virtual void visit_clear(romp::Clear &n) { __throw_unreachable_error(n); }
  virtual void visit_div(romp::Div &n) { __throw_unreachable_error(n); }
  virtual void visit_element(romp::Element &n) { __throw_unreachable_error(n); }
  virtual void visit_eq(romp::Eq &n) { __throw_unreachable_error(n); }
  virtual void visit_errorstmt(romp::ErrorStmt &n) { __throw_unreachable_error(n); }
  virtual void visit_exists(romp::Exists &n) { __throw_unreachable_error(n); }
  virtual void visit_exprid(romp::ExprID &n) { __throw_unreachable_error(n); }
  virtual void visit_field(romp::Field &n) { __throw_unreachable_error(n); }
  virtual void visit_for(romp::For &n) { __throw_unreachable_error(n); }
  virtual void visit_forall(romp::Forall &n) { __throw_unreachable_error(n); }
  virtual void visit_functioncall(romp::FunctionCall &n) { __throw_unreachable_error(n); }
  virtual void visit_geq(romp::Geq &n) { __throw_unreachable_error(n); }
  virtual void visit_gt(romp::Gt &n) { __throw_unreachable_error(n); }
  virtual void visit_if(romp::If &n) { __throw_unreachable_error(n); }
  virtual void visit_ifclause(romp::IfClause &n) { __throw_unreachable_error(n); }
  virtual void visit_implication(romp::Implication &n) { __throw_unreachable_error(n); }
  virtual void visit_isundefined(romp::IsUndefined &n) { __throw_unreachable_error(n); }
  virtual void visit_leq(romp::Leq &n) { __throw_unreachable_error(n); }
  virtual void visit_lsh(romp::Lsh &n) { __throw_unreachable_error(n); }
  virtual void visit_lt(romp::Lt &n) { __throw_unreachable_error(n); }
  virtual void visit_model(romp::Model &n) { __throw_unreachable_error(n); }
  virtual void visit_mod(romp::Mod &n) { __throw_unreachable_error(n); }
  virtual void visit_mul(romp::Mul &n) { __throw_unreachable_error(n); }
  virtual void visit_negative(romp::Negative &n) { __throw_unreachable_error(n); }
  virtual void visit_neq(romp::Neq &n) { __throw_unreachable_error(n); }
  virtual void visit_not(romp::Not &n) { __throw_unreachable_error(n); }
  virtual void visit_number(romp::Number &n) { __throw_unreachable_error(n); }
  virtual void visit_or(romp::Or &n) { __throw_unreachable_error(n); }
  virtual void visit_procedurecall(romp::ProcedureCall &n) { __throw_unreachable_error(n); }
  virtual void visit_property(romp::Property &n) { __throw_unreachable_error(n); }
  virtual void visit_propertystmt(romp::PropertyStmt &n) { __throw_unreachable_error(n); }
  virtual void visit_put(romp::Put &n) { __throw_unreachable_error(n); }
  virtual void visit_quantifier(romp::Quantifier &n) { __throw_unreachable_error(n); }
  virtual void visit_return(romp::Return &n) { __throw_unreachable_error(n); }
  virtual void visit_rsh(romp::Rsh &n) { __throw_unreachable_error(n); }
  virtual void visit_sub(romp::Sub &n) { __throw_unreachable_error(n); }
  virtual void visit_switch(romp::Switch &n) { __throw_unreachable_error(n); }
  virtual void visit_switchcase(romp::SwitchCase &n) { __throw_unreachable_error(n); }
  virtual void visit_ternary(romp::Ternary &n) { __throw_unreachable_error(n); }
  virtual void visit_undefine(romp::Undefine &n) { __throw_unreachable_error(n); }
  virtual void visit_while(romp::While &n) { __throw_unreachable_error(n); }
  virtual void visit_xor(romp::Xor &n) { __throw_unreachable_error(n); }
  

protected:
  static void set_pretty_str_rep_type(const romp::Node& t, int max_level=1);
public:
  static const std::string get_pretty_rep(const romp::TypeExpr& t);

  // void visit_constdecl(ConstDecl &n) final; // pretty sure I don't need this!


  // ModelSplitter &operator<<(std::string &s);
  // ModelSplitter &operator<<(romp::Node &n);

  // void dispatch(const romp::Node &n);

};

} // namespace romp
