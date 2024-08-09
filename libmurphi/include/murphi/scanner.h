#pragma once

#include <cstddef>
#include <iostream>

#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif

#include "parser.yy.hh"

#ifndef MURPHI_API_WITH_RTTI
#define MURPHI_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace murphi {

class MURPHI_API_WITH_RTTI scanner : public yyFlexLexer {

public:
  // Delegate to yyFlexLexer's constructor
  scanner(std::istream *arg_yyin = 0, std::ostream *arg_yyout = 0)
      : yyFlexLexer(arg_yyin, arg_yyout) {}


  using yyFlexLexer::yylex; // throws an error if called
  // Force a new available type signature for yylex
  virtual int yylex(parser::semantic_type *const lval,
                    parser::location_type *loc);
};

} // namespace murphi
