#include "check.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <romp/romp.h>

using namespace romp;

namespace {

class Check : public ConstTraversal {

public:
  bool ok = true;

  void visit_isundefined(const IsUndefined &) final {
    if (ok) {
      std::cerr << "isundefined expressions are not supported\n";
      ok = false;
    }
  }
};

} // namespace

bool check(const Node &n) {
  Check c;
  c.dispatch(n);
  return c.ok;
}
