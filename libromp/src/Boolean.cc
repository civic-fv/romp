#include "location.hh"
#include <cstddef>
#include <memory>
#include <romp/Boolean.h>
#include <romp/Decl.h>
#include <romp/Expr.h>
#include <romp/Number.h>
#include <romp/Ptr.h>
#include <romp/TypeExpr.h>
#include <string>
#include <utility>
#include <vector>

using namespace romp;

const Ptr<Enum> romp::Boolean =
    Ptr<Enum>::make(std::vector<std::pair<std::string, location>>(
                        {{"false", location()}, {"true", location()}}),
                    location());

const Ptr<Expr> romp::False = Ptr<ExprID>::make(
    "false",
    Ptr<ConstDecl>::make("boolean", Ptr<Number>::make(0, location()), Boolean,
                         location()),
    location());

const Ptr<Expr> romp::True = Ptr<ExprID>::make(
    "true",
    Ptr<ConstDecl>::make("boolean", Ptr<Number>::make(1, location()), Boolean,
                         location()),
    location());
