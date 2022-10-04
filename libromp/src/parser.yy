%skeleton "lalr1.cc"
%require "3.0"

  /* Ordinarily, Bison emits the parser in a namespace "yy". By changing the
   * namespace our parser can coexist with other Bison-generated parsers if
   * necessary.
   */
%define api.namespace {romp}

  /* Make yylval, the semantic type of the current token, a variant. The
   * purpose of this is to allow us to return richer information about the
   * contents of a token or expression.
   */
%define api.value.type variant

  /* Enable more explanatory error messages. Without this, Bison just says
   * "syntax error" for any problem. The extra information can sometimes be
   * inaccurate unless you define "parse.lac full" which is not available for
   * C++, but even a slightly inaccurate message is typically more useful to the
   * user than "syntax error".
   */
%define parse.error verbose

  /* Turn on some safety checks for construction and destruction of variant
   * types. This is only relevant if we enable them (api.value.type variant).
   */
%define parse.assert

  /* Receive source location from the scanner. This allows us to give proper
   * feedback on user errors, pointing them at the line and column where they
   * went wrong.
   */
%locations

  /* Code that we need before anything in both the implementation
   * (parser.yy.cc) and the header (parser.yy.hh).
   */
%code requires {

  #include <cstddef>
  #include <memory>
  #include <romp/Decl.h>
  #include <romp/Model.h>
  #include <romp/Node.h>
  #include <romp/Number.h>
  #include <romp/Ptr.h>
  #include <romp/Rule.h>
  #include <romp/Stmt.h>
  #include <romp/parse_helpers.h>

  /* Forward declare the scanner class that Flex will produce for us. */
  namespace romp {
    class scanner;
  }

}

  /* Code that we need in the implementation, but in no particular location.
   */
%code {

  #include <algorithm>
  #include <cassert>
  #include <gmpxx.h>
  #include <iostream>
  #include <iterator>
  #include <romp/except.h>
  #include <romp/parse.h>
  #include <tuple>
  #include <utility>
  #include <vector>
  #include <functional>

  /* Redirect yylex to call our derived scanner. */
  #ifdef yylex
    #undef yylex
  #endif
  #define yylex sc.yylex

}

  /* Code that we need to include at the top of the implementation
   * (parser.yy.cc) but not in the header. Including this code in the header
   * (parser.yy.hh) would induce a circular include.
   */
%code top {

  #include <romp/scanner.h>

}

  /* Tell Bison that the parser receives a reference to an instance of our
   * scanner class, in order to use our redirected yylex defined above.
   */
%parse-param { scanner &sc }

  /* Tell Bison we'll receive another parameter that will allow us to pass
   * back the result of parsing.
   */
%parse-param { romp::Ptr<romp::Model> &output }

  /* Tell Bison we'll receive another parameter that will allow us to pass
   * check ID's.
   */
%parse-param { std::function<std::string(const std::string&, const IdType, const location&)> &id_handler }

%token ALIAS
%token AMPAMP "&&"
%token ARRAY
%token ARROW
%token ASSERT
%token ASSUME
%token BEGIN_TOK
%token BOOLEAN
%token BY
%token CASE
%token CHOOSE
%token CLEAR
%token COLON_EQ ":="
%token CONST
%token COVER
%token DEQ "=="
%token DO
%token DOTDOT ".."
%token ELSE
%token ELSIF
%token END
%token ENDALIAS
%token ENDCHOOSE
%token ENDEXISTS
%token ENDFOR
%token ENDFORALL
%token ENDFUNCTION
%token ENDIF
%token ENDPROCEDURE
%token ENDRECORD
%token ENDRULE
%token ENDRULESET
%token ENDSTARTSTATE
%token ENDSWITCH
%token ENDWHILE
%token ENUM
%token ERROR
%token EXISTS
%token FOR
%token FORALL
%token FUNCTION
%token GEQ ">="
%token <std::string> ID
%token IF
%token IMPLIES "->"
%token INVARIANT
%token ISMEMBER
%token ISUNDEFINED
%token LAND "∧"
%token LEQ "<="
%token LIVENESS
%token LOR "∨"
%token LSH "<<"
%token MULTISET
%token MULTISETADD
%token MULTISETCOUNT
%token MULTISETREMOVE
%token MULTISETREMOVEPRED
%token NEQ "!="
%token <std::string> NUMBER
%token OF
%token PIPEPIPE "||"
%token PROCEDURE
%token PUT
/* %token REAL */
%token RECORD
%token RETURN
%token RSH ">>"
%token RULE
%token RULESET
%token SCALARSET
%token STARTSTATE
%token <std::string> STRING
%token SWITCH
%token THEN
%token TO
%token TYPE
%token UNDEFINE
%token UNION /* added to give full support to scalarset Unions in ROMP (not romp) */
%token VAR
%token WHILE

