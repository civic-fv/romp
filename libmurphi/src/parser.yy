%skeleton "lalr1.cc"
%require "3.0"

  /* Ordinarily, Bison emits the parser in a namespace "yy". By changing the
   * namespace our parser can coexist with other Bison-generated parsers if
   * necessary.
   */
%define api.namespace {murphi}

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
  #include <functional>
  #include <murphi/Decl.h>
  #include <murphi/Model.h>
  #include <murphi/Node.h>
  #include <murphi/Number.h>
  #include <murphi/Ptr.h>
  #include <murphi/Rule.h>
  #include <murphi/Stmt.h>
  #include <murphi/parse_helpers.h>

  /* Forward declare the scanner class that Flex will produce for us. */
  namespace murphi {
    class scanner;

    /**
     * @brief Serves the same as \c murphi::IdHandler , but what the parser will actually use.
     *        \c murphi::IdHandler is the outward facing version of this used in calls to the parser function.
     *        This abstraction allows us to move the generic error handling for an empty \c std::optional to
     *        a single centralized location, instead of spread throwout the bison parser definition file.
     */
    typedef std::function<std::string(std::string, const IdType, const location&)> _parser_IdHandler;

  } // namespace murphi
}

  /* Code that we need in the implementation, but in no particular location.
   */
%code {

  #include <algorithm>
  #include <cassert>
  #include <gmpxx.h>
  #include <iostream>
  #include <iterator>
  #include <murphi/except.h>
  #include <murphi/parse.h>
  #include <tuple>
  #include <utility>
  #include <vector>

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

  #include <murphi/scanner.h>

}

  /* Tell Bison that the parser receives a reference to an instance of our
   * scanner class, in order to use our redirected yylex defined above.
   */
%parse-param { scanner &sc }

  /* Tell Bison we'll receive another parameter that will allow us to pass
   * back the result of parsing.
   */
%parse-param { murphi::Ptr<murphi::Model> &output }

  /* Tell Bison we'll receive another parameter that will allow us to pass
   * check ID's.
   */
%parse-param { const murphi::_parser_IdHandler &id_handler }

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
%token UNION /* added to give full support to scalarset Unions in MURPHI (not murphi) */
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

%type <murphi::Ptr<murphi::AliasRule>>                          aliasrule
%type <std::shared_ptr<murphi::Property::Category>>           category
%type <murphi::Ptr<murphi::ChooseRule>>                         chooserule
%type <std::vector<murphi::Ptr<murphi::Decl>>>                  decl
%type <std::vector<murphi::Ptr<murphi::Decl>>>                  decls
%type <std::vector<murphi::Ptr<murphi::Decl>>>                  decls_header
%type <murphi::Ptr<murphi::Expr>>                               designator
%type <std::vector<murphi::IfClause>>                         else_opt
%type <std::vector<murphi::IfClause>>                         elsifs
%type <murphi::Ptr<murphi::Expr>>                               expr
%type <std::vector<std::tuple<std::string, murphi::Ptr<murphi::Expr>, murphi::location>>> exprdecl
%type <std::vector<std::tuple<std::string, murphi::Ptr<murphi::Expr>, murphi::location>>> exprdecls
%type <std::vector<murphi::Ptr<murphi::Expr>>>                  exprlist
%type <std::vector<murphi::Ptr<murphi::Expr>>>                  exprlist_cont
%type <murphi::Ptr<murphi::Expr>>                               guard_opt
%type <std::vector<std::pair<std::string, murphi::location>>> id_list
%type <std::vector<std::pair<std::string, murphi::location>>> id_list_opt
%type <std::shared_ptr<murphi::MultisetQuantifier>>           multisetquantifier
%type <std::vector<murphi::MultisetQuantifier>>               multisetquantifiers
%type <std::vector<murphi::Ptr<murphi::Node>>>                  nodes
%type <std::vector<murphi::Ptr<murphi::VarDecl>>>               parameter
%type <std::vector<murphi::Ptr<murphi::VarDecl>>>               parameters
%type <murphi::Ptr<murphi::Function>>                           procdecl
%type <murphi::Ptr<murphi::PropertyRule>>                       property
%type <std::shared_ptr<murphi::Quantifier>>                   quantifier
%type <std::vector<murphi::Quantifier>>                       quantifiers
%type <murphi::Ptr<murphi::TypeExpr>>                           return_type
%type <std::vector<murphi::Ptr<murphi::VarDecl>>>               record_member
%type <std::vector<murphi::Ptr<murphi::VarDecl>>>               record_members
%type <murphi::Ptr<murphi::Rule>>                               rule
%type <murphi::Ptr<murphi::Ruleset>>                            ruleset
%type <std::vector<murphi::Ptr<murphi::Rule>>>                  rules
%type <murphi::Ptr<murphi::SimpleRule>>                         simplerule
%type <murphi::Ptr<murphi::StartState>>                         startstate
%type <murphi::Ptr<murphi::Stmt>>                               stmt
%type <std::vector<murphi::Ptr<murphi::Stmt>>>                  stmts
%type <std::vector<murphi::Ptr<murphi::Stmt>>>                  stmts_cont
%type <std::string>                                         string_opt
%type <std::vector<murphi::SwitchCase>>                       switchcases
%type <std::vector<murphi::SwitchCase>>                       switchcases_cont
%type <std::vector<murphi::Ptr<murphi::Decl>>>                  typedecl
%type <std::vector<murphi::Ptr<murphi::Decl>>>                  typedecls
%type <murphi::Ptr<murphi::TypeExpr>>                           typeexpr
%type <std::vector<murphi::Ptr<murphi::TypeExpr>>>              union_list
%type <murphi::Ptr<murphi::TypeExpr>>                           union_list_item
%type <std::vector<murphi::Ptr<murphi::VarDecl>>>               vardecl
%type <std::vector<murphi::Ptr<murphi::VarDecl>>>               vardecls
%type <std::shared_ptr<bool>>                               var_opt

