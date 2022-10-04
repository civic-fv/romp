// Romp exported API

#pragma once

#ifndef ROMP_API
#define ROMP_API
#endif

namespace romp {

// forward declaration to update visibility
class ROMP_API parser;

} // namespace romp

#include "location.hh"
#include "parser.yy.hh"
#include "position.hh"
#include "romp-get-version.h" // generated
#include <cstddef>
#include <romp/Boolean.h>
#include <romp/Comment.h>
#include <romp/Decl.h>
#include <romp/Expr.h>
#include <romp/Function.h>
#include <romp/Model.h>
#include <romp/Node.h>
#include <romp/Property.h>
#include <romp/Ptr.h>
#include <romp/Rule.h>
#include <romp/Stmt.h>
#include <romp/Symtab.h>
#include <romp/TypeExpr.h>
#include <romp/except.h>
#include <romp/indexer.h>
#include <romp/parse.h>
#include <romp/updateASTs.h>
#include <romp/sanitize_rule_names.h>
#include <romp/scanner.h>
#include <romp/traverse.h>
#include <romp/validate.h>
// stack.hh is deliberately not included; just use std::stack
