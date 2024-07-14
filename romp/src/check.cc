#include "check.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <murphi/murphi.h>
#include <murphi/except.h>

using namespace murphi;

namespace  {

class Check : public ConstTraversal {

public:

  void visit_multisetremove(const MultisetRemove &n) final {
    throw Error("MultisetRemove statements are not supported by romp", n.loc);
  }
  void visit_chooserule(const ChooseRule &n) final {
    throw Error("Choose rule/rulesets's are not supported by romp", n.loc);
  }
};

} // namespace <anon>

void check(const Node &n) {
  Check c;
  c.dispatch(n);
}