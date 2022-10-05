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
#include <string>
#include <vector>

#ifndef MURPHI_API_WITH_RTTI
#define MURPHI_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace murphi {

struct MURPHI_API_WITH_RTTI Stmt : public Node {

  Stmt(const location &loc_);

  virtual ~Stmt() = default;
  virtual Stmt *clone() const = 0;

protected:
  Stmt(const Stmt &) = default;
  Stmt &operator=(const Stmt &) = default;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI AliasStmt : public Stmt {

  std::vector<Ptr<AliasDecl>> aliases;
  std::vector<Ptr<Stmt>> body;

  AliasStmt(const std::vector<Ptr<AliasDecl>> &aliases_,
            const std::vector<Ptr<Stmt>> &body_, const location &loc_);
  AliasStmt *clone() const override;
  virtual ~AliasStmt() = default;

  void visit(BaseTraversal &visitor) override;
  void visit(ConstBaseTraversal &visitor) const override;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI PropertyStmt : public Stmt {

  Property property;
  std::string message;

  PropertyStmt(const Property &property_, const std::string &message_,
               const location &loc_);
  PropertyStmt *clone() const;
  virtual ~PropertyStmt() = default;

  void validate() const final;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI Assignment : public Stmt {

  Ptr<Expr> lhs;
  Ptr<Expr> rhs;

  Assignment(const Ptr<Expr> &lhs_, const Ptr<Expr> &rhs_,
             const location &loc_);
  Assignment *clone() const;
  virtual ~Assignment() = default;

  void validate() const final;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;

  void update() final;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI Clear : public Stmt {

  Ptr<Expr> rhs;

  Clear(const Ptr<Expr> &rhs_, const location &loc);
  virtual ~Clear() = default;
  Clear *clone() const;

  void validate() const final;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI ErrorStmt : public Stmt {

  std::string message;

  ErrorStmt(const std::string &message_, const location &loc_);
  ErrorStmt *clone() const;
  virtual ~ErrorStmt() = default;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI For : public Stmt {

  Quantifier quantifier;
  std::vector<Ptr<Stmt>> body;

  For(const Quantifier &quantifier_, const std::vector<Ptr<Stmt>> &body_,
      const location &loc_);
  virtual ~For() = default;
  For *clone() const;

  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI IfClause : public Node {

  Ptr<Expr> condition;
  std::vector<Ptr<Stmt>> body;

  IfClause(const Ptr<Expr> &condition_, const std::vector<Ptr<Stmt>> &body_,
           const location &loc_);
  virtual ~IfClause() = default;
  IfClause *clone() const;

  void validate() const final;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI If : public Stmt {

  std::vector<IfClause> clauses;

  If(const std::vector<IfClause> &clauses_, const location &loc_);
  virtual ~If() = default;
  If *clone() const;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI ProcedureCall : public Stmt {

  FunctionCall call;

  ProcedureCall(const std::string &name,
                const std::vector<Ptr<Expr>> &arguments, const location &loc_);
  virtual ~ProcedureCall() = default;
  ProcedureCall *clone() const;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI Put : public Stmt {

  std::string value;
  Ptr<Expr> expr;

  Put(const std::string &value_, const location &loc_);
  Put(const Ptr<Expr> &expr_, const location &loc_);
  virtual ~Put() = default;
  Put *clone() const;

  void validate() const final;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI Return : public Stmt {

  Ptr<Expr> expr;

  Return(const Ptr<Expr> &expr_, const location &loc_);
  virtual ~Return() = default;
  Return *clone() const;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI SwitchCase : public Node {

  std::vector<Ptr<Expr>> matches;
  std::vector<Ptr<Stmt>> body;

  SwitchCase(const std::vector<Ptr<Expr>> &matches_,
             const std::vector<Ptr<Stmt>> &body_, const location &loc_);
  virtual ~SwitchCase() = default;
  SwitchCase *clone() const;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI Switch : public Stmt {

  Ptr<Expr> expr;
  std::vector<SwitchCase> cases;

  Switch(const Ptr<Expr> &expr_, const std::vector<SwitchCase> &cases_,
         const location &loc_);
  virtual ~Switch() = default;
  Switch *clone() const;

  void validate() const final;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI Undefine : public Stmt {

  Ptr<Expr> rhs;

  Undefine(const Ptr<Expr> &rhs_, const location &loc_);
  virtual ~Undefine() = default;
  Undefine *clone() const;

  void validate() const final;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI While : public Stmt {

  Ptr<Expr> condition;
  std::vector<Ptr<Stmt>> body;

  While(const Ptr<Expr> &condition_, const std::vector<Ptr<Stmt>> &body_,
        const location &loc_);
  virtual ~While() = default;
  While *clone() const;

  void validate() const final;
  void visit(BaseTraversal &visitor);
  void visit(ConstBaseTraversal &visitor) const;
};

// << ------------------------------------------------------------------------------------------ >> 
// everything below here is implemented in src/ext_Stmt.h 
// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI MultisetAdd : public Stmt {

  Ptr<Expr> value;
  Ptr<Expr> multiset;

  MultisetAdd(const Ptr<Expr>& value_, const Ptr<Expr>& multiset_, const location& loc_);
  MultisetAdd *clone() const override;
  ~MultisetAdd() = default;

  void visit(BaseTraversal &visitor) override;
  void visit(ConstBaseTraversal &visitor) const override;

  void validate() const final;
  void update() final;

};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI MultisetRemove : public Stmt {

  Ptr<Expr> index;
  Ptr<Expr> multiset;

  // is nullptr until after symbol resolution (updateAST)
  Ptr<MultisetQuantifier> ms_quantifier;

  MultisetRemove(const Ptr<Expr>& index_, const Ptr<Expr>& multiset_, const location& loc_);
  MultisetRemove *clone() const override;
  ~MultisetRemove() = default;

  void visit(BaseTraversal &visitor) override;
  void visit(ConstBaseTraversal &visitor) const override;

  void validate() const final;
  void update() final;
};

// << ------------------------------------------------------------------------------------------ >> 


struct MURPHI_API_WITH_RTTI MultisetRemovePred : public Stmt {

  MultisetQuantifier ms_quantifier;
  Ptr<Expr> pred;

  MultisetRemovePred(const MultisetQuantifier& ms_quantifier_, const Ptr<Expr>& pred_, const location& loc_);
  MultisetRemovePred *clone() const override;
  ~MultisetRemovePred() = default;

  void visit(BaseTraversal &visitor) override;
  void visit(ConstBaseTraversal &visitor) const override;

  void validate() const final;
  void update() final;
};


} // namespace murphi
