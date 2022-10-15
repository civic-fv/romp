#include "generate_c.hpp"
#include "nested_escape.hpp"
// #include "../../common/escape.h"
#include "ScalarEnumGenerator.hpp"
#include "ModelGenerator.hpp"
// #include "CTypeGenerator.hpp"
// #include "ModelSplitter.hpp"
// #include "SigPerm.hpp"
#include "StateSpaceCalc.hpp"
#include "options.h"
#include "resources.h"
#include <cstddef>
#include <iostream>
#include <murphi/murphi.h>
#include <string>
#include <vector>
#include <unordered_set>
// #include <streambuf>
#include <sstream>
#include <algorithm>
#include <iomanip>
// #include <pair>


#include "romp_def.hpp"

using namespace murphi;
using namespace romp;


std::string int_to_hex(unsigned long i ) {
  // std::stringstream stream;
  // stream << "0x" 
  //       //  << std::setfill ('0') << std::setw(sizeof(T)*2) 
  //        << std::hex << i;
  // return stream.str();
  return std::to_string(i);
}

namespace romp {

class CGenerator : public ModelGenerator {

private:
  static const std::unordered_set<std::string> RESERVED_VAR_NAMES; //{ROMP_RESERVED_NAMES};
  // std::vector<std::string> state_vars;
  // std::vector<murphi::Ptr<murphi::SimpleRule>> rules;
  // std::vector<murphi::Ptr<murphi::PropertyRule>> property_rules;
  // std::vector<murphi::Ptr<murphi::StartState>> startstates;
  // std::stringstream prop_info_list;
  // std::stringstream error_info_list;

public:
  CGenerator(const std::vector<murphi::Comment> &comments_, std::ostream &out_,
             bool pack_)
      : ModelGenerator(comments_, out_, pack_) 
  { 
    // error_info_list << ROMP_INFO_ERRORS_DECL " = {";
  }

  // << ------------------------------------------------------------------------------------------ >> 

  // << ------------------------------------------------------------------------------------------ >> 

  

  // << ------------------------------------------------------------------------------------------ >> 

  

  // << ------------------------------------------------------------------------------------------ >> 

  void visit_vardecl(const VarDecl &n) final {
    if (CGenerator::RESERVED_VAR_NAMES.find(n.name) != CGenerator::RESERVED_VAR_NAMES.end())
      throw Error("``"+n.name+"`` is a reserved name!",n.loc);
    *this << indentation() << *n.type << " " << n.name << ";";
    emit_trailing_comments(n);
    *this << "\n";
  }


  void gen_state_to_json(std::vector<Ptr<VarDecl>> &children) {    
    *this << "\n" << "#ifdef " ROMP_SIMPLE_TRACE_PREPROCESSOR_VAR "\n"
                  << indentation() 
                  << "template<class O> " ROMP_JSON_STREAM_TYPE "& operator << (" ROMP_JSON_STREAM_TYPE "& json, const " ROMP_STATE_TYPE "& s) { "
                       "json << '[' << ::" ROMP_MODEL_NAMESPACE_NAME "::" ROMP_MAKE_JSON_CONVERTER_CALL(ROMP_STATE_CLASS_NAME,"s") " << ']'; return json; }\n"
                  << "#else\n"
                  << indentation() 
                  << "template<class O> " ROMP_JSON_STREAM_TYPE "& operator << (" ROMP_JSON_STREAM_TYPE "& json, const " ROMP_STATE_TYPE "& s) { "
                       "(void) ::" ROMP_MODEL_NAMESPACE_NAME "::" ROMP_MAKE_JSON_CONVERTER_CALL(ROMP_STATE_CLASS_NAME,"s") "; return json; }\n"
                      //  "(void) ::" ROMP_TYPE_NAMESPACE "::" ROMP_MAKE_JSON_CONVERTER_CALL(ROMP_STATE_CLASS_NAME,"s") "; return json; }\n"
                  << "#endif\n"
                  << indentation() 
                  << ROMP_OUT_STREAM_TYPE "& operator << (" ROMP_OUT_STREAM_TYPE "& out, const " ROMP_STATE_TYPE "& s) { "
                       "(void) ::" ROMP_MODEL_NAMESPACE_NAME "::" ROMP_MAKE_STREAM_CONVERTER_CALL(ROMP_STATE_CLASS_NAME,"s") "; return out; }\n"
                      //  "(void) ::" ROMP_TYPE_NAMESPACE "::" ROMP_MAKE_JSON_CONVERTER_CALL(ROMP_STATE_CLASS_NAME,"s") "; return json; }\n"
                  << indentation()
                  << "::std::ostream& operator << (::std::ostream& out_, const " ROMP_STATE_TYPE "& s) { "
                       ROMP_OUT_STREAM_TYPE " out(out_,2); "
                       "(void) ::" ROMP_MODEL_NAMESPACE_NAME "::" ROMP_MAKE_STREAM_CONVERTER_CALL(ROMP_STATE_CLASS_NAME,"s") "; return out_; }\n";
                      //  "(void) ::" ROMP_TYPE_NAMESPACE "::" ROMP_MAKE_STREAM_CONVERTER_CALL(ROMP_STATE_CLASS_NAME,"s") "; return out_; }\n";
    // *this << "\n" << indentation() << "NLOHMANN_DEFINE_TYPE_INTRUSIVE("
    //       ROMP_STATE_CLASS_NAME;
    // for (const Ptr<const VarDecl> &c : children) 
    //   if (auto v = dynamic_cast<const VarDecl *>(c.get()))
    //     *this << "," << v->name;
    // *this << ")\n";
  }

