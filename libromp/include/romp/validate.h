#pragma once

#include <cstddef>
#include <romp/Model.h>
#include <romp/Node.h>

#ifndef ROMP_API
#define ROMP_API __attribute__((visibility("default")))
#endif

namespace romp {

/* Check a node in the AST and all its children for inconsistencies and throw
 * romp::Error if found.
 */
ROMP_API void validate(const Node &n);

} // namespace romp
