#pragma once

#include <romp/romp.h>

// validate the given AST contains no idioms that cannot be handled by murphi2c,
// and return false if any are found
bool check(const romp::Node &n);