  void gen_ruleset_array(const std::vector<murphi::Ptr<murphi::SimpleRule>>& rules) {
    std::stringstream ruleset_array;
    ruleset_array << indentation() << ROMP_CALLER_RULESETS_DECL " = {";
    std::string rs_sep = "\n\t\t";
    id_t info_id = 0u;
    // for (const Ptr<SimpleRule>& _rule : rules) {
    for (size_t i=0; i<rules.size(); ++i) {
      // const SimpleRule& rule = *_rule;
      const SimpleRule& rule = *rules[i];
      ruleset_array << rs_sep << ROMP_MAKE_RULESET_STRUCT_HEADER(info_id);
      // size_t rule_c = 0;
      *this << indentation() << "/* --- Rules Generated by: `" << rule.name << "` (RuleSet expansions) --- */\n";
      SigPerm sigs(rule);
      rule_count += sigs.size();
      std::stringstream _sig_str;
      std::string r_sep = "";
      for (const Sig& sig : sigs) {
        _sig_str << sig;
        // std::string sig_str(_sig_str.str()); sig_str += " ";
        std::string _guard = ROMP_RULE_GUARD_PREFIX + rule.name + "__" + std::to_string(sig.index);  // int_to_hex(sig.index);
        std::string _action = ROMP_RULE_ACTION_PREFIX + rule.name + "__" + std::to_string(sig.index); // int_to_hex(sig.index);
        ruleset_array << r_sep << ROMP_MAKE_RULE_STRUCT(_guard,_action,info_id,sig.to_json(),sig.to_string());
        *this << indentation()
              << CodeGenerator::M_RULE_GUARD__FUNC_ATTRS
              << " bool "
              << _guard
              << "(const State_t& s)" /* " throw (" ROMP_MODEL_EXCEPTION_TYPE ")" */ "{"
              "return s." ROMP_RULE_GUARD_PREFIX << sig/* _str */ << "; }\n"
              << indentation()
              << CodeGenerator::M_RULE_ACTION__FUNC_ATTRS
              << " void "
              << _action
              << "(State_t& s)"  /* " throw (" ROMP_MODEL_EXCEPTION_TYPE ")" */  "{"
              "s." ROMP_RULE_ACTION_PREFIX << sig/* _str */ << "; }\n";
        // rule_c++;
        // rule_count++;
        r_sep = ", ";
      }
      ruleset_array << indentation() << "\t" ROMP_MAKE_RULESET_STRUCT_FOOTER();
      rs_sep = ",\n\t\t";
      ++info_id;
      this->out << std::flush;
    }
    // *this << "\n#undef " ROMP_RULESETS_LEN "\n"; 
    // *this << "\n#define " ROMP_RULESETS_LEN " " << rules.size() << "\n"; 
    *this <<"\n/* the number of rules in the model, AFTER ruleset expansion */\n"
             "#define " ROMP_RULES_LEN " (" << rule_count << "ul)\n";
    *this << "\n\n" << indentation() << "// All of the rule sets in one place\n" 
          << ruleset_array.str() << "};\n\n";
    this->out << std::flush;
  }


