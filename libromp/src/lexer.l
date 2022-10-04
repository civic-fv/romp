%{

#include <cstddef>
#include "parser.yy.hh"
#include <romp/except.h>
#include <romp/scanner.h>

/* Override the declaration of yylex with the one from our derived scanner. */
#ifdef YY_DECL
  #undef YY_DECL
#endif
#define YY_DECL int romp::scanner::yylex(\
  romp::parser::semantic_type *const lval, romp::parser::location_type *loc)

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
%option yyclass="romp::scanner"

  /* Switch to case-insensitive. */
%option caseless

  /* States for handling comments. This is not the most efficient way of
   * dealing with these, but meh.
   */
%x SC_COMMENT SC_MULTILINE_COMMENT

%%

(0x[[:xdigit:]]+|[[:digit:]]+) {
  lval->build<std::string>(YYText());
  return romp::parser::token::NUMBER;
}

([[:digit:]]?\.[[:digit:]]+) {
  throw romp::Error("real types are not supported", *loc);
}

alias               { return romp::parser::token::ALIAS;               }
array               { return romp::parser::token::ARRAY;               }
assert              { return romp::parser::token::ASSERT;              }
assume              { return romp::parser::token::ASSUME;              }
begin               { return romp::parser::token::BEGIN_TOK;           }
boolean             { return romp::parser::token::BOOLEAN;             }
by                  { return romp::parser::token::BY;                  }
case                { return romp::parser::token::CASE;                }
choose              { return romp::parser::token::CHOOSE;              }
clear               { return romp::parser::token::CLEAR;               }
const               { return romp::parser::token::CONST;               }
cover               { return romp::parser::token::COVER;               }
do                  { return romp::parser::token::DO;                  }
else                { return romp::parser::token::ELSE;                }
elsif               { return romp::parser::token::ELSIF;               }
end                 { return romp::parser::token::END;                 }
endalias            { return romp::parser::token::ENDALIAS;            }
endchoose           { return romp::parser::token::ENDCHOOSE;           }
endexists           { return romp::parser::token::ENDEXISTS;           }
endfor              { return romp::parser::token::ENDFOR;              }
endforall           { return romp::parser::token::ENDFORALL;           }
endfunction         { return romp::parser::token::ENDFUNCTION;         }
endif               { return romp::parser::token::ENDIF;               }
endprocedure        { return romp::parser::token::ENDPROCEDURE;        }
endrecord           { return romp::parser::token::ENDRECORD;           }
endrule             { return romp::parser::token::ENDRULE;             }
endruleset          { return romp::parser::token::ENDRULESET;          }
endstartstate       { return romp::parser::token::ENDSTARTSTATE;       }
endswitch           { return romp::parser::token::ENDSWITCH;           }
endwhile            { return romp::parser::token::ENDWHILE;            }
enum                { return romp::parser::token::ENUM;                }
error               { return romp::parser::token::ERROR;               }
exists              { return romp::parser::token::EXISTS;              }
for                 { return romp::parser::token::FOR;                 }
ismember            { return romp::parser::token::ISMEMBER;            }
forall              { return romp::parser::token::FORALL;              }
function            { return romp::parser::token::FUNCTION;            }
if                  { return romp::parser::token::IF;                  }
invariant           { return romp::parser::token::INVARIANT;           }
liveness            { return romp::parser::token::LIVENESS;            }
isundefined         { return romp::parser::token::ISUNDEFINED;         }
multiset            { return romp::parser::token::MULTISET;            }
multisetadd         { return romp::parser::token::MULTISETADD;         }
multisetcount       { return romp::parser::token::MULTISETCOUNT;       }
multisetremove      { return romp::parser::token::MULTISETREMOVE;      }
multisetremovepred  { return romp::parser::token::MULTISETREMOVEPRED;  }
of                  { return romp::parser::token::OF;                  }
procedure           { return romp::parser::token::PROCEDURE;           }
put                 { return romp::parser::token::PUT;                 }
real                { throw romp::Error("real types are not supported", *loc); }
record              { return romp::parser::token::RECORD;              }
return              { return romp::parser::token::RETURN;              }
rule                { return romp::parser::token::RULE;                }
ruleset             { return romp::parser::token::RULESET;             }
scalarset           { return romp::parser::token::SCALARSET;           }
startstate          { return romp::parser::token::STARTSTATE;          }
switch              { return romp::parser::token::SWITCH;              }
then                { return romp::parser::token::THEN;                }
to                  { return romp::parser::token::TO;                  }
type                { return romp::parser::token::TYPE;                }
undefine            { return romp::parser::token::UNDEFINE;            }
union               { return romp::parser::token::UNION;               }
while               { return romp::parser::token::WHILE;               }
var                 { return romp::parser::token::VAR;                 }

"∃"                 { return romp::parser::token::EXISTS;              }
"∀"                 { return romp::parser::token::FORALL;              }

  /* Recognise true and false explicitly rather than as generic IDs (below). The
   * purpose of this is so that we match them case-insensitively.
   */
false {
  lval->build<std::string>("false");
  return romp::parser::token::ID;
}
true {
  lval->build<std::string>("true");
  return romp::parser::token::ID;
}

[[:alpha:]][_[:alnum:]]* {
  lval->build<std::string>(YYText());
  return romp::parser::token::ID;
}

"--" {
  BEGIN(SC_COMMENT);
}

"/*" {
  BEGIN(SC_MULTILINE_COMMENT);
}

":=" { return romp::parser::token::COLON_EQ;  }
"≔"  { return romp::parser::token::COLON_EQ;  }
".." { return romp::parser::token::DOTDOT;    }
">=" { return romp::parser::token::GEQ;       }
"≥"  { return romp::parser::token::GEQ;       }
">>" { return romp::parser::token::RSH;       }
"->" { return romp::parser::token::IMPLIES;   }
"→"  { return romp::parser::token::IMPLIES;   }
"<=" { return romp::parser::token::LEQ;       }
"≤"  { return romp::parser::token::LEQ;       }
"<<" { return romp::parser::token::LSH;       }
"!=" { return romp::parser::token::NEQ;       }
"≠"  { return romp::parser::token::NEQ;       }
"==>" { return romp::parser::token::ARROW;    }
"⇒"  { return romp::parser::token::ARROW;    }
"==" { return romp::parser::token::DEQ;       }
"¬"  { return '!';                             }
"∧"  { return romp::parser::token::LAND;      }
"∨"  { return romp::parser::token::LOR;       }
"&&" { return romp::parser::token::AMPAMP;    }
"||" { return romp::parser::token::PIPEPIPE;  }

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

  return romp::parser::token::STRING;
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
  throw romp::Error(std::string("unexpected character: '") + YYText() + "'", *loc);
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