%nonassoc '?' ':'
%nonassoc IMPLIES
%left PIPEPIPE LOR
%left AMPAMP LAND
%left '|'
%left '^'
%left '&'
%precedence '!'
%nonassoc '<' LEQ DEQ '=' NEQ GEQ '>'
%left LSH RSH
%left '+' '-'
%left '*' '/' '%'
%precedence '~'

%type <romp::Ptr<romp::AliasRule>>                          aliasrule
%type <std::shared_ptr<romp::Property::Category>>           category
%type <romp::Ptr<romp::ChooseRule>>                         chooserule
%type <std::vector<romp::Ptr<romp::Decl>>>                  decl
%type <std::vector<romp::Ptr<romp::Decl>>>                  decls
%type <std::vector<romp::Ptr<romp::Decl>>>                  decls_header
%type <romp::Ptr<romp::Expr>>                               designator
%type <std::vector<romp::IfClause>>                         else_opt
%type <std::vector<romp::IfClause>>                         elsifs
%type <romp::Ptr<romp::Expr>>                               expr
%type <std::vector<std::tuple<std::string, romp::Ptr<romp::Expr>, romp::location>>> exprdecl
%type <std::vector<std::tuple<std::string, romp::Ptr<romp::Expr>, romp::location>>> exprdecls
%type <std::vector<romp::Ptr<romp::Expr>>>                  exprlist
%type <std::vector<romp::Ptr<romp::Expr>>>                  exprlist_cont
%type <romp::Ptr<romp::Expr>>                               guard_opt
%type <std::vector<std::pair<std::string, romp::location>>> id_list
%type <std::vector<std::pair<std::string, romp::location>>> id_list_opt
%type <std::shared_ptr<romp::MultisetQuantifier>>           multisetquantifier
%type <std::vector<romp::MultisetQuantifier>>               multisetquantifiers
%type <std::vector<romp::Ptr<romp::Node>>>                  nodes
%type <std::vector<romp::Ptr<romp::VarDecl>>>               parameter
%type <std::vector<romp::Ptr<romp::VarDecl>>>               parameters
%type <romp::Ptr<romp::Function>>                           procdecl
%type <romp::Ptr<romp::PropertyRule>>                       property
%type <std::shared_ptr<romp::Quantifier>>                   quantifier
%type <std::vector<romp::Quantifier>>                       quantifiers
%type <romp::Ptr<romp::TypeExpr>>                           return_type
%type <romp::Ptr<romp::VarDecl>>                            record_member
%type <std::vector<romp::Ptr<romp::VarDecl>>>               record_members
%type <romp::Ptr<romp::Rule>>                               rule
%type <romp::Ptr<romp::Ruleset>>                            ruleset
%type <std::vector<romp::Ptr<romp::Rule>>>                  rules
%type <romp::Ptr<romp::SimpleRule>>                         simplerule
%type <romp::Ptr<romp::StartState>>                         startstate
%type <romp::Ptr<romp::Stmt>>                               stmt
%type <std::vector<romp::Ptr<romp::Stmt>>>                  stmts
%type <std::vector<romp::Ptr<romp::Stmt>>>                  stmts_cont
%type <std::string>                                         string_opt
%type <std::vector<romp::SwitchCase>>                       switchcases
%type <std::vector<romp::SwitchCase>>                       switchcases_cont
%type <std::vector<romp::Ptr<romp::Decl>>>                  typedecl
%type <std::vector<romp::Ptr<romp::Decl>>>                  typedecls
%type <romp::Ptr<romp::TypeExpr>>                           typeexpr
%type <std::vector<romp::Ptr<romp::TypeExpr>>>              union_list
%type <romp::Ptr<romp::TypeExpr>>                           union_list_item
%type <std::vector<romp::Ptr<romp::VarDecl>>>               vardecl
%type <std::vector<romp::Ptr<romp::VarDecl>>>               vardecls
%type <std::shared_ptr<bool>>                               var_opt

