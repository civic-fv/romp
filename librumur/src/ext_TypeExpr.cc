#include "../../common/isa.h"
#include <cassert>
#include <cstddef>
#include <gmpxx.h>
#include <iostream>
#include <limits.h>
#include <memory>
#include <rumur/Decl.h>
#include <rumur/Expr.h>
#include <rumur/Number.h>
#include <rumur/Ptr.h>
#include <rumur/ext/TypeExpr.h>
#include <rumur/except.h>
#include <rumur/ext/traverse.h>
#include <rumur/Boolean.h>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <functional>
#include <algorithm>

namespace rumur {
namespace ext {


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
    count += m->count() - 1; //remove undefined from considerations of each union member
  return count + 1;  // add in undefined value for the scalarset
}
std::string ScalarsetUnion::upper_bound() const {
  mpz_class size = count() - 1; // -1 to remove undefined value added in count 
  if (size > 0)
    --size; // & -1 to slide range down to start at 0 if it contains anything
  return "VALUE_C(" + size.get_str() + ")";
}
std::string ScalarsetUnion::lower_bound() const { return "VALUE_C(0)"; }

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
  /* Do nothing; new design removed the messy exp_members solution */
  // std::unordered_set<std::string> handled{name,""};
  // auto _union = [&](ScalarsetUnion& ssu, mpz_class _sum=1_mpz, std::unordered_set<std::string> _handled) -> mpz_class { // start at 1 to include undefined
  //   struct _Union : public ext::ConstExtTypeTraversal {
  //     mpz_class sum;
  //     std::unordered_set<std::string> handled;
  //     _Union(mpz_class sum_) : sum(sum_) {}
  //     auto try_insert(std::string& name, ScalarsetUnionMember& value) -> bool {
  //       if (handled.find(name) != handled.end()) 
  //         return false;
  //       handled.insert(value);
  //       return true;
  //     }
  //     auto _union_enum(Enum& e, mpz_class _sum) -> mpz_class {
  //       for (auto m : e.members)
  //           if (try_insert("_enum_"+m.first))
  //             ++_sum;
  //       return _sum;
  //     }
  //     void visit_array(const Array &n) final { throw Error("arrays are not allowed in unions", n.loc); }
  //
  //     void visit_enum(const Enum &n) final { sum = _union_enum(n,sum); } // inline enum TypeExpr
  //
  //     void visit_multiset(const Multiset& n) { throw Error("multisets are not allowed in unions", n.loc); }
  //     void visit_range(const Range &n) final { throw Error("ranges are not allowed in unions", n.loc); }
  //     void visit_record(const Record &n) final { throw Error("records are not allowed in unions", n.loc); }
  //
  //     void visit_scalarset(const Scalarset &n) final { throw Error("unnamed scalarsets are not allowed in unions", n.loc); }
  //
  //     void visit_scalarsetunion(const ScalarsetUnion& n) { // inline union TypeExpr
  //       throw Error("unnamed scalarset unions are not allowed in unions", n.loc); 
  //     }
  //
  //     void visit_typeexprid(const TypeExprID &n) final {
  //       mpz_class count = 0_mpz;
  //       auto _t = n.resolve();
  //       if (const auto _u = dynamic_cast<const ScalarsetUnion*>(_t.get())) { // prev decl union
  //         count = _union(*_u,sum);
  //       } else if (const auto _e = dynamic_cast<const Enum*>(_t.get())) { // prev decl enum
  //         count = _union_enum(*_e,sum); // don't save resulting sum, going to add that with the count measure below
  //       } else { // should be a scalarset (validate should catch if it is not)
  //         count = n.count()-1; // remove undefined from this entries considerations
  //       }
  //       if (try_insert(n.name,ScalarsetUnionMember(Ptr<TypeExprID>(n),sum,sum+count-1)))
  //         sum += count;
  //     }
  //   };
  //   _Union un(_sum);
  //   std::vector<Ptr<TypeExprID>> orderings;
  //   auto u_pos = orderings.begin();
  //   for (auto m : ssu.members) // proccess unions first
  //     if (isa<ScalarsetUnion>(m->resolve()))
  //       u_pos = orderings.insert(u_pos, m);
  //     else
  //       orderings.push_back(m);
  //   for (auto _m : orderings)
  //       un.dispatch(*_m);
  //   return un.sum;
  // };
  // members_exp.clear();
  // _union(*this);
}

std::string ScalarsetUnion::to_string() const {
  std::stringstream buf;
  buf << "union {";
  std::string sep;
  for (const auto _m : members) {
    buf << sep << _m.value->to_string();
    sep = ", ";
  }
  buf << '}';
  return buf.str();
}

