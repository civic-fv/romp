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
 * @version 0.1
 */

#pragma once

#include <rumur/rumur.h>
#include <cstddef>
#include <string>
#include <unordered_set>
#include <ostream>
#include <filesystem> // C++ 17 or greater
// #include <stack>

#include "romp_def.hpp"

namespace romp {

  // some common supporting code used by code generation functions
  class CodeGenerator {

  public:
    // the filepath of the input murphi model
    static std::filesystem::path input_file_path;
    // the filepath of the output romp model checker
    static std::filesystem::path output_file_path;
    // function attributes to prepend before the definition of any murphi function's C/C++ function.
    static std::string M_FUNCTION__FUNC_ATTRS;
    // function attributes to prepend before the definition of any murphi simple rule's guard C/C++ function.
    static std::string M_RULE_GUARD__FUNC_ATTRS;
    // function attributes to prepend before the definition of any murphi simple rule's action C/C++ function.
    static std::string M_RULE_ACTION__FUNC_ATTRS;
    // function attributes to prepend before the definition of any murphi start_state's C/C++ function.
    static std::string M_STARTSTATE__FUNC_ATTRS;
    // function attributes to prepend before the definition of any murphi invariant's (property-rule) C/C++ function.
    static std::string M_PROPERTY__FUNC_ATTRS;

  private:
    size_t indent_level = 0; // current indentation level

    

  protected:

    static std::vector<std::string> ENABLED_PREPROCESSOR_OPTIONS;
    static const std::unordered_set<std::string> RESERVED_NAMES;
    static bool do_ignore_romp_props;
    static bool is_assume_enabled;
    static bool is_cover_enabled;
    static bool is_liveness_enabled;
    static bool is_measure_enabled;

    // get a white space string for the current indentation level
    std::string indentation() const;

    // increase the current indentation level
    void indent();

    // decrease the current indentation level
    void dedent();

  public:
    static void enable_preprocessor_option(std::string dir);
    static void disable_romp_prop_errors();
    static void enable_assume_property();
    static void enable_cover_property();
    static void enable_liveness_property();
    static void enable_measurements();
    static bool is_prop_enabled(rumur::Property::Category prop);
    static void print_preprocessor_options(std::ostream& out);

    // make this class abstract
    virtual ~CodeGenerator() = 0;
  };

}
