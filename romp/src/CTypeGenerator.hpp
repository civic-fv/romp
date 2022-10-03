/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file CTypeGenerator.hpp
 * 
 * @brief An AST traversing structure that can only handle generating Types.
 * 
 * @date 2022/06/06
 * @version 0.1
 */

#pragma once

#include "CLikeGenerator.hpp"
// #include "IndType.hpp"
// #include <rumur/rumur.h>
#include <unordered_set>
#include <functional>


namespace romp {


class CTypeGenerator : public CLikeGenerator {
private:

  

protected:
  std::function<void(const rumur::ConstDecl&)> f_visit_constdecl;

public:
  CTypeGenerator(const std::vector<rumur::Comment> &comments_, const std::vector<bool>& emitted_,
                 std::ostream &out_, bool pack_, 
                 std::function<void(const rumur::ConstDecl&)> f_visit_constdecl_)
              : CLikeGenerator(comments_, out_, pack_), f_visit_constdecl(f_visit_constdecl_)
                { emitted = emitted_; }

public:

  void visit_typedecl(const rumur::TypeDecl &n) final;
  void visit_array(const rumur::Array &n) final;
  void visit_enum(const rumur::Enum &n) final;
  void visit_range(const rumur::Range &n) final;
  void visit_record(const rumur::Record &n) final;
  void visit_scalarset(const rumur::Scalarset &) final;
  // void visit_indtype(const IndType &n);

  void visit_constdecl(const rumur::ConstDecl &n) final { f_visit_constdecl(n); }
  // void visit_vardecl(const rumur::VarDecl &n) final;

  // - make this class non-abstract ---- 
  void visit_function(const rumur::Function &n) { __throw_unreachable_error(n); }
  void visit_propertyrule(const rumur::PropertyRule &n) { __throw_unreachable_error(n); }
  void visit_simplerule(const rumur::SimpleRule &n) { __throw_unreachable_error(n); }
  void visit_startstate(const rumur::StartState &n) { __throw_unreachable_error(n); }
  void visit_vardecl(const rumur::VarDecl &n) { __throw_unreachable_error(n); }


protected:
  void emit_stream_operators(const std::string &name, const rumur::Ptr<const rumur::TypeExpr> &te);

public:
  void emit_stream_operators__array(const std::string &name, const rumur::Array &te);
  void emit_stream_operators__enum(const std::string &name, const rumur::Enum &te);
  void emit_stream_operators__record(const std::string &name, const rumur::Record &te);
  void emit_stream_operators__range(const std::string &name, const rumur::Range &te);
  void emit_stream_operators__scalarset(const std::string &name, const rumur::Scalarset &te);
  void emit_stream_operators__typeexprid(const std::string &name, const rumur::TypeExprID &te);

protected:
  void __throw_unreachable_error(const rumur::Node &n);

};

}
