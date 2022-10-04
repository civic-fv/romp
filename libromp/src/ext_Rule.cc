
#include "../../common/isa.h"
#include <romp/Rule.h>
#include <romp/except.h>

namespace romp {



ChooseRule::ChooseRule(const std::vector<MultisetQuantifier> &ms_quantifiers_,
            const std::vector<Ptr<Rule>>& rules_, const location& loc_)
  : Rule("",loc_), rules(rules_) { ms_quantifiers = ms_quantifiers_; }
ChooseRule *ChooseRule::clone() const { return new ChooseRule(*this); }


void ChooseRule::visit(BaseTraversal &visitor) { visitor.visit_chooserule(*this); }
void ChooseRule::visit(ConstBaseTraversal &visitor) const { visitor.visit_chooserule(*this); }

void ChooseRule::validate() const {
  for (const auto q : quantifiers)
    if (not isa<MultisetQuantifier>(q))
      throw Error("choose is only valid for multiset quantifiers", q.loc);
}

std::vector<Ptr<Rule>> ChooseRule::flatten() const {
  std::vector<Ptr<Rule>> rs;
  for (const Ptr<Rule> &r : rules) {
    for (Ptr<Rule> &f : r->flatten()) {
      // for (const Quantifier &q : quantifiers)
      //   f->quantifiers.push_back(q);
      for (const MultisetQuantifier &mq : ms_quantifiers)
        f->ms_quantifiers.push_back(mq);
      rs.push_back(f);
    }
  }
  return rs;
}


} //namespace romp