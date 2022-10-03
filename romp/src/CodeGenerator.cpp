#include "CodeGenerator.hpp"
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>


namespace romp {

std::filesystem::path CodeGenerator::input_file_path = "stdin";
std::filesystem::path CodeGenerator::output_file_path = "./romp.cpp";

const std::unordered_set<std::string> CodeGenerator::RESERVED_NAMES{ROMP_RESERVED_NAMES, ROMP_RESERVED_NAMES};

std::string CodeGenerator::M_FUNCTION__FUNC_ATTRS = "";

std::string CodeGenerator::M_RULE_GUARD__FUNC_ATTRS = "";
std::string CodeGenerator::M_RULE_ACTION__FUNC_ATTRS = "";

std::string CodeGenerator::M_STARTSTATE__FUNC_ATTRS = "";

std::string CodeGenerator::M_PROPERTY__FUNC_ATTRS = "";


std::string CodeGenerator::indentation() const {
  return std::string(indent_level * 2, ' ');
}

void CodeGenerator::indent() { indent_level++; }

void CodeGenerator::dedent() {
  assert(indent_level > 0 && "attempted negative indentation");
  indent_level--;
}

std::vector<std::string> CodeGenerator::ENABLED_PREPROCESSOR_OPTIONS{};

void CodeGenerator::enable_preprocessor_option(std::string option) {
  ENABLED_PREPROCESSOR_OPTIONS.push_back(option);
}
void CodeGenerator::print_preprocessor_options(std::ostream& out) {
  for (auto var : ENABLED_PREPROCESSOR_OPTIONS)
    out << "\n#define " << var << "\n";
}

bool CodeGenerator::is_assume_enabled = false;
void CodeGenerator::enable_assume_property() {
  is_assume_enabled = true;
  ENABLED_PREPROCESSOR_OPTIONS.push_back(ROMP_ASSUME_PREPROCESSOR_VAR);
}
bool CodeGenerator::is_cover_enabled = false;
void CodeGenerator::enable_cover_property() {
  is_cover_enabled = true;
  ENABLED_PREPROCESSOR_OPTIONS.push_back(ROMP_COVER_PREPROCESSOR_VAR);
}
bool CodeGenerator::is_liveness_enabled = false;
void CodeGenerator::enable_liveness_property() {
  is_liveness_enabled = true;
  ENABLED_PREPROCESSOR_OPTIONS.push_back(ROMP_LIVENESS_PREPROCESSOR_VAR);
}
bool CodeGenerator::is_measure_enabled = false;
void CodeGenerator::enable_measurements() {
  is_measure_enabled = true;
  ENABLED_PREPROCESSOR_OPTIONS.push_back(ROMP_MEASURE_PREPROCESSOR_VAR);
}

bool CodeGenerator::is_prop_enabled(rumur::Property::Category prop) {
  if (CodeGenerator::do_ignore_romp_props) return true;
  switch (prop) {
  case rumur::Property::ASSERTION:
    return true;
  case rumur::Property::ASSUMPTION:
    return CodeGenerator::is_assume_enabled;
  case rumur::Property::COVER:
    return CodeGenerator::is_cover_enabled;
  case rumur::Property::LIVENESS:
    return CodeGenerator::is_liveness_enabled;
  default:
    return false;
  }
}

bool CodeGenerator::do_ignore_romp_props = false;
void CodeGenerator::disable_romp_prop_errors() {
  CodeGenerator::do_ignore_romp_props = true;
}

CodeGenerator::~CodeGenerator() {}

}
