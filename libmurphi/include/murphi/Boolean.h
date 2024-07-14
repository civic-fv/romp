#pragma once

#include <cstddef>
#include <memory>
#include <murphi/Expr.h>
#include <murphi/Ptr.h>
#include <murphi/TypeExpr.h>
#include <murphi/Decl.h>

#ifndef MURPHI_API
#define MURPHI_API __attribute__((visibility("default")))
#endif

namespace murphi {

/// the built in boolean type that is implicitly declared in all Murphi models
extern MURPHI_API const Ptr<Enum> BooleanEnum;
extern MURPHI_API const Ptr<TypeDecl> BooleanDecl;
extern MURPHI_API const Ptr<TypeExprID> Boolean;

/// literals for Murphi “False” and “True”
///
/// These are included for convenience, so you can assign to expressions to
/// these constants if relevant. Do not compare against these expressions. If
/// you want to ask “is this expression the literal true/false?” use
/// `Expr::is_literal_true`/`Expr::is_literal_false`.
extern MURPHI_API const Ptr<ConstDecl> FalseDecl;
extern MURPHI_API const Ptr<Expr> False;
extern MURPHI_API const Ptr<ConstDecl> TrueDecl;
extern MURPHI_API const Ptr<Expr> True;

} // namespace murphi