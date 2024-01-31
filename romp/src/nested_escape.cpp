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
 * @version 0.3
 */


#include "nested_escape.hpp"
#include <ctype.h>

static std::string _octal_esc(char c) {
  char buffer[10ul] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
  std::snprintf(buffer, 6ul, "\\%03o", c);
  return buffer;
}

std::string nEscape(const std::string &s) {
  std::string out;
  for (size_t i=0; i<s.size(); ++i) {
    switch (s[i]) {
      case '\\':
        out += '\\';
        out += '\\';
      break;
      case '"':
        out += '\\';
        out += '"';
        break;
      case '\t':
      case '\r':
      case '\n':
        out += _octal_esc(s[i]);
      default:
        out += s[i];
    }
  }
  return out;
}
