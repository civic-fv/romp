/**
 * @proj romp
 * @author Andrew Osterhout
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp_def.hpp
 * 
 * @brief A bunch of definitions for configuration 
 *        and other details in the romp codegen tool.
 * 
 * @date 2022/05/11
 * @version 0.1
 */

#ifndef _romp_src_romp_def_hpp
#define _romp_src_romp_def_hpp

#ifdef DEBUG  // CMAKE debug config should take care of this
#ifndef _ROMP_DEV_DEBUG_INCLUDE_DIR  // manually adjust this here if you want it to be different than the auto cmake system config default
/* Define to make debugging the generated model checker easier
     set it to the path from the generated model checker file to the romp/resources dir to work */
#define _ROMP_DEV_DEBUG_INCLUDE_DIR "../romp/resources"
#endif
#endif

#define ROMP_VERSION "0.0.1"

#define ROMP_UTIL_NAMESPACE_NAME "romp"

#define ROMP_UTIL_NAMESPACE "::" ROMP_UTIL_NAMESPACE_NAME

#define ROMP_RAND_WALKER_TYPE ROMP_UTIL_NAMESPACE "::" "IRandWalker"

#define ROMP_STATE_RAND_WALKER_VAR "__rw__"

#define ROMP_RAND_WALKER_DECL  "" ROMP_RAND_WALKER_TYPE "* " ROMP_STATE_RAND_WALKER_VAR "; // reference to associated romp rand walker"

#define ROMP_MODEL_NAMESPACE_NAME "__model__"

#define ROMP_CALLER_NAMESPACE_NAME "__caller__"

#define ROMP_INFO_NAMESPACE_NAME "__info__"

#define ROMP_STATE_CLASS_NAME "__Model__"

#define ROMP_STATE_TYPE "::" ROMP_MODEL_NAMESPACE_NAME "::" ROMP_STATE_CLASS_NAME

#define ROMP_TYPE_NAMESPACE "__type__"

#define ROMP_HISTORY_SIZE_PREPROCESSOR_VAR "_ROMP_HIST_LEN"
#define ROMP_HISTORY_SIZE_PREPROCESSOR_VAR_DEFAULT_VALUE (4ul)
#define ROMP_MEASURE_PREPROCESSOR_VAR "__ROMP__DO_MEASURE"
#define ROMP_SIMPLE_TRACE_PREPROCESSOR_VAR "__ROMP__SIMPLE_TRACE"
#define ROMP_SYMMETRY_PREPROCESSOR_VAR "__romp__ENABLE_symmetry"
#define ROMP_ASSUME_PREPROCESSOR_VAR "__romp__ENABLE_assume_property"
#define ROMP_COVER_PREPROCESSOR_VAR "__romp__ENABLE_cover_property"
#define ROMP_LIVENESS_PREPROCESSOR_VAR "__romp__ENABLE_liveness_property"

#define ROMP_STATESPACE_LEN "_ROMP_STATESPACE_COUNT_str"
// #define ROMP_CALLER_RULE_DECL "const ::romp::Rule ";
#define ROMP_RULESETS_LEN "_ROMP_RULESETS_LEN"
#define ROMP_RULES_LEN "_ROMP_RULE_COUNT"
#define ROMP_CALLER_RULESETS_VAR_NAME "RULESETS"
#define ROMP_CALLER_RULE_TYPE ROMP_UTIL_NAMESPACE "::Rule"
#define ROMP_CALLER_RULESETS_TYPE ROMP_UTIL_NAMESPACE "::RuleSet"
#define ROMP_CALLER_RULESETS_DECL "const " ROMP_CALLER_RULESETS_TYPE " " ROMP_CALLER_RULESETS_VAR_NAME "[" ROMP_RULESETS_LEN "]"
#define ROMP_CALLER_RULESETS_VAR "::" ROMP_CALLER_NAMESPACE_NAME "::" ROMP_CALLER_RULESETS_VAR_NAME
// #define ROMP_RULESET_INFOS_LEN "_ROMP_RULESET_INFO_LEN"
#define ROMP_INFO_RULESETS_VAR_NAME "RULE_SET_INFOS"
#define ROMP_INFO_RULESET_TYPE ROMP_UTIL_NAMESPACE "::RuleInfo"
#define ROMP_INFO_RULESETS_DECL "const " ROMP_INFO_RULESET_TYPE " " ROMP_INFO_RULESETS_VAR_NAME "[" ROMP_RULESETS_LEN "]"
#define ROMP_INFO_RULESETS_VAR "::" ROMP_INFO_NAMESPACE_NAME "::" ROMP_INFO_RULESETS_VAR_NAME

