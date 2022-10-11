/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file StateSpaceCalc.hpp
 * 
 * @brief Simple utility to calculate the total number of possible permutations 
 *        a murphi models state can be in.
 * 
 * @date 2022/08/19
 * @version 0.2
 */


#include "StateSpaceCalc.hpp"
#include "type_traverse.hpp"
#include <cmath>

namespace romp {

mpz_class statespace_count(const murphi::Record& n) {
  struct state_perm : public murphi::ConstBaseTypeTraversal {
    mpz_class perm = 1_mpz;
  public: state_perm() : ConstBaseTypeTraversal("was not a type") {}
  protected:
    void visit_array(const murphi::Array& n) { 
      mpz_class count = n.index_type->count();
      state_perm elm; elm.dispatch(*n.element_type);
      mpz_class arr_perm(std::pow(elm.perm.get_ui(),count.get_ui()));
      perm *= arr_perm;
    }
    void visit_record(const murphi::Record& n) { 
      state_perm field;
      for (const auto& f: n.fields) {
        if (f == nullptr) continue;
        field.perm = 1_mpz; field.dispatch(*f->type);
        perm *= field.perm;
      }
    }
    void visit_typeexprid(const murphi::TypeExprID& n) { 
      dispatch(*n.referent->value);
    }
    void visit_enum(const murphi::Enum& n) {
      perm *= n.count();
    }
    void visit_range(const murphi::Range& n) {
      perm *= n.count();
    }
    void visit_scalarset(const murphi::Scalarset& n) {
      perm *= n.count();
    }
  };
  state_perm sp; sp.dispatch(n);
  return sp.perm;
}
}