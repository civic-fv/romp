#include "CodeGenerator.hpp"
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>
#include <functional>
#include <cassert>


namespace romp {

void CodeGenerator::set_out(std::unique_ptr<std::ofstream> out_) { out = std::move(out_); }

// std::filesystem::path CodeGenerator::input_file_path = "stdin";
// std::filesystem::path CodeGenerator::output_file_path = "./romp.cpp";

// const std::unordered_set<std::string> CodeGenerator::RESERVED_NAMES{ROMP_RESERVED_NAMES, ROMP_RESERVED_NAMES};

// std::string CodeGenerator::M_FUNCTION__FUNC_ATTRS = "";

// std::string CodeGenerator::M_RULE_GUARD__FUNC_ATTRS = "";
// std::string CodeGenerator::M_RULE_ACTION__FUNC_ATTRS = "";

// std::string CodeGenerator::M_STARTSTATE__FUNC_ATTRS = "";

// std::string CodeGenerator::M_PROPERTY__FUNC_ATTRS = "";


std::string CodeGenerator::indentation() const {
  return std::string(indent_level * 2, ' ');
}

StreamVoid& CodeGenerator::indent() { indent_level++;  return S_VOID; }

StreamVoid& CodeGenerator::dedent() {
  assert(indent_level > 0 && "attempted negative indentation");
  indent_level--;
  return S_VOID;
}

// std::vector<std::string> CodeGenerator::ENABLED_PREPROCESSOR_OPTIONS{};

void CodeGenerator::enable_preprocessor_option(std::string option) {
  ENABLED_PREPROCESSOR_OPTIONS.push_back(option);
}
void CodeGenerator::print_preprocessor_options() {
  for (auto var : ENABLED_PREPROCESSOR_OPTIONS)
    *out << "\n#define " << var << "\n";
}

// bool CodeGenerator::is_assume_enabled = false;
void CodeGenerator::enable_assume_property() {
  is_assume_enabled = true;
  ENABLED_PREPROCESSOR_OPTIONS.push_back(ROMP_ASSUME_PREPROCESSOR_VAR);
}
// bool CodeGenerator::is_cover_enabled = false;
void CodeGenerator::enable_cover_property() {
  is_cover_enabled = true;
  ENABLED_PREPROCESSOR_OPTIONS.push_back(ROMP_COVER_PREPROCESSOR_VAR);
}
// bool CodeGenerator::is_liveness_enabled = false;
void CodeGenerator::enable_liveness_property() {
  is_liveness_enabled = true;
  ENABLED_PREPROCESSOR_OPTIONS.push_back(ROMP_LIVENESS_PREPROCESSOR_VAR);
}
// bool CodeGenerator::is_measure_enabled = false;
void CodeGenerator::enable_measurements() {
  is_measure_enabled = true;
  ENABLED_PREPROCESSOR_OPTIONS.push_back(ROMP_MEASURE_PREPROCESSOR_VAR);
}

bool CodeGenerator::is_prop_enabled(murphi::Property::Category prop) {
  if (CodeGenerator::do_ignore_rumur_props) return true;
  switch (prop) {
  case murphi::Property::ASSERTION:
    return true;
  case murphi::Property::ASSUMPTION:
    return CodeGenerator::is_assume_enabled;
  case murphi::Property::COVER:
    return CodeGenerator::is_cover_enabled;
  case murphi::Property::LIVENESS:
    return CodeGenerator::is_liveness_enabled;
  default:
    return false;
  }
}

// bool CodeGenerator::do_ignore_rumur_props = false;
void CodeGenerator::disable_romp_prop_errors() {
  CodeGenerator::do_ignore_rumur_props = true;
}



void CodeGenerator::output_embedded_code_file(const unsigned char* ecf, const size_t ecf_l) {
  for (size_t i = 0; i < ecf_l; ++i)
    *out << (char) ecf[i];
  *out << std::flush;
}

// CodeGenerator::~CodeGenerator() {}

// CodeGenerator& CodeGenerator::operator << (const murphi::Node &n) {
//   // should never be called from the base of this type
//   assert(!"unreachable");
//   __builtin_unreachable();
// }

// CodeGenerator& CodeGenerator::operator << (bool val) {
//   *out << ((val) ? "true" : "false");
//   return *this;
// }
// CodeGenerator& CodeGenerator::operator << (const std::function<std::ostream&(std::ostream&)>& manipulator) {
//   manipulator(*out);
//   return *this;
// }
// CodeGenerator& CodeGenerator::operator << (const std::function<CodeGenerator&(CodeGenerator&)>& manipulator) {
//   return manipulator(*this);
// }
CodeGenerator& CodeGenerator::operator << (char val) {
  *out << val;
  return *this;
}
CodeGenerator& CodeGenerator::operator << (int val) {
  *out << val;
  return *this;
}
CodeGenerator& CodeGenerator::operator << (unsigned int val) {
  *out << val;
  return *this;
}
CodeGenerator& CodeGenerator::operator << (long val) {
  *out << val;
  return *this;
}
CodeGenerator& CodeGenerator::operator << (unsigned long val) {
  *out << val;
  return *this;
}
CodeGenerator& CodeGenerator::operator << (long long val) {
  *out << val;
  return *this;
}
CodeGenerator& CodeGenerator::operator << (unsigned long long val) {
  *out << val;
  return *this;
}
// CodeGenerator& CodeGenerator::operator << (typeof(std::flush) flush) {
//   *out << std::flush;
//   return *this;
// }
// CodeGenerator& CodeGenerator::operator << (typeof(std::endl) endl) {
//   *out << std::endl;
//   return *this;
// }
CodeGenerator& CodeGenerator::operator << (const std::string& str) {
  *out << str;
  return *this;
}
CodeGenerator& CodeGenerator::operator << (const mpz_class& val) {
  *out << val.get_str();
  return *this;
}
CodeGenerator& CodeGenerator::operator << (const _StreamVoid&) { return *this; }


// template<typename T>
// inline CodeGenerator& operator << (CodeGenerator& gen, const T& val) {
//   (*gen.out) << val;
//   return gen;
// }
// template<typename T>
// inline typename std::enable_if<!std::is_base_of<murphi::Node,T>::value,CodeGenerator&>::type operator << (CodeGenerator& gen, const T& val) {
//   (*gen.out) << val;
//   return gen;
// }
// template<>
// inline typename CodeGenerator& operator << <std::function<std::ostream&(std::ostream&)>>(CodeGenerator& gen, const std::function<std::ostream&(std::ostream&)>& manipulator) {
//   manipulator(*gen.out);
//   return gen;
// }
// template<typename T>
// inline typename std::enable_if<!std::is_base_of<murphi::Node,T>::value,CodeGenerator&>::type  CodeGenerator::operator << (const T& val) {
//   (*(out)) << val;
//   return *this;
// }

// template<>
// inline CodeGenerator& operator << <bool>(CodeGenerator& gen, const bool& val) {
//   (*gen.out) << ((val) ? "true" : "false");
//   return gen;
// }

// inline CodeGenerator& flush(CodeGenerator& gen) {
StreamVoid& CodeGenerator::flush() {
  out->flush();
  return S_VOID;
}

} // namespace romp
