/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file CTypeGenerator.cpp
 * 
 * @brief An AST traversing structure that can only handle generating Types.
 * 
 * @date 2022/06/10
 * @version 0.1
 */


#include "CTypeGenerator.hpp"
#include "type_traverse.hpp"
#include "options.h"
#include "romp_def.hpp"
#include "nested_escape.hpp"
#include "ModelSplitter.hpp"
// #include "../../common/escape.h"
#include <rumur/rumur.h>
#include <sstream>

using namespace rumur;

namespace romp {


void CTypeGenerator::visit_typedecl(const TypeDecl &n) {
  if (reserved_type_names.find(n.name) != reserved_type_names.end())
    throw Error("Tried to define a type with a reserved/built-in type name!!", n.loc);
  if (emitted_tDecls.find(n.name) != emitted_tDecls.end())
    throw Error("Tried to redefine an already defined type!", n.loc);

  // *this << "\n" << indentation() << "namespace " ROMP_TYPE_NAMESPACE " {\n";
  indent();


  // If we are type-def-ing something that is an enum, save this for later lookup.
  // See CGenerator/HGenerator::visit_constdecl for the purpose of this.
  if (auto e = dynamic_cast<const Enum *>(n.value.get()))
    enum_typedefs[e->unique_id] = n.name;

  *this << indentation() << "typedef " << *n.value << " " << n.name << ";";
  emit_trailing_comments(n);
  *this << "\n";
  
  // dedent();
  // *this << "\n" << indentation() << "}\n\n";

  emitted_tDecls.insert(n.name);
  emit_stream_operators(n.name, n.value);
  *this << "\n";
  dedent();

}

// void CTypeGenerator::visit_indtype(const IndType &n) {
//   *this << n.eval_size_str;
// }


void CTypeGenerator::visit_array(const Array &n) {

  // check_type_ref(n, n.element_type);
  // check_type_ref(n, n.index_type);


  mpz_class count = n.index_type->count();

  assert(count > 0 && "index type of array does not include undefined");
  count--;

  // wrap the array in a struct so that we do not have the awkwardness of
  // having to emit its type and size on either size of another node
  *this << "struct " <<  (pack ? "__attribute__((packed)) " : "") << "{ "
        << *n.element_type 
        // << " data[" << *(n.index_type) << "];";
        << " data[" << count.get_str() << "]; "
        << "constexpr const size_t size() const {return (" << count.get_str() <<  "ul);}";

  // // The index for this array may be an enum declared inline:
  // //
  // //   array [enum {A, B}] of foo
  // //
  // // If so, we need to emit it somehow so that the enum’s members can be
  // // referenced later. We define it within this struct to avoid any awkward
  // // lexical issues.
  // if (auto e = dynamic_cast<const Enum *>(n.index_type.get())) {
  //   *this << " " << *e << ";";
  // }
  *this << " }";

}

void CTypeGenerator::emit_stream_operators__array(const std::string &name, const Array &te) { 
  std::string type_str = nEscape(ModelSplitter::get_pretty_rep(te));
  std::string el_type;
  if (auto _tid = dynamic_cast<const TypeExprID*>(te.element_type.get()))
    el_type = _tid->referent->name;
  else throw Error("Was not made anonymous before export \t[dev-error]", te.element_type->loc);

  *this << "#ifdef " ROMP_SIMPLE_TRACE_PREPROCESSOR_VAR "\n"
        << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " {"
        // << "json << \"[\"; " // double escape time
            "std::string sep; "
            "for (size_t i=(0ul); i<val.size(); ++i) { "
              "json << sep << " ROMP_MAKE_JSON_CONVERTER_CALL(el_type,"val.data[i]") "; "
              "sep = \",\"; } "
            // "json << ']'; "
            "return ::romp::S_VOID;"
            "}\n"
            "#else\n";

  if (auto _e = dynamic_cast<const Enum *>(te.index_type->resolve().get())) { 
    *this << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " { ";
    *this << "json << \"" // double escape time
                "{\\\"$type\\\":\\\"enum-array-value\\\","
                "\\\"type\\\":\\\"" << nEscape(type_str) << "\\\","
                // "\\\"element-type\\\":\\\"" << nEscape(et_str) << "\\\"
                // "\\\"index-type\\\":\\\"" << nEscape(it_str) <<"\\\","
                "\\\"size\\\":\" << val.size() << \","
                "\\\"elements\\\":[";
    std::string sep;
    for (int i=0; i<_e->members.size(); ++i) {
      *this << sep << "{\\\"$type\\\":\\\"kv-pair\\\",\\\"key\\\":\\\"" << nEscape(_e->members[i].first)
                   << "\\\"value\\\":\" << " ROMP_MAKE_JSON_CONVERTER_CALL(el_type,"val.data[" + std::to_string(i) + "]") " << \"}";
      sep = ",";
    }
    *this << "]}\"; "
             // "return json; "
             "return ::romp::S_VOID;"
             "}\n"
             "#endif\n";

    *this << indentation() << ROMP_MAKE_STREAM_CONVERTER_SIG(name) " { ";
    *this << "out << \"[\\n\" "
                  "<< out.indent() ";
    for (int i=0; i<_e->members.size(); ++i) {
      *this << "<< out.indentation() << \"[" << _e->members[i].first << "]: \" "
               "<< " ROMP_MAKE_STREAM_CONVERTER_CALL(el_type,"val.data[" + std::to_string(i) + "]") " << '\\n'";
    }
                    // "out ; } "
    *this << "out << out.dedent() << out.indentation() << ']'; "
            // "return out; "
            "return ::romp::S_VOID;"
              "}\n";

  } else { // range/scalarset based array indexes 
    *this << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " {";
    *this << "json << \"" // double escape time
                "{\\\"$type\\\":\\\"array-value\\\","
                "\\\"type\\\":\\\"" << nEscape(type_str) << "\\\","
                // "\\\"element-type\\\":\\\"" << nEscape(et_str) << "\\\","
                // "\\\"index-type\\\":\\\"" << nEscape(it_str) <<"\\\","
                "\\\"size\\\":\" << val.size() << \","
                "\\\"lower-bound\\\":\" << " << te.index_type->lower_bound() << " << \","
                "\\\"upper-bound\\\":\" << " << te.index_type->upper_bound() << " << \","
                "\\\"elements\\\":[\"; " // end double escape time
            "std::string sep; "
            "for (size_t i=(0ul); i<val.size(); ++i) { "
                    "json << sep << " ROMP_MAKE_JSON_CONVERTER_CALL(el_type,"val.data[i]") "; "
                    "sep = \",\"; } "
            "json << \"]}\"; "
            // "return json; "
            "return ::romp::S_VOID;"
            "}\n"
            "#endif\n";
    *this << indentation() << ROMP_MAKE_STREAM_CONVERTER_SIG(name) " { ";
    *this << "out << \"[\\n\" "
                  "<< out.indent(); "
                  "for (size_t i=0; i<val.size(); ++i) { "
                    "out << out.indentation() << \"[\" << (i + (" << te.index_type->lower_bound() << ")) << \"]: \""
                        "<< " ROMP_MAKE_STREAM_CONVERTER_CALL(el_type,"val.data[i]") " << '\\n'; } ";
    *this << "out << out.dedent() << out.indentation() << ']'; "
            // "return out; "
            "return ::romp::S_VOID;"
              "}\n";
  }
  // *this << indentation() << "void to_json(" ROMP_JSON_TYPE "& j, const " << name << "& data) { "
  //          "if (" << ROMP_SHOW_TYPE_OPTION_EXPR << ") {" 
  //             "j = " ROMP_JSON_TYPE "{{\"type\",\"" << name << te.to_string() << "\"},"
  //                           "{\"value\", std::vector<" << et_str << ">(std::begin(data), std::end(data))}};"
  //          "} else {to_json(j, std::vector<" << et_str << ">(std::begin(data), std::end(data))));} }\n";

  // init provider //TODO
  // *this << indentation() << "void init_"

}


void CTypeGenerator::visit_enum(const Enum &n) {
  *this << "enum { ";
  for (const std::pair<std::string, location> &m : n.members) {
    *this << m.first << ", ";
  }
  *this << "}";
}

void CTypeGenerator::emit_stream_operators__enum(const std::string &name, const Enum &te) {
  std::string type_str = nEscape(ModelSplitter::get_pretty_rep(te));
  *this << indentation() << "std::string to_string(const " << name << " val) { "
           "switch (val) { ";
  for (auto val : te.members)
    *this << "case " << val.first << ": return \"" << val.first << "\"; ";
  *this << "default: break; } return \"" << name << "::__UNKNOWN_ENUM_VALUE__\"; }\n";

  *this << "#ifdef " ROMP_SIMPLE_TRACE_PREPROCESSOR_VAR "\n"
        << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " { "
           "json << '\"' << to_string(val) << '\"'; "
           "return ::romp::S_VOID; }\n"
        << "#else\n";
  *this << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " { ";
  *this << "json << \"{\\\"$type\\\":\\\"enum-value\\\","
                      "\\\"type\\\":\\\"" << nEscape(type_str) << "\\\","
                      "\\\"value\\\":\\\"\" << to_string(val) <<\"\\\"}\"; "
           // "return json; "
           "return ::romp::S_VOID; "
           "}\n"
           "#endif\n";

  *this << indentation() << ROMP_MAKE_STREAM_CONVERTER_SIG(name) " { ";
  // *this << "out << \": " << type_str << " := \" << to_string(val); "
  *this << "out << to_string(val); "
           // "return out; "
           "return ::romp::S_VOID; "
           "}\n";

  // *this << ROMP_MAKE_JSON_CONVERTER_FOOTER "\n";
  // *this << indentation() << "NLOHMANN_JSON_SERIALIZE_ENUM( " << name << ", { ";
  // for (auto &m : te.members)
  //   *this << "{" << m.first << "," 
  //         "((" ROMP_SHOW_TYPE_OPTION_EXPR ") ? ("
  //         " \"" << name << "::" << m.first << "\" "
  //         ") : (\"" << m.first << "\")},";
  // *this << " })\n";
}


void CTypeGenerator::visit_range(const Range &) { *this << "range_t"; }


void CTypeGenerator::emit_stream_operators__range(const std::string &name, const Range &te) {
  std::string type_str = nEscape(ModelSplitter::get_pretty_rep(te));

  *this << "#ifdef " ROMP_SIMPLE_TRACE_PREPROCESSOR_VAR "\n"
        << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " { "
           "json << val; "
           "return ::romp::S_VOID; }\n"
        << "#else\n";

  *this << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " { ";
  *this << "json << \"{\\\"$type\\\":\\\"range-value\\\","
                      "\\\"type\\\":\\\"" << nEscape(type_str) << "\\\","
                      "\\\"min\\\":\" << (" << te.lower_bound() << ") << \","
                      "\\\"max\\\":\" << (" << te.upper_bound() << ") << \","
                      "\\\"value\\\":\" << ((range_t)val) << \"}\"; "
            // "return json; "
            "return ::romp::S_VOID;"
            "}\n"
            "#endif\n";

  *this << indentation() << ROMP_MAKE_STREAM_CONVERTER_SIG(name) " { ";
  // *this << "out << \": " << type_str << " := \" << ((range_t)val); "
  *this << "out << ((range_t)val); "
           // "return out; "
           "return ::romp::S_VOID;"
           "}\n";

  // *this << indentation() << "void to_json(" ROMP_JSON_TYPE "& j, const ::" ROMP_TYPE_NAMESPACE"::" << name << "& data) { "
  //       "if (" ROMP_SHOW_TYPE_OPTION_EXPR ") {" 
  //         "j = " ROMP_JSON_TYPE "{{\"type\",\"" << name << ": " << te.to_string() << "\"}, "
  //                         "{\"value\",(" << value_type << ")data}};"
  //       "} else {"
  //         "to_json(j,(" << value_type << ")data);} }\n";
}


void CTypeGenerator::visit_record(const Record &n) {
  *this << "struct " << (pack ? "__attribute__((packed)) " : "") << "{\n";
  indent();
  indent();
  for (const Ptr<VarDecl> &f : n.fields) {
    if (f==nullptr) continue; // (TMP FIX) not sure why vector's keep getting null Ptr values
    check_type_ref(*f, f->type);
    emit_leading_comments(*f);
    *this << indentation() << *(f->type) << " " << f->name << ";";
    emit_trailing_comments(*f);
    *this << "\n";
  }
  dedent();
  *this << indentation() << "}";
  dedent();
}


void CTypeGenerator::emit_stream_operators__record(const std::string &name, const Record &te) {
  std::string type_str = nEscape(ModelSplitter::get_pretty_rep(te));
  std::string m_type;
  std::string sep;

  *this << "#ifdef " ROMP_SIMPLE_TRACE_PREPROCESSOR_VAR "\n"
        << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " { using namespace ::" ROMP_TYPE_NAMESPACE "; "
           "json "; // "<< \"{\" ";
  sep = "";
  // sep = " << \"\\\"";
  for (const auto& m : te.fields) {
    if (m==nullptr) continue; // (TMP-FIX) Figure out why vector's keep init-ing w/ nullptr's 
    if (const auto _tid = dynamic_cast<const TypeExprID*>(m->type.get()))
      m_type = _tid->referent->name;
    else throw Error("type wan not anonymized durring intermediary processing \t[dev-error]",m->type->loc);
    *this << sep <<
            //  m->name << "\\\":\""
            " << " ROMP_MAKE_JSON_CONVERTER_CALL(m_type,"val." + m->name);
    sep = " << ','";
    // sep = " << \",\\\"";
  }
  *this << // " << '}'"
           "; "
           "return ::romp::S_VOID; }\n"
           "#else\n";

  *this << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " { using namespace ::" ROMP_TYPE_NAMESPACE "; ";
  *this << "json << \"{\\\"$type\\\":\\\"record-value\\\","
                      "\\\"type\\\":\\\"" << nEscape(type_str) << "\\\","
                      "\\\"fields\\\":[\" ";
  sep = "";
  for (const auto& m : te.fields) {
    if (m==nullptr) continue; // (TMP-FIX) Figure out why vector's keep init-ing w/ nullptr's 
    if (const auto _tid = dynamic_cast<const TypeExprID*>(m->type.get()))
      m_type = _tid->referent->name;
    else throw Error("type wan not anonymized durring intermediary processing \t[dev-error]",m->type->loc);
    *this << sep 
          << "<< \"{\\\"$type\\\":\\\"kv-pair\\\","
                    "\\\"key\\\":\\\"" << m->name << "\\\","
                    "\\\"value\\\":\" << " ROMP_MAKE_JSON_CONVERTER_CALL(m_type,"val." + m->name);
    sep = " << \"},\" ";
  }
  *this << "<< \"}]}\"; "
            // "return json; "
            "return ::romp::S_VOID;"
            "}\n"
            "#endif\n";

  *this << indentation() << ROMP_MAKE_STREAM_CONVERTER_SIG(name) " { using namespace ::" ROMP_TYPE_NAMESPACE "; ";
  *this << "out << \"{\\n\" "
            "<< out.indent() ";
  for (const auto& m : te.fields) {
    if (m==nullptr) continue; // (TMP-FIX) Figure out why vector's keep init-ing w/ nullptr's 
    if (const auto _tid = dynamic_cast<const TypeExprID*>(m->type.get()))
      m_type = _tid->referent->name;
    else throw Error("type wan not anonymized durring intermediary processing \t[dev-error]",m->type->loc);
    std::string field_type = nEscape(ModelSplitter::get_pretty_rep(*m->type));
    *this << "<< out.indentation() "
             "<< \"" << m->name << " \" << ((" ROMP_SHOW_TYPE_OPTION_EXPR ") ? \": " << field_type << " =\" : \":=\") << ' ' "
             "<< " ROMP_MAKE_STREAM_CONVERTER_CALL(m_type,"val." + m->name) << " << '\\n' ";
  }
  *this << "<< out.dedent()"
           "<< out.indentation() << '}'; "
           // "return out; "
           "return ::romp::S_VOID;"
           "}\n";

  // std::string conv_str = ROMP_JSON_TYPE "{";
  // for (const Ptr<VarDecl> &f : te.fields)
  //   conv_str += "{\"" + f->name + "\", data." + f->name + "},";
  // conv_str += "}";
  // *this << indentation() << "void to_json(" ROMP_JSON_TYPE "& j, const ::" ROMP_TYPE_NAMESPACE"::" << name << "& data) { "
  //       "j = (" ROMP_SHOW_TYPE_OPTION_EXPR ") ? (" 
  //           ROMP_JSON_TYPE "{{\"type\",\"" << name << ": " << te.to_string() << "\"},"
  //           "{\"value\"," << conv_str << "}}"
  //         ") : (" << conv_str << "); }\n";
}


void CTypeGenerator::visit_scalarset(const Scalarset &) { *this << "scalarset_t"; }


void CTypeGenerator::emit_stream_operators__scalarset(const std::string &name, const Scalarset &te) {
  std::string type_str = nEscape(ModelSplitter::get_pretty_rep(te));

  *this << "#ifdef " ROMP_SIMPLE_TRACE_PREPROCESSOR_VAR "\n"
        << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " { "
           "json << val; "
           "return ::romp::S_VOID; }\n"
        << "#else\n";

  *this << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) " { ";
  *this << "json << \"{\\\"$type\\\":\\\"scalarset-value\\\","
                      "\\\"type\\\":\\\"" << nEscape(type_str) << "\\\","
                      "\\\"bound\\\":" << te.bound->constant_fold().get_str() << ","
                      "\\\"value\\\":\" << ((scalarset_t)val) << \"}\"; "
            // "return json; "
            "return ::romp::S_VOID;"
            "}\n"
            "#endif\n";

