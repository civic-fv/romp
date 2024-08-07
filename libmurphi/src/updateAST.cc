#include "../../common/isa.h"
#include "location.hh"
#include <cassert>
#include <cstddef>
#include <gmpxx.h>
#include <memory>
#include <murphi/Boolean.h>
#include <murphi/Decl.h>
#include <murphi/Expr.h>
#include <murphi/Model.h>
#include <murphi/Node.h>
#include <murphi/Number.h>
#include <murphi/Ptr.h>
#include <murphi/Rule.h>
#include <murphi/Stmt.h>
#include <murphi/Symtab.h>
#include <murphi/TypeExpr.h>
#include <murphi/updateAST.h>
#include <murphi/validate.h>
#include <murphi/traverse.h>
#include <string>
#include <queue>
#include <utility>

using namespace murphi;
// using namespace murphi::ext;

namespace {


class Resolver : public Traversal {

private:
  Symtab symtab;
  Symtab ms_quantifiers;

public:
  Resolver() {

    // Open a global scope
    symtab.open_scope();

    // Teach the symbol table the built ins
    symtab.declare("boolean", BooleanDecl);
    symtab.declare("true", TrueDecl);
    symtab.declare("false", FalseDecl);
  }

  void visit_add(Add &n) final { visit_bexpr(n); }

  void visit_aliasdecl(AliasDecl &n) final {
    dispatch(*n.value);
    disambiguate(n.value);
  }

  void visit_aliasrule(AliasRule &n) final {
    symtab.open_scope();
    for (auto &a : n.aliases) {
      dispatch(*a);
      symtab.declare(a->name, a);
    }
    for (auto &r : n.rules)
      dispatch(*r);
    symtab.close_scope();
  }

  void visit_aliasstmt(AliasStmt &n) final {
    symtab.open_scope();
    for (auto &a : n.aliases) {
      dispatch(*a);
      symtab.declare(a->name, a);
    }
    for (auto &s : n.body)
      dispatch(*s);
    symtab.close_scope();
  }

  void visit_ambiguousamp(AmbiguousAmp &n) final { visit_bexpr(n); }

  void visit_ambiguouspipe(AmbiguousPipe &n) final { visit_bexpr(n); }

  void visit_and(And &n) final { visit_bexpr(n); }

  void visit_assignment(Assignment &n) final {
    dispatch(*n.lhs);
    dispatch(*n.rhs);
    disambiguate(n.lhs);
    disambiguate(n.rhs);
  }

  void visit_band(Band &n) final { visit_bexpr(n); }

  void visit_bnot(Bnot &n) final { visit_uexpr(n); }

  void visit_bor(Bor &n) final { visit_bexpr(n); }

  void visit_clear(Clear &n) final {
    dispatch(*n.rhs);
    disambiguate(n.rhs);
  }

  void visit_constdecl(ConstDecl &n) final {
    dispatch(*n.value);
    disambiguate(n.value);
  }

  void visit_div(Div &n) final { visit_bexpr(n); }

  void visit_element(Element &n) final {
    dispatch(*n.array);
    dispatch(*n.index);
    disambiguate(n.array);
    disambiguate(n.index);
  }

  void visit_enum(Enum &n) final {
    auto e = Ptr<Enum>::make(n);

    // register all the enum members so they can be referenced later
    mpz_class index = 0;
    size_t id = e->unique_id + 1;
    for (const std::pair<std::string, location> &m : n.members) {
      auto cd = Ptr<ConstDecl>::make(
          m.first, Ptr<Number>::make(index, m.second), e, m.second);
      // assign this member a unique id so that referrers can use it if need be
      assert(id < e->unique_id_limit &&
             "number of enum members exceeds what was expected");
      cd->unique_id = id;
      symtab.declare(m.first, cd);
      index++;
      id++;
    }
  }

  void visit_eq(Eq &n) final { visit_bexpr(n); }

  void visit_exists(Exists &n) final {
    symtab.open_scope();
    dispatch(n.quantifier);
    dispatch(*n.expr);
    symtab.close_scope();
    disambiguate(n.expr);
  }

  void visit_exprid(ExprID &n) final {
    if (n.value == nullptr) {
      // This reference is unresolved

      // if (n.is_literal_true())
      //   n.value = True;
      // else if (n.is_literal_false())
      //   n.value = False;
      // else {
        Ptr<ExprDecl> d = symtab.lookup<ExprDecl>(n.id, n.loc);
        if (d == nullptr)
          throw Error("unknown symbol \"" + n.id + "\"", n.loc);

        n.value = d;
      // }
    }
  }

