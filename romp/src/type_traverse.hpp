/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file type_traverse.hpp
 * 
 * @brief a semi-abstract traverser that can take in a \c romp::TypeExpr 
 *        and allows you to just write what happens when it encounters specific \c romp::TypeExpr 's
 *        else throws a \c romp::Error if it encounters a non-typeexpr \c romp::Node , 
 *        with a configurable custom error message.
 * 
 * @date 2022/06/28
 * @version 0.1
 */

#pragma once

#include <romp/romp.h>
#include <string> 

namespace romp {

class ConstBaseTypeTraversal : public romp::ConstBaseTraversal {
protected:
  std::string msg;
  ConstBaseTypeTraversal(std::string& msg_) : msg(msg_) {}
  ConstBaseTypeTraversal(const char* msg_) : msg(msg_) {}
  void unsupported_traversal(const Node& n, const char* type_name) const { throw Error(" [" + std::string(type_name) +"] :: " + msg, n.loc); }
public:
  void visit_add(const Add& n) { unsupported_traversal(n,"romp::Add"); }
  void visit_aliasdecl(const AliasDecl& n) { unsupported_traversal(n,"romp::AliasDecl"); }
  void visit_aliasrule(const AliasRule& n) { unsupported_traversal(n,"romp::AliasRule"); }
  void visit_aliasstmt(const AliasStmt& n) { unsupported_traversal(n,"romp::AliasStmt"); }
  void visit_and(const And& n) { unsupported_traversal(n,"romp::And"); }
//   void visit_array(const Array& n) { unsupported_traversal(n,"romp::Array"); }
  void visit_assignment(const Assignment& n) { unsupported_traversal(n,"romp::Assignment"); }
  void visit_band(const Band& n) { unsupported_traversal(n,"romp::Band"); }
  void visit_bnot(const Bnot& n) { unsupported_traversal(n,"romp::Bnot"); }
  void visit_bor(const Bor& n) { unsupported_traversal(n,"romp::Bor"); }
  void visit_clear(const Clear& n) { unsupported_traversal(n,"romp::Clear"); }
  void visit_constdecl(const ConstDecl& n) { unsupported_traversal(n,"romp::ConstDecl"); }
  void visit_div(const Div& n) { unsupported_traversal(n,"romp::Div"); }
  void visit_element(const Element& n) { unsupported_traversal(n,"romp::Element"); }
//   void visit_enum(const Enum& n) { unsupported_traversal(n,"romp::Enum"); }
  void visit_eq(const Eq& n) { unsupported_traversal(n,"romp::Eq"); }
  void visit_errorstmt(const ErrorStmt& n) { unsupported_traversal(n,"romp::ErrorStmt"); }
  void visit_exists(const Exists& n) { unsupported_traversal(n,"romp::Exists"); }
  void visit_exprid(const ExprID& n) { unsupported_traversal(n,"romp::ExprID"); }
  void visit_field(const Field& n) { unsupported_traversal(n,"romp::Field"); }
  void visit_for(const For& n) { unsupported_traversal(n,"romp::For"); }
  void visit_forall(const Forall& n) { unsupported_traversal(n,"romp::Forall"); }
  void visit_function(const Function& n) { unsupported_traversal(n,"romp::Function"); }
  void visit_functioncall(const FunctionCall& n) { unsupported_traversal(n,"romp::FunctionCall"); }
  void visit_geq(const Geq& n) { unsupported_traversal(n,"romp::Geq"); }
  void visit_gt(const Gt& n) { unsupported_traversal(n,"romp::Gt"); }
  void visit_if(const If& n) { unsupported_traversal(n,"romp::If"); }
  void visit_ifclause(const IfClause& n) { unsupported_traversal(n,"romp::IfClause"); }
  void visit_implication(const Implication& n) { unsupported_traversal(n,"romp::Implication"); }
  void visit_isundefined(const IsUndefined& n) { unsupported_traversal(n,"romp::IsUndefined"); }
  void visit_leq(const Leq& n) { unsupported_traversal(n,"romp::Leq"); }
  void visit_lsh(const Lsh& n) { unsupported_traversal(n,"romp::Lsh"); }
  void visit_lt(const Lt& n) { unsupported_traversal(n,"romp::Lt"); }
  void visit_model(const Model& n) { unsupported_traversal(n,"romp::Model"); }
  void visit_mod(const Mod& n) { unsupported_traversal(n,"romp::Mod"); }
  void visit_mul(const Mul& n) { unsupported_traversal(n,"romp::Mul"); }
  void visit_negative(const Negative& n) { unsupported_traversal(n,"romp::Negative"); }
  void visit_neq(const Neq& n) { unsupported_traversal(n,"romp::Neq"); }
  void visit_not(const Not& n) { unsupported_traversal(n,"romp::Not"); }
  void visit_number(const Number& n) { unsupported_traversal(n,"romp::Number"); }
  void visit_or(const Or& n) { unsupported_traversal(n,"romp::Or"); }
  void visit_procedurecall(const ProcedureCall& n) { unsupported_traversal(n,"romp::ProcedureCall"); }
  void visit_property(const Property& n) { unsupported_traversal(n,"romp::Property"); }
  void visit_propertyrule(const PropertyRule& n) { unsupported_traversal(n,"romp::PropertyRule"); }
  void visit_propertystmt(const PropertyStmt& n) { unsupported_traversal(n,"romp::PropertyStmt"); }
  void visit_put(const Put& n) { unsupported_traversal(n,"romp::Put"); }
  void visit_quantifier(const Quantifier& n) { unsupported_traversal(n,"romp::Quantifier"); }
//   void visit_range(const Range& n) { unsupported_traversal(n,"romp::Range"); }
//   void visit_record(const Record& n) { unsupported_traversal(n,"romp::Record"); }
  void visit_return(const Return& n) { unsupported_traversal(n,"romp::Return"); }
  void visit_rsh(const Rsh& n) { unsupported_traversal(n,"romp::Rsh"); }
  void visit_ruleset(const Ruleset& n) { unsupported_traversal(n,"romp::Ruleset"); }
//   void visit_scalarset(const Scalarset& n) { unsupported_traversal(n,"romp::Scalarset"); }
  void visit_simplerule(const SimpleRule& n) { unsupported_traversal(n,"romp::SimpleRule"); }
  void visit_startstate(const StartState& n) { unsupported_traversal(n,"romp::StartState"); }
  void visit_sub(const Sub& n) { unsupported_traversal(n,"romp::Sub"); }
  void visit_switch(const Switch& n) { unsupported_traversal(n,"romp::Switch"); }
  void visit_switchcase(const SwitchCase& n) { unsupported_traversal(n,"romp::SwitchCase"); }
  void visit_ternary(const Ternary& n) { unsupported_traversal(n,"romp::Ternary"); }
  void visit_typedecl(const TypeDecl& n) { unsupported_traversal(n,"romp::TypeDecl"); }
//   void visit_typeexprid(const TypeExprID& n) { unsupported_traversal(n,"romp::TypeExprID"); }
  void visit_undefine(const Undefine& n) { unsupported_traversal(n,"romp::Undefine"); }
  void visit_vardecl(const VarDecl& n) { unsupported_traversal(n,"romp::VarDecl"); }
  void visit_while(const While& n) { unsupported_traversal(n,"romp::While"); }
  void visit_xor(const Xor& n) { unsupported_traversal(n,"romp::Xor"); }

  void dispatch(const Node& n) { n.visit(*this); }
};
}