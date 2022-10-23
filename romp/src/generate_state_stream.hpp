/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file generate_state_stream.hpp
 * 
 * @brief generate the stream operators used to output the state to json files or the console
 * 
 * @date 2022/10/19
 * @version 0.2
 */

#include "CodeGenerator.hpp"
#include <murphi/murphi.h>


namespace romp {


  /**
   * @brief Generate the stream operators for the state data object 
   *        used to output the state to json traces and the console output
   */
  void generate_state_stream(romp::CodeGenerator& gen, const murphi::Model& m);



} // namespace romp
