%{

#include <cstddef>
#include "parser.yy.hh"
#include <murphi/except.h>
#include <murphi/scanner.h>

/* Override the declaration of yylex with the one from our derived scanner. */
#ifdef YY_DECL
  #undef YY_DECL
#endif
#define YY_DECL int murphi::scanner::yylex(\
  murphi::parser::semantic_type *const lval, murphi::parser::location_type *loc)

/* Each time yylex() is called, update the begin position with the last end
 * position. This ensures we get correct starting column numbers.
 */
#define YY_USER_ACTION  loc->step(); loc->columns(yyleng);

%}

  /* Track line numbers while scanning. These are retrievable via
   * FlexLexer::lineno().
   */
%option yylineno

  /* When the end of the input is encountered, do not expect another file. */
%option noyywrap

  /* Generate a C++ scanner, not C. */
%option c++

  /* Use our own scanner class, rather than the default yyFlexLexer. */
%option yyclass="murphi::scanner"

  /* Switch to case-insensitive. */
%option caseless

  /* States for handling comments. This is not the most efficient way of
   * dealing with these, but meh.
   */
%x SC_COMMENT SC_MULTILINE_COMMENT

%%

(0x[[:xdigit:]]+|[[:digit:]]+) {
  lval->build<std::string>(YYText());
  return murphi::parser::token::NUMBER;
}

([[:digit:]]?\.[[:digit:]]+) {
  throw murphi::Error("real types are not supported", *loc);
}

alias               { return murphi::parser::token::ALIAS;               }
array               { return murphi::parser::token::ARRAY;               }
assert              { return murphi::parser::token::ASSERT;              }
assume              { return murphi::parser::token::ASSUME;              }
begin               { return murphi::parser::token::BEGIN_TOK;           }
boolean             { return murphi::parser::token::BOOLEAN;             }
by                  { return murphi::parser::token::BY;                  }
case                { return murphi::parser::token::CASE;                }
choose              { return murphi::parser::token::CHOOSE;              }
clear               { return murphi::parser::token::CLEAR;               }
const               { return murphi::parser::token::CONST;               }
cover               { return murphi::parser::token::COVER;               }
do                  { return murphi::parser::token::DO;                  }
else                { return murphi::parser::token::ELSE;                }
elsif               { return murphi::parser::token::ELSIF;               }
end                 { return murphi::parser::token::END;                 }
endalias            { return murphi::parser::token::ENDALIAS;            }
endchoose           { return murphi::parser::token::ENDCHOOSE;           }
endexists           { return murphi::parser::token::ENDEXISTS;           }
endfor              { return murphi::parser::token::ENDFOR;              }
endforall           { return murphi::parser::token::ENDFORALL;           }
endfunction         { return murphi::parser::token::ENDFUNCTION;         }
endif               { return murphi::parser::token::ENDIF;               }
endprocedure        { return murphi::parser::token::ENDPROCEDURE;        }
endrecord           { return murphi::parser::token::ENDRECORD;           }
endrule             { return murphi::parser::token::ENDRULE;             }
endruleset          { return murphi::parser::token::ENDRULESET;          }
endstartstate       { return murphi::parser::token::ENDSTARTSTATE;       }
endswitch           { return murphi::parser::token::ENDSWITCH;           }
endwhile            { return murphi::parser::token::ENDWHILE;            }
enum                { return murphi::parser::token::ENUM;                }
error               { return murphi::parser::token::ERROR;               }
exists              { return murphi::parser::token::EXISTS;              }
for                 { return murphi::parser::token::FOR;                 }
ismember            { return murphi::parser::token::ISMEMBER;            }
forall              { return murphi::parser::token::FORALL;              }
function            { return murphi::parser::token::FUNCTION;            }
if                  { return murphi::parser::token::IF;                  }
invariant           { return murphi::parser::token::INVARIANT;           }
liveness            { return murphi::parser::token::LIVENESS;            }
isundefined         { return murphi::parser::token::ISUNDEFINED;         }
multiset            { return murphi::parser::token::MULTISET;            }
multisetadd         { return murphi::parser::token::MULTISETADD;         }
multisetcount       { return murphi::parser::token::MULTISETCOUNT;       }
multisetremove      { return murphi::parser::token::MULTISETREMOVE;      }
multisetremovepred  { return murphi::parser::token::MULTISETREMOVEPRED;  }
of                  { return murphi::parser::token::OF;                  }
procedure           { return murphi::parser::token::PROCEDURE;           }
put                 { return murphi::parser::token::PUT;                 }
real                { throw murphi::Error("real types are not supported", *loc); }
record              { return murphi::parser::token::RECORD;              }
return              { return murphi::parser::token::RETURN;              }
rule                { return murphi::parser::token::RULE;                }
ruleset             { return murphi::parser::token::RULESET;             }
scalarset           { return murphi::parser::token::SCALARSET;           }
startstate          { return murphi::parser::token::STARTSTATE;          }
switch              { return murphi::parser::token::SWITCH;              }
then                { return murphi::parser::token::THEN;                }
to                  { return murphi::parser::token::TO;                  }
type                { return murphi::parser::token::TYPE;                }
undefine            { return murphi::parser::token::UNDEFINE;            }
union               { return murphi::parser::token::UNION;               }
while               { return murphi::parser::token::WHILE;               }
var                 { return murphi::parser::token::VAR;                 }