%%

model: nodes {
  output = romp::Ptr<romp::Model>::make($1, @$);
};

nodes: nodes decl {
  $$ = $1;
  std::move($2.begin(), $2.end(), std::back_inserter($$));
} | nodes procdecl {
  $$ = $1;
  $$.push_back($2);
} | nodes rule semi_opt {
  $$ = $1;
  $$.push_back($2);
} | %empty {
};

aliasrule: ALIAS exprdecls DO rules endalias {
  std::vector<romp::Ptr<romp::AliasDecl>> decls;
  for (const std::tuple<std::string, romp::Ptr<romp::Expr>, romp::location> &d : $2) {
    decls.push_back(romp::Ptr<romp::AliasDecl>::make(id_handler(std::get<0>(d), romp::ALIAS_NAME, std::get<2>(d)), 
                                                     std::get<1>(d), std::get<2>(d)));
  }
  $$ = romp::Ptr<romp::AliasRule>::make(decls, $4, @$);
};

begin_opt: BEGIN_TOK | %empty;

category: ASSERT {
  $$ = std::make_shared<romp::Property::Category>(romp::Property::ASSERTION);
} | ASSUME {
  $$ = std::make_shared<romp::Property::Category>(romp::Property::ASSUMPTION);
} | COVER {
  $$ = std::make_shared<romp::Property::Category>(romp::Property::COVER);
} | INVARIANT {
  $$ = std::make_shared<romp::Property::Category>(romp::Property::ASSERTION);
} | LIVENESS {
  $$ = std::make_shared<romp::Property::Category>(romp::Property::LIVENESS);
};

comma_opt: ',' | %empty;

decl: CONST exprdecls {
  for (const std::tuple<std::string, romp::Ptr<romp::Expr>, romp::location> &d : $2) {
    $$.push_back(romp::Ptr<romp::ConstDecl>::make(id_handler(std::get<0>(d),romp::CONST_NAME,std::get<2>(d)), 
                                                  std::get<1>(d), std::get<2>(d)));
  }
} | TYPE typedecls {
  $$ = $2;
} | VAR vardecls {
  std::move($2.begin(), $2.end(), std::back_inserter($$));
};

decls: decls decl {
  $$ = $1;
  std::move($2.begin(), $2.end(), std::back_inserter($$));
} | %empty {
  /* nothing required */
};

decls_header: decls BEGIN_TOK {
  $$ = $1;
} | %empty {
};

designator: designator '.' ID {
  $$ = romp::Ptr<romp::Field>::make($1, $3, @$);
} | designator '[' expr ']' {
  $$ = romp::Ptr<romp::Element>::make($1, $3, @$);
} | ID {
  $$ = romp::Ptr<romp::ExprID>::make($1, nullptr, @$);
};

multisetquantifier: ID ':' designator {
  $$ = std::make_shared<romp::MultisetQuantifier>(id_handler($1,romp::QUANTIFIER_NAME,@1), $3, @$);
};

multisetquantifiers: multisetquantifiers semis multisetquantifier {
  $$ = $1;
  $$.push_back(*$3);
} | multisetquantifier {
  $$.push_back(*$1);
};

else_opt: ELSE stmts {
  $$.push_back(romp::IfClause(nullptr, $2, @$));
} | %empty {
};

elsifs: elsifs ELSIF expr THEN stmts {
  $$ = $1;
  $$.push_back(romp::IfClause($3, $5, romp::location(@2.begin, @5.end)));
} | %empty {
};

endalias: END | ENDALIAS;
endexists: END | ENDEXISTS;
endfor: END | ENDFOR;
endforall: END | ENDFORALL;
endfunction: END | ENDFUNCTION | ENDPROCEDURE;
endif: END | ENDIF;
endrecord: END | ENDRECORD;
endrule: END | ENDRULE;
endruleset: END | ENDRULESET;
endchoose: END | ENDCHOOSE;
endstartstate: END | ENDSTARTSTATE;
endswitch: END | ENDSWITCH;
endwhile: END | ENDWHILE;

