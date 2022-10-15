#include "../../common/isa.h"
#include <cassert>
#include <cstddef>
#include <gmpxx.h>
#include <iostream>
#include <limits.h>
#include <memory>
#include <murphi/Decl.h>
#include <murphi/Expr.h>
#include <murphi/Number.h>
#include <murphi/Ptr.h>
#include <murphi/TypeExpr.h>
#include <murphi/except.h>
#include <murphi/traverse.h>
#include <murphi/Boolean.h>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <functional>
#include <algorithm>

namespace murphi {



ScalarsetUnion::ScalarsetUnion(const std::vector<Ptr<TypeExpr>>& members_, const location &loc_) 
  : TypeExpr(loc_), members(members_), name("") {}
ScalarsetUnion::ScalarsetUnion(const std::vector<Ptr<TypeExpr>>& members_, 
                               const std::string& name_, const location &loc_) 
  : TypeExpr(loc_), members(members_), name(name_) {}
ScalarsetUnion* ScalarsetUnion::clone() const { return new ScalarsetUnion(*this); }

void ScalarsetUnion::visit(BaseTraversal &visitor) { visitor.visit_scalarsetunion(*this); }
void ScalarsetUnion::visit(ConstBaseTraversal &visitor) const { visitor.visit_scalarsetunion(*this); }

mpz_class ScalarsetUnion::count() const {
  mpz_class count = 0_mpz;
  for (const Ptr<TypeExpr> m : members)
    count += m->count();
  return count;
}
std::string ScalarsetUnion::upper_bound() const {
  mpz_class size = count();
  return "VALUE_C(" + size.get_str() + ")";
}
std::string ScalarsetUnion::lower_bound() const { return "VALUE_C(1)"; }

void ScalarsetUnion::validate() const { 
  for (const auto _m : members) {
    const auto m = _m->resolve();
    if (isa<Enum>(m)) {
      if (m->count() <= 0)
        throw Error("ScalarsetUnions require included enums to define at least 1 member!",_m->loc);
      continue;
    } else if (isa<TypeExprID>(_m) && isa<Scalarset>(m)) {
      continue;
    }
    throw Error("ScalarsetUnion can only union: enums, and named Scalarsets.", _m->loc);
  }
}
bool ScalarsetUnion::is_useful() const {
  bool useful = false;
  for (const auto m : members)
    if (isa<Scalarset>(m)) {
      if (isa<ScalarsetUnion>(m))
        useful |= m->is_useful();
    }
  return (useful && count() > 1_mpz); // @Smattr you might want to tweak this comparison, too
}
void ScalarsetUnion::update() {
  // do nothing in current design
}

std::string ScalarsetUnion::to_string() const {
  std::stringstream buf;
  buf << "union {";
  std::string sep;
  for (const auto _m : members) {
    buf << sep << _m->to_string();
    sep = ", ";
  }
  buf << '}';
  return buf.str();
}

bool ScalarsetUnion::contains(const TypeExpr& n) const {
  struct Contain : public ConstTypeTraversal {
    bool result = false;
    const ScalarsetUnion& u;
    Contain(const ScalarsetUnion& u_) : u(u_) {} 
    void visit_array(const Array &n) final { result = false; }

    void visit_enum(const Enum &n) final {
      auto r = std::find_if(u.members.begin(),u.members.end(), [&](Ptr<TypeExpr> i) -> bool {
        if (const auto _e = dynamic_cast<const Enum*>(i->resolve().get()))
          return (n.equal_to(*_e));
        return false;
      });
      result = (r == u.members.end());
    }

    void visit_multiset(const Multiset& n) { result = false; }
    void visit_range(const Range &n) final { result = false; }
    void visit_record(const Record &n) final { result = false; }

    void visit_scalarset(const Scalarset &n) final {
      auto r = std::find_if(u.members.begin(),u.members.end(), [&](Ptr<TypeExpr> i) -> bool {
        if (const auto _tid = dynamic_cast<const TypeExprID*>(i.get()))
          if (const auto _s = dynamic_cast<const Scalarset*>(i->resolve().get()))
            return ((n.name==_tid->name) 
                    && (n.bound->constant_fold() == _s->bound->constant_fold()));
        return false;
      });
      result = (r == u.members.end());
    }

    void visit_scalarsetunion(const ScalarsetUnion& n) {
      /* new design does not allow for nesting unions (makes things cleaner).
          therefore, one scalarset only contains the other if they are equal */ 
      result = u.equal_to(n);
    }

    void visit_typeexprid(const TypeExprID &n) final {
      auto r = std::find_if(u.members.begin(),u.members.end(), [&](Ptr<TypeExpr> i) -> bool {
        if (const auto _tid = dynamic_cast<const TypeExprID*>(i.get()))
          return ((n.name==_tid->name) && (n.equal_to(*i)));
        return false;
      });
      result = (r == u.members.end());
    }
  };
  Contain c(*this);
  c.dispatch(n);
  return c.result;
}


// << ------------------------------------------------------------------------------------------ >> 


Multiset::Multiset(const Ptr<Expr>& size_, const Ptr<TypeExpr>& element_type_, const location& loc_)
  : TypeExpr(loc_), element_type(element_type_), size(size_) {}

Multiset* Multiset::clone() const { return new Multiset(*this); }

void Multiset::visit(BaseTraversal& visitor) { visitor.visit_multiset(*this); }
void Multiset::visit(ConstBaseTraversal& visitor) const { visitor.visit_multiset(*this); }

void Multiset::update() {
  // nothing to do here (moved to make legacy)
}
void Multiset::validate() const {
  if (size->is_boolean())
    throw Error("Multiset size constraint must be a number not a boolean!", size->loc);
  if (not size->constant())
    throw Error("Multiset size constraint must be constant and inferable at compile time!", size->loc);
}
std::string Multiset::to_string() const {
  return "multiset [" + size->to_string() + "] of " + element_type->to_string();
}


} //namespace murphi
