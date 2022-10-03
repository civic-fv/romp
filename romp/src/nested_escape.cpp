/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file nested_escape.hpp
 * 
 * @brief a handy utility for escaping strings in a way that works with nesting strings isn strings.
 *        like when you want to generate c/c++ code that contains a string with json info 
 *          where a json string may or may-not contain `"`
 * 
 * @date 2022/07/20
 * @version 0.1
 */


#include "nested_escape.hpp"
#include <ctype.h>

static std::string _octal_esc(char c) {
  char buffer[sizeof("\\000")];
  std::snprintf(buffer, sizeof(buffer), "\\%03o", c);
  return buffer;
}

std::string nEscape(const std::string &s) {
  std::string out;
  for (size_t i=0; i<s.size(); ++i) {
    if (s[i] == '\\') {
      out += '\\';
      out += '\\';
    } else if (s[i] == '\"') {
      out += '\\';
      out += '"';
    // } else if (iscntrl(s[i])) {
    //   out += _octal_esc(s[i]);
    } else {
      out += s[i];
    }
  }
  return out;
}
