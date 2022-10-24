#pragma once

#include "location.hh"
#include <cstddef>
#include <iostream>
#include <memory>
#include <murphi/Decl.h>
#include <murphi/Expr.h>
#include <murphi/Node.h>
#include <murphi/Property.h>
#include <murphi/Ptr.h>
#include <murphi/Stmt.h>
#include <string>
#include <vector>

#ifndef MURPHI_API_WITH_RTTI
#define MURPHI_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace murphi {

struct MURPHI_API_WITH_RTTI Rule : public Node {

  std::string name;
  std::vector<Quantifier> quantifiers;
  std::vector<Ptr<AliasDecl>> aliases;
  /// for supporting Multiset's ChooseRule, legacy systems can ignore
  std::vector<MultisetQuantifier> ms_quantifiers;

  Rule(const std::string &name_, const location &loc_);

  Rule *clone() const override = 0;

  virtual std::vector<Ptr<Rule>> flatten() const;

  virtual ~Rule() = default;

protected:
  Rule(const Rule &) = default;
  Rule &operator=(const Rule &) = default;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI AliasRule : public Rule {
  std::vector<Ptr<Rule>> rules;

  AliasRule(const std::vector<Ptr<AliasDecl>> &aliases_,
            const std::vector<Ptr<Rule>> &rules_, const location &loc_);
  virtual ~AliasRule() = default;
  AliasRule *clone() const;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  std::vector<Ptr<Rule>> flatten() const final;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI SimpleRule : public Rule {

  Ptr<Expr> guard;
  std::vector<Ptr<Decl>> decls;
  std::vector<Ptr<Stmt>> body;

  SimpleRule(const std::string &name_, const Ptr<Expr> &guard_,
             const std::vector<Ptr<Decl>> &decls_,
             const std::vector<Ptr<Stmt>> &body_, const location &loc_);
  virtual ~SimpleRule() = default;
  SimpleRule *clone() const override;
  void validate() const final;
  void update() final;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI StartState : public Rule {

  std::vector<Ptr<Decl>> decls;
  std::vector<Ptr<Stmt>> body;

  StartState(const std::string &name_, const std::vector<Ptr<Decl>> &decls_,
             const std::vector<Ptr<Stmt>> &body_, const location &loc_);
  virtual ~StartState() = default;
  StartState *clone() const;
  void validate() const final;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI PropertyRule : public Rule {

  Property property;

  PropertyRule(const std::string &name_, const Property &property_,
               const location &loc_);
  virtual ~PropertyRule() = default;
  PropertyRule *clone() const;

  void update() final;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI Ruleset : public Rule {

  std::vector<Ptr<Rule>> rules;

  Ruleset(const std::vector<Quantifier> &quantifiers_,
          const std::vector<Ptr<Rule>>& rules_, const location& loc_);
  virtual ~Ruleset() = default;
  Ruleset *clone() const;
  void validate() const final;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  std::vector<Ptr<Rule>> flatten() const final;
};

// << ------------------------------------------------------------------------------------------ >> 
// everything below here is implemented in src/ext_Rule.h 
// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI ChooseRule : public Rule {

  std::vector<Ptr<Rule>> rules;

  ChooseRule(const std::vector<MultisetQuantifier> &ms_quantifiers_,
             const std::vector<Ptr<Rule>>& rules_, const location& loc_);
  virtual ~ChooseRule() = default;
  ChooseRule *clone() const override;


  void visit(BaseTraversal &visitor) override;
  void visit(ConstBaseTraversal &visitor) const override;

  void validate() const final;
  std::vector<Ptr<Rule>> flatten() const final;
};


} // namespace murphi
