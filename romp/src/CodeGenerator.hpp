/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file CodeGenerator.hpp
 * 
 * @brief The place where dreams come to die
 * 
 * @date 2022/06/10
 * @version 0.2
 */

#pragma once

#include "StreamVoid.hpp"
#include <murphi/Property.h>
#include <cstddef>
#include <string>
#include <unordered_set>
#include <fstream>
#include <memory>
#include <filesystem> // C++ 17 or greater
#include <type_traits>
// #include <stack>

#include "romp_def.hpp"

namespace romp {

  // some common supporting code used by code generation functions
  class CodeGenerator {
  protected:
    std::shared_ptr<std::ofstream> out = nullptr;

  public:
    CodeGenerator() = default;
    ~CodeGenerator() = default;
    void set_out(std::shared_ptr<std::ofstream>& out_);


    // the backend type for ranges
    std::string value_type = "int";
    // the backend type for scalars and enum values (not currently supported)
    std::string scalar_type = "";

    // the filepath of the input murphi model
    std::filesystem::path input_file_path  = "stdin";
    // the filepath of the output romp model checker
    std::filesystem::path output_file_path = "./romp.cpp";
    // the number of rule applications to keep track of for trace reports
    size_t hist_len = ROMP_HISTORY_SIZE_PREPROCESSOR_VAR_DEFAULT_VALUE;
    // the number of rule applications to keep track of for trace reports
    size_t default_walk_multiplier = 16u;
    // the number of walkers per unique state to explore upto during initial BFS
    size_t default_bfs_coefficient = 16u;
    // function attributes to prepend before the definition of any murphi function's C/C++ function.
    std::string M_FUNCTION__FUNC_ATTRS = "";
    // function attributes to prepend before the definition of any murphi simple rule's guard C/C++ function.
    std::string M_RULE_GUARD__FUNC_ATTRS = "";
    // function attributes to prepend before the definition of any murphi simple rule's action C/C++ function.
    std::string M_RULE_ACTION__FUNC_ATTRS = "";
    // function attributes to prepend before the definition of any murphi start_state's C/C++ function.
    std::string M_STARTSTATE__FUNC_ATTRS = "";
    // function attributes to prepend before the definition of any murphi invariant's (property-rule) C/C++ function.
    std::string M_PROPERTY__FUNC_ATTRS = "";
    // set of reserved names to not allow to be defined
    const std::unordered_set<std::string> RESERVED_NAMES{"romp","bool","_undefined_","__model__","__caller__","__info__","size_t"};

  private:
    size_t indent_level = 0; // current indentation level
    std::vector<std::string> ENABLED_PREPROCESSOR_OPTIONS;
    bool do_ignore_rumur_props = false;
    bool is_assume_enabled = false;
    bool is_cover_enabled = false;
    bool is_liveness_enabled = false;
    bool is_measure_enabled = false;
    

  protected:
    // id_t next_property_rule_id = 0u;
    // id_t next_rule_id = 0u;
    // id_t next_startstate_id = 0u;
    // id_t next_funct_id = 0u;
    // id_t next_property_id = 0u;
    // id_t next_cover_id = 0u;
    // id_t next_liveness_id = 0u;
    // id_t next_assert_id = 0u;
    // id_t next_assume_id = 0u;
    // id_t next_error_id = 0u;
    // // id_t next_type_id = 0u;
    // // id_t next_enum_id = 0u;
    // id_t next_record_member_id = 0u;
    

  public:
    // get a white space string for the current indentation level
    std::string indentation() const;

    // increase the current indentation level
    StreamVoid& indent();

    // decrease the current indentation level
    StreamVoid& dedent();

    // flush the output stream
    StreamVoid& flush();

  public:
    void enable_preprocessor_option(std::string dir);
    void disable_romp_prop_errors();
    void enable_assume_property();
    void enable_cover_property();
    void enable_liveness_property();
    void enable_measurements();
    bool is_prop_enabled(murphi::Property::Category prop);
    void print_preprocessor_options();


    void output_embedded_code_file(const unsigned char* ecf, const size_t ecf_l);

    // CodeGenerator& operator << (bool val);
    CodeGenerator& operator << (char val);
    CodeGenerator& operator << (int val);
    CodeGenerator& operator << (unsigned int val);
    CodeGenerator& operator << (long val);
    CodeGenerator& operator << (unsigned long val);
    CodeGenerator& operator << (long long val);
    CodeGenerator& operator << (unsigned long long val);
    // CodeGenerator& operator << (typeof(std::flush) flush);
    // CodeGenerator& operator << (typeof(std::endl) endl);
    CodeGenerator& operator << (const std::string& str);
    CodeGenerator& operator << (const mpz_class& val);
    CodeGenerator& operator << (const _StreamVoid&);
    // CodeGenerator& operator << (const murphi::position::counter_type val);
    // CodeGenerator& operator << (const std::function<std::ostream&(std::ostream&)>& manipulator);
    // CodeGenerator& operator << (const std::function<CodeGenerator&(CodeGenerator&)>& manipulator);
    // inline CodeGenerator& operator << (const murphi::Node &n);
    
    // friend inline CodeGenerator& _flush(CodeGenerator& gen);
    

    // template<typename T>
    // friend inline CodeGenerator& operator << (CodeGenerator& gen, const T &val);
    // template<typename T>
    // friend inline CodeGenerator& operator << (CodeGenerator& gen, const T &val);
    // template<>
    // friend inline typename CodeGenerator& operator << <std::function<std::ostream&(std::ostream&)>>(CodeGenerator& gen, const std::function<std::ostream&(std::ostream&)>& manipulator);
    // template<typename T>
    // inline typename std::enable_if<!std::is_base_of<murphi::Node,T>::value,CodeGenerator&>::type operator << (const T &val);

  };


}
