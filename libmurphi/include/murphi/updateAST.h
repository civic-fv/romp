#pragma once

#include <cstddef>
#include <murphi/Model.h>

#ifndef MURPHI_API
#define MURPHI_API __attribute__((visibility("default")))
#endif

namespace murphi {

/* Resolve symbolic references (murphi::ExprIDs and murphi::TypeExprIDs) within a
 * model. Throws murphi::Error if this process fails.
 */
MURPHI_API void updateAST(Model &m);

} // namespace murphi
