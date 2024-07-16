/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file generate_metadata.hpp
 *
 * @brief Output the metadata constructs for the model_checker
 *
 * @date 2022/10/18
 * @version 0.3
 */

#include "CodeGenerator.hpp"
#include <utility>
#include <murphi/Node.h>

namespace romp {


/**
 * @brief Generate a structured list/array of string literals representing the names of type_id's
 */
void generate_type_ids_metadata(CodeGenerator& gen, const murphi::Node& n);

/**
 * @brief Generate a structured list/array of string literals representing the labels of record members
 */
void generate_record_members_metadata(CodeGenerator& gen, const murphi::Node& n);

/**
 * @brief Generate a structured list/array of string literals representing the names of type_id's
 */
void generate_ruleset_metadata(CodeGenerator& gen, const murphi::Node& n);

/**
 * @brief Generate a structured list/array of string literals representing the names of type_id's
 * @returns \c std::pair<id_t,id_t> - the number of cover and liveness properties respectively
 */
std::pair<id_t,id_t> generate_property_metadata(CodeGenerator& gen, const murphi::Node& n);

/**
 * @brief Generate a structured list/array of string literals representing the names of type_id's
 */
void generate_startstate_metadata(CodeGenerator& gen, const murphi::Node& n);

/**
 * @brief Generate a structured list/array of string literals representing the names of type_id's
 */
void generate_error_metadata(CodeGenerator& gen, const murphi::Node& n);

/**
 * @brief Generate a structured list/array of string literals representing the names of type_id's
 */
void generate_function_metadata(CodeGenerator& gen, const murphi::Node& n);

} // namespace romp