#define ROMP_PROPERTY_RULES_LEN "_ROMP_PROPERTY_RULES_LEN"
#define ROMP_COVER_PROP_COUNT "_ROMP_COVER_PROP_COUNT"
#define ROMP_LIVENESS_PROP_COUNT "_ROMP_LIVENESS_PROP_COUNT"
#define ROMP_CALLER_PROPERTIES_VAR_NAME "PROPERTIES"
#define ROMP_CALLER_PROPERTY_TYPE ROMP_UTIL_NAMESPACE "::Property"
#define ROMP_CALLER_PROPERTIES_DECL "const " ROMP_CALLER_PROPERTY_TYPE " " ROMP_CALLER_PROPERTIES_VAR_NAME "[" ROMP_PROPERTY_RULES_LEN "]"
#define ROMP_PROPERTY_INFOS_LEN "_ROMP_PROPERTIES_LEN"
#define ROMP_INFO_PROPERTIES_VAR_NAME "PROPERTY_INFOS"
#define ROMP_INFO_PROPERTY_TYPE ROMP_UTIL_NAMESPACE "::PropertyInfo"
#define ROMP_INFO_PROPERTIES_DECL "const " ROMP_INFO_PROPERTY_TYPE " " ROMP_INFO_PROPERTIES_VAR_NAME "[" ROMP_PROPERTY_INFOS_LEN "]"
#define ROMP_INFO_PROPERTIES_VAR "::" ROMP_INFO_NAMESPACE_NAME "::" ROMP_INFO_PROPERTIES_VAR_NAME

#define ROMP_STARTSTATE_RULES_LEN "_ROMP_STARTSTATES_LEN"
#define ROMP_CALLER_STARTSTATE_VAR_NAME "STARTSTATES"
#define ROMP_CALLER_STARTSTATES_DECL "const " ROMP_UTIL_NAMESPACE "::StartState " ROMP_CALLER_STARTSTATE_VAR_NAME "[" ROMP_STARTSTATE_RULES_LEN "]"
#define ROMP_STARTSTATE_INFOS_LEN "_ROMP_STARTSTATE_INFO_LEN"
#define ROMP_INFO_STARTSTATE_VAR_NAME "STARTSTATE_INFOS"
#define ROMP_INFO_STARTSTATES_DECL "const " ROMP_UTIL_NAMESPACE "::StartStateInfo " ROMP_INFO_STARTSTATE_VAR_NAME "[" ROMP_STARTSTATE_INFOS_LEN "]"
#define ROMP_INFO_STARTSTATES_VAR "::" ROMP_INFO_NAMESPACE_NAME "::" ROMP_INFO_STARTSTATE_VAR_NAME

#define ROMP_ERRORS_LEN "_ROMP_ERRORS_LEN"
#define ROMP_INFO_ERRORS_VAR_NAME "ERROR_INFOS"
#define ROMP_INFO_ERRORS_DECL "const " ROMP_UTIL_NAMESPACE "::MErrorInfo " ROMP_INFO_ERRORS_VAR_NAME "[" ROMP_ERRORS_LEN "]"
#define ROMP_INFO_ERRORS_VAR "::" ROMP_INFO_NAMESPACE_NAME "::" ROMP_INFO_ERRORS_VAR_NAME

