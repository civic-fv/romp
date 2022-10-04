#include <cstddef>
#include <romp/Property.h>
#include <romp/Ptr.h>
#include <romp/traverse.h>

namespace romp {

Property::Property(Category category_, const Ptr<Expr> &expr_,
                   const location &loc_)
    : Node(loc_), category(category_), expr(expr_) {}

Property *Property::clone() const { return new Property(*this); }

void Property::visit(BaseTraversal &visitor) { visitor.visit_property(*this); }

void Property::visit(ConstBaseTraversal &visitor) const {
  visitor.visit_property(*this);
}

} // namespace romp
