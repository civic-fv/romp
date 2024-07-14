#pragma once

#include <cstddef>
#include <iostream>
#include <murphi/Model.h>
#include <murphi/Ptr.h>
#include <murphi/parse_helpers.h>
#include <functional>
#include <optional>
#include <string>
#include <unordered_set>

#ifndef MURPHI_API
#define MURPHI_API __attribute__((visibility("default")))
#endif

namespace murphi {

extern const IdHandler MURPHI_RESERVED_NAMES_HANDLER;


/**
 * @brief Parse in a model from an input stream.
 *
 * @param input : \c std::istream& - a input source to read from
 * @return \c murphi::Ptr<murphi::Model> - a fully parsed murphi AST
 * @throw \c murphi::Error - on parsing and Murphi language errors.
 */
MURPHI_API Ptr<Model> parse(std::istream &input);

/**
 * @brief Parse in a model from an input stream. Throws Errors on parsing errors.
 *
 * @param input : \c std::istream& - a input source to read from
 * @param reserved_names : \c std::unordered_set<std::string> - a single generic list of reserved names
 *                                                              that all ID's will be checked against.
 * @return \c murphi::Ptr<murphi::Model> - a fully parsed murphi AST
 * @throw \c murphi::Error - on parsing and Murphi language errors.
 */
MURPHI_API Ptr<Model> parse(std::istream &input, const std::unordered_set<std::string>& reserved_names);

// /**
//  * @brief Parse in a model from an input stream. Throws Errors on parsing errors.
//  *
//  * @param input : \c std::istream& - a input source to read from
//  * @param reserved_var_enum_names : \c std::unordered_set<std::string> - a set of reserved names
//  *                                                                       for variables and enum values.
//  * @param reserved_type_names : \c std::unordered_set<std::string> - a set of reserved names for type IDs
//  * @param reserved_func_names : \c std::unordered_set<std::string> - a set of reserved names for functions
//  * @param reserved_rule_names : \c std::unordered_set<std::string> - a set of reserved names for rule strings.
//  * @param reserved_rec_member_names : \c std::unordered_set<std::string> - a set of reserved names for record member IDs.
//  * @return \c murphi::Ptr<murphi::Model> - a fully parsed murphi AST
//  * @throw \c murphi::Error - on parsing and Murphi language errors.
//  */
// MURPHI_API Ptr<Model> parse(std::istream &input, const std::unordered_set<std::string>& reserved_var_enum_names,
//                                                const std::unordered_set<std::string>& reserved_type_names,
//                                                const std::unordered_set<std::string>& reserved_func_names,
//                                                const std::unordered_set<std::string>& reserved_rule_names,
//                                                const std::unordered_set<std::string>& reserved_rec_member_names);

/**
 * @brief Parse in a model from an input stream. Throws Errors on parsing errors.
 *
 * @param input : \c std::istream& - a input source to read from
 * @param id_handler \c murphi::IdHandler - A handler for processing all id's
 * @return \c murphi::Ptr<murphi::Model> - a fully parsed murphi AST
 * @throw \c murphi::Error - on parsing and Murphi language errors.
 */
MURPHI_API Ptr<Model> parse(std::istream &input, const IdHandler& id_handler);

} // namespace murphi