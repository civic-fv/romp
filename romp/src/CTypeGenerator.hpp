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
// #include <romp/romp.h>
#include <unordered_set>
#include <functional>


namespace romp {


class CTypeGenerator : public CLikeGenerator {
private:

  

protected:
  std::function<void(const romp::ConstDecl&)> f_visit_constdecl;

public:
  CTypeGenerator(const std::vector<romp::Comment> &comments_, const std::vector<bool>& emitted_,
                 std::ostream &out_, bool pack_, 
                 std::function<void(const romp::ConstDecl&)> f_visit_constdecl_)
              : CLikeGenerator(comments_, out_, pack_), f_visit_constdecl(f_visit_constdecl_)
                { emitted = emitted_; }

public:

  void visit_typedecl(const romp::TypeDecl &n) final;
  void visit_array(const romp::Array &n) final;
  void visit_enum(const romp::Enum &n) final;
  void visit_range(const romp::Range &n) final;
  void visit_record(const romp::Record &n) final;
  void visit_scalarset(const romp::Scalarset &) final;
  // void visit_indtype(const IndType &n);

  void visit_constdecl(const romp::ConstDecl &n) final { f_visit_constdecl(n); }
  // void visit_vardecl(const romp::VarDecl &n) final;

  // - make this class non-abstract ---- 
  void visit_function(const romp::Function &n) { __throw_unreachable_error(n); }
  void visit_propertyrule(const romp::PropertyRule &n) { __throw_unreachable_error(n); }
  void visit_simplerule(const romp::SimpleRule &n) { __throw_unreachable_error(n); }
  void visit_startstate(const romp::StartState &n) { __throw_unreachable_error(n); }
  void visit_vardecl(const romp::VarDecl &n) { __throw_unreachable_error(n); }


protected:
  void emit_stream_operators(const std::string &name, const romp::Ptr<const romp::TypeExpr> &te);

public:
  void emit_stream_operators__array(const std::string &name, const romp::Array &te);
  void emit_stream_operators__enum(const std::string &name, const romp::Enum &te);
  void emit_stream_operators__record(const std::string &name, const romp::Record &te);
  void emit_stream_operators__range(const std::string &name, const romp::Range &te);
  void emit_stream_operators__scalarset(const std::string &name, const romp::Scalarset &te);
  void emit_stream_operators__typeexprid(const std::string &name, const romp::TypeExprID &te);

protected:
  void __throw_unreachable_error(const romp::Node &n);

};

}