#define ROMP_FUNCTS_LEN "_ROMP_FUNCTS_LEN"
#define ROMP_INFO_FUNCTS_VAR_NAME "FUNCT_INFOS"
#define ROMP_INFO_FUNCTS_DECL "const " ROMP_UTIL_NAMESPACE "::FunctInfo " ROMP_INFO_FUNCTS_VAR_NAME "[" ROMP_FUNCTS_LEN "]"
#define ROMP_INFO_FUNCTS_VAR "::" ROMP_INFO_NAMESPACE_NAME "::" ROMP_INFO_FUNCTS_VAR_NAME

// #define ROMP_STARTSTATES_LEN "ROMP_ERRORS_LEN"
// #define ROMP_CALLER_STARTSTATES_DECL "const " ROMP_UTIL_NAMESPACE "::ErrorInfo STARTSTATES["ROMP_STARTSTATES_LEN"]"

#define ROMP_MODEL_EXCEPTION_TYPE ROMP_UTIL_NAMESPACE "::" "IModelError"

#define ROMP_MODEL_ERROR_TYPE_PROPERTY ROMP_UTIL_NAMESPACE "::" "ModelPropertyError"
#define ROMP_MODEL_ERROR_TYPE_RULE ROMP_UTIL_NAMESPACE "::" "ModelRuleError"
#define ROMP_MODEL_ERROR_TYPE_STARTSTATE ROMP_UTIL_NAMESPACE "::" "ModelStartStateError"
#define ROMP_MODEL_ERROR_TYPE_FUNCT ROMP_UTIL_NAMESPACE "::" "ModelFunctError"
#define ROMP_MODEL_ERROR_TYPE_ERROR ROMP_UTIL_NAMESPACE "::" "ModelMErrorError"

#define ROMP_JSON_TYPE "nlohmann::json"
#define ROMP_JSON_STREAM_TYPE "::" ROMP_UTIL_NAMESPACE_NAME "::" "ojstream<O>"
// #define ROMP_OUT_STREAM_TYPE "::std::ostream"
#define ROMP_OUT_STREAM_TYPE "::" ROMP_UTIL_NAMESPACE_NAME "::" "ostream_p"
#define ROMP_MAKE_JSON_CONVERTER_SIG(_type) "template<class O> const ::romp::stream_void& " << (_type) << "_to_json(" ROMP_JSON_STREAM_TYPE "& json, const " << (_type) << "& val) noexcept"
#define ROMP_MAKE_STREAM_CONVERTER_SIG(_type) "const ::romp::stream_void& " << (_type) << "_to_str(" ROMP_OUT_STREAM_TYPE "& out, const " << (_type) << "& val) noexcept"
// #define ROMP_MAKE_JSON_CONVERTER_SIG(_type) "template<class O> " ROMP_JSON_STREAM_TYPE "& " << (type_) << "_to_json(" ROMP_JSON_STREAM_TYPE "& json, const " << (_type) << "& val) noexcept"
// #define ROMP_MAKE_STREAM_CONVERTER_SIG(_type) ROMP_OUT_STREAM_TYPE "& " << (_type) << "_to_str(" ROMP_OUT_STREAM_TYPE "& out, const " << (_type) << "& val) noexcept"
#define ROMP_MAKE_JSON_CONVERTER_CALL(_type,_val) "" << (_type) << "_to_json(json," << (_val) << ")"
#define ROMP_MAKE_STREAM_CONVERTER_CALL(_type,_val) "" << (_type) << "_to_str(out," << (_val) << ")"
#define ROMP_MAKE_TYPE_INIT_SIG(_type) "void _init_" << (_name) << "(" << (_name) << "& val)"
#define ROMP_MAKE_TYPE_INIT_CALL(_type,_val) "_init_" << (_type) << "(" << (_val) << ")" 

#define ROMP_SHOW_TYPE_OPTION_EXPR "::romp::OPTIONS.report_show_type"
// #define ROMP_MAKE_SHOW_TYPE_TURN_COND(_type) "((::romp::OPTIONS.result_show_type) ? \\": " + (_type) + " =\\" : \\":=\\")"

#define ROMP_GENERATED_FILE_PREFACE(p) \
        "/*\n" p "\n*/\n"

#define ROMP_PREDEFINED_TYPES "boolean"

