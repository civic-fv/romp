#include "location.hh"
#include "parser.yy.hh"
#include <cassert>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <romp/Decl.h>
#include <romp/Model.h>
#include <romp/Ptr.h>
#include <romp/except.h>
#include <romp/parse.h>
#include <romp/scanner.h>
#include <romp/sanitize_rule_names.h>

namespace romp {

std::string& _to_lower(std::string& data) {
  std::transform(data.begin(), data.end(), data.begin(),
    [](unsigned char c){ return std::tolower(c); })
  return data;
}

// implementation ignores case for these items
const std::unordered_set<std::string> RESERVED_FUNCT_NAMES{"ismember", "isundefined", "multisetadd", "multisetcount", "multisetremove", "multisetremovepred"};

const IDHandler MURPHI_RESERVED_NAMES_HANDLER = [&](std::string name, const IdType id_type, const location& loc) -> std::optional<std::string> {
    switch (id_type) {
      case FUNCTION_NAME:
        auto res = RESERVED_FUNCT_NAMES.find(_to_lower(name));
        if (res != RESERVED_FUNCT_NAMES.end())
          throw throw Error("Function/Procedure name/id `"+name+"` conflicts with reserved id `"+*res+"`", loc);
        break;
      case VALUE_NAME:
      case VARIABLE_NAME:
      case CONST_NAME:
      case ENUM_NAME:
      case ALIAS_NAME:
      case QUANTIFIER_NAME:
      case FUNCT_PARAM_NAME:
        if (_to_lower(name) == "undefined")
          throw Error("name/id `"+name+"` conflicts with reserved word `undefined`", loc);
        break;
      case TYPE_NAME:
        if (_to_lower(name) == "undefined")
          throw Error("type name/id `"+name+"` conflicts with reserved word `undefined`", loc);
        break;
      case RULE_NAME:
      case PROPERTY_RULE_NAME:
      case PROPERTY_STMT_NAME:
      case REC_MEMBER_NAME:
      default:
        break;
    }
    return {name};
  };


Ptr<Model> parse(std::istream &input) {
  return parse(input)
}

Ptr<Model> parse(std::istream &input, const std::unordered_set<std::string>& reserved_names) {
  std::unordered_set<std::string> reserved(RESERVED_NAMES);

  return parse(input, [&](std::string name, const id_type, const location& loc) -> std::optional<std::string> {
                        auto res = reserved_names.find(name);
                        if (name != reserved_names.end())
                          throw Error("`"+name+"` conflicts with reserved name `"+*res+"`", loc);
                        return {name};
                      });
}

Ptr<Model> parse(std::istream &input, IdHandler id_handler) {
  // Setup the parser
  scanner s(&input);
  Ptr<Model> m;
  parser p(s, m, [&](std::string name, const IdType id_type, const location& loc) -> std::string {
                  MURPHI_RESERVED_NAMES_HANDLER(name,id_type,loc);
                  auto result = id_handler(name, id_type, loc);
                  if (not result)
                    return *result;
                  throw Error("`" + name + "` not allowed as a name!", loc);
                 });

  // Parse the input model
  int err = p.parse();
  if (err != 0)
    throw Error("parsing failed", location());

  return m;
}

} //namespace romp

namespace std {

std::string to_string(const romp::IdType value) {
  using namespace romp;
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
      case REC_MEMBER_NAME: return "REC_MEMBER_NAME";
      default: return "<UNKNOWN_TYPE>";
    }
    return "<UNKNOWN_TYPE>";
}

} // namespace std