  void gen_property_array(const std::vector<murphi::Ptr<murphi::PropertyRule>>& property_rules) {
    std::stringstream prop_list;
    prop_list << ROMP_CALLER_PROPERTIES_DECL " = {\n";
    id_t _lid = 0u;
    // size_t count = 0u;
    size_t count_invar = 0u;
    size_t count_assume = 0u;
    size_t count_cover = 0u;
    size_t count_liveness = 0u;
    // std::string sep = "";
    // for (const Ptr<const PropertyRule>& _prop : property_rules) {
    for (size_t i=0; i<property_rules.size(); ++i) {
      // const PropertyRule& prop = *_prop;
      const PropertyRule& prop = *property_rules[i];
      *this << indentation() << "/* --- Property Rule(s) generated by: `" << prop.name << "` (RuleSet expansions) --- */\n";
      SigPerm sigs(prop);
      for (auto& sig : sigs) {
        std::string _check = ROMP_PROPERTYRULE_PREFIX + prop.name + "__" + std::to_string(sig.index);  // int_to_hex(sig.index);
        out << indentation() 
            << CodeGenerator::M_PROPERTY__FUNC_ATTRS
            // << " void "
            << " bool "
            << _check
            << "(const State_t& s)"  /* " throw (" ROMP_MODEL_EXCEPTION_TYPE ")" */  " {"
               "return s." ROMP_PROPERTYRULE_PREFIX << sig << "; }\n";
        switch (prop.property.category) {
        case Property::ASSERTION:
          prop_list << "\t\t" << ROMP_MAKE_PROPERTY_STRUCT(_check,_lid,sig.to_json(),sig.to_string()) << ",\n";
          ++count_invar;
          break;
        case Property::ASSUMPTION:
          prop_list << "#ifdef " ROMP_ASSUME_PREPROCESSOR_VAR "\n\t\t"
                    << ROMP_MAKE_PROPERTY_STRUCT(_check,_lid,sig.to_json(),sig.to_string()) << ",\n"
                       "#endif\n";
          ++count_assume;
          break;
        case Property::COVER:
          prop_list << "#ifdef " ROMP_COVER_PREPROCESSOR_VAR "\n\t\t"
                    << ROMP_MAKE_PROPERTY_STRUCT(_check,_lid,sig.to_json(),sig.to_string()) << ",\n"
                       "#endif\n";
          ++count_cover;
          break;
        case Property::LIVENESS:
          prop_list << "#ifdef " ROMP_COVER_PREPROCESSOR_VAR "\n\t\t"
                    << ROMP_MAKE_PROPERTY_STRUCT(_check,_lid,sig.to_json(),sig.to_string()) << ",\n"
                       "#endif\n";
          ++count_liveness;
          break;
        }
         
        // sep = ",";
        // ++count;
      }
      ++_lid;
      this->out << std::flush;
    }
    // *this << "\n\n#define " ROMP_PROPERTY_RULES_LEN " (" << count <<  "ul) // the number of property rules (after ruleset expansion) in the model\n"; 
    *this << "\n#ifdef " ROMP_ASSUME_PREPROCESSOR_VAR "\n"
             "#define ___propRule_assume_count___ (" << count_assume << "ul)\n"
             "#else\n"
             "#define ___propRule_assume_count___ (0ul)\n"
             "#endif\n"
             "#ifdef " ROMP_COVER_PREPROCESSOR_VAR "\n"
             "#define ___propRule_cover_count___ (" << count_cover << "ul)\n"
             "#else\n"
             "#define ___propRule_cover_count___ (0ul)\n"
             "#endif\n"
             "#ifdef " ROMP_LIVENESS_PREPROCESSOR_VAR "\n"
             "#define ___propRule_liveness_count___ (" << count_liveness << "ul)\n"
             "#else\n"
             "#define ___propRule_liveness_count___ (0ul)\n"
             "#endif\n";
    *this << "\n/* the number of property rules (after ruleset expansion) in the model */\n"
             "#define " ROMP_PROPERTY_RULES_LEN " ((" << count_invar << "ul) + ___propRule_assume_count___ + ___propRule_cover_count___ + ___propRule_liveness_count___)\n"; 
    *this << "\n" << indentation() << "/* All of the property rules expanded in one place */\n" 
          << prop_list.str() << "};\n\n";
    this->out << std::flush;
  }


