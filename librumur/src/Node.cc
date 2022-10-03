#include <cstddef>
#include <rumur/Node.h>

namespace rumur {

Node::Node(const location &loc_) : loc(loc_) {}

void Node::visit(BaseTraversal& visitor) { 
  visit(*(reinterpret_cast<BaseTraversal*>(&visitor))); 
}
void Node::visit(ConstBaseTraversal& visitor) const { 
  visit(*(reinterpret_cast<ConstBaseTraversal*>(&visitor)));
}

void Node::update() {}

} // namespace rumur