%%

model: nodes {
  output = murphi::Ptr<murphi::Model>::make($1, @$);
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
  std::vector<murphi::Ptr<murphi::AliasDecl>> decls;
  for (const std::tuple<std::string, murphi::Ptr<murphi::Expr>, murphi::location> &d : $2) {
    decls.push_back(murphi::Ptr<murphi::AliasDecl>::make(id_handler(std::get<0>(d), murphi::ALIAS_NAME, std::get<2>(d)), 
                                                     std::get<1>(d), std::get<2>(d)));
  }
  $$ = murphi::Ptr<murphi::AliasRule>::make(decls, $4, @$);
};

begin_opt: BEGIN_TOK | %empty;

category: ASSERT {
  $$ = std::make_shared<murphi::Property::Category>(murphi::Property::ASSERTION);
} | ASSUME {
  $$ = std::make_shared<murphi::Property::Category>(murphi::Property::ASSUMPTION);
} | COVER {
  $$ = std::make_shared<murphi::Property::Category>(murphi::Property::COVER);
} | INVARIANT {
  $$ = std::make_shared<murphi::Property::Category>(murphi::Property::ASSERTION);
} | LIVENESS {
  $$ = std::make_shared<murphi::Property::Category>(murphi::Property::LIVENESS);
};

comma_opt: ',' | %empty;

