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
 * @version 0.2
 */

#pragma once

#include "CLikeGenerator.hpp"
// #include "IndType.hpp"
// #include <murphi/rumur.h>
#include <unordered_set>
#include <functional>


namespace romp {


class CTypeGenerator : public CLikeGenerator {
private:

  

protected:
  std::function<void(const murphi::ConstDecl&)> f_visit_constdecl;

public:
  CTypeGenerator(const std::vector<murphi::Comment> &comments_, const std::vector<bool>& emitted_,
                 std::ostream &out_, bool pack_, 
                 std::function<void(const murphi::ConstDecl&)> f_visit_constdecl_)
              : CLikeGenerator(comments_, out_, pack_), f_visit_constdecl(f_visit_constdecl_)
                { emitted = emitted_; }

public:

  void visit_typedecl(const murphi::TypeDecl &n) final;
  void visit_array(const murphi::Array &n) final;
  void visit_enum(const murphi::Enum &n) final;
  void visit_range(const murphi::Range &n) final;
  void visit_record(const murphi::Record &n) final;
  void visit_scalarset(const murphi::Scalarset &) final;
  // void visit_indtype(const IndType &n);

  void visit_constdecl(const murphi::ConstDecl &n) final { f_visit_constdecl(n); }
  // void visit_vardecl(const murphi::VarDecl &n) final;

  // - make this class non-abstract ---- 
  void visit_function(const murphi::Function &n) { __throw_unreachable_error(n); }
  void visit_propertyrule(const murphi::PropertyRule &n) { __throw_unreachable_error(n); }
  void visit_simplerule(const murphi::SimpleRule &n) { __throw_unreachable_error(n); }
  void visit_startstate(const murphi::StartState &n) { __throw_unreachable_error(n); }
  void visit_vardecl(const murphi::VarDecl &n) { __throw_unreachable_error(n); }


protected:
  void emit_stream_operators(const std::string &name, const murphi::Ptr<const murphi::TypeExpr> &te);

public:
  void emit_stream_operators__array(const std::string &name, const murphi::Array &te);
  void emit_stream_operators__enum(const std::string &name, const murphi::Enum &te);
  void emit_stream_operators__record(const std::string &name, const murphi::Record &te);
  void emit_stream_operators__range(const std::string &name, const murphi::Range &te);
  void emit_stream_operators__scalarset(const std::string &name, const murphi::Scalarset &te);
  void emit_stream_operators__typeexprid(const std::string &name, const murphi::TypeExprID &te);

protected:
  void __throw_unreachable_error(const murphi::Node &n);

};

}