#define ROMP_STARTSTATE_PREFIX "__StartState__"
#define ROMP_RULE_GUARD_PREFIX "__Rule_guard__"
#define ROMP_RULE_ACTION_PREFIX "__Rule_action__"
#define ROMP_PROPERTYRULE_PREFIX "__Property__"

#define ROMP_PROPERTY_TYPE_BASE ROMP_UTIL_NAMESPACE "::PropertyType"
#define ROMP_PROPERTY_TYPE_INVAR ROMP_PROPERTY_TYPE_BASE "::INVARIANT"
#define ROMP_PROPERTY_TYPE_ASSERT ROMP_PROPERTY_TYPE_BASE "::ASSERTION"
#define ROMP_PROPERTY_TYPE_ASSUME ROMP_PROPERTY_TYPE_BASE "::ASSUMPTION"
#define ROMP_PROPERTY_TYPE_COVER ROMP_PROPERTY_TYPE_BASE "::COVER"
#define ROMP_PROPERTY_TYPE_LIVENESS ROMP_PROPERTY_TYPE_BASE "::LIVENESS"

#define ROMP_MAKE_LOCATION_STRUCT(_loc) "{{" << (_loc).begin.line << "," << (_loc).begin.column << "},"\
                                         "{" << (_loc).end.line << "," << (_loc).end.column << "}}"

#define ROMP_MAKE_RULE_INFO_STRUCT(_n, _json) "{\"" << nEscape((_n).name) << "\"," ROMP_MAKE_LOCATION_STRUCT((_n).loc) ",\"" << nEscape(_json) << "\"}"
#define ROMP_MAKE_PROPERTY_INFO_STRUCT(_n, _id, _name, _pt, _json) "{\"" << nEscape(_name) << "\"," << (_pt) << ",\"" << nEscape((_n).property.expr->to_string()) << "\"," << (_id) << "," ROMP_MAKE_LOCATION_STRUCT((_n).loc) ",\"" << nEscape(_json) << "\"}"
#define ROMP_MAKE_STARTSTATE_INFO_STRUCT(_n, _json) "{\"" << nEscape((_n).name) << "\"," ROMP_MAKE_LOCATION_STRUCT((_n).loc) ",\"" << nEscape(_json) << "\"}"
#define ROMP_MAKE_ERROR_INFO_STRUCT(_n, _inFunct, _json) "{\"" << nEscape((_n).message) << "\"," ROMP_MAKE_LOCATION_STRUCT((_n).loc) "," << (_inFunct) << ",\"" << nEscape(_json) << "\"}"
#define ROMP_MAKE_FUNCT_INFO_STRUCT(_n, _json, _str) "{\"" << nEscape((_n).name) << "\"," ROMP_MAKE_LOCATION_STRUCT((_n).loc) ",\"" << nEscape(_json) << "\",\"" << nEscape(_str) << "\"}"

#define ROMP_MAKE_RULESET_STRUCT_HEADER(_info_id) "{" ROMP_INFO_RULESETS_VAR"[" <<(_info_id)<<"]" ",std::vector<" ROMP_CALLER_RULE_TYPE ">{" 
#define ROMP_MAKE_RULESET_STRUCT_FOOTER(...) "}}" 
#define ROMP_MAKE_RULE_STRUCT(_guard, _action, _info_id, _json, _str) ROMP_CALLER_RULE_TYPE "{" << (_guard) << "," << (_action) << "," ROMP_INFO_RULESETS_VAR "[" <<(_info_id)<<"],\"" << nEscape(_json) << "\",\"" << nEscape(_str) << "\"}"
#define ROMP_MAKE_PROPERTY_STRUCT(_check, _info_id, _json, _str) "{" << (_check) << "," ROMP_INFO_PROPERTIES_VAR "[" <<(_info_id)<<"],\"" << nEscape(_json) << "\",\"" << nEscape(_str) << "\"}"
#define ROMP_MAKE_STARTSTATE_STRUCT(_init, _id, _info_id, _json, _str) "{" << (_init) << "," ROMP_INFO_STARTSTATES_VAR "[" <<(_info_id)<<"]," << (_id) << ",\"" << nEscape(_json) << "\",\"" << nEscape(_str) << "\"}"