expr: expr '?' expr ':' expr {
  $$ = romp::Ptr<romp::Ternary>::make($1, $3, $5, @$);
} | expr IMPLIES expr {
  $$ = romp::Ptr<romp::Implication>::make($1, $3, @$);
} | expr PIPEPIPE expr {
  $$ = romp::Ptr<romp::Or>::make($1, $3, @$);
} | expr LOR expr {
  $$ = romp::Ptr<romp::Or>::make($1, $3, @$);
} | expr AMPAMP expr {
  $$ = romp::Ptr<romp::And>::make($1, $3, @$);
} | expr LAND expr {
  $$ = romp::Ptr<romp::And>::make($1, $3, @$);
} | expr '|' expr {
  /* construct this as an ambiguous expression, that will later be resolved into
   * an Or or a Bor
   */
  $$ = romp::Ptr<romp::AmbiguousPipe>::make($1, $3, @$);
} | expr '^' expr {
  $$ = romp::Ptr<romp::Xor>::make($1, $3, @$);
} | expr '&' expr {
  /* construct this as an ambiguous expression, that will later be resolved into
   * an And or a Band
   */
  $$ = romp::Ptr<romp::AmbiguousAmp>::make($1, $3, @$);
} | '!' expr {
  $$ = romp::Ptr<romp::Not>::make($2, @$);
} | '~' expr {
  $$ = romp::Ptr<romp::Bnot>::make($2, @$);
} | expr '<' expr {
  $$ = romp::Ptr<romp::Lt>::make($1, $3, @$);
} | expr LEQ expr {
  $$ = romp::Ptr<romp::Leq>::make($1, $3, @$);
} | expr '>' expr {
  $$ = romp::Ptr<romp::Gt>::make($1, $3, @$);
} | expr GEQ expr {
  $$ = romp::Ptr<romp::Geq>::make($1, $3, @$);
} | expr DEQ expr {
  $$ = romp::Ptr<romp::Eq>::make($1, $3, @$);
} | expr '=' expr {
  $$ = romp::Ptr<romp::Eq>::make($1, $3, @$);
} | expr NEQ expr {
  $$ = romp::Ptr<romp::Neq>::make($1, $3, @$);
} | expr LSH expr {
  $$ = romp::Ptr<romp::Lsh>::make($1, $3, @$);
} | expr RSH expr {
  $$ = romp::Ptr<romp::Rsh>::make($1, $3, @$);
} | expr '+' expr {
  $$ = romp::Ptr<romp::Add>::make($1, $3, @$);
} | expr '-' expr {
  $$ = romp::Ptr<romp::Sub>::make($1, $3, @$);
} | '+' expr %prec '*' {
  $$ = $2;
  $$->loc = @$;
} | '-' expr %prec '*' {
  $$ = romp::Ptr<romp::Negative>::make($2, @$);
} | expr '*' expr {
  $$ = romp::Ptr<romp::Mul>::make($1, $3, @$);
} | expr '/' expr {
  $$ = romp::Ptr<romp::Div>::make($1, $3, @$);
} | expr '%' expr {
  $$ = romp::Ptr<romp::Mod>::make($1, $3, @$);
} | FORALL quantifier DO expr endforall {
    $$ = romp::Ptr<romp::Forall>::make(*$2, $4, @$);
} | EXISTS quantifier DO expr endexists {
    $$ = romp::Ptr<romp::Exists>::make(*$2, $4, @$);
} | designator {
  $$ = $1;
} | NUMBER {
  $$ = romp::Ptr<romp::Number>::make($1, @$);
} | '(' expr ')' {
  $$ = $2;
  $$->loc = @$;
} | ID '(' exprlist ')' {
  $$ = romp::Ptr<romp::FunctionCall>::make($1, $3, @$);
} | ISUNDEFINED '(' designator ')' {
  $$ = romp::Ptr<romp::IsUndefined>::make($3, @$);
// extended expr ...
} | ISMEMBER '(' designator ',' typeexpr ')' {
  $$ = romp::Ptr<romp::IsMember>::make($3, $5, @$);
} | MULTISETCOUNT '(' multisetquantifier ',' expr ')' {
  $$ = romp::Ptr<romp::MultisetCount>::make(*$3, $5, @$);
};

