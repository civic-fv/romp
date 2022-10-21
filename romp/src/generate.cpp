#include "generate.hpp"
#include "nested_escape.hpp"
// #include "../../common/escape.h"
#include "ScalarEnumGenerator.hpp"
#include "ModelGenerator.hpp"
#include "generate_metadata.hpp"
#include "generate_callers.hpp"
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


namespace  {

} // namespace <anon>

std::string int_to_hex(unsigned long i ) {
  // std::stringstream stream;
  // stream << "0x" 
  //       //  << std::setfill ('0') << std::setw(sizeof(T)*2) 
  //        << std::hex << i;
  // return stream.str();
  return std::to_string(i);
}

void output_embedded_code_file(std::ostream& out, const unsigned char* ecf, const size_t ecf_l) {
  for (size_t i = 0; i < ecf_l; i++)
    out << (char) ecf[i];
}



void generate(const Model &m, const std::vector<Comment> &comments,
                romp::CodeGenerator &out, const std::string& build_cmds) {
  
  out << ROMP_GENERATED_FILE_PREFACE("\tGenerated code for a romp \"parallel random walker\" verification tool based off of the Murphi Model described in:\n"
                                     "\t\tOriginal Murphi Model: " + romp::CodeGenerator::input_file_path.filename().string() + "\n"
                                     "\tPlease build with the following command(s):\n\t\t" + build_cmds + "") "\n";

  out << "\n#define __romp__GENERATED_CODE\n\n";
  out << "\n#define _ROMP_STATE_TYPE " ROMP_STATE_TYPE "\n\n";
  out << "\n#define _ROMP_STATE_HISTORY_LEN (" << out.hist_len << "ul)\n\n";
  out << "\n#define _ROMP_THREAD_TO_RW_RATIO (" << out.default_walk_multiplier << "ul)\n\n";
  std::string file_path = out.input_file_path.string();
  out << "\n#define __model__filepath \"" << nEscape(file_path) << "\"\n\n";
  int _count = std::count(file_path.begin(), file_path.end(), ' ');
  out << "\n#define __model__filepath_contains_space (" 
      << ((_count > 0) ? "true" : "false") << ")\n\n";
  std::string file_name = out.input_file_path.filename().string();
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
  se_gen.dispatch(m);
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

  out << "\n\n#pragma region model__generated_code\n\n"
      << out.indentation() << "namespace " ROMP_MODEL_NAMESPACE_NAME " {\n";
  romp::ModelGenerator gen(out, se_gen.enum_ids, comments);
  gen.dispatch(m);
  out << "\n" << out.indentation() << "} // namespace " ROMP_MODEL_NAMESPACE_NAME "\n"
      << "\n\n#pragma endregion model__generated_code\n\n" << std::flush;

  out << "\n\n#pragma region metadata__generated_code\n\n"
      << out.indentation() << "namespace " ROMP_INFO_NAMESPACE_NAME " {\n";
  out.indent();
  out << "/* the number possible variations in the state (# of permutations of the state-space) */\n"
          "#define " ROMP_STATESPACE_LEN " \"" << statespace_count(state).get_str() << "\"\n"
  out << ROMP_INFO_TYPE_IDS_DECL " = "
  romp::generate_type_ids_metadata(out,m);
  out << ";\n";
  out << ROMP_INFO_RF_IDS_DECL " = "
  romp::generate_record_members_metadata(out,m);
  out << ";\n";
  out << ROMP_INFO_RULESETS_DECL " = ";
  romp::generate_ruleset_metadata(out,m);
  out << ";\n";
  out << ROMP_INFO_PROPERTIES_DECL " = ";
  auto prop_ids = romp::generate_property_metadata(out,m);
  out << ";\n"
      << "/* the number of cover property statements & rules in the model */\n"
      << "#define " ROMP_COVER_PROP_COUNT " (" << prop_ids.first <<  "ul)\n"
      << "/* the number of liveness property rules in the model */\n"
      << "#define " ROMP_LIVENESS_PROP_COUNT " (" << prop_ids.second <<  "ul)\n";
  out << ROMP_INFO_STARTSTATES_DECL " = ";
  romp::generate_startstate_metadata(out,m);
  out << ";\n";
  out << ROMP_INFO_FUNCTS_DECL " = ";
  romp::generate_function_metadata(out,m);
  out << ";\n";
  out << ROMP_INFO_ERRORS_DECL " = ";
  romp::generate_error_metadata(out,m);
  out << ";\n";
  out.dedent();
  out << "\n" << out.indentation() << "} // namespace " ROMP_INFO_NAMESPACE_NAME "\n"
      << "\n\n#pragma endregion metadata__generated_code\n\n" << std::flush;

  out << "\n\n#pragma region rule_caller__generated_code\n\n"
      << out.indentation() << "namespace " ROMP_CALLER_NAMESPACE_NAME " {\n\n"
      << out.indentation() << "// << ==================================== Rule Expansions ===================================== >> \n\n";
  romp::generate_ruleset_callers(out,m);
  out << "\n\n" << out.indentation() 
      << "// << =============================== Property Rule Expansions ================================= >> \n\n"
  romp::generate_property_rule_callers(out,m);
  out << "\n\n" << out.indentation() 
      << "// << ================================= Startstate Expansions ================================== >> \n\n"
  romp::generate_startstate_callers(out,m);
  out << "\n\n" << out.indentation() << "} // namespace " ROMP_CALLER_NAMESPACE_NAME "\n"
      << "\n\n#pragma endregion rule_caller__generated_code\n\n" << std::flush;

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
