#include <cstddef>
#include <romp/Node.h>
#include <romp/Ptr.h>
#include <romp/Rule.h>
#include <romp/sanitize_rule_names.h>
#include <romp/traverse.h>
#include <string>
#include <unordered_set>

using namespace romp;

namespace {

class RuleNamer : public Traversal {

private:
  size_t index = 0;
  std::unordered_set<std::string> used; // names already taken

  void name(Rule &n, const std::string &prefix) {

    std::string replacement = n.name;

    // name by index if there is no name
    if (replacement == "") {
      replacement = prefix + std::to_string(index);
      index++;
    }
    
    // replace non-letter symbols
    replacement = sanitize_name(replacement);

    std::string candidate = replacement;
    while (!used.insert(candidate).second) {
      candidate = replacement + std::to_string(index);
      index++;
    }

    n.name = candidate;
  }

public:
  void visit_aliasrule(AliasRule &n) final {
    name(n, "alias");
    for (Ptr<Rule> &r : n.rules) {
      dispatch(*r);
    }
  }

  void visit_propertyrule(PropertyRule &n) final { name(n, "property"); }

  void visit_ruleset(Ruleset &n) final {
    name(n, "ruleset");
    for (Ptr<Rule> &r : n.rules) {
      dispatch(*r);
    }
  }

  void visit_simplerule(SimpleRule &n) final { name(n, "rule"); }

  void visit_startstate(StartState &n) final { name(n, "startstate"); }

  void visit_chooserule(ChooseRule& n) final {
    name(n, "chooserule");
    for (Ptr<Rule> &r : n.rules) {
      dispatch(*r);
    }
  }
};

} // namespace

void romp::sanitize_rule_names(Node &n) {
  RuleNamer r;
  r.dispatch(n);
}

std::string romp::sanitize_name(const std::string& name) {
  std::string replacement = name;
  // remove non-symbol characters
  for (char &c : replacement) {
    if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') &&
        !(c >= '0' && c <= '9')) {
      c = '_';
    }
  }
  return replacement;
}