  void visit_field(Field &n) final {
    dispatch(*n.record);
    disambiguate(n.record);
  }

  void visit_for(For &n) final {
    symtab.open_scope();
    dispatch(n.quantifier);
    for (auto &s : n.body)
      dispatch(*s);
    symtab.close_scope();
  }

  void visit_forall(Forall &n) final {
    symtab.open_scope();
    dispatch(n.quantifier);
    dispatch(*n.expr);
    symtab.close_scope();
    disambiguate(n.expr);
  }

  void visit_function(Function &n) final {
    symtab.open_scope();
    for (auto &p : n.parameters)
      dispatch(*p);
    if (n.return_type != nullptr)
      dispatch(*n.return_type);
    // register the function itself, even though its body has not yet been
    // resolved, in order to allow contained function calls to resolve to the
    // containing function, supporting recursion
    symtab.declare(n.name, Ptr<Function>::make(n));
    // only register the function parameters now, to avoid their names shadowing
    // anything that needs to be resolved during symbol resolution of another
    // parameter or the return type
    for (auto &p : n.parameters)
      symtab.declare(p->name, p);
    for (auto &d : n.decls) {
      dispatch(*d);
      symtab.declare(d->name, d);
    }
    for (auto &s : n.body)
      dispatch(*s);
    symtab.close_scope();
  }

  void visit_functioncall(FunctionCall &n) final {
    if (n.function == nullptr) {
      // This reference is unresolved

      Ptr<Function> f = symtab.lookup<Function>(n.name, n.loc);
      if (f == nullptr)
        throw Error("unknown function call \"" + n.name + "\"", n.loc);

      n.function = f;
    }
    for (auto &a : n.arguments)
      dispatch(*a);

    for (Ptr<Expr> &a : n.arguments)
      disambiguate(a);
  }

  void visit_geq(Geq &n) final { visit_bexpr(n); }

  void visit_gt(Gt &n) final { visit_bexpr(n); }

  void visit_ifclause(IfClause &n) final {
    if (n.condition != nullptr)
      dispatch(*n.condition);
    for (auto &s : n.body)
      dispatch(*s);
    if (n.condition != nullptr)
      disambiguate(n.condition);
  }

  void visit_implication(Implication &n) final { visit_bexpr(n); }

  void visit_isundefined(IsUndefined &n) final { visit_uexpr(n); }

  void visit_leq(Leq &n) final { visit_bexpr(n); }

  void visit_lsh(Lsh &n) final { visit_bexpr(n); }

  void visit_lt(Lt &n) final { visit_bexpr(n); }

  void visit_model(Model &n) final {

    // running marker of offset in the global state data
    mpz_class offset = 0;

    /* whether we have not yet hit any problems that make offset calculation
     * impossible
     */
    bool ok = true;

    for (Ptr<Node> &c : n.children) {
      dispatch(*c);

      /* if this was a variable declaration, we now know enough to determine its
       * offset in the global state data
       */
      if (ok) {
        if (auto v = dynamic_cast<VarDecl *>(c.get())) {

          /* If the declaration or one of its children does not validate, it is
           * unsafe to call width().
           */
          try {
            validate(*v);
          } catch (Error &) {
            /* Skip this and future offset calculations and assume our caller
             * will eventually discover the underlying reason when they call
             * n.validate().
             */
            ok = false;
          }

          if (ok) {
            v->offset = offset;
            offset += v->type->width();
          }
        }
      }

      if (auto d = dynamic_cast<Decl *>(c.get()))
        symtab.declare(d->name, c);
      if (auto f = dynamic_cast<Function *>(c.get()))
        symtab.declare(f->name, c);
    }
  }

  void visit_mod(Mod &n) final { visit_bexpr(n); }

  void visit_mul(Mul &n) final { visit_bexpr(n); }

  void visit_negative(Negative &n) final { visit_uexpr(n); }

  void visit_neq(Neq &n) final { visit_bexpr(n); }

  void visit_not(Not &n) final { visit_uexpr(n); }

  void visit_or(Or &n) final { visit_bexpr(n); }

  void visit_property(Property &n) final {
    dispatch(*n.expr);
    disambiguate(n.expr);
  }

