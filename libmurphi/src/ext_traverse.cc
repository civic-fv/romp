
#include <murphi/traverse.h>
#include <cassert>

namespace murphi {


void Traversal::visit_chooserule(ChooseRule& n) {
  for (auto &mq : n.ms_quantifiers)
    dispatch(mq);
  for (auto &r : n.rules)
    dispatch(*r);
}
void ConstTraversal::visit_chooserule(const ChooseRule& n) {
  for (auto &mq : n.ms_quantifiers)
    dispatch(mq);
  for (auto &r : n.rules)
    dispatch(*r);
}
void ConstExprTraversal::visit_chooserule(const ChooseRule& n) {
  assert(false && "`visit_chooserule` needs to be overriden in implementing classes! "
                  "(from: murphi::ConstExprTraversal)");
}
void ConstStmtTraversal::visit_chooserule(const ChooseRule& n) {
  for (auto &mq : n.ms_quantifiers)
    dispatch(mq);
  for (auto &r : n.rules)
    dispatch(*r);
}
void ConstTypeTraversal::visit_chooserule(const ChooseRule& n) {
  for (auto &mq : n.ms_quantifiers)
    dispatch(mq);
  for (auto &r : n.rules)
    dispatch(*r);
}

// << ------------------------------------------------------------------------------------------ >> 

void Traversal::visit_ismember(IsMember& n) {
  dispatch(*n.designator);
  dispatch(*n.type_value);
}
void ConstTraversal::visit_ismember(const IsMember& n) {
  dispatch(*n.designator);
  dispatch(*n.type_value);
}
void ConstStmtTraversal::visit_ismember(const IsMember& n) {
  dispatch(*n.designator);
  dispatch(*n.type_value);
}
void ConstTypeTraversal::visit_ismember(const IsMember& n) {
  dispatch(*n.designator);
  dispatch(*n.type_value);
}

// << ------------------------------------------------------------------------------------------ >> 


void Traversal::visit_multiset(Multiset& n) {
  dispatch(*n.size);
  dispatch(*n.element_type);
}
void ConstTraversal::visit_multiset(const Multiset& n) {
  dispatch(*n.size);
  dispatch(*n.element_type);
}
void ConstExprTraversal::visit_multiset(const Multiset& n) {
  dispatch(*n.size);
  dispatch(*n.element_type);
}
void ConstStmtTraversal::visit_multiset(const Multiset& n) {
  dispatch(*n.size);
  dispatch(*n.element_type);
}

// << ------------------------------------------------------------------------------------------ >> 

void Traversal::visit_multisetadd(MultisetAdd& n) {
  dispatch(*n.multiset);
  dispatch(*n.value);
}
void ConstTraversal::visit_multisetadd(const MultisetAdd& n) {
  dispatch(*n.multiset);
  dispatch(*n.value);
}
void ConstExprTraversal::visit_multisetadd(const MultisetAdd& n) {
  dispatch(*n.multiset);
  dispatch(*n.value);
}
void ConstTypeTraversal::visit_multisetadd(const MultisetAdd& n) {
  dispatch(*n.multiset);
  dispatch(*n.value);
}


// << ------------------------------------------------------------------------------------------ >> 


void Traversal::visit_multisetcount(MultisetCount& n) {
  dispatch(n.ms_quantifier);
  dispatch(*n.condition);
}
void ConstTraversal::visit_multisetcount(const MultisetCount& n) {
  dispatch(n.ms_quantifier);
  dispatch(*n.condition);
}
void ConstStmtTraversal::visit_multisetcount(const MultisetCount& n) {
  dispatch(n.ms_quantifier);
  dispatch(*n.condition);
}
void ConstTypeTraversal::visit_multisetcount(const MultisetCount& n) {  //not used for a type expr
  dispatch(n.ms_quantifier);
  dispatch(*n.condition);
}


// << ------------------------------------------------------------------------------------------ >> 


void Traversal::visit_multisetelement(MultisetElement& n) {
  dispatch(*n.multiset);
  dispatch(*n.index);
}
void ConstTraversal::visit_multisetelement(const MultisetElement& n) {
  dispatch(*n.multiset);
  dispatch(*n.index);
}
void ConstStmtTraversal::visit_multisetelement(const MultisetElement& n) {
  dispatch(*n.multiset);
  dispatch(*n.index);
}
void ConstTypeTraversal::visit_multisetelement(const MultisetElement& n) {  //not used for a type expr
  dispatch(*n.multiset);
  dispatch(*n.index);
}


// << ------------------------------------------------------------------------------------------ >> 



void Traversal::visit_multisetremove(MultisetRemove& n) {
  dispatch(*n.index);
  dispatch(*n.multiset);
}
void ConstTraversal::visit_multisetremove(const MultisetRemove& n) {
  dispatch(*n.index);
  dispatch(*n.multiset);
}
void ConstExprTraversal::visit_multisetremove(const MultisetRemove& n) {
  dispatch(*n.index);
  dispatch(*n.multiset);
}
void ConstTypeTraversal::visit_multisetremove(const MultisetRemove& n) { 
  dispatch(*n.index);
  dispatch(*n.multiset);
}


// << ------------------------------------------------------------------------------------------ >> 


void Traversal::visit_multisetremovepred(MultisetRemovePred& n) {
  dispatch(n.ms_quantifier);
  dispatch(*n.pred);
}
void ConstTraversal::visit_multisetremovepred(const MultisetRemovePred& n) {
  dispatch(n.ms_quantifier);
  dispatch(*n.pred);
}
void ConstExprTraversal::visit_multisetremovepred(const MultisetRemovePred& n) {
  dispatch(n.ms_quantifier);
  dispatch(*n.pred);
}
void ConstTypeTraversal::visit_multisetremovepred(const MultisetRemovePred& n) { 
  dispatch(n.ms_quantifier);
  dispatch(*n.pred);
}


// << ------------------------------------------------------------------------------------------ >> 


void Traversal::visit_multisetquantifier(MultisetQuantifier& n) {
  dispatch(*n.multiset);
}
void ConstTraversal::visit_multisetquantifier(const MultisetQuantifier& n) {
  dispatch(*n.multiset);
}
void ConstExprTraversal::visit_multisetquantifier(const MultisetQuantifier& n) {
  dispatch(*n.multiset);
}
void ConstTypeTraversal::visit_multisetquantifier(const MultisetQuantifier& n) { 
  dispatch(*n.multiset);
}


// << ------------------------------------------------------------------------------------------ >> 


void Traversal::visit_scalarsetunion(ScalarsetUnion& n) {
  for (auto m : n.members) 
    dispatch(*m);
}
void ConstTraversal::visit_scalarsetunion(const ScalarsetUnion& n) {
  for (const auto m : n.members) 
    dispatch(*m);
}
void ConstExprTraversal::visit_scalarsetunion(const ScalarsetUnion& n) {
  for (const auto m : n.members) 
    dispatch(*m);
}
void ConstStmtTraversal::visit_scalarsetunion(const ScalarsetUnion& n) {
  for (const auto m : n.members) 
    dispatch(*m);
}

// << ------------------------------------------------------------------------------------------ >> 


void Traversal::visit_sucast(SUCast& n) { 
  dispatch(*n.rhs);
}
void ConstTraversal::visit_sucast(const SUCast& n) {
  dispatch(*n.rhs);
}
void ConstStmtTraversal::visit_sucast(const SUCast& n) {
  dispatch(*n.rhs);
}
void ConstTypeTraversal::visit_sucast(const SUCast& n) {
  dispatch(*n.rhs);
}

// << ------------------------------------------------------------------------------------------ >> 


} // namespace murphi