  *this << indentation() << ROMP_MAKE_STREAM_CONVERTER_SIG(name) " { ";
  // *this << "out << \": " << type_str << " := \" << ((scalarset_t)val); "
  *this << "out << ((scalarset_t)val) << \"_" << name << "\"; "
           // "return out; "
           "return ::romp::S_VOID;"
           "}\n";

  // *this << indentation() << "void to_json(" ROMP_JSON_TYPE "& j, const ::" ROMP_TYPE_NAMESPACE"::" << name << "& data) { "
  //       "j = (" ROMP_SHOW_TYPE_OPTION_EXPR ") ? (" 
  //         ROMP_JSON_TYPE "{{\"type\",\"" << name << ": " << te.to_string() << "\"}, "
  //                         "{\"value\",(" << value_type << ")data}} "
  //         ") : ( to_json((" << value_type << ")data) ); }\n";
}


void CTypeGenerator::emit_stream_operators__typeexprid(const std::string &name, const TypeExprID &te) {
  std::string type_id = te.referent->name;
  *this << indentation() << ROMP_MAKE_JSON_CONVERTER_SIG(name) "{ ";
  *this << "json << " ROMP_MAKE_JSON_CONVERTER_CALL(type_id,"((" + type_id + ")val)") "; "
            // "return json; "
            "return ::romp::S_VOID;"
            "}\n";

  *this << indentation() << ROMP_MAKE_STREAM_CONVERTER_SIG(name) " { ";
  *this << "out << " ROMP_MAKE_STREAM_CONVERTER_CALL(type_id,"((" + type_id + ")val)") "; "
           // "return out; "
           "return ::romp::S_VOID;"
           "}\n";

  // *this << indentation() << "void to_json(" ROMP_JSON_TYPE "& j, const ::" ROMP_TYPE_NAMESPACE"::" << name << "& data) { "
  //       "to_json(j,(" << te.referent->name << ")data); "
  //       "}\n";
}


