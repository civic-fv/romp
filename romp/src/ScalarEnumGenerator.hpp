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
 * @version 0.3
 */

#include "CodeGenerator.hpp"
#include <murphi/murphi.h>
#include <murphi/traverse.h>

#include <unordered_map>
#include <list>

namespace romp {

class ScalarEnumGenerator : public murphi::ConstTraversal {
protected:
  CodeGenerator& gen;
  std::string sep;
  bool add_enum_id(const std::string& name, const std::string& display_name);

public:

  std::unordered_map<std::string,size_t> enum_ids = {{ROMP_SCALAR_ENUM_UNDEFINED_NAME,0}};
  std::list<std::string> _enum_ids = {ROMP_SCALAR_ENUM_UNDEFINED_DISPLAY_NAME};
  
  
  ScalarEnumGenerator(CodeGenerator& gen_);
  ~ScalarEnumGenerator() = default;


  void visit_model(const murphi::Model& m) final;

  void visit_enum(const murphi::Enum& n) final;
  void visit_scalarset(const murphi::Scalarset& n) final;
  // void visit_scalarsetunion(murphi::ScalarsetUnion& n) final;

  // overriden because we don't want to explore enums in it's type specifier
  void visit_ismember(const murphi::IsMember& n) final;

  // template<typename T>
  // friend inline ScalarEnumGenerator& operator << (ScalarEnumGenerator& gen, const T& val);
};

} // namespace romp