#define ROMP_MAKE_MODEL_ERROR_PROPERTY(_n,_id) ROMP_MODEL_ERROR_TYPE_PROPERTY "(" << (_id) << ")"
#define ROMP_MAKE_MODEL_ERROR_RULE(_n,_id) ROMP_MODEL_ERROR_TYPE_RULE "(" << (_id) << ")"
#define ROMP_MAKE_MODEL_ERROR_RULE_GUARD(_n,_id) ROMP_MODEL_ERROR_TYPE_RULE "(" << (_id) << "," ROMP_MODEL_ERROR_TYPE_RULE "::GUARD)"
#define ROMP_MAKE_MODEL_ERROR_RULE_ACTION(_n,_id) ROMP_MODEL_ERROR_TYPE_RULE "(" << (_id) << "," ROMP_MODEL_ERROR_TYPE_RULE "::ACTION)"
#define ROMP_MAKE_MODEL_ERROR_STARTSTATE(_n,_id) ROMP_MODEL_ERROR_TYPE_STARTSTATE "(" << (_id) << ")"
#define ROMP_MAKE_MODEL_ERROR_FUNCT(_n,_id) ROMP_MODEL_ERROR_TYPE_FUNCT "(" << (_id) << ")"
#define ROMP_MAKE_MODEL_ERROR_ERROR(_n,_id) ROMP_MODEL_ERROR_TYPE_ERROR "(" << (_id) << ")"


#define _ROMP_PROPERTY_HANDLER_BASE "this->" ROMP_STATE_RAND_WALKER_VAR "->"
#define _ROMP_PROPERTY_HANDLER_INVAR _ROMP_PROPERTY_HANDLER_BASE "invariant_handler"
#define _ROMP_PROPERTY_HANDLER_ASSERT _ROMP_PROPERTY_HANDLER_BASE "assertion_handler"
#define _ROMP_PROPERTY_HANDLER_ASSUME _ROMP_PROPERTY_HANDLER_BASE "assumption_handler"
#define _ROMP_PROPERTY_HANDLER_COVER _ROMP_PROPERTY_HANDLER_BASE "cover_handler"
#define _ROMP_PROPERTY_HANDLER_LIVENESS _ROMP_PROPERTY_HANDLER_BASE "liveness_handler"
#define _ROMP_ERROR_HANDLER _ROMP_PROPERTY_HANDLER_BASE "error_handler"

#define ROMP_ASSERTION_HANDLER(_n,_id) _ROMP_PROPERTY_HANDLER_ASSERT "(" << *((_n).property.expr) << "," << (_id) << "u" ")"
#define ROMP_INVARIANT_HANDLER(_n,_id) _ROMP_PROPERTY_HANDLER_INVAR "(" << *((_n).property.expr) << "," << (_id) << "u" ")"
#define ROMP_ASSUMPTION_HANDLER(_n,_id) _ROMP_PROPERTY_HANDLER_ASSUME "(" << *((_n).property.expr) << "," << (_id) << "u" ")"
#define ROMP_COVER_HANDLER(_n,_id,_cn) _ROMP_PROPERTY_HANDLER_COVER "(" << *((_n).property.expr) << "," << (_cn) << "u," << (_id) << "u" ")"
#define ROMP_LIVENESS_HANDLER(_n,_id,_ln) _ROMP_PROPERTY_HANDLER_LIVENESS "(" << *((_n).property.expr) << "," << (_ln) << "u," << (_id) << "u" ")"
#define ROMP_ERROR_HANDLER(_id) _ROMP_ERROR_HANDLER "(" << (_id) << "u" ")"


#define ROMP_RESERVED_NAMES "" ROMP_STATE_CLASS_NAME, "to_json", \
                            ROMP_MODEL_NAMESPACE_NAME, ROMP_CALLER_NAMESPACE_NAME, ROMP_UTIL_NAMESPACE_NAME, \
                            "boolean", ROMP_STATE_RAND_WALKER_VAR, "std", ROMP_INFO_NAMESPACE_NAME, "res_"

#endif