exprdecl: id_list_opt ':' expr {
  for (const std::pair<std::string, romp::location> &m : $1) {
    $$.push_back(std::make_tuple(m.first, $3, @$));
  }
};

exprdecls: exprdecls exprdecl semi_opt {
  $$ = $1;
  std::move($2.begin(), $2.end(), std::back_inserter($$));
} | %empty {
  /* nothing required */
};

exprlist: exprlist_cont expr comma_opt {
  $$ = $1;
  $$.push_back($2);
} | %empty {
};

exprlist_cont: exprlist_cont expr ',' {
  $$ = $1;
  $$.push_back($2);
} | %empty {
};

function: FUNCTION | PROCEDURE;

guard_opt: expr ARROW {
  $$ = $1;
} | %empty {
  $$ = nullptr;
};

id_list: id_list ',' ID {
  $$ = $1;
  $$.emplace_back(std::make_pair($3, @3));
} | ID {
  $$.emplace_back(std::make_pair($1, @$));
};

  /* Support optional trailing comma to make it easier for tools that generate
   * an input mdoels.
   */
id_list_opt: id_list comma_opt {
  $$ = $1;
} | %empty {
};

parameter: var_opt id_list ':' typeexpr {
  for (const std::pair<std::string, romp::location> &i : $2) {
    auto v = romp::Ptr<romp::VarDecl>::make(i.first, $4, @$);
    v->readonly = !*$1;
    $$.push_back(v);
  }
};

parameters: parameters parameter semi_opt {
  $$ = $1;
  std::move($2.begin(), $2.end(), std::back_inserter($$));
} | %empty {
};

procdecl: function ID '(' parameters ')' return_type decls begin_opt stmts endfunction semi_opt {
  std::transform($4.begin(), $4.end(), 
                [&](romp::Ptr<romp::VarDecl> v) -> romp::Ptr<romp::VarDecl> {
                  v->name = id_handler(v->name, romp::FUNCT_PARAM_NAME, v->loc);
                  return v;
                });
  $$ = romp::Ptr<romp::Function>::make(id_handler($2, romp::FUNCTION_NAME, @2), $4, $6, $7, $9, @$);
};

property: category STRING expr {
  $$ = romp::Ptr<romp::PropertyRule>::make(id_handler($2, romp::PROPERTY_RULE_NAME, @2), 
                                           romp::Property(*$1, $3, @3), @$);
} | category expr string_opt {
  ;
  $$ = romp::Ptr<romp::PropertyRule>::make((($3!="") ? id_handler($3, romp::PROPERTY_RULE_NAME, @3) : ""), 
                                            romp::Property(*$1, $2, @2), @$);
};

quantifier: ID ':' typeexpr {
  $$ = std::make_shared<romp::Quantifier>(id_handler($1,romp::QUANTIFIER_NAME,@1), $3, @$);
} | ID COLON_EQ expr TO expr BY expr {
  $$ = std::make_shared<romp::Quantifier>(id_handler($1,romp::QUANTIFIER_NAME,@1), $3, $5, $7, @$);
} | ID COLON_EQ expr TO expr {
  $$ = std::make_shared<romp::Quantifier>(id_handler($1,romp::QUANTIFIER_NAME,@1), $3, $5, @$);
};

quantifiers: quantifiers semis quantifier {
  $$ = $1;
  $$.push_back(*$3);
} | quantifier {
  $$.push_back(*$1);
};

return_type: ':' typeexpr semi_opt {
  $$ = $2;
} | semi_opt {
  $$ = nullptr;
};

rule: startstate {
  $$ = $1;
} | simplerule {
  $$ = $1;
} | property {
  $$ = $1;
} | ruleset {
  $$ = $1;
} | aliasrule {
  $$ = $1;
// extended syntax rules
} | chooserule {
  $$ = $1;
};

rules: rules rule semi_opt {
  $$ = $1;
  $$.push_back($2);
} | %empty {
};

ruleset: RULESET quantifiers DO rules endruleset {
  $$ = romp::Ptr<romp::Ruleset>::make($2, $4, @$);
};

semi_opt: semi_opt ';' | %empty;

semis: semi_opt ';';

simplerule: RULE string_opt guard_opt decls_header stmts endrule {
  $$ = romp::Ptr<romp::SimpleRule>::make((($2!="") ? id_handler($2, romp::RULE_NAME, @2) : ""), 
                                         $3, $4, $5, @$);
};