void CTypeGenerator::emit_stream_operators(const std::string &name, const Ptr<const TypeExpr> &te) {
  class type_dispatcher : public ConstBaseTypeTraversal {
    const std::string& _name;
    CTypeGenerator* parent;
  public:
    type_dispatcher(const std::string& name_, CTypeGenerator* parent_) 
      : _name(name_), parent(parent_),
        ConstBaseTypeTraversal("Not a TypeExpr!! `type_dispatcher` can't handle it \t[dev-error]") 
    {}
    void visit_array(const Array& n) { parent->emit_stream_operators__array(_name, n); }
    void visit_enum(const Enum& n) { parent->emit_stream_operators__enum(_name, n); }
    void visit_range(const Range& n) { parent->emit_stream_operators__range(_name, n); }
    void visit_record(const Record& n) { parent->emit_stream_operators__record(_name, n); }
    void visit_scalarset(const Scalarset& n) { parent->emit_stream_operators__scalarset(_name, n); }
    void visit_typeexprid(const TypeExprID& n) { parent->emit_stream_operators__typeexprid(_name, n); }
    // void dispatch(const Node& n) { n->visit(*this); }
  };
  type_dispatcher tf(name,this);
  tf.dispatch(*te);
}

void CTypeGenerator::__throw_unreachable_error(const Node &n) {
  throw Error("The CType Code generator encountered an unsupported syntactic object during generation!!", n.loc);
}

}
