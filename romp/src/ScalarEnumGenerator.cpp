/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file ScalarEnumGenerator.cpp
 * 
 * @brief 
 * 
 * @date 2022/10/14
 * @version 0.2
 */

#include "ScalarEnumGenerator.hpp"
#include <murphi/except.h>
// #include <murphi/sanitize_rule_names.h>

namespace romp {

using namespace murphi;

ScalarEnumGenerator::ScalarEnumGenerator(const CodeGenerator& cg_)
  : CodeGenerator(cg_) {}


void ScalarEnumGenerator::visit_model(const murphi::Model& m) {
  *this << "\n" << indentation() << ROMP_SCALAR_ENUM_DECL_h << "\n";
  indent();
  *this << indentation() << ROMP_SCALAR_ENUM_UNDEFINED_NAME << " = " 
                         << ROMP_SCALAR_ENUM_UNDEFINED_VALUE << ",\n"; 

  for (auto& n : m.children)
    dispatch(n);

  *this << "\n";
  dedent()
  *this << indentation() << "};\n" << std::flush;
}

size_t ScalarEnumGenerator::add_enum_id(const std::string& name) {
  if (enum_ids.find(name) != enum_ids.end()) {
      enum_ids[name] = enum_ids.size();
      _enum_ids.push_back(name);
      *this << sep << '\n' << indentation() << name;
      sep = ",";
      return 1;
    }
  }
  return 0;
}


void ScalarEnumGenerator::visit_enum(const murphi::Enum& n) {
  n.unique_id_limit = 0;
  *this << "\n" << indentation() << "/* " << n.to_string() << " */\n";
  sep = "";
  for (const auto& m : n.members)
    n.unique_id_limit += add_enum_id(n.first);
}


void ScalarEnumGenerator::visit_scalarset(const murphi::Scalarset& n) {
  int added = 0;
  // these complex names are to both avoid collisions and because I scrub names that contain `_romp_` at parse time none should exist
  std::string prefix = (((n.name == "") ? "_romp_"+name : "__romp__scalarset")
                          + '_' + ->get_str() + '_');
  *this << "\n" << indentation() << "/* " 
        << ((name != "") ? name + ": " : "")
        << n.to_string() << " */\n";
  sep = "";
  for (size_t i=1; i<=n.count(); ++i)
    added += add_enum_id(prefix + std::to_string(i));
    
  if (added != n.count() && added != 0)
    throw Error("there exists (generated) name conflicts with this scalarset "
                "and some enum, variable, alias, or parameter",n.loc);
}


// void ScalarEnumGenerator::visit_scalarsetunion(const murphi::ScalarsetUnion& n) {}


} // namespace romp
