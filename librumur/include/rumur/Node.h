#pragma once

#include "location.hh"
#include <climits>
#include <cstddef>
#include <iostream>

#ifndef RUMUR_API_WITH_RTTI
#define RUMUR_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace rumur {

class BaseTraversal;
class ConstBaseTraversal;

class BaseTraversal;
class ConstBaseTraversal;

struct RUMUR_API_WITH_RTTI Node {

  /// originating line and column source position
  location loc;

  /// A numeric identifier of this node, unique within the current AST. A value
  /// of `SIZE_MAX` means this node (and its children) have not yet been indexed
  /// (see `Model::reindex`). This value can be useful when doing code
  /// generation and needing to invent unique symbols.
  size_t unique_id = SIZE_MAX;

  Node() = delete;
  Node(const location &loc_);
  virtual ~Node() = default;

  /// Create a copy of this node. This is necessary rather than simply relying
  /// on the copy constructor because of the inheritance hierarchy. That is, an
  /// agnostic class like `Ptr` can call this to copy a node without knowing its
  /// precise derived type and without object slicing.
  virtual Node *clone() const = 0;

  /// Perform operations that require symbol resolution to be complete first,
  /// or that need to be recalculated after changes to dependent nodes occurred
  /// (a messy solution to a earlier design decision, and to support legacy code).
  /// Must be called after symbol resolution has occurred for all of it's members!
  /// It is always called whenever a non-const traversal tool is used to visit a node!
  /// This is called by default in the resolve-symbol helper after a Node has been visited
  ///   and its symbols linked.
  ///  (aka in the dispatch method after returning from a visit call)
  /// It is recommended to always call it after modifying an AST member
  ///  therefore it is also always recommended to ensure a node's 
  ///  dependent and dependee symbols are properly updated after making any changes.
  /// (This exists only because this parsing system/lib does not keeping 
  ///   an active symtab structure during parsing and until the AST is discarded)
  /// CONTRACT: implementations and overrides of this function should NEVER break symbol resolution!
  virtual void update();

  /// Confirm that data structure invariants hold. This function throws
  /// `rumur::Error` if invariants are violated.
  virtual void validate() const {}

  /// traverse this node and its children using the given action
  virtual void visit(BaseTraversal &visitor) = 0;
  virtual void visit(ConstBaseTraversal &visitor) const = 0;

protected:
  Node(const Node &) = default;
  Node &operator=(const Node &) = default;
};

} // namespace rumur