"∃"                 { return murphi::parser::token::EXISTS;              }
"∀"                 { return murphi::parser::token::FORALL;              }

  /* Recognise true and false explicitly rather than as generic IDs (below). The
   * purpose of this is so that we match them case-insensitively.
   */
false {
  lval->build<std::string>("false");
  return murphi::parser::token::ID;
}
true {
  lval->build<std::string>("true");
  return murphi::parser::token::ID;
}

[[:alpha:]][_[:alnum:]]* {
  lval->build<std::string>(YYText());
  return murphi::parser::token::ID;
}

"--" {
  BEGIN(SC_COMMENT);
}

"/*" {
  BEGIN(SC_MULTILINE_COMMENT);
}

":=" { return murphi::parser::token::COLON_EQ;  }
"≔"  { return murphi::parser::token::COLON_EQ;  }
".." { return murphi::parser::token::DOTDOT;    }
">=" { return murphi::parser::token::GEQ;       }
"≥"  { return murphi::parser::token::GEQ;       }
">>" { return murphi::parser::token::RSH;       }
"->" { return murphi::parser::token::IMPLIES;   }
"→"  { return murphi::parser::token::IMPLIES;   }
"<=" { return murphi::parser::token::LEQ;       }
"≤"  { return murphi::parser::token::LEQ;       }
"<<" { return murphi::parser::token::LSH;       }
"!=" { return murphi::parser::token::NEQ;       }
"≠"  { return murphi::parser::token::NEQ;       }
"==>" { return murphi::parser::token::ARROW;    }
"⇒"  { return murphi::parser::token::ARROW;    }
"==" { return murphi::parser::token::DEQ;       }
"¬"  { return '!';                             }
"∧"  { return murphi::parser::token::LAND;      }
"∨"  { return murphi::parser::token::LOR;       }
"&&" { return murphi::parser::token::AMPAMP;    }
"||" { return murphi::parser::token::PIPEPIPE;  }

[\^~&!|:=><\-\%\+;{},\[\]\.()/\*\?] {
  return YYText()[0];
}

(\"|“)(\\.|[^\\\"]|\\”)*(\"|”) {
  std::string s(YYText());

  /* figure out which quote character this string starts with */
  const std::string opener = s.find("“") == 0 ? "“" : "\"";
  assert(s.find(opener) == 0 && "logic bug in string lexing rule");

  /* figure out which quote character this string ends with */
  static const std::string squote = "”";
  size_t offset = s.size() - squote.size();
  const std::string closer
    = s.size() > squote.size() && s.find(squote, offset) == offset
    ? squote
    : "\"";

  /* build a string, stripping the quote delimiters */
  lval->build<std::string>(s.substr(opener.size(),
    s.size() - opener.size() - closer.size()).c_str());

  return murphi::parser::token::STRING;
}

    /* Ensure we keep a correct line count for error reporting. */
"\n" {
  loc->lines(yyleng);
  loc->step(); /* maintain correct column count */
}

  /* Ignore white space. */
[[:space:]] {
  loc->step(); /* maintain correct column count */
}

. {
  throw murphi::Error(std::string("unexpected character: '") + YYText() + "'", *loc);
}

  /* Comment handling. */
<SC_COMMENT>. {
  /* do nothing */
}

<SC_COMMENT>\n {
  loc->lines(yyleng);
  loc->step(); /* maintain correct column count */
  BEGIN(INITIAL);
}

<SC_MULTILINE_COMMENT>[^*\n]* {
  /* do nothing */
}

<SC_MULTILINE_COMMENT>"*"+[^*/\n]* {
  /* do nothing */
}

<SC_MULTILINE_COMMENT>\n {
  loc->lines(yyleng);
}

<SC_MULTILINE_COMMENT>"*"+"/" {
  loc->step(); /* maintain correct column count */
  BEGIN(INITIAL);
}
