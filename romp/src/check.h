#pragma once

#include <murphi/murphi.h>

// validate the given AST contains no idioms that cannot be handled by romp,
// and throws error if any are found
void check(const murphi::Node &n);