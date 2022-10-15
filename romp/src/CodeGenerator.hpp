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

#include <murphi/murphi.h>
#include <cstddef>
#include <string>
#include <unordered_set>
#include <ostream>
#include <memory>
#include <filesystem> // C++ 17 or greater
// #include <stack>

#include "romp_def.hpp"

namespace romp {

  // some common supporting code used by code generation functions
  class CodeGenerator {
  protected:
    std::shared_ptr<std::ostream> out;

  public:
    CodeGenerator() = default;
    ~CodeGenerator() = default;
    friend void set_out(CodeGenerator& gen, std::shared_ptr<std::ostream>& out);

    // the filepath of the input murphi model
    std::filesystem::path input_file_path;
    // the filepath of the output romp model checker
    std::filesystem::path output_file_path;
    // function attributes to prepend before the definition of any murphi function's C/C++ function.
    std::string M_FUNCTION__FUNC_ATTRS;
    // function attributes to prepend before the definition of any murphi simple rule's guard C/C++ function.
    std::string M_RULE_GUARD__FUNC_ATTRS;
    // function attributes to prepend before the definition of any murphi simple rule's action C/C++ function.
    std::string M_RULE_ACTION__FUNC_ATTRS;
    // function attributes to prepend before the definition of any murphi start_state's C/C++ function.
    std::string M_STARTSTATE__FUNC_ATTRS;
    // function attributes to prepend before the definition of any murphi invariant's (property-rule) C/C++ function.
    std::string M_PROPERTY__FUNC_ATTRS;

  private:
    size_t indent_level = 0; // current indentation level
    std::vector<std::string> ENABLED_PREPROCESSOR_OPTIONS;
    const std::unordered_set<std::string> RESERVED_NAMES;
    bool do_ignore_rumur_props;
    bool is_assume_enabled;
    bool is_cover_enabled;
    bool is_liveness_enabled;
    bool is_measure_enabled;
    

  protected:
    id_t next_property_rule_id = 0u;
    id_t next_rule_id = 0u;
    id_t next_startstate_id = 0u;
    id_t next_funct_id = 0u;
    id_t next_property_id = 0u;
    id_t next_cover_id = 0u;
    id_t next_liveness_id = 0u;
    id_t next_assert_id = 0u;
    id_t next_assume_id = 0u;
    id_t next_error_id = 0u;
    id_t next_type_id = 0u;
    id_t next_enum_id = 0u;
    

    // get a white space string for the current indentation level
    std::string indentation() const;

    // increase the current indentation level
    void indent();

    // decrease the current indentation level
    void dedent();

  public:
    void enable_preprocessor_option(std::string dir);
    void disable_romp_prop_errors();
    void enable_assume_property();
    void enable_cover_property();
    void enable_liveness_property();
    void enable_measurements();
    bool is_prop_enabled(murphi::Property::Category prop);
    void print_preprocessor_options(std::ostream& out);


    CodeGenerator& operator << (const murphi::Node &n);
    CodeGenerator& operator << (bool val);
    template<typename T>
    CodeGenerator& operator << (const T &val);

  };

}
