#include "location.hh"
#include <cstddef>
#include <memory>
#include <murphi/Boolean.h>
#include <murphi/Decl.h>
#include <murphi/Expr.h>
#include <murphi/Number.h>
#include <murphi/Ptr.h>
#include <murphi/TypeExpr.h>
#include <string>
#include <utility>
#include <vector>

using namespace murphi;

const Ptr<Enum> murphi::BooleanEnum =
    Ptr<Enum>::make(std::vector<std::pair<std::string, location>>(
                        {{"false", location()}, {"true", location()}}),
                    location());

const Ptr<TypeDecl> murphi::BooleanDecl =
    Ptr<TypeDecl>::make("boolean", murphi::BooleanEnum, location());

const Ptr<TypeExprID> murphi::Boolean =
    Ptr<TypeExprID>::make("boolean", murphi::BooleanDecl, location());


const Ptr<ConstDecl> murphi::FalseDecl = Ptr<ConstDecl>::make("false", 
                                                              Ptr<Number>::make(0, location()), Boolean,
                                                              location());

const Ptr<ConstDecl> murphi::TrueDecl = Ptr<ConstDecl>::make("true", 
                                                              Ptr<Number>::make(1, location()), Boolean,
                                                              location());

const Ptr<Expr> murphi::False = Ptr<ExprID>::make(
    "false",
    murphi::FalseDecl,
    location());

const Ptr<Expr> murphi::True = Ptr<ExprID>::make(
    "true",
    murphi::TrueDecl,
    location());
