#pragma once

#include <cstddef>
#include <murphi/Node.h>
#include <string>

#ifndef MURPHI_API
#define MURPHI_API __attribute__((visibility("default")))
#endif

namespace murphi {

/** 
 * @brief ensure all rules have [a-zA-Z_][a-zA-Z_0-9]* names
 *
 *        This will rename any rules that are not safe to use as, e.g. a C symbol. This
 *        can be useful for code generators that want to derive symbols to emit from
 *        the names of the rules.
 * 
 * @param n : \c murphi::Node& - an AST Node that is the root af a subtree 
 *                              that will be traversed for sanitization.
 *                              (modifies existing AST)
 */
MURPHI_API void sanitize_rule_names(Node &n);

/**
 * @brief ensure provided name conforms to 
 *        `[a-zA-Z_][a-zA-Z_0-9]*` (C/C++) naming conventions
 * 
 * @param name : \c const \c std::string& - the name to be sanitized.
 * @return \c std::string - the resulting sanitized name.
 */
MURPHI_API std::string sanitize_name(const std::string& name);

} // namespace murphi
