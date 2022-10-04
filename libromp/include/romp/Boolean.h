#pragma once

#include <cstddef>
#include <memory>
#include <romp/Expr.h>
#include <romp/Ptr.h>
#include <romp/TypeExpr.h>

#ifndef ROMP_API
#define ROMP_API __attribute__((visibility("default")))
#endif

namespace romp {

/// the built in boolean type that is implicitly declared in all Murphi models
extern ROMP_API const Ptr<Enum> Boolean;

/// literals for Murphi “False” and “True”
///
/// These are included for convenience, so you can assign to expressions to
/// these constants if relevant. Do not compare against these expressions. If
/// you want to ask “is this expression the literal true/false?” use
/// `Expr::is_literal_true`/`Expr::is_literal_false`.
extern ROMP_API const Ptr<Expr> False;
extern ROMP_API const Ptr<Expr> True;

} // namespace romp
