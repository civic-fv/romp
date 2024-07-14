#include "location.hh"
#include "parser.yy.hh"
#include <cassert>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <murphi/Decl.h>
#include <murphi/Model.h>
#include <murphi/Ptr.h>
#include <murphi/except.h>
#include <murphi/parse.h>
#include <murphi/scanner.h>
#include <murphi/sanitize_rule_names.h>

namespace murphi {

std::string _to_lower(const std::string& data) {
  std::string result;
  std::transform(data.begin(), data.end(), result.begin(),
    [](unsigned char c){ return std::tolower(c); });
  return result;
}


// implementation ignores case for these items
const std::unordered_set<std::string> RESERVED_FUNCT_NAMES{"clear", "ismember", "isundefined", "multisetadd", "multisetcount", "multisetremove", "multisetremovepred", "undefine", "undefined"};
const std::unordered_set<std::string> RESERVED_TYPE_NAMES{"array", "boolean", "enum", "multiset", "range", "scalarset" /* , "real" */, "undefined", "union"};

const IdHandler MURPHI_RESERVED_NAMES_HANDLER = [](std::string name, const IdType id_type, const location& loc) -> std::optional<std::string> {
    std::string lower_name = _to_lower(name);
    switch (id_type) {
      case FUNCTION_NAME: {
        // if (name == "") // technically parser should never allow this
        //   throw Error("missing name/id in Function/Procedure declaration", loc);
        auto res = RESERVED_FUNCT_NAMES.find(lower_name);
        if (res != RESERVED_FUNCT_NAMES.end())
          throw Error("Function/Procedure name/id `"+name+"` conflicts with reserved id `"+*res+"`", loc);
        break;
      }
      case VALUE_NAME:
      case VARIABLE_NAME:
      case CONST_NAME:
      case ENUM_NAME:
      case QUANTIFIER_NAME:
      case ALIAS_NAME:
      case FUNCT_PARAM_NAME:
        if (lower_name == "undefined")
          throw Error("name/id (`"+name+"`) conflicts with a reserved word (`undefined`) "
                      "["+murphi::to_string(id_type)+"]", loc);
        break;
      case TYPE_NAME: {
        // if (name == "") // technically parser should never allow this
        //   throw Error("missing name/id in type declaration", loc);
        auto res = RESERVED_TYPE_NAMES.find(lower_name);
        if (res != RESERVED_TYPE_NAMES.end())
          throw Error("type name/id (`"+name+"`) conflicts with a reserved id (`"+*res+"`)", loc);
        break;
      }
      case RULE_NAME:
      case PROPERTY_RULE_NAME:
      case PROPERTY_STMT_NAME:
      case ERROR_STMT_NAME:
      case REC_MEMBER_NAME:
      default:
        break;
    }
    return {name};
  };


Ptr<Model> parse(std::istream &input) {
  return parse(input,
               [&](std::string name, const IdType id_type, const location& loc) -> std::optional<std::string> {
                  return {name};
               });
}

Ptr<Model> parse(std::istream &input, const std::unordered_set<std::string>& reserved_names) {
  return parse(input, [&](std::string name, const IdType id_type, const location& loc) -> std::optional<std::string> {
                        auto res = reserved_names.find(name);
                        if (res != reserved_names.end())
                          throw Error("name/id (`"+name+"`) conflicts with a reserved name (`"+*res+"`) "
                                      "["+murphi::to_string(id_type)+"]", loc);
                        return {name};
                      });
}

Ptr<Model> parse(std::istream &input, const IdHandler& id_handler) {
  // Setup the parser
  scanner s(&input);
  Ptr<Model> m;
  parser p(s, m, [&](std::string name, const IdType id_type, const location& loc) -> std::string {
                  MURPHI_RESERVED_NAMES_HANDLER(name,id_type,loc);
                  auto result = id_handler(name, id_type, loc);
                  if (not result.has_value())
                    throw Error("`" + name + "` not allowed as a name/id! ["+murphi::to_string(id_type)+"]", loc);
                  return std::string(result.value());
                 });

  // Parse the input model
  int err = p.parse();
  if (err != 0)
    throw Error("parsing failed", location());

  return m;
}


std::string to_string(const murphi::IdType value) {
  using namespace murphi;
  switch (value) {
      case ALIAS_NAME: return "ALIAS_NAME";
      case FUNCTION_NAME: return "FUNCTION_NAME";
      case VALUE_NAME: return "VALUE_NAME";
      case VARIABLE_NAME: return "VARIABLE_NAME";
      case CONST_NAME: return "CONST_NAME";
      case ENUM_NAME: return "ENUM_NAME";
      case QUANTIFIER_NAME: return "QUANTIFIER_NAME";
      case FUNCT_PARAM_NAME: return "FUNCT_PARAM_NAME";
      case TYPE_NAME: return "TYPE_NAME";
      case RULE_NAME: return "RULE_NAME";
      case PROPERTY_RULE_NAME: return "PROPERTY_RULE_NAME";
      case PROPERTY_STMT_NAME: return "PROPERTY_STMT_NAME";
      case ERROR_STMT_NAME: return "ERROR_STMT_NAME";
      case REC_MEMBER_NAME: return "REC_MEMBER_NAME";
      default: return "<UNKNOWN_TYPE>";
    }
    return "<UNKNOWN_TYPE>";
}

} // namespace murphi