bool ScalarsetUnion::contains(const TypeExpr& n) const {
  struct Contain : public ConstExtTypeTraversal {
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
          therefore, one scalarset only contains the other if they are equal 
                      (just equal NOT necessarily abs_equal) */ 
      result = u.equal_to(n);
      // // a union `this` can only contain another scalarset union `n`...
      // //  IF it meets the same conditions as a scalarset to be contained in this union
      // //  AND `this` contains ALL of the children of `n`
      // visit_scalarset(n);
      // if (not result) return; // failed scalarset test
      // for (const auto m : n.members)
      //   result &= u.contains(*m);
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

bool ScalarsetUnion::abs_equal_to(const ScalarsetUnion& other) const {
  class Next {
    const ScalarsetUnion& u;
    std::vector<Ptr<TypeExpr>>::iterator i;
    Ptr<Enum> e;
    typeof(rumur::Boolean->members.end()) ei;
  public:
    Next(const ScalarsetUnion& u_) : u(u_), i(u_.members.begin()), e(nullptr) {}
    bool end() { return i == u.members.end(); }
    std::string operator () () { return _next(); }
  protected:
    std::string _next() { // all this to make sure we don't care how they group enums
      std::string name = "";
      if (e != nullptr) { // we are in an enum
        name = "_enum_" + ei->first;  // prepend "_enum_" to distinguish enum vales from type expr's
        ++ei;
        if (ei == e->members.end()) {
          e = nullptr;
          ++i;
        }
      } else {
        auto t = i->resolve();
        if (const auto _e = dynamic_cast<const Enum*>(t.get())) {
          e = Ptr<Enum>(_e);
          ei = e->members.begin();
          return _next();
        } else if (const auto _s = dynamic_cast<const Scalarset*>(t.get()) {
          name = _s->name;
          ++i;
        }
      }
      return name;
    }
  };
  std::unordered_set<std::string> handled{name,other.name,""};
  Next this_next(*this);
  Next other_next(other);
  bool result = true;
  while (result && !(this_next.end() || other_next.end())) {
    auto i = this_next();
    while (handled.find(i) != handled.end()) { i = this_next(); } // ignore duplicated i elements
    auto j = other_next();
    while (handled.find(j) != handled.end()) { j = other_next(); } // ignore duplicate j elements
    result &= (i == j);
    handled.insert(i); // only need to add i or j since the while loop will stop if result is ever false.
  }
}

Ptr<Scalarset> ScalarsetUnion::make_legacy() const {
  std::unordered_set<std::string> handled{name,""}; // ignore self and never add unnamed
  auto res = Ptr<Scalarset>(gen_legacy_bound(handled),loc);
  res->name = name;
  return res;
}

Ptr<Add> ScalarsetUnion::gen_legacy_bound(std::unordered_set<std::string>& handled) const {
  auto _extend = [&](Ptr<Add>& add, int i=0) -> void {
    if (i<members.size()) { // base case end of assets
      // add->rhs = Ptr<Number>::make(0_mpz,location());
      return;
    }
    Ptr<Expr> _bound = nullptr; 
    if (const auto _u = dynamic_cast<const ScalarSetUnion*>(members[i])) {
      if (_u->name == "")
        throw Error("A union can't contain an unnamed union",_u->loc);
      if (handled.find(_u->name) != handled.end()) {
        handled.insert(_u->name);
        _bound = _u->gen_legacy_bound(handled);
      }
    } else if (const auto _e = dynamic_cast<const Enum*>(members[i])) {
      mpz_class count = 0_mpz;
      for (const auto m : _e->members)
        if (handled.find("_enum_"+m.first) != handled.end()) {
          handled.insert("_enum_"+m.first);
          ++count;
      _bound = Ptr<Number>::make(count,_e->loc);
    } else if (const auto _s = dynamic_cast<const Scalarset*>(members[i])) {
      if (_s->name == "")
        throw Error("A union can't contain an unnamed scalarset",_u->loc);
      handled.insert(_s->name);
      _bound = _s->bound;
    }
    add->rhs = Ptr<Add>::make(
                  _bound,
                  Ptr<Number>::make(0_mpz,location()),
                  loc);
    _extend(add->rhs,++i);
  };
  auto bound = Ptr<Add>::make(Ptr<Number>::make(0_mpz,location()),
                              Ptr<Number>::make(0_mpz,location()),
                              loc);
  _extend(bound);
  return bound;
}

// << ------------------------------------------------------------------------------------------ >> 

Multiset::Multiset(const Ptr<Expr> size_, const Ptr<TypeExpr> element_type_, const location loc_)
  : Array(nullptr, element_type_, loc), size(size_) {}

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

Ptr<Array> Multiset::make_legacy() const { 
  return Ptr<Array>(Ptr<Range>::make(Ptr<Number>::make(1_mpz,location()), size, size->loc),
                    element_type, loc);
}


} //namespace ext
} //namespace rumur