  void gen_startstate_array(const std::vector<murphi::Ptr<murphi::StartState>>& startstates) {
    std::stringstream prop_list;
    prop_list << ROMP_CALLER_STARTSTATES_DECL " = {";
    id_t info_id = 0u;
    size_t count = 0u;
    std::string sep = "";
    // for (const Ptr<const StartState>& _startstate : startstates) {
    for (size_t i=0; i<startstates.size(); ++i) {
      // const StartState& startstate = *_startstate;
      const StartState& startstate = *startstates[i];
      *this << indentation() << "/* --- StartState Rule(s) generated by: `" << startstate.name << "` (RuleSet expansions) --- */\n";
      SigPerm sigs(startstate);
      for (auto& sig : sigs) {
        std::string _init = ROMP_STARTSTATE_PREFIX + startstate.name + "__" + std::to_string(sig.index);  // int_to_hex(sig.index);
        out << indentation() 
            << CodeGenerator::M_STARTSTATE__FUNC_ATTRS
            << " void "
            << _init
            << "(State_t& s)"  /* " throw (" ROMP_MODEL_EXCEPTION_TYPE ")" */  "{ "
               "s." ROMP_STARTSTATE_PREFIX << sig << "; }\n";
        prop_list << sep << ROMP_MAKE_STARTSTATE_STRUCT(_init,count,info_id,sig.to_json(),sig.to_string());
        sep = ", ";
        ++count;
      }
      ++info_id;
      this->out << std::flush;
    }
    *this << "\n\n#define " ROMP_STARTSTATE_RULES_LEN " (" << count <<  "ul) // the number of property rules (after ruleset expansion) in the model\n"; 
    *this << "\n" << indentation() << "// All of the rule sets in one place\n" 
          << prop_list.str() << "};\n\n";
    this->out << std::flush;
  }