  void visit_put(Put &n) final {
    if (n.expr != nullptr) {
      dispatch(*n.expr);
      disambiguate(n.expr);
    }
  }

  void visit_quantifier(Quantifier &n) final {
    if (n.type != nullptr) {
      // wrap symbol resolution within the type in a dummy scope to suppress any
      // declarations (primarily enum members) as these will be duplicated in
      // when we descend into decl below
      symtab.open_scope();
      dispatch(*n.type);
      symtab.close_scope();
    }
    if (n.from != nullptr)
      dispatch(*n.from);
    if (n.to != nullptr)
      dispatch(*n.to);
    if (n.step != nullptr)
      dispatch(*n.step);

    if (n.from != nullptr)
      disambiguate(n.from);
    if (n.to != nullptr)
      disambiguate(n.to);
    if (n.step != nullptr)
      disambiguate(n.step);

    // if the bounds for this iteration are now known to be constant, we can
    // narrow its VarDecl
    if (n.from != nullptr && n.from->constant() && n.to != nullptr &&
        n.to->constant()) {
      auto r = dynamic_cast<Range *>(n.decl->type.get());
      assert(r != nullptr && "non-range type used for inferred loop decl");
      // the range may have been given as either an up count or down count
      if (n.from->constant_fold() <= n.to->constant_fold()) {
        r->min = n.from;
        r->max = n.to;
      } else {
        r->min = n.to;
        r->max = n.from;
      }
    }

    dispatch(*n.decl);

    symtab.declare(n.name, n.decl);
  }

  void visit_range(Range &n) final {
    dispatch(*n.min);
    disambiguate(n.min);
    dispatch(*n.max);
    disambiguate(n.max);
  }

  void visit_return(Return &n) final {
    if (n.expr != nullptr) {
      dispatch(*n.expr);
      disambiguate(n.expr);
    }
  }

  void visit_rsh(Rsh &n) final { visit_bexpr(n); }

  void visit_ruleset(Ruleset &n) final {
    symtab.open_scope();
    for (Quantifier &q : n.quantifiers)
      dispatch(q);
    for (auto &r : n.rules)
      dispatch(*r);
    symtab.close_scope();
  }

  void visit_scalarset(Scalarset &n) final {
    dispatch(*n.bound);
    disambiguate(n.bound);
  }

  void visit_simplerule(SimpleRule &n) final {
    symtab.open_scope();
    for (Quantifier &q : n.quantifiers)
      dispatch(q);
    if (n.guard != nullptr)
      dispatch(*n.guard);
    for (auto &d : n.decls) {
      dispatch(*d);
      symtab.declare(d->name, d);
    }
    for (auto &s : n.body)
      dispatch(*s);
    symtab.close_scope();
    if (n.guard != nullptr)
      disambiguate(n.guard);
  }

  void visit_startstate(StartState &n) final {
    symtab.open_scope();
    for (Quantifier &q : n.quantifiers)
      dispatch(q);
    for (auto &d : n.decls) {
      dispatch(*d);
      symtab.declare(d->name, d);
    }
    for (auto &s : n.body)
      dispatch(*s);
    symtab.close_scope();
  }

  void visit_sub(Sub &n) final { visit_bexpr(n); }

  void visit_switch(Switch &n) final {
    dispatch(*n.expr);
    for (SwitchCase &c : n.cases)
      dispatch(c);
    disambiguate(n.expr);
  }

  void visit_switchcase(SwitchCase &n) final {
    for (auto &m : n.matches)
      dispatch(*m);
    for (auto &s : n.body)
      dispatch(*s);
    for (Ptr<Expr> &m : n.matches)
      disambiguate(m);
  }

  void visit_ternary(Ternary &n) final {
    dispatch(*n.cond);
    dispatch(*n.lhs);
    dispatch(*n.rhs);
    disambiguate(n.cond);
    disambiguate(n.lhs);
    disambiguate(n.rhs);
  }

# ifdef DEBUG
  void visit_typedecl(TypeDecl& n) final {
    dispatch(*n.value);
    assert((n.value->resolve()) != nullptr && "symlinks completed");
  }
  void visit_array(Array& n) final {
    dispatch(*n.index_type);
    dispatch(*n.element_type);
    assert((n.index_type->resolve()) != nullptr && "symlinks completed");
    assert((n.element_type->resolve()) != nullptr && "symlinks completed");
  }
# endif

