
#include "../../common/isa.h"
#include <rumur/ext/make_legacy.h>
#include <rumur/ext/traverse.h>


using namespace rumur;
using namespace ext;

Ptr<Node> un_ext(const Ptr<Node> &n) {

  struct MakeLegacy : public ConstBaseTraversal {
    Ptr<Node> result;
    MakeLegacy() {}

    void visit_add(const Add &n) final {
      Ptr<Add> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_aliasdecl(const AliasDecl &n) final {
      Ptr<AliasDecl> _n(n.clone());
      _n->value = un_ext(n.value);
      result = _n;
    }

    void visit_aliasrule(const AliasRule &n) final {
      Ptr<AliasRule> _n(n.clone());
      _n->aliases.clear();
      for (auto &a : n.aliases)
        _n->aliases.push_back(un_ext(a));
      _n->rules.clear();
      for (auto &r : n.rules)
        _n->rules.push_back(un_ext(r));
      result = _n;
    }

    void visit_aliasstmt(const AliasStmt &n) final {
      Ptr<AliasStmt> _n(n.clone());
      _n->aliases.clear();
      for (auto &a : n.aliases)
        _n->aliases.push_back(un_ext(a));
      _n->body.clear();
      for (auto &s : n.body)
        _n->body.push_back(un_ext(s));
      result = _n;
    }

    void visit_ambiguousamp(const AmbiguousAmp &n) final {
      Ptr<AmbiguousAmp> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_ambiguouspipe(const AmbiguousPipe &n) final {
      Ptr<AmbiguousPipe> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_and(const And &n) final {
      Ptr<And> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_array(const Array &n) final {
      Ptr<Array> _n(n.clone());
      _n->index_type = un_ext(n.index_type);
      _n->element_type = un_ext(n.element_type);
      result = _n;
    }

    void visit_assignment(const Assignment &n) final {
      Ptr<Assignment> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_band(const Band &n) final {
      Ptr<Band> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_bnot(const Bnot &n) final {
      Ptr<Bnot> _n(n.clone());
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_bor(const Bor &n) final {
      Ptr<Bor> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_clear(const Clear &n) final {
      Ptr<Clear> _n(n.clone());
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_constdecl(const ConstDecl &n) final {
      Ptr<ConstDecl> _n(n.clone());
      _n->value = un_ext(n.value);
      result = _n;
    }

    void visit_div(const Div &n) final {
      Ptr<Div> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_element(const Element &n) final {
      Ptr<Element> _n(n.clone());
      _n->array = un_ext(n.array);
      _n->index = un_ext(n.index);
      result = _n;
    }

    void visit_enum(const Enum &n) final {
      Ptr<Enum> _n(n.clone()); 
      result = _n; 
    }

    void visit_eq(const Eq &n) final {
      Ptr<Eq> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_errorstmt(const ErrorStmt &n) final {
      Ptr<ErrorStmt> _n(n.clone()); 
      result = _n; 
    }

    void visit_exists(const Exists &n) final {
      Ptr<Exists> _n(n.clone());
      _n->quantifier = *un_ext(Ptr<Node>(&n.quantifier));
      _n->expr = un_ext(n.expr);
      result = _n;
    }

    void visit_exprid(const ExprID &n) final {
      Ptr<ExprID> _n(n.clone());
      if (n.value != nullptr)
        _n->value = un_ext(n.value);
      result = _n;
    }

    void visit_field(const Field &n) final {
      Ptr<Field> _n(n.clone());
      _n->record = un_ext(n.record);
      result = _n;
    }

    void visit_for(const For &n) final {
      Ptr<For> _n(n.clone());
      _n->quantifier = *un_ext(Ptr<Node>(&n.quantifier));
      _n->body.clear();
      for (auto &s : n.body)
        _n->body.push_back(un_ext(s));
      result = _n;
    }

    void visit_forall(const Forall &n) final {
      Ptr<Forall> _n(n.clone());
      _n->quantifier = *un_ext(Ptr<Node>(&n.quantifier));
      _n->expr = un_ext(n.expr);
      result = _n;
    }

    void visit_function(const Function &n) final {
      Ptr<Function> _n(n.clone());
      _n->parameters.clear();
      for (auto &p : n.parameters)
        _n->parameters.push_back(un_ext(p));
      if (n.return_type != nullptr)
        _n->return_type = un_ext(n.return_type);
      _n->decls.clear();
      for (auto &d : n.decls)
        _n->decls.push_back(un_ext(d));
      _n->body.clear();
      for (auto &s : n.body)
        _n->body.push_back(un_ext(s));
      result = _n;
    }

    void visit_functioncall(const FunctionCall &n) final {
      Ptr<FunctionCall> _n(n.clone());
      _n->arguments.clear();
      for (auto &a : n.arguments)
        _n->arguments.push_back(un_ext(a));
      result = _n;
    }

    void visit_geq(const Geq &n) final {
      Ptr<Geq> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_gt(const Gt &n) final {
      Ptr<Gt> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_if(const If &n) final {
      Ptr<If> _n(n.clone());
      _n->clauses.clear();
      for (const IfClause &c : n.clauses)
        _n->clauses.push_back(*un_ext(Ptr<Node>(&c)));
      result = _n;
    }

    void visit_ifclause(const IfClause &n) final {
      Ptr<IfClause> _n(n.clone());
      if (n.condition != nullptr)
        _n->condition = un_ext(n.condition);
      _n->body.clear();
      for (auto &s : n.body)
        _n->body.push_back(un_ext(s));
      result = _n;
    }

    void visit_implication(const Implication &n) final {
      Ptr<Implication> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_isundefined(const IsUndefined &n) final {
      Ptr<IsUndefined> _n(n.clone());
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_leq(const Leq &n) final {
      Ptr<Leq> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_lsh(const Lsh &n) final {
      Ptr<Lsh> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_lt(const Lt &n) final {
      Ptr<Lt> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_mod(const Mod &n) final {
      Ptr<Mod> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_model(const Model &n) final {
      Ptr<Model> _n(n.clone());
      _n->children.clear();
      for (const Ptr<Node> &c : n.children)
        _n->children.push_back(un_ext(c));
      result = _n;
    }

    void visit_mul(const Mul &n) final {
      Ptr<Mul> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_negative(const Negative &n) final {
      Ptr<Negative> _n(n.clone());
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_neq(const Neq &n) final {
      Ptr<Neq> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_not(const Not &n) final {
      Ptr<Not> _n(n.clone());
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_number(const Number &n) final {
      Ptr<Number> _n(n.clone()); result = _n; }

    void visit_or(const Or &n) final {
      Ptr<Or> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_procedurecall(const ProcedureCall &n) final {
      Ptr<ProcedureCall> _n(n.clone());
      _n->call = un_ext(n.call);
      result = _n;
    }

    void visit_property(const Property &n) final {
      Ptr<Property> _n(n.clone());
      _n->expr = un_ext(n.expr);
      result = _n;
    }

    void visit_propertyrule(const PropertyRule &n) final {
      Ptr<PropertyRule> _n(n.clone());
      _n->quantifiers.clear();
      for (const Quantifier &q : n.quantifiers)
        _n->quantifiers.push_back(*un_ext(Ptr<Node>(&q)));
      _n->property = un_ext(n.property);
      result = _n;
    }

    void visit_propertystmt(const PropertyStmt &n) final {
      Ptr<PropertyStmt> _n(n.clone());
      _n->property = un_ext(n.property);
      result = _n;
    }

    void visit_put(const Put &n) final {
      Ptr<Put> _n(n.clone());
      if (n.expr != nullptr)
        _n->expr = un_ext(n.expr);
      result = _n;
    }

    void visit_quantifier(const Quantifier &n) final {
      Ptr<Quantifier> _n(n.clone());
      if (n.type != nullptr)
        _n->type = un_ext(n.type);
      if (n.from != nullptr)
        _n->from = un_ext(n.from);
      if (n.to != nullptr)
        _n->to = un_ext(n.to);
      if (n.step != nullptr)
        _n->step = un_ext(n.step);
      result = _n;
    }

    void visit_range(const Range &n) final {
      Ptr<Range> _n(n.clone());
      _n->min = un_ext(n.min);
      _n->max = un_ext(n.max);
      result = _n;
    }

    void visit_record(const Record &n) final {
      Ptr<Record> _n(n.clone());
      _n->fields.clear();
      for (auto &f : n.fields)
        _n->fields.push_back(un_ext(f));
      result = _n;
    }

    void visit_return(const Return &n) final {
      Ptr<Return> _n(n.clone());
      if (n.expr != nullptr)
        _n->expr = un_ext(n.expr);
      result = _n;
    }

    void visit_rsh(const Rsh &n) final {
      Ptr<Rsh> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_ruleset(const Ruleset &n) final {
      Ptr<Ruleset> _n(n.clone());
      _n->quantifiers.clear();
      for (const Quantifier &q : n.quantifiers)
        _n->quantifiers.push_back(*un_ext(Ptr<Node>(&q)));
      _n->rules.clear();
      for (auto &r : n.rules)
        _n->rules.push_back(un_ext(r));
      result = _n;
    }

    void visit_scalarset(const Scalarset &n) final {
      Ptr<Scalarset> _n(n.clone());
      _n->bound = un_ext(n.bound);
      result = _n;
    }

    void visit_simplerule(const SimpleRule &n) final {
      Ptr<SimpleRule> _n(n.clone());
      _n->quantifiers.clear();
      for (const Quantifier &q : n.quantifiers)
        _n->quantifiers.push_back(un_ext(q));
      if (n.guard != nullptr)
        _n->guard = un_ext(n.guard);
      _n->decls.clear();
      for (auto &d : n.decls)
        _n->decls.push_back(un_ext(d));
      _n->body.clear();
      for (auto &s : n.body)
        _n->body.push_back(un_ext(s));
      result = _n;
    }

    void visit_startstate(const StartState &n) final {
      Ptr<StartState> _n(n.clone());
      _n->quantifiers.clear();
      for (const Quantifier &q : n.quantifiers)
        _n->quantifiers.push_back(un_ext(q));
      _n->decls.clear();
      for (auto &d : n.decls)
        _n->decls.push_back(un_ext(d));
      _n->body.clear();
      for (auto &s : n.body)
        _n->body.push_back(un_ext(s));
      result = _n;
    }

    void visit_sub(const Sub &n) final {
      Ptr<Sub> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_switch(const Switch &n) final {
      Ptr<Switch> _n(n.clone());
      _n->expr = un_ext(n.expr);
      _n->cases.clear();
      for (const SwitchCase &c : n.cases)
        _n->cases.push_back(un_ext(c));
      result = _n;
    }

    void visit_switchcase(const SwitchCase &n) final {
      Ptr<SwitchCase> _n(n.clone());
      _n->matches.clear();
      for (auto &m : n.matches)
        _n->matches.push_back(un_ext(m));
      _n->body.clear();
      for (auto &s : n.body)
        _n->body.push_back(un_ext(s));
      result = _n;
    }

    void visit_ternary(const Ternary &n) final {
      Ptr<Ternary> _n(n.clone());
      _n->cond = un_ext(n.cond);
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_typedecl(const TypeDecl &n) final {
      Ptr<TypeDecl> _n(n.clone());
      _n->value = un_ext(n.value);
      result = _n;
    }

    void visit_typeexprid(const TypeExprID &n) final {
      Ptr<TypeExprID> _n(n.clone());
      if (n.referent != nullptr)
        _n->referent = un_ext(n.referent);
      result = _n;
    }

    void visit_undefine(const Undefine &n) final {
      Ptr<Undefine> _n(n.clone());
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }

    void visit_vardecl(const VarDecl &n) final {
      Ptr<VarDecl> _n(n.clone());
      if (n.type != nullptr)
        _n->type = un_ext(n.type);
      result = _n;
    }

    void visit_while(const While &n) final {
      Ptr<While> _n(n.clone());
      _n->condition = un_ext(n.condition);
      _n->body.clear();
      for (auto &s : n.body)
        _n->body.push_back(un_ext(s));
      result = _n;
    }

    void visit_xor(const Xor &n) final {
      Ptr<Xor> _n(n.clone());
      _n->lhs = un_ext(n.lhs);
      _n->rhs = un_ext(n.rhs);
      result = _n;
    }


    // void visit_chooserule(const ext::ChooseRule& n) final { result = un_ext(n.make_legacy()); }
    // void visit_ismember(const ext::IsMember& n) final { result = un_ext(n.make_legacy()); }
    // void visit_multiset(const ext::Multiset& n) final { result = un_ext(n.make_legacy()); }
    // void visit_multisetadd(const ext::MultisetCount& n) final { result = un_ext(n.make_legacy()); }
    // void visit_multisetcount(const ext::MultisetCount& n) final { result = un_ext(n.make_legacy()); }
    // void visit_multisetelement(const ext::MultisetElement& n) final { result = n.make_legacy(); } // will cause infinite loop if called with un_ext
    // void visit_multisetremove(const ext::MultisetRemove& n) final { result = un_ext(n.make_legacy()); }
    // void visit_multisetremovepred(const ext::MultisetRemovePred& n) final { result = un_ext(n.make_legacy()); }
    // void visit_multisetquantifier(const ext::MultisetQuantifier& n) final { result = un_ext(n.make_legacy()); } 
    // void visit_scalarsetunion(const ext::ScalarsetUnion& n) final { result = un_ext(n.make_legacy()); }
    // void visit_sucast(const ext::SUCast& n) final { result = un_ext(n.make_legacy()); }
  };

  if (const auto _en = dynamic_cast<const IExtNode<Node>*>(n.get())) {
    return un_ext(_en->make_legacy());
  }
  MakeLegacy ml();
  ml.dispatch(*n);
  return ml.result;
}

#include <rumur/validate.h>

rumur::Ptr<rumur::Node> make_legacy(const rumur::Ptr<rumur::Node> &n) {
#ifdef DEBUG
  rumur::validate(*n); // during debug for safety ensure validation happens before transformation
#endif
  Ptr<Node> _n = un_ext(n);
  rumur::validate(*_n);
  return _n; 
}

// dead end generic implementation (should never be called)
template<class LT>
rumur::Ptr<LT> rumur::ext::IExtNode<LT>::make_legacy() const { 
  assert(false && "This should never be called!, replace this when extending INodeExt");
  return Ptr<LT>(new LT()); 
}

