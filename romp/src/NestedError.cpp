/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file throw_nested_error.hpp
 * 
 * @brief util function for joining and throwing a nested rumur error, for easy nested error traces.
 * 
 * @date 2022/06/28
 * @version 0.1
 */

#include "NestedError.hpp"
#include <sstream>
// #include <algorithm>

std::ostream& operator << (std::ostream& out, const rumur::Error& er) { romp::fprint_exception(out,er,""); return out; }
std::ostream& operator << (std::ostream& out, const std::exception& er) { romp::fprint_exception(out,er,""); return out; }

namespace romp {

#define __romp__nested_exception__print_prefix "| "

  // template<>
  // void fprint_exception<Error>(std::ostream& out, const Error& ex) noexcept { fprint_exception(out,ex,""); }
  // template<>
  // void fprint_exception<Error>(std::ostream& out, const Error& ex, const std::string& prefix) noexcept {
  
  void fprint_exception(std::ostream& out, const rumur::Error& ex) noexcept { fprint_exception(out,ex,""); }
  void fprint_exception(std::ostream& out, const rumur::Error& ex, const std::string& prefix) noexcept {
    out << prefix << ex.loc << " :: " << ex.what();
    try {
        std::rethrow_if_nested(ex);
    } catch(const rumur::Error& mod_ex) {
      fprint_exception/* <rumur::Error> */(out, mod_ex, prefix + __romp__nested_exception__print_prefix);
    } catch(const std::exception& ex) {
      fprint_exception/* <std::exception> */(out, ex, prefix + __romp__nested_exception__print_prefix);
    } catch(...) {}
  }

  // template<>
  // void fprint_exception<std::exception>(std::ostream& out, const std::exception& ex) noexcept { fprint_exception(out,ex,""); }
  // template<>
  // void fprint_exception<std::exception>(std::ostream& out, const std::exception& ex, const std::string& prefix) noexcept {
  
  void fprint_exception(std::ostream& out, const std::exception& ex) noexcept { fprint_exception(out,ex,""); }
  void fprint_exception(std::ostream& out, const std::exception& ex, const std::string& prefix) noexcept {
    out << prefix << ex.what() << '\n';
    try {
        std::rethrow_if_nested(ex);
    } catch(const rumur::Error& mod_ex) {
      fprint_exception/* <rumur::Error> */(out, mod_ex, prefix + __romp__nested_exception__print_prefix);
    } catch(const std::exception& ex) {
      fprint_exception/* <std::exception> */(out, ex, prefix + __romp__nested_exception__print_prefix);
    } catch(...) {}
  }

// const NestedError::format_str NestedError::default_format = "{loc} : {message}\n";
// const std::regex NestedError::loc_re("\\{[Ll][Oo][Cc](?:[Aa][Tt][Ii][Oo][Nn])?\\}");
// const std::regex NestedError::msg_re("\\{[Mm][Ss][Gg]|[Mm][Ee][Ss][Ss][Aa][Gg][Ee]|[Ww][Hh][Aa][Tt]\\}");
// const std::regex NestedError::nl_re("\\n");
// // const std::regex NestedError::loc_re;
// // const std::regex NestedError::msg_re;


// NestedError::NestedError(const std::string msg_, const location loc_, const NestedError& er_) 
//   : Error(msg_,loc_), prev_error(new NestedError(er_))
// {}


// NestedError::NestedError(const char* msg_, const location loc_, const NestedError& er_) 
//   : NestedError(std::string(msg_), loc_, er_) 
// {}


// NestedError::NestedError(const std::string msg_, const location loc_) 
//   : Error(msg_,loc_), prev_error(nullptr)
// {}


// NestedError::NestedError(const char* msg_, const location loc_) 
//   : NestedError(std::string(msg_), loc_)
// {}


// NestedError::NestedError(const std::string msg_, const location loc_, const Error& er_) 
//   : Error(msg_,loc_), prev_error(new NestedError(er_.what(), er_.loc))
// {}


// NestedError::NestedError(const char* msg_, const location loc_, const Error& er_) 
//   : NestedError(std::string(msg_), loc_, er_) 
// {}


// char* NestedError::what() const { return what(NestedError::default_format); }


// char* NestedError::what(const NestedError::format_str& format) const { 
//   std::vector<std::string> msg;
//   format_what("", msg, format);
//   std::stringstream str;
//   for (auto line : msg)
//     str << line;
//   return str.str();
// }


// char* NestedError::what(const NestedError::format_str_ format) const { return what(NestedError::format_str(format)); }


// void NestedError::format_what(const std::string& prefix, std::vector<std::string>& msg, const NestedError::format_str& format) {
//   std::stringstream tmp;
//   tmp << loc;
//   msg.push_back(std::regex_replace(std::regex_replace(std::regex_replace(format,
//                                                                           NestedError::loc_re,
//                                                                           tmp.str())
//                                                       NestedError::msg_re,
//                                                       Error::what()),
//                                     NestedError::nl_re,
//                                     "\n"+prefix));
//   if (prev_error != nullptr)
//     prev_error->format_what(prefix + "| ", msg, format);
// }


  // FormatNestedException::FormatNestedException(std::exception& error_) : error(error_) {}
}

// std::ostream& ::operator << (const FormatNestedException& ex);