  void visit_typeexprid(TypeExprID &n) final {
    if (n.referent == nullptr) {
      // This reference is unresolved

      Ptr<TypeDecl> t = symtab.lookup<TypeDecl>(n.name, n.loc);
      if (t == nullptr)
        throw Error("unknown type symbol \"" + n.name + "\"", n.loc);

      n.referent = t;
      // n.type_id = t->value->type_id;
    }
  }

  void visit_undefine(Undefine &n) final {
    dispatch(*n.rhs);
    disambiguate(n.rhs);
  }

  void visit_while(While &n) final {
    dispatch(*n.condition);
    for (auto &s : n.body)
      dispatch(*s);
    disambiguate(n.condition);
  }

  void visit_xor(Xor &n) final { visit_bexpr(n); }


  // added syntax nodes ---------------------

  void visit_chooserule(ChooseRule& n) final {
    symtab.open_scope();
    ms_quantifiers.open_scope();
    for (MultisetQuantifier &mq : n.ms_quantifiers) {
      dispatch(mq);
      symtab.declare(mq.name, Ptr<VarDecl>(mq.decl));
    }
    for (auto &r : n.rules)
      dispatch(*r);
    ms_quantifiers.close_scope();
    symtab.close_scope();
  }

  void visit_ismember(IsMember& n) final {
    dispatch(*n.designator);
    // wrap symbol resolution within the type in a dummy scope to suppress any
    // declarations (primarily enum members) as these will be duplicated in
    // when we descend into decl below
    symtab.open_scope();
    dispatch(*n.type_value);
    symtab.close_scope();
    disambiguate(n.designator);
  }

  void visit_multiset(Multiset& n) final {
    dispatch(*n.size); // index_type should be nullptr
    dispatch(*n.element_type);
    disambiguate(n.size);
  }

  void visit_multisetadd(MultisetAdd& n) final {
    dispatch(*n.value);
    dispatch(*n.multiset);
    disambiguate(n.value);
    disambiguate(n.multiset);
  }

  void visit_multisetcount(MultisetCount& n) final {
    symtab.open_scope();
    ms_quantifiers.open_scope();
    dispatch(n.ms_quantifier);
    symtab.declare(n.ms_quantifier.name, Ptr<VarDecl>(n.ms_quantifier.decl));
    dispatch(*n.condition);
    disambiguate(n.condition);
    ms_quantifiers.close_scope();
    symtab.close_scope();
  }

  void visit_multisetelement(MultisetElement& n) final {
    dispatch(*n.multiset);
    dispatch(*n.index);
    disambiguate(n.multiset);
    // disambiguate(n.index);
  }

  void visit_multisetremove(MultisetRemove& n) final {
    dispatch(*n.index);
    dispatch(*n.multiset);
    // disambiguate(n.index);
    disambiguate(n.multiset);
    n.ms_quantifier = ms_quantifiers.lookup<MultisetQuantifier>(n.index->id, n.index->loc);

  }

  void visit_multisetremovepred(MultisetRemovePred& n) final {
    symtab.open_scope();
    ms_quantifiers.open_scope();
    dispatch(n.ms_quantifier);
    symtab.declare(n.ms_quantifier.name, Ptr<VarDecl>(n.ms_quantifier.decl));
    dispatch(*n.pred);
    disambiguate(n.pred);
    ms_quantifiers.close_scope();
    symtab.close_scope();
  }

  void visit_multisetquantifier(MultisetQuantifier& n) final {
    dispatch(*n.multiset);
    disambiguate(n.multiset);
    n.update();
    ms_quantifiers.declare(n.name, Ptr<MultisetQuantifier>::make(n));
  }

  void visit_scalarsetunion(ScalarsetUnion& n) final {
    // wrap symbol resolution within the type in a dummy scope to suppress any
    // declarations (primarily enum members) as these will be duplicated in
    // when we descend into decl below
    symtab.open_scope();
    for (Ptr<TypeExpr>& m : n.members)
      dispatch(*m);
    symtab.close_scope();
    //bound is nullptr until update is called
  }

  void visit_sucast(SUCast& n) final {
    dispatch(*n.target);
    dispatch(*n.rhs);
    disambiguate(n.rhs);
  }

  virtual ~Resolver() = default;

private:
  void visit_bexpr(BinaryExpr &n) {
    dispatch(*n.lhs);
    dispatch(*n.rhs);
    disambiguate(n.lhs);
    disambiguate(n.rhs);
  }

