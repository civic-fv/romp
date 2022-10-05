#pragma once

#include <cstddef>
#include <murphi/Model.h>
#include <murphi/Node.h>

#ifndef MURPHI_API
#define MURPHI_API __attribute__((visibility("default")))
#endif

namespace murphi {

/* Check a node in the AST and all its children for inconsistencies and throw
 * murphi::Error if found.
 */
MURPHI_API void validate(const Node &n);

} // namespace murphi