  void visit_model(const Model &n) {
    ModelSplitter sorter;
    sorter.sort_model(n.children);
    if (sorter.startstate_decls.size() < 1) 
      throw Error("Model must contain at least one startstate rule!!",n.loc);
    next_property_id = sorter.next_property_id;
    next_cover_id = sorter.next_cover_id;
    next_liveness_id = sorter.next_liveness_id;
    next_assert_id = sorter.next_invar_id;
    next_assume_id = sorter.next_assume_id;
    // prop_info_list = sorter.prop_info_list; // not possible just output this before the one made here
    // SplitModel split = splitter.split_model(n);

    *this << "\n" << indentation() << "/* ======= Header Comments ====== */\n";
    emit_leading_comments(n);
    *this << "\n\n" << indentation() << "/* ======= Model Type & Const Definitions ====== */\n";
    *this << "\n" << indentation() << "namespace " ROMP_TYPE_NAMESPACE " {\n";
    indent();

    CTypeGenerator type_gen(comments, emitted, out, pack, 
      [&](const ConstDecl &_n) -> void {visit_constdecl(_n);});
    for (const Ptr<const Decl> &decl : sorter.global_decls)
      type_gen << *decl;

    emitted = type_gen.emitted;

    dedent();
    *this << "\n" << indentation() << "}\n\n"; // << std::flush;

    // update these to reflect the processes from the type emitter
    enum_typedefs = type_gen.enum_typedefs;
    emitted_tDecls = type_gen.emitted_tDecls;
    is_pointer = type_gen.is_pointer;
    // emitted = type_gen.emitted;

    *this << "\n\n" << indentation() << "/* ======= Generated Model & State ====== */\n";
    *this << "\n" << indentation() << "namespace " ROMP_MODEL_NAMESPACE_NAME " {\n";
    indent();

    *this << "\n" << indentation() << "struct " ROMP_STATE_CLASS_NAME " {\n";
    indent();
    *this << indentation() << ROMP_RAND_WALKER_DECL "\n\n";
    *this << "\n" << indentation() << "/* ======= Model State Variables ====== */\n\n";
    // split.state_var_decl.visit(*this);
    for (const Ptr<const VarDecl> &var : sorter.state_var_decls)
      *this << *var << "\n"; 
    // gen_state_to_json(sorter.state_var_decls); // moved outside ot state struct

    *this << "\n" << indentation() << "/* ======= Murphi Model Functions ====== */\n\n"; // << std::flush;
    // split.funct_decls.visit(*this);
    for (const Ptr<const Function> &funct : sorter.funct_decls)
      *this << *funct << "\n";

    *this << "\n" << indentation() << "/* ======= Murphi Model StartStates, Rules & Global Properties ====== */\n\n"; // << std::flush;
    // split.rule_decls.visit(*this);
    // for (const Ptr<const Rule> &_r : sorter.rule_decls) {
    //   std::vector<Ptr<Rule>> rs = _r->flatten();
    //   for (auto &r2 : rs) {
    //     if (_r->quantifiers.size() < r2->quantifiers.size())
    //       throw Error("rule did not flatten properly\t[dev-error]",_r->loc);
    //     for (int i=0; i<_r->quantifiers.size(); ++i) // bad lazy patch that will not work for nested rulesets!!
    //       r2->quantifiers[i] = _r->quantifiers[i]; // reason: flattening is loosing pointers to quantifier members 
    //     *this << *r2 << "\n";
    //   }
    // }
    for (const auto& _s : sorter.startstate_decls)
      *this << *_s << "\n";
    *this << "\n";
    for (const auto& _r : sorter.rule_decls)
      *this << *_r << "\n";
    *this << "\n";
    for (const auto& _p : sorter.property_decls)
      *this << *_p << "\n";
  
    dedent();
    *this << "\n" << indentation() << "};\n"; // << std::flush;
    // dedent();
    // *this << indentation() << "}\n\n";

    *this << "\n" << indentation() << "/* ======= Murphi Model Output Functions ====== */\n";
    // *this << indentation() << "namespace " ROMP_TYPE_NAMESPACE " {\n";
    // indent();
    auto state = Record(sorter.state_var_decls,n.loc);
    // ModelSplitter::pretty_type_reprs[state.unique_id] = ROMP_STATE_CLASS_NAME;
    ModelSplitter::model_unique_id = state.unique_id;
    // type_gen.indent();
    type_gen.emit_stream_operators__record(ROMP_STATE_CLASS_NAME, state);
    // type_gen.dedent();
    dedent();
    *this << indentation() << "}\n"
          << indentation() << "namespace " ROMP_UTIL_NAMESPACE_NAME " {";
    indent();
    gen_state_to_json(sorter.state_var_decls);
    dedent();
    *this << indentation() << "}\n\n";

    
    *this << "\n\n" << indentation() << "/* ======= Murphi Model Infos & MetaData ====== */\n"; // << std::flush;
    *this << indentation() << "namespace " ROMP_INFO_NAMESPACE_NAME " {\n\n";
    indent();
    *this << "/* the number possible variations in the state (# of permutations of the state-space) */\n"
             "#define " ROMP_STATESPACE_LEN " \"" << statespace_count(state).get_str() << "\"\n"
          << "/* the number of functions & procedures in the model */\n"
             "#define " ROMP_FUNCTS_LEN " (" << sorter.funct_decls.size() << "ul)\n"
          << indentation() << "/* the info/metadata about the functions/procedures in the model */\n"
          << indentation() << sorter.funct_info_list.str() << "};\n"
          << "/* the number of error statements in the model */\n"
             "#define " ROMP_ERRORS_LEN " (" << next_error_id << "ul)\n"
          << indentation() << "/* the info/metadata about the murphi error statements in the model */\n"
          << indentation() << error_info_list.str() << "};\n"
          << "/* the number of property statements & rules in the model */\n"
             "#define " ROMP_PROPERTY_INFOS_LEN " (" << next_property_id <<  "ul)\n"
          // << "#define " ROMP_PROPERTY_RULES_LEN " (" << property_rules.size() <<  "ul) // the number of property rules (after ruleset expansion) in the model\n"
          << "/* the number of cover property statements & rules in the model */\n"
          << "#define " ROMP_COVER_PROP_COUNT " (" << next_cover_id <<  "ul) // the number of property rules (after ruleset expansion) in the model\n"
          << "/* the number of liveness property rules in the model */\n"
          << "#define " ROMP_LIVENESS_PROP_COUNT " (" << next_liveness_id <<  "ul) // the number of property rules (after ruleset expansion) in the model\n"
          << indentation() << "/* the info/metadata about the murphi properties in the model */\n"
          << indentation() << sorter.prop_info_list.str() << prop_info_list.str() << "};\n"
          << "/* the number of start state rules (before ruleset expansions) in the model */\n"
             "#define " ROMP_STARTSTATE_INFOS_LEN " (" << sorter.startstate_decls.size() <<  "ul)\n"
          // << "#define " ROMP_STARTSTATE_RULES_LEN " (" << startstates.size() <<  "ul) // the number of start state rules (after ruleset expansions) in the model\n"
          << indentation() << "/* the info/metadata about the startstate rules in the model */\n"
          << indentation() << sorter.startstate_info_list.str() << "};\n"
          << "/* the number of rules in the model, BEFORE ruleset expansion */\n"
             "#define " ROMP_RULESETS_LEN " (" << sorter.rule_decls.size() << "ul)\n"
          // << "/* the number of rules in the model, AFTER ruleset expansion */\n"
          //    "#define " ROMP_RULES_LEN " (" << rule_count << "ul)\n"
          << indentation() << "/* the info/metadata about the rules in the model */\n"
          << indentation() << sorter.rule_info_list.str() << "};\n";
    dedent();
    *this << "\n" << indentation() << "}\n\n"; out << std::flush;

    *this << indentation() << "/* ======= Romp CALLER Lists ====== */\n";
    *this << indentation() << "namespace " ROMP_CALLER_NAMESPACE_NAME " {\n";
    indent();

    *this << indentation() << "typedef " ROMP_STATE_TYPE " State_t; // type mask for the generated state object\n";

    gen_ruleset_array(sorter.rule_decls);
    gen_property_array(sorter.property_decls);
    gen_startstate_array(sorter.startstate_decls);

    dedent();
    *this << "\n" << indentation() << "}\n\n"; // << std::flush;
    out << std::flush;
  }

