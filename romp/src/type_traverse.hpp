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
 * @brief a semi-abstract traverser that can take in a \c murphi::TypeExpr 
 *        and allows you to just write what happens when it encounters specific \c murphi::TypeExpr 's
 *        else throws a \c murphi::Error if it encounters a non-typeexpr \c murphi::Node , 
 *        with a configurable custom error message.
 * 
 * @date 2022/06/28
 * @version 0.2
 */

#pragma once

#include <murphi/rumur.h>
#include <string> 

namespace murphi {

class ConstBaseTypeTraversal : public murphi::ConstBaseTraversal {
protected:
  std::string msg;
  ConstBaseTypeTraversal(std::string& msg_) : msg(msg_) {}
  ConstBaseTypeTraversal(const char* msg_) : msg(msg_) {}
  void unsupported_traversal(const Node& n, const char* type_name) const { throw Error(" [" + std::string(type_name) +"] :: " + msg, n.loc); }
public:
  void visit_add(const Add& n) { unsupported_traversal(n,"murphi::Add"); }
  void visit_aliasdecl(const AliasDecl& n) { unsupported_traversal(n,"murphi::AliasDecl"); }
  void visit_aliasrule(const AliasRule& n) { unsupported_traversal(n,"murphi::AliasRule"); }
  void visit_aliasstmt(const AliasStmt& n) { unsupported_traversal(n,"murphi::AliasStmt"); }
  void visit_and(const And& n) { unsupported_traversal(n,"murphi::And"); }
//   void visit_array(const Array& n) { unsupported_traversal(n,"murphi::Array"); }
  void visit_assignment(const Assignment& n) { unsupported_traversal(n,"murphi::Assignment"); }
  void visit_band(const Band& n) { unsupported_traversal(n,"murphi::Band"); }
  void visit_bnot(const Bnot& n) { unsupported_traversal(n,"murphi::Bnot"); }
  void visit_bor(const Bor& n) { unsupported_traversal(n,"murphi::Bor"); }
  void visit_clear(const Clear& n) { unsupported_traversal(n,"murphi::Clear"); }
  void visit_constdecl(const ConstDecl& n) { unsupported_traversal(n,"murphi::ConstDecl"); }
  void visit_div(const Div& n) { unsupported_traversal(n,"murphi::Div"); }
  void visit_element(const Element& n) { unsupported_traversal(n,"murphi::Element"); }
//   void visit_enum(const Enum& n) { unsupported_traversal(n,"murphi::Enum"); }
  void visit_eq(const Eq& n) { unsupported_traversal(n,"murphi::Eq"); }
  void visit_errorstmt(const ErrorStmt& n) { unsupported_traversal(n,"murphi::ErrorStmt"); }
  void visit_exists(const Exists& n) { unsupported_traversal(n,"murphi::Exists"); }
  void visit_exprid(const ExprID& n) { unsupported_traversal(n,"murphi::ExprID"); }
  void visit_field(const Field& n) { unsupported_traversal(n,"murphi::Field"); }
  void visit_for(const For& n) { unsupported_traversal(n,"murphi::For"); }
  void visit_forall(const Forall& n) { unsupported_traversal(n,"murphi::Forall"); }
  void visit_function(const Function& n) { unsupported_traversal(n,"murphi::Function"); }
  void visit_functioncall(const FunctionCall& n) { unsupported_traversal(n,"murphi::FunctionCall"); }
  void visit_geq(const Geq& n) { unsupported_traversal(n,"murphi::Geq"); }
  void visit_gt(const Gt& n) { unsupported_traversal(n,"murphi::Gt"); }
  void visit_if(const If& n) { unsupported_traversal(n,"murphi::If"); }
  void visit_ifclause(const IfClause& n) { unsupported_traversal(n,"murphi::IfClause"); }
  void visit_implication(const Implication& n) { unsupported_traversal(n,"murphi::Implication"); }
  void visit_isundefined(const IsUndefined& n) { unsupported_traversal(n,"murphi::IsUndefined"); }
  void visit_leq(const Leq& n) { unsupported_traversal(n,"murphi::Leq"); }
  void visit_lsh(const Lsh& n) { unsupported_traversal(n,"murphi::Lsh"); }
  void visit_lt(const Lt& n) { unsupported_traversal(n,"murphi::Lt"); }
  void visit_model(const Model& n) { unsupported_traversal(n,"murphi::Model"); }
  void visit_mod(const Mod& n) { unsupported_traversal(n,"murphi::Mod"); }
  void visit_mul(const Mul& n) { unsupported_traversal(n,"murphi::Mul"); }
  void visit_negative(const Negative& n) { unsupported_traversal(n,"murphi::Negative"); }
  void visit_neq(const Neq& n) { unsupported_traversal(n,"murphi::Neq"); }
  void visit_not(const Not& n) { unsupported_traversal(n,"murphi::Not"); }
  void visit_number(const Number& n) { unsupported_traversal(n,"murphi::Number"); }
  void visit_or(const Or& n) { unsupported_traversal(n,"murphi::Or"); }
  void visit_procedurecall(const ProcedureCall& n) { unsupported_traversal(n,"murphi::ProcedureCall"); }
  void visit_property(const Property& n) { unsupported_traversal(n,"murphi::Property"); }
  void visit_propertyrule(const PropertyRule& n) { unsupported_traversal(n,"murphi::PropertyRule"); }
  void visit_propertystmt(const PropertyStmt& n) { unsupported_traversal(n,"murphi::PropertyStmt"); }
  void visit_put(const Put& n) { unsupported_traversal(n,"murphi::Put"); }
  void visit_quantifier(const Quantifier& n) { unsupported_traversal(n,"murphi::Quantifier"); }
//   void visit_range(const Range& n) { unsupported_traversal(n,"murphi::Range"); }
//   void visit_record(const Record& n) { unsupported_traversal(n,"murphi::Record"); }
  void visit_return(const Return& n) { unsupported_traversal(n,"murphi::Return"); }
  void visit_rsh(const Rsh& n) { unsupported_traversal(n,"murphi::Rsh"); }
  void visit_ruleset(const Ruleset& n) { unsupported_traversal(n,"murphi::Ruleset"); }
//   void visit_scalarset(const Scalarset& n) { unsupported_traversal(n,"murphi::Scalarset"); }
  void visit_simplerule(const SimpleRule& n) { unsupported_traversal(n,"murphi::SimpleRule"); }
  void visit_startstate(const StartState& n) { unsupported_traversal(n,"murphi::StartState"); }
  void visit_sub(const Sub& n) { unsupported_traversal(n,"murphi::Sub"); }
  void visit_switch(const Switch& n) { unsupported_traversal(n,"murphi::Switch"); }
  void visit_switchcase(const SwitchCase& n) { unsupported_traversal(n,"murphi::SwitchCase"); }
  void visit_ternary(const Ternary& n) { unsupported_traversal(n,"murphi::Ternary"); }
  void visit_typedecl(const TypeDecl& n) { unsupported_traversal(n,"murphi::TypeDecl"); }
//   void visit_typeexprid(const TypeExprID& n) { unsupported_traversal(n,"murphi::TypeExprID"); }
  void visit_undefine(const Undefine& n) { unsupported_traversal(n,"murphi::Undefine"); }
  void visit_vardecl(const VarDecl& n) { unsupported_traversal(n,"murphi::VarDecl"); }
  void visit_while(const While& n) { unsupported_traversal(n,"murphi::While"); }
  void visit_xor(const Xor& n) { unsupported_traversal(n,"murphi::Xor"); }

  void dispatch(const Node& n) { n.visit(*this); }
};
}