decl: CONST exprdecls {
  for (const std::tuple<std::string, murphi::Ptr<murphi::Expr>, murphi::location> &d : $2) {
    $$.push_back(murphi::Ptr<murphi::ConstDecl>::make(id_handler(std::get<0>(d),murphi::CONST_NAME,std::get<2>(d)), 
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
  $$ = murphi::Ptr<murphi::Field>::make($1, $3, @$);
} | designator '[' expr ']' {
  $$ = murphi::Ptr<murphi::Element>::make($1, $3, @$);
} | ID {
  $$ = murphi::Ptr<murphi::ExprID>::make($1, nullptr, @$);
};

multisetquantifier: ID ':' designator {
  $$ = std::make_shared<murphi::MultisetQuantifier>(id_handler($1,murphi::QUANTIFIER_NAME,@1), $3, @$);
};

multisetquantifiers: multisetquantifiers semis multisetquantifier {
  $$ = $1;
  $$.push_back(*$3);
} | multisetquantifier {
  $$.push_back(*$1);
};

else_opt: ELSE stmts {
  $$.push_back(murphi::IfClause(nullptr, $2, @$));
} | %empty {
};

elsifs: elsifs ELSIF expr THEN stmts {
  $$ = $1;
  $$.push_back(murphi::IfClause($3, $5, murphi::location(@2.begin, @5.end)));
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
  $$ = murphi::Ptr<murphi::Ternary>::make($1, $3, $5, @$);
} | expr IMPLIES expr {
  $$ = murphi::Ptr<murphi::Implication>::make($1, $3, @$);
} | expr PIPEPIPE expr {
  $$ = murphi::Ptr<murphi::Or>::make($1, $3, @$);
} | expr LOR expr {
  $$ = murphi::Ptr<murphi::Or>::make($1, $3, @$);
} | expr AMPAMP expr {
  $$ = murphi::Ptr<murphi::And>::make($1, $3, @$);
} | expr LAND expr {
  $$ = murphi::Ptr<murphi::And>::make($1, $3, @$);
} | expr '|' expr {
  /* construct this as an ambiguous expression, that will later be resolved into
   * an Or or a Bor
   */
  $$ = murphi::Ptr<murphi::AmbiguousPipe>::make($1, $3, @$);
} | expr '^' expr {
  $$ = murphi::Ptr<murphi::Xor>::make($1, $3, @$);
} | expr '&' expr {
  /* construct this as an ambiguous expression, that will later be resolved into
   * an And or a Band
   */
  $$ = murphi::Ptr<murphi::AmbiguousAmp>::make($1, $3, @$);
} | '!' expr {
  $$ = murphi::Ptr<murphi::Not>::make($2, @$);
} | '~' expr {
  $$ = murphi::Ptr<murphi::Bnot>::make($2, @$);
} | expr '<' expr {
  $$ = murphi::Ptr<murphi::Lt>::make($1, $3, @$);
} | expr LEQ expr {
  $$ = murphi::Ptr<murphi::Leq>::make($1, $3, @$);
} | expr '>' expr {
  $$ = murphi::Ptr<murphi::Gt>::make($1, $3, @$);
} | expr GEQ expr {
  $$ = murphi::Ptr<murphi::Geq>::make($1, $3, @$);
} | expr DEQ expr {
  $$ = murphi::Ptr<murphi::Eq>::make($1, $3, @$);
} | expr '=' expr {
  $$ = murphi::Ptr<murphi::Eq>::make($1, $3, @$);
} | expr NEQ expr {
  $$ = murphi::Ptr<murphi::Neq>::make($1, $3, @$);
} | expr LSH expr {
  $$ = murphi::Ptr<murphi::Lsh>::make($1, $3, @$);
} | expr RSH expr {
  $$ = murphi::Ptr<murphi::Rsh>::make($1, $3, @$);
} | expr '+' expr {
  $$ = murphi::Ptr<murphi::Add>::make($1, $3, @$);
} | expr '-' expr {
  $$ = murphi::Ptr<murphi::Sub>::make($1, $3, @$);
} | '+' expr %prec '*' {
  $$ = $2;
  $$->loc = @$;
} | '-' expr %prec '*' {
  $$ = murphi::Ptr<murphi::Negative>::make($2, @$);
} | expr '*' expr {
  $$ = murphi::Ptr<murphi::Mul>::make($1, $3, @$);
} | expr '/' expr {
  $$ = murphi::Ptr<murphi::Div>::make($1, $3, @$);
} | expr '%' expr {
  $$ = murphi::Ptr<murphi::Mod>::make($1, $3, @$);
} | FORALL quantifier DO expr endforall {
    $$ = murphi::Ptr<murphi::Forall>::make(*$2, $4, @$);
} | EXISTS quantifier DO expr endexists {
    $$ = murphi::Ptr<murphi::Exists>::make(*$2, $4, @$);
} | designator {
  $$ = $1;
} | NUMBER {
  $$ = murphi::Ptr<murphi::Number>::make($1, @$);
} | '(' expr ')' {
  $$ = $2;
  $$->loc = @$;
} | ID '(' exprlist ')' {
  $$ = murphi::Ptr<murphi::FunctionCall>::make($1, $3, @$);
} | ISUNDEFINED '(' designator ')' {
  $$ = murphi::Ptr<murphi::IsUndefined>::make($3, @$);
// extended expr ...
} | ISMEMBER '(' designator ',' typeexpr ')' {
  $$ = murphi::Ptr<murphi::IsMember>::make($3, $5, @$);
} | MULTISETCOUNT '(' multisetquantifier ',' expr ')' {
  $$ = murphi::Ptr<murphi::MultisetCount>::make(*$3, $5, @$);
};

exprdecl: id_list_opt ':' expr {
  for (const std::pair<std::string, murphi::location> &m : $1) {
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
  for (const std::pair<std::string, murphi::location> &i : $2) {
    auto v = murphi::Ptr<murphi::VarDecl>::make(id_handler(i.first, murphi::FUNCT_PARAM_NAME, i.second), $4, @$);
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
  // std::transform($4.begin(), $4.end(), 
  //               [&](murphi::Ptr<murphi::VarDecl> v) -> murphi::Ptr<murphi::VarDecl> {
  //                 v->name = id_handler(v->name, murphi::FUNCT_PARAM_NAME, v->loc);
  //                 return v;
  //               });
  $$ = murphi::Ptr<murphi::Function>::make(id_handler($2, murphi::FUNCTION_NAME, @2), $4, $6, $7, $9, @$);
};

property: category STRING expr {
  $$ = murphi::Ptr<murphi::PropertyRule>::make(id_handler($2, murphi::PROPERTY_RULE_NAME, @2), 
                                           murphi::Property(*$1, $3, @3), @$);
} | category expr string_opt {
  ;
  $$ = murphi::Ptr<murphi::PropertyRule>::make((($3!="") ? id_handler($3, murphi::PROPERTY_RULE_NAME, @3) : ""), 
                                            murphi::Property(*$1, $2, @2), @$);
};

quantifier: ID ':' typeexpr {
  $$ = std::make_shared<murphi::Quantifier>(id_handler($1,murphi::QUANTIFIER_NAME,@1), $3, @$);
} | ID COLON_EQ expr TO expr BY expr {
  $$ = std::make_shared<murphi::Quantifier>(id_handler($1,murphi::QUANTIFIER_NAME,@1), $3, $5, $7, @$);
} | ID COLON_EQ expr TO expr {
  $$ = std::make_shared<murphi::Quantifier>(id_handler($1,murphi::QUANTIFIER_NAME,@1), $3, $5, @$);
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
  $$ = murphi::Ptr<murphi::Ruleset>::make($2, $4, @$);
};

semi_opt: semi_opt ';' | %empty;

semis: semi_opt ';';

simplerule: RULE string_opt guard_opt decls_header stmts endrule {
  $$ = murphi::Ptr<murphi::SimpleRule>::make((($2!="") ? id_handler($2, murphi::RULE_NAME, @2) : ""), 
                                         $3, $4, $5, @$);
};

startstate: STARTSTATE string_opt decls_header stmts endstartstate {
  $$ = murphi::Ptr<murphi::StartState>::make($2, $3, $4, @$);
};

chooserule: CHOOSE multisetquantifiers DO rules endchoose {
  $$ = murphi::Ptr<murphi::ChooseRule>::make($2, $4, @$);
};

stmt: category STRING expr {
  murphi::Property p(*$1, $3, @3);
  $$ = murphi::Ptr<murphi::PropertyStmt>::make(p, id_handler($2, murphi::PROPERTY_STMT_NAME, @2), @$);
} | category expr string_opt {
  murphi::Property p(*$1, $2, @2);
  $$ = murphi::Ptr<murphi::PropertyStmt>::make(p, 
                                           (($3!="") ? id_handler($3, murphi::PROPERTY_STMT_NAME, @3) : ""),
                                           @$);
} | designator COLON_EQ expr {
  $$ = murphi::Ptr<murphi::Assignment>::make($1, $3, @$);
} | ALIAS exprdecls DO stmts endalias {
  std::vector<murphi::Ptr<murphi::AliasDecl>> decls;
  for (const std::tuple<std::string, murphi::Ptr<murphi::Expr>, murphi::location> &d : $2) {
    decls.push_back(murphi::Ptr<murphi::AliasDecl>::make(id_handler(std::get<0>(d), murphi::ALIAS_NAME, std::get<2>(d)), 
                                                                std::get<1>(d), std::get<2>(d)));
  }
  $$ = murphi::Ptr<murphi::AliasStmt>::make(decls, $4, @$);
} | ERROR STRING {
  $$ = murphi::Ptr<murphi::ErrorStmt>::make(id_handler($2,murphi::ERROR_STMT_NAME, @2), @$);
} | CLEAR designator {
  $$ = murphi::Ptr<murphi::Clear>::make($2, @$);
} | FOR quantifier DO stmts endfor {
  $$ = murphi::Ptr<murphi::For>::make(*$2, $4, @$);
} | IF expr THEN stmts elsifs else_opt endif {
  std::vector<murphi::IfClause> cs = {
    murphi::IfClause($2, $4, murphi::location(@1.begin, @4.end)) };
  cs.insert(cs.end(), $5.begin(), $5.end());
  cs.insert(cs.end(), $6.begin(), $6.end());
  $$ = murphi::Ptr<murphi::If>::make(cs, @$);
} | PUT STRING {
  $$ = murphi::Ptr<murphi::Put>::make($2, @$);
} | PUT expr {
  $$ = murphi::Ptr<murphi::Put>::make($2, @$);
} | RETURN {
  $$ = murphi::Ptr<murphi::Return>::make(nullptr, @$);
} | RETURN expr {
  $$ = murphi::Ptr<murphi::Return>::make($2, @$);
} | UNDEFINE designator {
  $$ = murphi::Ptr<murphi::Undefine>::make($2, @$);
} | ID '(' exprlist ')' {
  $$ = murphi::Ptr<murphi::ProcedureCall>::make($1, $3, @$);
} | WHILE expr DO stmts endwhile {
  $$ = murphi::Ptr<murphi::While>::make($2, $4, @$);
} | SWITCH expr switchcases endswitch {
  $$ = murphi::Ptr<murphi::Switch>::make($2, $3, @$);
// extended statements
} | MULTISETADD '(' expr ',' designator ')' {
  $$ = murphi::Ptr<murphi::MultisetAdd>::make($3, $5, @$);
} | MULTISETREMOVE '(' expr ',' designator ')' {
  $$ = murphi::Ptr<murphi::MultisetRemove>::make($3, $5, @$);
} | MULTISETREMOVEPRED '(' multisetquantifier ',' expr ')' {
  $$ = murphi::Ptr<murphi::MultisetRemovePred>::make(*$3, $5, @$);
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
  $$.push_back(murphi::SwitchCase(std::vector<Ptr<murphi::Expr>>(), $3, @$));
} | switchcases_cont {
  $$ = $1;
};

switchcases_cont: switchcases_cont CASE exprlist ':' stmts {
  $$ = $1;
  $$.push_back(murphi::SwitchCase($3, $5, @$));
} | %empty {
  /* nothing required */
};

typedecl: id_list_opt ':' typeexpr {
  for (const std::pair<std::string, murphi::location> &m : $1) {
    $$.push_back(murphi::Ptr<murphi::TypeDecl>::make(id_handler(m.first, murphi::TYPE_NAME, m.second), $3, @$));
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
  $$ = murphi::Ptr<murphi::TypeExprID>::make($1, nullptr, @$);
} | ENUM '{' id_list_opt '}' {
  $$ = murphi::Ptr<murphi::Enum>::make($3, @$);
};

/* addition of optional union list */
union_list: union_list ',' union_list_item {
  $$ = $1;
  $$.emplace_back($3);
} | union_list_item ',' union_list_item { /* at least 2 is required */
  $$ = std::vector<murphi::Ptr<murphi::TypeExpr>>{$1,$3};
} | %empty {
  /* do nothing and check size later */ 
};

typeexpr: BOOLEAN {
  /* We need to special case this instead of just using the ID rule because IDs
   * are treated as case-sensitive while "boolean" is not. To avoid awkwardness
   * in later symbol resolution, we force it to lower case here.
   */
  $$ = murphi::Ptr<murphi::TypeExprID>::make("boolean", nullptr, @$);
} | ID {
  $$ = murphi::Ptr<murphi::TypeExprID>::make($1, nullptr, @$);
} | expr DOTDOT expr {
  $$ = murphi::Ptr<murphi::Range>::make($1, $3, @$);
} | ENUM '{' id_list_opt '}' {
  std::transform($3.begin(), $3.end(), $3.begin(),
                [&](std::pair<std::string,murphi::location> v) -> std::pair<std::string,murphi::location> {
                  return std::make_pair(id_handler(v.first, murphi::ENUM_NAME, v.second), v.second);
                });
  $$ = murphi::Ptr<murphi::Enum>::make($3, @$);
} | RECORD record_members endrecord {
  $$ = murphi::Ptr<murphi::Record>::make($2, @$);
} | ARRAY '[' typeexpr ']' OF typeexpr {
  $$ = murphi::Ptr<murphi::Array>::make($3, $6, @$);
} | SCALARSET '(' expr ')' {
  $$ = murphi::Ptr<murphi::Scalarset>::make($3, @$);
// extended types ...
} | UNION '{' union_list '}' {
  $$ = murphi::Ptr<murphi::ScalarsetUnion>::make($3,@$);
} | MULTISET '[' expr ']' OF typeexpr {
  $$ = murphi::Ptr<murphi::Multiset>::make($3, $6, @$);
};

vardecl: id_list_opt ':' typeexpr {
  for (const std::pair<std::string, murphi::location> &m : $1) {
    $$.push_back(murphi::Ptr<murphi::VarDecl>::make(id_handler(m.first, murphi::VARIABLE_NAME, m.second), $3, @$));
  }
};

vardecls: vardecls vardecl semi_opt {
  $$ = $1;
  std::move($2.begin(), $2.end(), std::back_inserter($$));
} | %empty {
  /* nothing required */
};

record_member: id_list_opt ':' typeexpr {
  for (const std::pair<std::string, murphi::location> &m : $1) {
    $$.push_back(murphi::Ptr<murphi::VarDecl>::make(id_handler(m.first, murphi::REC_MEMBER_NAME, m.second), $3, @$));
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

void murphi::parser::error(const location_type &loc, const std::string &message) {
  throw Error(message, loc);
}