  virtual ~CGenerator() = default;

  // CGenerator& operator << (std::ostream& os) {
  //   out << os;
  //   return *this;
  // }

  std::string to_json(const ErrorStmt& rule) {
    std::stringstream buf;
    buf << "{\"$type\":\"error-statement\",";
    buf << "\"label\":\"" << nEscape(rule.message) << "\","
            "\"loc\":{\"$type\":\"location\","
                      "\"file\":\"" << nEscape(CodeGenerator::input_file_path.string()) <<  "\","
    //                   "\"inside\":\"";
    // // TODO ...
    // buf <<            "\","
                      "\"start\":["<< rule.loc.begin.line << "," << rule.loc.begin.column << "],"  
                      "\"end\":["<< rule.loc.end.line << "," << rule.loc.end.column << "]}";
    return buf.str();
  }

  std::string to_json(const PropertyStmt& prop, const std::string prop_type) {
    std::stringstream buf;
    buf << "{\"$type\":\"property\","
        << "\"type\":\"" << prop_type << "\","
        << "\"label\":\"" << nEscape(prop.message == "" ? prop.property.expr->to_string() : prop.message) << "\","
        << "\"expr\":\"" << nEscape(prop.property.expr->to_string()) << "\","
            "\"loc\":{\"$type\":\"location\","
                      "\"file\":\"" << nEscape(CodeGenerator::input_file_path.string()) << "\","
    //                   "\"inside\":\"";
    // // TODO ...
    // buf <<            "\","
                      "\"start\":["<< prop.loc.begin.line << "," << prop.loc.begin.column << "],"  
                      "\"end\":["<< prop.loc.end.line << "," << prop.loc.end.column << "]}";
    return buf.str();
  }
public:
  CGenerator& operator << (const char*& str) { out << str; return *this; }
  CGenerator& operator << (const std::string& str) { out << str; return *this; }
  // CGenerator& operator << (const char* str) { out << str; return *this; }
  CGenerator& operator << (const int val) { out << val; return *this; }
  CGenerator& operator << (const unsigned int val) { out << val; return *this; }
  CGenerator& operator << (const long val) { out << val; return *this; }
  CGenerator& operator << (const unsigned long val) { out << val; return *this; }
  CGenerator& operator << (const murphi::Node& n) { dispatch(n); return *this; }
  CGenerator& operator << (const Sig& sig) { out << sig; return *this; }
  friend CGenerator& operator << (CGenerator& gen, const SigParam& param) { gen.out << param; return gen; }
  // CGenerator& operator << (const SigParam& param) { out << param; return *this; }
};

const std::unordered_set<std::string> CGenerator::RESERVED_VAR_NAMES{ROMP_RESERVED_NAMES};


std::ostream& operator << (std::ostream& out, const Sig& sig) {
  out << sig.perm.rule.name << "(";
  std::string sep;
  for (size_t i=0; i<sig.size(); ++i) 
    if (sig.params[i] != nullptr) {
      out << sep << *sig.params[i];
      sep = ", ";
    }
  return (out << ")");
}

std::ostream& operator << (std::ostream& out, const SigParam& param) { return (out << param.to_string()); }



} // namespace

