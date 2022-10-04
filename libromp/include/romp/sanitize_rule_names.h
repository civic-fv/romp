#pragma once

#include <cstddef>
#include <romp/Node.h>
#include <string>

#ifndef ROMP_API
#define ROMP_API __attribute__((visibility("default")))
#endif

namespace romp {

/** 
 * @brief ensure all rules have [a-zA-Z_][a-zA-Z_0-9]* names
 *
 *        This will rename any rules that are not safe to use as, e.g. a C symbol. This
 *        can be useful for code generators that want to derive symbols to emit from
 *        the names of the rules.
 * 
 * @param n : \c romp::Node& - an AST Node that is the root af a subtree 
 *                              that will be traversed for sanitization.
 *                              (modifies existing AST)
 */
ROMP_API void sanitize_rule_names(Node &n);

/**
 * @brief ensure provided name conforms to 
 *        `[a-zA-Z_][a-zA-Z_0-9]*` (C/C++) naming conventions
 * 
 * @param name : \c const \c std::string& - the name to be sanitized.
 * @return \c std::string - the resulting sanitized name.
 */
ROMP_API std::string sanitize_name(const std::string& name);

} // namespace romp
