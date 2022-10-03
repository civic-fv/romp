#pragma once

#include <rumur/Ptr.h>
#include <rumur/Node.h>
#include <typeinfo> 

#ifndef RUMUR_API_WITH_RTTI
#define RUMUR_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace rumur {
namespace ext {

/**
 * @brief Convert a model with extended (ext) AST nodes to a legacy AST.
 *        This allows older model checkers to easily support newer Murphi syntax.
 *        NOTE: make sure that the AST you pass in has been validated in it's current state 
 *              before producing a legacy AST.
 *        NOTE: This function will validate the resulting AST after it has been transformed,
 *              therefore catch the \c rumur::Error 's as you see fit.
 */
Ptr<Node> make_legacy(const Ptr<Node> &n);

/**
 * @brief abstract interface for extended AST nodes to allow for them to be easily replaced by 
 *        legacy compliant AST nodes.
 * @tparam LT the legacy node that 
 */
template<class LT>
struct RUMUR_API_WITH_RTTI IExtNode {
  static_assert(not std::is_base_of<IExtNode, LT>::value, "LT (Legacy node Type) cannot be an extended node!");
  static_assert(std::is_base_of<Node, LT>::value, "LT needs to be an inheritor of rumur::Node");

  /**
   * @brief Convert an extended AST node to a legacy AST node.
   * @return Ptr to legacy conversion of node 
   */
  virtual Ptr<LT> make_legacy() const;
  // virtual Ptr<Node> make_legacy() const = 0;

  IExtNode() = default;
  ~IExtNode() = default;
};

} //namespace ext
} //namespace rumur