void output_embedded_code_file(std::ostream& out, const unsigned char* ecf, const size_t ecf_l) {
  for (size_t i = 0; i < ecf_l; i++)
    out << (char) ecf[i];
}



void generate(const Node &n, const std::vector<Comment> &comments,
                romp::CodeGenerator &out, const std::string& build_cmds) {
  
  out << ROMP_GENERATED_FILE_PREFACE("\tGenerated code for a romp \"parallel random walker\" verification tool based off of the Murphi Model described in:\n"
                                     "\t\tOriginal Murphi Model: " + romp::CodeGenerator::input_file_path.filename().string() + "\n"
                                     "\tPlease build with the following command(s):\n\t\t" + build_cmds + "") "\n";

  out << "\n#define __romp__GENERATED_CODE\n\n";
  out << "\n#define _ROMP_STATE_TYPE " ROMP_STATE_TYPE "\n\n";
  out << "\n#define _ROMP_STATE_HISTORY_LEN (" << 4 << "ul)\n\n";  // TODO: make this adjustable
  out << "\n#define _ROMP_THREAD_TO_RW_RATIO (" << 8 << "ul)\n\n";  // TODO: make this adjustable
  std::string file_path = romp::CodeGenerator::input_file_path.string();
  out << "\n#define __model__filepath \"" << nEscape(file_path) << "\"\n\n";
  int _count = std::count(file_path.begin(), file_path.end(), ' ');
  out << "\n#define __model__filepath_contains_space (" 
      << ((_count > 0) ? "true" : "false") << ")\n\n";
  std::string file_name = romp::CodeGenerator::input_file_path.filename().string();
  out << "\n#define __model__filename \"" << nEscape(file_name) << "\"\n";
  _count = std::count(file_name.begin(), file_name.end(), ' ');
  out << "\n#define __model__filename_contains_space (" 
      << ((_count > 0) ? "true" : "false") << ")\n\n";

  out << "namespace " ROMP_UTIL_NAMESPACE_NAME " {\n"
         "  typedef " << value_type << " range_t;\n"
        //  "  typedef " << scalar_type << " scalar_t;\n"
         "} // namespace " ROMP_UTIL_NAMESPACE_NAME "\n\n";

  romp::CodeGenerator::print_preprocessor_options(out);


  // out << "\n#pragma region inline_library_includes\n\n";
  // write json library to the file
  // output_embedded_code_file(out, resources_lib_nlohmann_json_hpp, resources_lib_nlohmann_json_hpp_len);
  // out << "\n#pragma endregion inline_library_includes\n\n" << std::flush;

  out << "namespace " ROMP_MODEL_NAMESPACE_NAME " { struct " ROMP_STATE_CLASS_NAME "; } // helpful pre-definition\n\n";

  // write the static prefixes to the beginning of the source file
  out << "\n#pragma region romp_prefix\n\n";
# ifdef _ROMP_DEV_DEBUG_INCLUDE_DIR
    out << "#include \"" <<  _ROMP_DEV_DEBUG_INCLUDE_DIR << "/romp-rw/include.hpp\"\n";
    out << "#include \"" <<  _ROMP_DEV_DEBUG_INCLUDE_DIR << "/romp-rw/decl.hpp\"\n";
    out << "#include \"" <<  _ROMP_DEV_DEBUG_INCLUDE_DIR << "/romp-rw/writers.hpp\"\n";
# else
    output_embedded_code_file(out, resources_romp_rw_include_hpp, resources_romp_rw_include_hpp_len);
    output_embedded_code_file(out, resources_romp_rw_decl_hpp, resources_romp_rw_decl_hpp_len);
    output_embedded_code_file(out, resources_romp_rw_writers_hpp, resources_romp_rw_writers_hpp_len);
# endif
  out << "\n#pragma endregion romp_prefix\n\n" << std::flush;


  out << "\n\n#pragma region scalar_enums__generated_code\n"
      << out.indentation() << "namespace " ROMP_MODEL_NAMESPACE_NAME " {\n";
  out.indent()
  romp::ScalarEnumGenerator se_gen(comments, out, pack);
  se_gen.dispatch(n);
  out.dedent();
  out << "\n" << out.indentation() << "} // namespace " ROMP_MODEL_NAMESPACE_NAME "\n"
      << out.indentation() << "namespace " ROMP_UTIL_NAMESPACE_NAME " { typedef " ROMP_SCALAR_ENUM_TYPE " SCALAR_ENUM_t; }\n"
      << out.indentation() << "namespace " ROMP_INFO_NAMESPACE_NAME " { std::string SCALAR_IDS[] = { ";
  { std::string sep;
    for (auto name : se_gen._enum_ids) {
      out << sep << name;
      sep = ", ";
  } }
  out << " }; }\n"
      << "\n\n#pragma endregion scalar_enums__generated_code\n\n" << std::flush;

  // write the static infixes to the "middle" of the source file
  out << "\n#pragma region romp_infix\n\n";
# ifdef _ROMP_DEV_DEBUG_INCLUDE_DIR
    out << "#include \"" <<  _ROMP_DEV_DEBUG_INCLUDE_DIR << "/romp-rw/options.hpp\"\n";
    out << "#include \"" <<  _ROMP_DEV_DEBUG_INCLUDE_DIR << "/romp-rw/types.hpp\"\n";
    out << "#include \"" <<  _ROMP_DEV_DEBUG_INCLUDE_DIR << "/romp-rw/error.hpp\"\n";
# else
    output_embedded_code_file(out, resources_romp_rw_types_hpp, resources_romp_rw_options_hpp_len);
    output_embedded_code_file(out, resources_romp_rw_types_hpp, resources_romp_rw_types_hpp_len);
    output_embedded_code_file(out, resources_romp_rw_error_hpp, resources_romp_rw_error_hpp_len);
# endif
  out << "\n#pragma endregion romp_infix\n\n" << std::flush;

  out << "\n\n#pragma region model__generated_code\n\n";
  romp::ModelGenerator gen(out, se_gen.enum_ids, comments);
  gen.dispatch(n);
  out << "\n\n#pragma endregion model__generated_code\n\n" << std::flush;

  out << "\n\n#pragma region model__generated_code\n"
      << out.indentation() << "namespace " ROMP_MODEL_NAMESPACE_NAME " {\n\n";
  out.indent()
  romp::ModelGenerator m_gen(out);
  m_gen.dispatch(n);
  out.dedent();
  out << "\n\n" << out.indentation() << "} // namespace " ROMP_MODEL_NAMESPACE_NAME "\n"
         "#pragma endregion metadata__generated_code\n\n" << std::flush;

  out << "\n\n#pragma region rule_caller__generated_code\n\n";
  romp::CGenerator gen(comments, out, pack);  //TODO update this to new metadata generator
  gen.dispatch(n);
  out << "\n\n#pragma endregion rule_caller__generated_code\n\n" << std::flush;

  // write the static postfixes to the end of the source file
  out << "\n#pragma region romp_postfix\n\n";
# ifdef _ROMP_DEV_DEBUG_INCLUDE_DIR
    out << "#include \"" <<  _ROMP_DEV_DEBUG_INCLUDE_DIR << "/romp-rw/impls.hpp\"\n";
    out << "#include \"" <<  _ROMP_DEV_DEBUG_INCLUDE_DIR << "/romp-rw/walker.hpp\"\n";
# else
    output_embedded_code_file(out, resources_romp_rw_impls_hpp, resources_romp_rw_impls_hpp_len);
    output_embedded_code_file(out, resources_romp_rw_walker_hpp, resources_romp_rw_walker_hpp_len);
# endif
  out << "\n#pragma endregion romp_postfix\n\n" << std::flush;

  // write the static postfixes to the end of the source file
  out << "\n#pragma region romp_main\n\n";
# ifdef _ROMP_DEV_DEBUG_INCLUDE_DIR
    out << "#include \"" <<  _ROMP_DEV_DEBUG_INCLUDE_DIR << "/romp-rw/main.hpp\"\n";
# else
    output_embedded_code_file(out, resources_romp_rw_main_hpp, resources_romp_rw_main_hpp_len);
# endif
  out << "\n#pragma endregion romp_main\n\n" 
         "/* << === EOF === >> */\n"<< std::flush;


  // out << buffer.rdbuf() << "\n\n";
  // out << std::flush;
}