startstate: STARTSTATE string_opt decls_header stmts endstartstate {
  $$ = romp::Ptr<romp::StartState>::make($2, $3, $4, @$);
};

chooserule: CHOOSE multisetquantifiers DO rules endchoose {
  $$ = romp::Ptr<romp::ChooseRule>::make($2, $4, @$);
};

stmt: category STRING expr {
  romp::Property p(*$1, $3, @3);
  $$ = romp::Ptr<romp::PropertyStmt>::make(p, id_handler($2, romp::PROPERTY_STMT_NAME, @2), @$);
} | category expr string_opt {
  romp::Property p(*$1, $2, @2);
  $$ = romp::Ptr<romp::PropertyStmt>::make(p, 
                                           (($3!="") ? id_handler($3, romp::PROPERTY_STMT_NAME, @3) : ""),
                                           @$);
} | designator COLON_EQ expr {
  $$ = romp::Ptr<romp::Assignment>::make($1, $3, @$);
} | ALIAS exprdecls DO stmts endalias {
  std::vector<romp::Ptr<romp::AliasDecl>> decls;
  for (const std::tuple<std::string, romp::Ptr<romp::Expr>, romp::location> &d : $2) {
    decls.push_back(romp::Ptr<romp::AliasDecl>::make(id_handler(std::get<0>(d), romp::ALIAS_NAME, std::get<2>(d)), 
                                                                std::get<1>(d), std::get<2>(d)));
  }
  $$ = romp::Ptr<romp::AliasStmt>::make(decls, $4, @$);
} | ERROR STRING {
  $$ = romp::Ptr<romp::ErrorStmt>::make($2, @$);
} | CLEAR designator {
  $$ = romp::Ptr<romp::Clear>::make($2, @$);
} | FOR quantifier DO stmts endfor {
  $$ = romp::Ptr<romp::For>::make(*$2, $4, @$);
} | IF expr THEN stmts elsifs else_opt endif {
  std::vector<romp::IfClause> cs = {
    romp::IfClause($2, $4, romp::location(@1.begin, @4.end)) };
  cs.insert(cs.end(), $5.begin(), $5.end());
  cs.insert(cs.end(), $6.begin(), $6.end());
  $$ = romp::Ptr<romp::If>::make(cs, @$);
} | PUT STRING {
  $$ = romp::Ptr<romp::Put>::make($2, @$);
} | PUT expr {
  $$ = romp::Ptr<romp::Put>::make($2, @$);
} | RETURN {
  $$ = romp::Ptr<romp::Return>::make(nullptr, @$);
} | RETURN expr {
  $$ = romp::Ptr<romp::Return>::make($2, @$);
} | UNDEFINE designator {
  $$ = romp::Ptr<romp::Undefine>::make($2, @$);
} | ID '(' exprlist ')' {
  $$ = romp::Ptr<romp::ProcedureCall>::make($1, $3, @$);
} | WHILE expr DO stmts endwhile {
  $$ = romp::Ptr<romp::While>::make($2, $4, @$);
} | SWITCH expr switchcases endswitch {
  $$ = romp::Ptr<romp::Switch>::make($2, $3, @$);
// extended statements
} | MULTISETADD '(' expr ',' designator ')' {
  $$ = romp::Ptr<romp::MultisetAdd>::make($3, $5, @$);
} | MULTISETREMOVE '(' expr ',' designator ')' {
  $$ = romp::Ptr<romp::MultisetRemove>::make($3, $5, @$);
} | MULTISETREMOVEPRED '(' multisetquantifier ',' expr ')' {
  $$ = romp::Ptr<romp::MultisetRemovePred>::make(*$3, $5, @$);
};

stmts: stmts_cont stmt semi_opt {
  $$ = $1;
  $$.push_back($2);
} | stmt semi_opt {
  $$.push_back($1);
} | %empty {
};

stmts_cont: stmts_cont stmt semis {
  $$ = $1;
  $$.push_back($2);
} | stmt semis {
  $$.push_back($1);
};

string_opt: STRING {
  $$ = $1;
} | %empty {
  /* nothing required */
};

