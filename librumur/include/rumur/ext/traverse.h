#pragma once

#include <rumur/traverse.h>
#include <rumur/ext/Expr.h>
#include <rumur/ext/TypeExpr.h>
#include <rumur/ext/Stmt.h>
#include <rumur/ext/Rule.h>

#ifndef RUMUR_API_WITH_RTTI
#define RUMUR_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace rumur {
namespace ext {

class RUMUR_API_WITH_RTTI ExtBaseTraversal : public BaseTraversal {
public:
  void visit_chooserule(ChooseRule& n) override;
  void visit_ismember(IsMember& n) override;
  void visit_multiset(Multiset& n) override;
  void visit_multisetadd(MultisetAdd& n) override;
  void visit_multisetcount(MultisetCount& n) override;
  void visit_multisetelement(MultisetElement& n) override;
  void visit_multisetremove(MultisetRemove& n) override;
  void visit_multisetremovepred(MultisetRemovePred& n) override;
  void visit_multisetquantifier(MultisetQuantifier& n) override; 
  void visit_scalarsetunion(ScalarsetUnion& n) override;
  void visit_sucast(SUCast& n) override;

};

class RUMUR_API_WITH_RTTI ExtTraversal : public Traversal {
public:
  void visit_chooserule(ChooseRule& n) override;
  void visit_ismember(IsMember& n) override;
  void visit_multiset(Multiset& n) override;
  void visit_multisetadd(MultisetAdd& n) override;
  void visit_multisetcount(MultisetCount& n) override;
  void visit_multisetelement(MultisetElement& n) override;
  void visit_multisetremove(MultisetRemove& n) override;
  void visit_multisetremovepred(MultisetRemovePred& n) override;
  void visit_multisetquantifier(MultisetQuantifier& n) override; 
  void visit_scalarsetunion(ScalarsetUnion& n) override;
  void visit_sucast(SUCast& n) override;

};

class RUMUR_API_WITH_RTTI ConstExtBaseTraversal : public ConstBaseTraversal {
public:
  void visit_chooserule(const ChooseRule& n) override;
  void visit_ismember(const IsMember& n) override;
  void visit_multiset(const Multiset& n) override;
  void visit_multisetadd(const MultisetAdd& n) override;
  void visit_multisetcount(const MultisetCount& n) override;
  void visit_multisetelement(const MultisetElement& n) override;
  void visit_multisetremove(const MultisetRemove& n) override;
  void visit_multisetremovepred(const MultisetRemovePred& n) override;
  void visit_multisetquantifier(const MultisetQuantifier& n) override; 
  void visit_scalarsetunion(const ScalarsetUnion& n) override;
  void visit_sucast(const SUCast& n) override;

};

class RUMUR_API_WITH_RTTI ConstExtTraversal : public ConstTraversal {
public:
  void visit_chooserule(const ChooseRule& n) override;
  void visit_ismember(const IsMember& n) override;
  void visit_multiset(const Multiset& n) override;
  void visit_multisetadd(const MultisetAdd& n) override;
  void visit_multisetcount(const MultisetCount& n) override;
  void visit_multisetelement(const MultisetElement& n) override;
  void visit_multisetremove(const MultisetRemove& n) override;
  void visit_multisetremovepred(const MultisetRemovePred& n) override;
  void visit_multisetquantifier(const MultisetQuantifier& n) override; 
  void visit_scalarsetunion(const ScalarsetUnion& n) override;
  void visit_sucast(const SUCast& n) override;

};

class RUMUR_API_WITH_RTTI ConstExtExprTraversal : public ConstExprTraversal {
public:
  void visit_chooserule(const ChooseRule& n) override;
  void visit_ismember(const IsMember& n) override; // override me in your implementation
  void visit_multiset(const Multiset& n) final;
  void visit_multisetadd(const MultisetAdd& n) final;
  void visit_multisetcount(const MultisetCount& n) override; // override me in your implementation
  void visit_multisetelement(const MultisetElement& n) override; // override me in your implementation
  void visit_multisetremove(const MultisetRemove& n) final;
  void visit_multisetremovepred(const MultisetRemovePred& n) final;
  void visit_multisetquantifier(const MultisetQuantifier& n) override;
  void visit_scalarsetunion(const ScalarsetUnion& n) final;
  void visit_sucast(const SUCast& n) override;  // override me in your implementation

};

class RUMUR_API_WITH_RTTI ConstExtStmtTraversal : public ConstStmtTraversal {
public:
  void visit_chooserule(const ChooseRule& n) override;
  void visit_ismember(const IsMember& n) final;
  void visit_multiset(const Multiset& n) final;
  void visit_multisetadd(const MultisetAdd& n) override; // override me in your implementation
  void visit_multisetcount(const MultisetCount& n) final;
  void visit_multisetelement(const MultisetElement& n) final;
  void visit_multisetremove(const MultisetRemove& n) override; // override me in your implementation
  void visit_multisetremovepred(const MultisetRemovePred& n) override; // override me in your implementation
  void visit_multisetquantifier(const MultisetQuantifier& n) override;
  void visit_scalarsetunion(const ScalarsetUnion& n) final;
  void visit_sucast(const SUCast& n) final;

};

class RUMUR_API_WITH_RTTI ConstExtTypeTraversal : public ConstTypeTraversal {
public:
  void visit_chooserule(const ChooseRule& n) override;
  void visit_ismember(const IsMember& n) final;
  void visit_multiset(const Multiset& n) override;  // override me in your implementation
  void visit_multisetadd(const MultisetAdd& n) final;
  void visit_scalarsetunion(const ScalarsetUnion& n) override;  // override me in your implementation
  void visit_multisetremove(const MultisetRemove& n) final;
  void visit_multisetremovepred(const MultisetRemovePred& n) final;
  void visit_multisetquantifier(const MultisetQuantifier& n) override;
  void visit_sucast(const SUCast& n) final;

};

} // namespace ext
} // namespace rumur
