#pragma once

#include <cstddef>
#include <romp/Model.h>

#ifndef ROMP_API
#define ROMP_API __attribute__((visibility("default")))
#endif

namespace romp {

/* Resolve symbolic references (romp::ExprIDs and romp::TypeExprIDs) within a
 * model. Throws romp::Error if this process fails.
 */
ROMP_API void updateASTs(Model &m);

} // namespace romp
