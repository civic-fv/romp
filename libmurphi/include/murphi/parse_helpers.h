#pragma once

#include "location.hh"
#include <cstddef>
#include <iostream>
#include <murphi/Model.h>
#include <murphi/Ptr.h>
#include <functional>
#include <optional>
#include <string>
#include <unordered_set>

#ifndef MURPHI_API
#define MURPHI_API __attribute__((visibility("default")))
#endif

namespace murphi {

enum IdType { NO_ID=0, VALUE_NAME, VARIABLE_NAME, CONST_NAME, ENUM_NAME, QUANTIFIER_NAME, ALIAS_NAME, FUNCT_PARAM_NAME,
              TYPE_NAME, REC_MEMBER_NAME, FUNCTION_NAME, RULE_NAME, PROPERTY_RULE_NAME,
              PROPERTY_STMT_NAME, ERROR_STMT_NAME };

std::string to_string(const IdType value);

/**
 * @brief A function that will be called when processing a user defined ID in the model,
 *        It allows you to perform actions and checks on names,
 *        then return an acceptable ID to use internally.
 *
 *        The return type is \c std::optional<std::string>,
 *        returning an empty optional construct
 *        will cause the parser to throw a generic
 *        \c murphi::Error about the name not being acceptable.
 *        Therefore, if you want to provide a \c murphi::Error with a more detailed
 *        message throw it yourself in your implementation.
 */
typedef std::function<std::optional<std::string>(const std::string&, const IdType, const location& loc)> IdHandler;

} // namespace murphi
