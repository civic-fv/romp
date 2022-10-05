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

const Ptr<Enum> murphi::Boolean =
    Ptr<Enum>::make(std::vector<std::pair<std::string, location>>(
                        {{"false", location()}, {"true", location()}}),
                    location());

const Ptr<Expr> murphi::False = Ptr<ExprID>::make(
    "false",
    Ptr<ConstDecl>::make("boolean", Ptr<Number>::make(0, location()), Boolean,
                         location()),
    location());

const Ptr<Expr> murphi::True = Ptr<ExprID>::make(
    "true",
    Ptr<ConstDecl>::make("boolean", Ptr<Number>::make(1, location()), Boolean,
                         location()),
    location());
