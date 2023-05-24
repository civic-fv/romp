/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file generate_callers.hpp
 * 
 * @brief generate all of the ruleset expansion callers for the model.
 * 
 * @date 2022/10/19
 * @version 0.3
 */

#include "CodeGenerator.hpp"
#include <murphi/murphi.h>

namespace romp {

  /**
   * @brief generate the list/array of rulesets containing all of the expanded rules
   */
  void generate_ruleset_callers(romp::CodeGenerator& gen, const murphi::Model& m);

  /**
   * @brief generate the list/array of all the expanded property rules
   */
  void generate_property_rule_callers(romp::CodeGenerator& gen, const murphi::Model& m);

  /**
   * @brief generate the list/array of expanded startstates
   */
  void generate_startstate_callers(romp::CodeGenerator& gen, const murphi::Model& m);

}  // namespace romp
