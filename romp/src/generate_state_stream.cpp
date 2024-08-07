/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file generate_state_stream.cpp
 *
 * @brief generate the stream operators used to output the state to json files or the console
 *
 * @date 2022/10/19
 * @version 0.3
 */

#include "generate_state_stream.hpp"
#include "romp_def.hpp"
#include "nested_escape.hpp"
#include <murphi/murphi.h>
#include <sstream>
#include <cassert>


namespace romp {
  using namespace murphi;

void generate_state_stream(romp::CodeGenerator& gen, const murphi::Model& m) {
  std::stringstream json;
  std::stringstream json_simp;
  std::string j_sep, p_sep;
  gen << gen.indentation() << "friend " ROMP_OUT_STREAM_TYPE "& operator << (" ROMP_OUT_STREAM_TYPE "& out, const " ROMP_STATE_TYPE "& s) {\n";
  gen.indent();
  gen << gen.indentation() << " return (out << '{' << out._indent() << out.nl()";
  gen.indent(); gen.indent();
  for (const auto& c : m.children) {
    if (const auto _vd = dynamic_cast<const VarDecl*>(c.get())) {
      json_simp << j_sep << " << s." << _vd->name;
      json << j_sep << " << \"{\\\"$type\\\":\\\"kv-pair\\\",\\\"key\\\":\\\"" << _vd->name <<  "\\\",\\\"value\\\":\" << s." << _vd->name << " << '}'";
      gen << p_sep << '\n' << gen.indentation() << " << \"" << _vd->name << "\" "
                                                "<< ((((not s." << _vd->name <<".__IS_RECORD())||(s."<< _vd->name <<".__IS_TYPEID()))&&" ROMP_SHOW_TYPE_OPTION_EXPR ") "
                                                    "? \": \" + s." << _vd->name << ".__p_type() + \" = \" : \" := \") "
                                                "<< s." << _vd->name << " << ';'";
      j_sep = " << ','";
      p_sep = " << out.nl()";
    }
  }
  gen << '\n' << gen.indentation() << "<< out.dedent() << out.nl() << '}');";
  gen.dedent(); gen.dedent(); gen.dedent();
  gen << gen.indentation() << "}\n"
      << gen.indentation() << "friend ::std::ostream& operator << (::std::ostream& out_, const " ROMP_STATE_TYPE "& s) { "
                                ROMP_OUT_STREAM_TYPE " out(out_," ROMP_UTIL_NAMESPACE "::Options(),2); "
                                "out << s; "
                                "return out_; }\n";
  gen << "\n" << "#ifdef " ROMP_SIMPLE_TRACE_PREPROCESSOR_VAR "\n"
              << gen.indentation()
              << "template<class O> friend " ROMP_JSON_STREAM_TYPE "& operator << (" ROMP_JSON_STREAM_TYPE "& json, const " ROMP_STATE_TYPE "& s) { "
                    "return (json << '[' " << json_simp.str() << " << ']'); }\n"
              << "#else\n"
              << gen.indentation()
              << "template<class O> friend " ROMP_JSON_STREAM_TYPE "& operator << (" ROMP_JSON_STREAM_TYPE "& json, const " ROMP_STATE_TYPE "& s) { "
                    "return (json << \"{\\\"$type\\\":\\\"model-state\\\",\\\"value\\\":[\"" << json.str() << " << \"]}\"); }\n"
              << "#endif\n";
}


void generate_state_hash(romp::CodeGenerator& gen, const murphi::Model& m) {
  std::stringstream eq;
  gen << gen.indentation() << "inline size_t " ROMP_MODEL_HASH_METHOD_NAME "() const {\n";
  gen.indent();
  gen << gen.indentation() << "size_t _hash = 0ul;\n";
  std::string eq_sep;
  for (const auto& c : m.children) {
    if (const auto _vd = dynamic_cast<const VarDecl*>(c.get())) {
      gen << gen.indentation() << ROMP_MAKE_HASH_COMBINER("_hash",_vd->name) << ";\n";
      eq << eq_sep << gen.indentation() << "l." << _vd->name << " == " << "r." << _vd->name;
      eq_sep = " && \n";
    }
  }
  gen << gen.indentation() << "return _hash;\n";
  gen.dedent();
  gen << gen.indentation() << "}\n\n"
      << gen.indentation() << "friend inline bool operator == (const " ROMP_STATE_TYPE "& l, const " ROMP_STATE_TYPE "& r) {\n";
  gen.indent();
  gen << gen.indentation() << "return (" << eq.str() << ");\n";
  gen.dedent();
  gen << gen.indentation() << "}\n\n";
}


} // namespace romp