  void visit_uexpr(UnaryExpr &n) {
    dispatch(*n.rhs);
    disambiguate(n.rhs);
  }

  // detect whether this is an ambiguous node and, if so, resolve it into its
  // more precise AST node type
  void disambiguate(Ptr<Expr> &e) {

    if (auto a = dynamic_cast<const AmbiguousAmp *>(e.get())) {

      // try to get the type of the left hand side
      Ptr<TypeExpr> t;
      try {
        t = a->lhs->type();
      } catch (Error &) {
        // We failed because the left operand is somehow invalid. Silently
        // ignore this, assuming it will be rediscovered during AST validation.
        return;
      }

      // Form an unambiguous replacement node based on the type of the left
      // operand. Note that the types of the left and right operands may be
      // incompatible. However, this will cause an error during AST validation
      // so we do not need to worry about that here.
      Ptr<Expr> replacement;
      if (isa<Range>(t)) {
        replacement = Ptr<Band>::make(a->lhs, a->rhs, a->loc);
      } else {
        replacement = Ptr<And>::make(a->lhs, a->rhs, a->loc);
      }

      // also preserve the identifier which has already been set
      replacement->unique_id = a->unique_id;

      // replace the ambiguous node
      e = replacement;

      return;
    }

    if (auto o = dynamic_cast<const AmbiguousPipe *>(e.get())) {

      // try to get the type of the left hand side
      Ptr<TypeExpr> t;
      try {
        t = o->lhs->type();
      } catch (Error &) {
        // We failed because the left operand is somehow invalid. Silently
        // ignore this, assuming it will be rediscovered during AST validation.
        return;
      }

      // Form an unambiguous replacement node based on the type of the left
      // operand. Note that the types of the left and right operands may be
      // incompatible. However, this will cause an error during AST validation
      // so we do not need to worry about that here.
      Ptr<Expr> replacement;
      if (isa<Range>(t)) {
        replacement = Ptr<Bor>::make(o->lhs, o->rhs, o->loc);
      } else {
        replacement = Ptr<Or>::make(o->lhs, o->rhs, o->loc);
      }

      // also preserve the identifier which has already been set
      replacement->unique_id = o->unique_id;

      // replace the ambiguous node
      e = replacement;

      return;
    }


    /* disambiguate normal Element/Array accesses from "proper" Multiset Element accesses */
    // if nto already a Multiset Element
    if (not isa<MultisetElement>(e)) {
      // but it is an Element
      if (auto _e = dynamic_cast<const Element*>(e.get())) {
        // the Element is trying to access a Multiset not an Array
        const auto _t = _e->array->type()->resolve();
        if (const auto _ms = dynamic_cast<const Multiset*>(_t.get())) {
          // Element index must be unmodified var/ExprID referring to a multiset quantifier
          if (const auto _eid = dynamic_cast<const ExprID*>(_e->index.get())) {
            // lookup the id in both the current scope and the multiset scope (this means the Id is the same)
            const auto st_vd = symtab.lookup<VarDecl>(_eid->id, _eid->loc);
            const auto msq = ms_quantifiers.lookup<MultisetQuantifier>(_eid->id, _eid->loc);
                // both lookups succeeded (this condition also assures the index var Id matches the ms_quantifier's)
            if ((st_vd != nullptr && msq != nullptr)
                // the type of multiset being accessed is the same type as referred to in the MultisetQuantifier
                && _ms->equal_to(*msq->multiset->type())
                // the types of the quantifier variable are the same (should already be assured by prev check)
                && msq->decl->type->equal_to(*st_vd->type)
                // both must be readonly (MultisetQuantifier always marks its VarDecl as readonly)
                && (msq->decl->is_readonly() && _eid->is_readonly())) {
                // biggest flaw left is ensuring that the multiset being refereed to is the same as the ms_quantifier's
                // if (_e->array->to_string() == msq->multiset->to_string()) // approximate rough check for the above
              auto tmp_uid = e->unique_id;
              e = Ptr<MultisetElement>::make(_e->array, Ptr<ExprID>::make(*_eid), e->loc);
              e->unique_id = tmp_uid;
            }
          }
        }
      }
    }
  }
};

} // namespace

void murphi::updateAST(Model &m) {
  Resolver r;
  r.dispatch(m);
}
