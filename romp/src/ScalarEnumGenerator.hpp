/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file ScalarEnum.hpp
 * 
 * @brief 
 * 
 * @date 2022/10/14
 * @version 0.2
 */

#include "CodeGenerator.hpp"
#include <murphi/murphi.h>
#include <murphi/traverse.h>

#include <unordered_map>
#include <list>

namespace romp {

class ScalarEnumGenerator : public romp::CodeGenerator,
                            public murphi::Traversal {
protected:
  std::string sep;
  size_t add_enum_id(const std::string& name);

public:

  std::unordered_map<std::string,size_t> enum_ids = {{ROMP_SCALAR_ENUM_UNDEFINED_NAME,0}};
  std::list<std::string> _enum_ids = {ROMP_SCALAR_ENUM_UNDEFINED_NAME};
  
  
  ScalarEnumGenerator(const CodeGenerator& cg_);
  ~ScalarEnumGenerator() = default;


  void visit_model(murphi::Model& m) final;

  void visit_enum(murphi::Enum& n) final;
  void visit_scalarset(murphi::Scalarset& n) final;
  // void visit_scalarsetunion(murphi::ScalarsetUnion& n) final;
};

} // namespace romp