switchcases: switchcases_cont ELSE stmts {
  $$ = $1;
  $$.push_back(romp::SwitchCase(std::vector<Ptr<romp::Expr>>(), $3, @$));
} | switchcases_cont {
  $$ = $1;
};

switchcases_cont: switchcases_cont CASE exprlist ':' stmts {
  $$ = $1;
  $$.push_back(romp::SwitchCase($3, $5, @$));
} | %empty {
  /* nothing required */
};

typedecl: id_list_opt ':' typeexpr {
  for (const std::pair<std::string, romp::location> &m : $1) {
    $$.push_back(romp::Ptr<romp::TypeDecl>::make(id_handler(m.first, romp::TYPE_NAME, m.second), $3, @$));
  }
};

typedecls: typedecls typedecl semi_opt {
  $$ = $1;
  std::move($2.begin(), $2.end(), std::back_inserter($$));
} | %empty {
  /* nothing required */
};

/* addition of optional union list */
union_list_item: ID {
  $$ = romp::Ptr<romp::TypeExprID>::make($1, nullptr, @$);
} | ENUM '{' id_list_opt '}' {
  $$ = romp::Ptr<romp::Enum>::make($3, @$);
};

/* addition of optional union list */
union_list: union_list ',' union_list_item {
  $$ = $1;
  $$.emplace_back($3);
} | union_list_item ',' union_list_item { /* at least 2 is required */
  $$ = std::vector<romp::Ptr<romp::TypeExpr>>{$1,$3};
} | %empty {
  /* do nothing and check size later */ 
};

typeexpr: BOOLEAN {
  /* We need to special case this instead of just using the ID rule because IDs
   * are treated as case-sensitive while "boolean" is not. To avoid awkwardness
   * in later symbol resolution, we force it to lower case here.
   */
  $$ = romp::Ptr<romp::TypeExprID>::make("boolean", nullptr, @$);
} | ID {
  $$ = romp::Ptr<romp::TypeExprID>::make($1, nullptr, @$);
} | expr DOTDOT expr {
  $$ = romp::Ptr<romp::Range>::make($1, $3, @$);
} | ENUM '{' id_list_opt '}' {
  std::transform($3.begin(), $3.end(), 
                [&](std::pair<std::string,romp::location> v) -> std::pair<std::string,romp::location> {
                  return std::make_pair(id_handler(v.first, romp::ENUM_NAME, v.second), v.second);
                });
  $$ = romp::Ptr<romp::Enum>::make($3, @$);
} | RECORD record_members endrecord {
  $$ = romp::Ptr<romp::Record>::make($2, @$);
} | ARRAY '[' typeexpr ']' OF typeexpr {
  $$ = romp::Ptr<romp::Array>::make($3, $6, @$);
} | SCALARSET '(' expr ')' {
  $$ = romp::Ptr<romp::Scalarset>::make($3, @$);
// extended types ...
} | UNION '{' union_list '}' {
  $$ = romp::Ptr<romp::ScalarsetUnion>::make($3,@$);
} | MULTISET '[' expr ']' OF typeexpr {
  $$ = romp::Ptr<romp::Multiset>::make($3, $6, @$);
};

vardecl: id_list_opt ':' typeexpr {
  for (const std::pair<std::string, romp::location> &m : $1) {
    $$.push_back(romp::Ptr<romp::VarDecl>::make(id_handler(m.first, romp::VARIABLE_NAME, m.second), $3, @$));
  }
};

vardecls: vardecls vardecl semi_opt {
  $$ = $1;
  std::move($2.begin(), $2.end(), std::back_inserter($$));
} | %empty {
  /* nothing required */
};

record_member: id_list_opt ':' typeexpr {
  for (const std::pair<std::string, romp::location> &m : $1) {
    $$.push_back(romp::Ptr<romp::VarDecl>::make(id_handler(m.first, romp::REC_MEMBER_NAME, m.second), $3, @$));
  }
};

record_members: record_members record_member semi_opt {
  $$ = $1;
  std::move($2.begin(), $2.end(), std::back_inserter($$));
} | %empty {
  /* nothing required */
};

var_opt: VAR {
  $$ = std::make_shared<bool>(true);
} | %empty {
  $$ = std::make_shared<bool>(false);
};

%%

void romp::parser::error(const location_type &loc, const std::string &message) {
  throw Error(message, loc);
}
