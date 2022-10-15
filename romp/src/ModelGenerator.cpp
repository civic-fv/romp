#include "ModelGenerator.h"
#include "../../common/escape.h"
#include "../../common/isa.h"
#include "options.h"
#include <cassert>
#include <cstddef>
#include <ctype.h>
#include <gmpxx.h>
#include <murphi/murphi.h>
#include <string>
#include <utility>
#include <vector>


using namespace murphi;
using namespace romp;

// << ------------------------------------------------------------------------------------------ >> 

void visit_add(const Add &n) {
  *this << "(" << *n.lhs << " + " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_aliasdecl(const AliasDecl &n) {
  *this << "#define " << n.name << "() " << *n.value;
  emit_trailing_comments(n);
  *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_aliasrule(const AliasRule &) {
  // this is unreachable because generate_c is only ever called with a Model
  // and visit_model flattens all rules
  assert(!"unreachable");
  __builtin_unreachable();
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_aliasstmt(const AliasStmt &n) {
  for (const Ptr<AliasDecl> &a : n.aliases) {
    emit_leading_comments(*a);
    *this << *a;
  }
  for (const Ptr<Stmt> &s : n.body) {
    emit_leading_comments(*s);
    *this << *s;
  }
  for (const Ptr<AliasDecl> &a : n.aliases) {
    *this << "#undef " << a->name << "\n";
  }
  if (emit_trailing_comments(n) > 0)
    *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_and(const And &n) {
  *this << "(" << *n.lhs << " && " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_array(const Array &n) {
  //TODO: update visit_array to new standards
  mpz_class count = n.index_type->count();

  assert(count > 0 && "index type of array does not include undefined");
  count--;

  // wrap the array in a struct so that we do not have the awkwardness of
  // having to emit its type and size on either size of another node
  *this << "struct " << (pack ? "__attribute__((packed)) " : "") << "{ "
        << *n.element_type << " data[" << count.get_str() << "];";

  // The index for this array may be an enum declared inline:
  //
  //   array [enum {A, B}] of foo
  //
  // If so, we need to emit it somehow so that the enum’s members can be
  // referenced later. We define it within this struct to avoid any awkward
  // lexical issues.
  if (auto e = dynamic_cast<const Enum *>(n.index_type.get())) {
    *this << " " << *e << ";";
  }

  *this << " }";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_assignment(const Assignment &n) {
  *this << indentation() << *n.lhs << " = " << *n.rhs << ";";
  emit_trailing_comments(n);
  *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_band(const Band &n) {
  *this << "(" << *n.lhs << " & " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_bnot(const Bnot &n) {
  *this << "(~" << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_bor(const Bor &n) {
  *this << "(" << *n.lhs << " | " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_chooserule(const ChooseRule &n) {
  // this is unreachable because generate_c is only ever called with a Model
  // and all rules are flattened during visit_model
  assert(!"unreachable");
  __builtin_unreachable();
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_clear(const Clear &n) {
  //TODO: update visit_clear to new standards
  *this << indentation() << "memset(&" << *n.rhs << ", 0, sizeof(" << *n.rhs
        << "));";
  emit_trailing_comments(n);
  *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_constdecl(const ConstDecl &n) {
  //TODO: update visit_constdecl to new standards
  *this << indentation() << "const ";

  // if this constant has an explicit type, use that
  if (n.type != nullptr) {
    *this << *n.type;

  } else {

    // otherwise, if it was a previously typedefed enum, use its typedefed
    // name (to avoid later -Wsign-compare warnings on GCC)
    const Ptr<TypeExpr> type = n.value->type();
    auto it = enum_typedefs.find(type->unique_id);
    if (it != enum_typedefs.end()) {
      *this << ROMP_SCALAR_ENUM_TYPE;

    } else { // fallback on the type of the right hand side
      *this << "__typeof__(" << *n.value << ")";
    }
  }
  *this << " " << n.name << " = " << *n.value << ";";
  emit_trailing_comments(n);
  *this << "\n";
}


// << ------------------------------------------------------------------------------------------ >> 

void visit_div(const Div &n) {
  *this << "(" << *n.lhs << " / " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_element(const Element &n) {
  //TODO: update visit_element to new standards

  // rather than simply indexing into the array based on the value of the index
  // expression, we need to account for the fact that the generated C array will
  // start from 0 while the Murphi array will start from a custom lower bound

  // find the type of the array expression
  const Ptr<TypeExpr> t = n.array->type()->resolve();
  auto a = dynamic_cast<const Array *>(t.get());
  assert(a != nullptr && "non-array on LHS of array indexing expression");

  // find the lower bound of its index type, using some hacky mangling to align
  // with one of the macros from ../resources/c_prefix.c
  const std::string lb = value_type + "_" + a->index_type->lower_bound();

  // emit an indexing operation, now account for this
  *this << "(" << *n.array << ".data[(" << *n.index << ") - " << lb << "])";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_enum(const Enum &n) {
  //TODO: update visit_enum to new standards
  *this << "enum { ";
  for (const std::pair<std::string, location> &m : n.members) {
    *this << m.first << ", ";
  }
  *this << "}";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_eq(const Eq &n) {

  if (!n.lhs->type()->is_simple()) {
    // This is a comparison of an array or struct. We cannot use the built-in
    // == operator, so we use memcmp. This only works if all members are
    // packed, hence why `__attribute__((pack))` is emitted in other places.
    assert(pack && "comparison of complex types is present but structures "
                   "are not packed");
    *this << "(memcmp(&" << *n.lhs << ", &" << *n.rhs << ", sizeof" << *n.lhs
          << ") == 0)";

    return;
  }

  *this << "(" << *n.lhs << " == " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_errorstmt(const ErrorStmt &n) {
  //TODO: update visit_errorstmt to new standards
  id_t id = next_error_id++;
  *this << indentation() << "if (" ROMP_ERROR_HANDLER(id) ")\n";
  indent();
  *this << indentation() << "throw " ROMP_MAKE_MODEL_ERROR_ERROR(n,id) ";\n";
  dedent();
  emit_trailing_comments(n);
  *this << "\n";
  error_info_list << ROMP_MAKE_ERROR_INFO_STRUCT(n,(inType==FUNCT),to_json(n)) ",";
# ifdef DEBUG
    *this << std::flush;  // flush output more frequently for easier debug
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_exists(const Exists &n) {
  *this << "({ bool res_ = false; " << n.quantifier << " { res_ |= " << *n.expr
        << "; } res_; })";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_exprid(const ExprID &n) {
  *this << "(";
  if (is_pointer.count(n.value->unique_id) > 0) {
    *this << "*";
  }
  *this << n.id;
  // if this refers to an alias, it will have been emitted as a macro
  if (isa<AliasDecl>(n.value)) {
    *this << "()";
  }
  *this << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_field(const Field &n) {
  //TODO: update visit_field to new standards
  *this << "(" << *n.record << "." << n.field << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_for(const For &n) {

  // open a scope to make all of this appear as a single statement to any
  // enclosing code
  *this << indentation() << "do {\n";
  indent();

  // if the type of the quantifier is an enum defined inline, we need to
  // define this in advance because C does not permit this to be defined
  // within the for loop initialiser
  if (auto e = dynamic_cast<const Enum *>(n.quantifier.type.get())) {
    *this << indentation() << *e << ";\n";
  }

  *this << indentation() << n.quantifier << " {\n";
  indent();
  for (const Ptr<Stmt> &s : n.body) {
    emit_leading_comments(*s);
    *this << *s;
  }
  dedent();
  *this << indentation() << "}\n";

  dedent();
  *this << indentation() << "} while (0);";
  emit_trailing_comments(n);
  *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_forall(const Forall &n) {

  // open a GNU statement expression
  *this << "({ ";

  // see corresponding logic in visit_for() for an explanation
  if (auto e = dynamic_cast<const Enum *>(n.quantifier.type.get())) {
    *this << *e << "; ";
  }

  *this << "bool res_ = true; " << n.quantifier << " { res_ &= " << *n.expr
        << "; } res_; })";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_function(const Function &n) {
  //TODO: update visit_function to new standards
  id_t id = next_funct_id++;
  *this << indentation() << CodeGenerator::M_FUNCTION__FUNC_ATTRS << "\n"
        << indentation();
  if (n.return_type == nullptr) {
    *this << "void";
  } else {
    *this << *n.return_type;
  }
  *this << " " << n.name << "(";
  if (n.parameters.empty()) {
    *this << "void";
  } else {
    std::string sep;
    for (const Ptr<VarDecl> &p : n.parameters) {
      *this << sep;
      if (p->readonly)
        *this << "const ";
      *this << *p->type; // << " ";
      // if this is a var parameter, it needs to be a ~~pointer~~ reference
      if (!p->readonly) {
        // (void)is_pointer.insert(p->unique_id);  // no need for pointer shenanigans in C++
        *this << "&"; // "*";
      }
      *this << " " << p->name;
      sep = ", ";
    }
  }
  *this << ") ";
  if (n.is_pure()) *this << "const "; // if function never changes the state mark it as const (allowed in guards and property_rules)
  *this << " " /* "throw (" ROMP_MODEL_EXCEPTION_TYPE ")" */  "{\n";
  indent();
  *this << indentation() << "using namespace ::" ROMP_TYPE_NAMESPACE ";\n";
  
  *this << indentation() << "try {\n";
  indent(); 

  for (const Ptr<Decl> &d : n.decls) {
    emit_leading_comments(*d);
    *this << *d;
  }
  for (const Ptr<Stmt> &s : n.body) {
    emit_leading_comments(*s);
    *this << *s;
  }

  dedent();
  // *this << indentation() << "} catch (...) { ::std::throw_with_nested( " 
  //                       ROMP_MAKE_MODEL_ERROR_FUNCT(n,id) " ); }\n";
  *this << indentation() << "} catch (...) { throw " 
                        ROMP_MAKE_MODEL_ERROR_FUNCT(n,id) "; }\n";

  dedent();
  *this << "}\n";
# ifdef DEBUG
    *this << std::flush;  // flush output more frequently for easier debug
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_functioncall(const FunctionCall &n) {
  *this << n.name << "(";
  assert(n.function != nullptr && "unresolved function call in AST");
  auto it = n.function->parameters.begin();
  bool first = true;
  for (const Ptr<Expr> &a : n.arguments) {
    if (!first) {
      *this << ", ";
    }
    if (!(*it)->readonly) {
      *this << "&";
    }
    *this << *a;
    first = false;
    it++;
  }
  *this << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_geq(const Geq &n) {
  *this << "(" << *n.lhs << " >= " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_gt(const Gt &n) {
  *this << "(" << *n.lhs << " > " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_if(const If &n) {
  bool first = true;
  for (const IfClause &c : n.clauses) {
    if (first) {
      *this << indentation();
    } else {
      *this << " else ";
    }
    dispatch(c);
    first = false;
  }
  emit_trailing_comments(n);
  *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_ifclause(const IfClause &n) {
  if (n.condition != nullptr) {

    // we do not need to emit surrounding brackets for binary expressions
    // because they are already emitted with brackets
    bool needs_bracketing = !isa<BinaryExpr>(n.condition);

    *this << "if ";
    if (needs_bracketing)
      *this << "(";
    *this << *n.condition;
    if (needs_bracketing)
      *this << ")";
    *this << " ";
  }
  *this << "{\n";
  indent();
  for (const Ptr<Stmt> &s : n.body) {
    emit_leading_comments(*s);
    *this << *s;
  }
  dedent();
  *this << indentation() << "}";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_implication(const Implication &n) {
  *this << "(!" << *n.lhs << " || " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_ismember(const IsMember& n) {
  //TODO: update visit_ismember to new standards
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_isundefined(const IsUndefined &n) {
  //TODO: update visit_isundefined to new standards
  // check() prevents a model with isundefined expressions from making it
  // through to here
  assert(!"unreachable");
  __builtin_unreachable();
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_leq(const Leq &n) {
  *this << "(" << *n.lhs << " <= " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_lsh(const Lsh &n) {
  *this << "(" << *n.lhs << " << " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_lt(const Lt &n) {
  *this << "(" << *n.lhs << " < " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_mod(const Mod &n) {
  *this << "(" << *n.lhs << " % " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_model(const Model &n) {

  emit_leading_comments(n);

  this* << indentation() << "class " ROMP_STATE_CLASS_NAME " {\n\n";
  indent();

  for (const Ptr<Node> &c : n.children) {

    emit_leading_comments(*c);

    // if this is a rule, first flatten it so we do not have to deal with the
    // hierarchy of rulesets, aliasrules, etc.
    if (auto r = dynamic_cast<const Rule *>(c.get())) {
      std::vector<Ptr<Rule>> rs = r->flatten();
      for (const Ptr<Rule> &r2 : rs)
        *this << *r2 << "\n";

    } else {
      *this << *c << "\n";
    }
  }

  *this << "\n"
  dedent();
  *this << indentation() << "};\n\n" << std::flush;
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_mul(const Mul &n) {
  *this << "(" << *n.lhs << " * " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_multiset(const Multiset &n) {
  //TODO: update visit_multiset to new standards
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_multisetadd(const MultisetAdd &n) {
  //TODO: update visit_multisetadd to new standards
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_multisetcount(const MultisetCount &n) {
  //TODO: update visit_multisetcount to new standards
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_multisetelement(const MultisetElement &n) {
  //TODO: update visit_multisetelement to new standards
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_multisetremove(const MultisetRemove &n) {
  //TODO: update visit_multisetremove to new standards
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_multisetremovepred(const MultisetRemovePred &n) {
  //TODO: update visit_multisetremovepred to new standards
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_multisetquantifier(const MultisetQuantifier &n) {
  // this is unreachable because we handle all multiset loops internally
  assert(!"unreachable");
  __builtin_unreachable();
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_negative(const Negative &n) {
  *this << "(-" << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_neq(const Neq &n) {

  if (!n.lhs->type()->is_simple()) {
    // see explanation in visit_eq()
    assert(pack && "comparison of complex types is present but structures "
                   "are not packed");
    *this << "(memcmp(&" << *n.lhs << ", &" << *n.rhs << ", sizeof" << *n.lhs
          << ") != 0)";

    return;
  }

  *this << "(" << *n.lhs << " != " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_not(const Not &n) { *this << "(!" << *n.rhs << ")"; }

// << ------------------------------------------------------------------------------------------ >> 

void visit_number(const Number &n) {
  *this << "((" << value_type << ")(" << n.value.get_str() << "))";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_or(const Or &n) {
  *this << "(" << *n.lhs << " || " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_procedurecall(const ProcedureCall &n) {
  *this << indentation() << n.call << ";";
  emit_trailing_comments(n);
  *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_property(const Property &) {
  // this is unreachable because generate_c is only ever called with a Model
  // and nothing that contains a Property descends into it
  assert(!"unreachable");
  __builtin_unreachable();
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_propertyrule(const PropertyRule &n) {
  //TODO: update visit_propertyrule to new standards
  id_t prop_id = next_property_rule_id++;
  // property_rules.push_back(Ptr<const PropertyRule>::make(n));
  // function prototype
  *this << indentation() << CodeGenerator::M_PROPERTY__FUNC_ATTRS << "\n"
        // << indentation() << "void " ROMP_PROPERTYRULE_PREFIX << n.name << "(";
        << indentation() << "bool " ROMP_PROPERTYRULE_PREFIX << n.name << "(";

  // parameters
  if (n.quantifiers.empty()) {
    *this << "void";
  } else {
    std::string sep;
    for (const Quantifier &q : n.quantifiers) {
      if (q.type == nullptr || q.decl == nullptr || q.decl->type == nullptr)
        throw Error("(property-rule) Quantifier is missing type/decl info !! \t[dev-error]",q.loc);
      *this << sep // ;
            << "const " // quantifier parameters should never be edited
            << *(q.type) << " " << q.name;
      // if (auto t = dynamic_cast<const TypeExprID *>(q.type.get()))
      //   *this << *t; //t->name;
      // else
      //   *this << value_type;
      // *this << " " << q.name;
      sep = ", ";
    }
  }

  *this << ") const "  /* " throw (" ROMP_MODEL_EXCEPTION_TYPE ")" */  "{\n";
  indent();
  *this << indentation() << "using namespace ::" ROMP_TYPE_NAMESPACE ";\n";
  
  *this << indentation() << "try {\n";
  indent(); 

  // any aliases this property uses
  for (const Ptr<AliasDecl> &a : n.aliases) {
    *this << *a;
  }

  // processing_global_prop = true;
  // const auto stmt = Ptr<PropertyStmt>::make(n.property,n.name,n.loc);
  //       << *stmt;
  // processing_global_prop = false;

  *this << indentation() << "return ";
  id_t _id = 0;
  switch (n.property.category) {
  case Property::ASSERTION:
    // if (not CodeGenerator::is_prop_enabled(Property::ASSERTION)) // not needed always enabled
    //   throw Error("`assert`/`invariant` properties are not enabled !!", n.loc);
    *this << ROMP_INVARIANT_HANDLER(n,prop_id);
    break;

  case Property::ASSUMPTION:
    if (not CodeGenerator::is_prop_enabled(Property::ASSUMPTION))
      throw Error("`assume` properties are not enabled !!", n.loc);
    *this  << ROMP_ASSUMPTION_HANDLER(n,prop_id);
    break;

  case Property::COVER:
  if (not CodeGenerator::is_prop_enabled(Property::COVER))
      throw Error("`cover` properties are not enabled !!", n.loc);
    _id = next_cover_id++;
    *this  << ROMP_COVER_HANDLER(n,prop_id,_id);
    break;

  case Property::LIVENESS:
  if (not CodeGenerator::is_prop_enabled(Property::LIVENESS))
      throw Error("`liveness` properties are not enabled !!", n.loc);
    _id = next_liveness_id++;
    *this << ROMP_LIVENESS_HANDLER(n,prop_id,_id);
    break;
  }
  *this << ";\n";

  // *this << "(" << *n.property.expr << ");\n";

  // clean up any aliases we defined
  for (const Ptr<AliasDecl> &a : n.aliases) {
    *this << "#undef " << a->name << "\n";
  }

  dedent();
  // *this << indentation() << "} catch (...) { ::std::throw_with_nested( " 
  //                       ROMP_MAKE_MODEL_ERROR_PROPERTY(n,prop_id) " ); }\n";
  *this << indentation() << "} catch (...) { throw " 
                        ROMP_MAKE_MODEL_ERROR_PROPERTY(n,prop_id) "; }\n";

  dedent();
  *this << indentation() << "}\n";
  inType = GLOBAL;
# ifdef DEBUG
    *this << std::flush;  // flush output more frequently for easier debug
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_propertystmt(const PropertyStmt &n) {
  //TODO: update visit_propertystmt to new romp standards
  id_t id = next_property_id++;
  id_t _id = 0u;

  // *this << indentation() << "if (";
  // indent();

  switch (n.property.category) {
  case Property::ASSERTION:
  // if (not CodeGenerator::is_prop_enabled(Property::ASSUMPTION))  // not needed always enabled
  //     throw Error("`assert`/`invariant` properties are not enabled !!", n.loc);
    *this << indentation() << "if (" << ROMP_ASSERTION_HANDLER(n,id) << ") "
          /* << indentation() */ << "throw " ROMP_MAKE_MODEL_ERROR_PROPERTY(n,id) ";\n";
    prop_info_list << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,id,n.message,ROMP_PROPERTY_TYPE_ASSERT, to_json(n,"assert")) ",";
    break;

  case Property::ASSUMPTION:
  if (not CodeGenerator::is_prop_enabled(Property::ASSUMPTION))
      throw Error("`assume` properties are not enabled !!", n.loc);
    *this << "#ifdef " ROMP_ASSUME_PREPROCESSOR_VAR "\n"
          << indentation() << "if (" << ROMP_ASSUMPTION_HANDLER(n,id) << ") "
          /* << indentation() */ << "throw " ROMP_MAKE_MODEL_ERROR_PROPERTY(n,id) ";\n"
              "#endif\n";
    if (not processing_global_prop)
      prop_info_list << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,id,n.message,ROMP_PROPERTY_TYPE_ASSUME, to_json(n,"assume")) ",";
    break;

  case Property::COVER:
    if (not CodeGenerator::is_prop_enabled(Property::COVER))
      throw Error("`cover` properties are not enabled !!", n.loc);
    _id = next_cover_id++;
    *this << "#ifdef " ROMP_COVER_PREPROCESSOR_VAR "\n"
          << indentation() << "if (" << ROMP_COVER_HANDLER(n,id,_id) << ")"
          /* << indentation() */ << "throw " ROMP_MAKE_MODEL_ERROR_PROPERTY(n,id) ";\n"
          << "#endif\n";
    if (not processing_global_prop)
      prop_info_list << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,_id,n.message,ROMP_PROPERTY_TYPE_COVER, to_json(n,"cover")) ",";
    break;

  case Property::LIVENESS:
    if (not processing_global_prop)
      throw Error("liveness properties are NOT supported as embedded statements only global rules!", n.loc);
    // _id = next_liveness_id++;
    // *this << indentation() << "if (" << ROMP_LIVENESS_HANDLER(n,id,_id) << ")\n"
    //       << indentation() << "throw " ROMP_MAKE_MODEL_ERROR_PROPERTY(n,id) ";\n";
    // prop_info_list << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,_id,n.message,ROMP_PROPERTY_TYPE_LIVENESS, to_json(n,"liveness")) ",";
    break;
  }
  // dedent();

  emit_trailing_comments(n);
  *this << "\n";
# ifdef DEBUG
    *this << std::flush;  // flush output more frequently for easier debug
# endif
}



// << ========================================================================================== >> 
// <<                                     UTILITY FUNCTIONS                                      >> 
// << ========================================================================================== >> 

void ModelGenerator::print(const std::string &suffix, const TypeExpr &t,
                           const Expr &e, size_t counter) {

  const Ptr<TypeExpr> type = t.resolve();

  // if this is boolean, handle it separately to other Enums to avoid
  // -Wswitch-bool warnings and cope with badly behaved users setting non-0/1
  // values
  if (type->is_boolean()) {

    *this << indentation() << "printf(\"%s\", ((" << e << suffix
          << ") ? \"true\" : \"false\"))";

    return;
  }

  // if this is an enum, print the member corresponding to its value
  if (auto en = dynamic_cast<const Enum *>(type.get())) {

    *this << indentation() << "do {\n";
    indent();

    *this << indentation() << "switch (" << e << suffix << ") {\n";
    indent();
    size_t i = 0;
    for (const std::pair<std::string, location> &m : en->members) {
      *this << indentation() << "case " << std::to_string(i) << ":\n";
      indent();
      *this << indentation() << "printf(\"%s\", \"" << m.first << "\");\n"
            << indentation() << "break;\n";
      dedent();
      ++i;
    }
    *this << indentation() << "default:\n";
    indent();
    *this << indentation() << "assert(!\"invalid enum value\");\n"
          << indentation() << "__builtin_unreachable();\n";
    dedent();
    dedent();
    *this << indentation() << "}\n";

    dedent();
    *this << indentation() << "} while (0)";

    return;
  }

  if (auto a = dynamic_cast<const Array *>(type.get())) {

    // printing opening “[”
    *this << indentation() << "do {\n";
    indent();
    *this << indentation() << "printf(\"[\");\n";

    // invent a unique symbol using our counter
    const std::string i = "array_index" + std::to_string(counter);

    // get the bounds of the index and hackily prepend the value type to produce
    // something corresponding to one of the macros in ../resources/c_prefix.c
    const std::string lb = value_type + "_" + a->index_type->lower_bound();
    const std::string ub = value_type + "_" + a->index_type->upper_bound();

    *this << indentation() << "for (size_t " << i << " = 0; ; ++" << i
          << ") {\n";
    indent();

    // construct a print statement of the element at this index
    print(suffix + ".data[" + i + "]", *a->element_type, e, counter + 1);
    *this << ";\n";

    *this << indentation() << "if (" << i << " == (size_t)" << ub
          << " - (size_t)" << lb << ") {\n";
    indent();
    *this << indentation() << "break;\n";
    dedent();
    *this << indentation() << "} else {\n";
    indent();
    *this << indentation() << "printf(\", \");\n";
    dedent();
    *this << indentation() << "}\n";
    dedent();
    *this << indentation() << "}\n";

    // print closing “]”
    *this << indentation() << "printf(\"]\");\n";
    dedent();
    *this << indentation() << "} while (0)";

    return;
  }

  if (auto r = dynamic_cast<const Record *>(type.get())) {

    // print opening “{”
    *this << indentation() << "do {\n";
    indent();
    *this << indentation() << "printf(\"{\");\n";

    // print contained fields as a comma-separated list
    std::string sep;
    for (const Ptr<VarDecl> &f : r->fields) {
      *this << indentation() << "printf(\"%s\", \"" << sep << "\");\n";
      const Ptr<TypeExpr> ft = f->get_type();
      print(suffix + "." + f->name, *ft, e, counter);
      *this << ";\n";
      sep = ", ";
    }

    // print closing “}”
    *this << indentation() << "printf(\"}\");\n";
    dedent();
    *this << indentation() << "} while (0)";

    return;
  }

  // fall back case, for Ranges and Scalarsets
  *this << indentation() << "print_" << value_type << "(" << e << suffix << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_put(const Put &n) {

  // is this a put of a literal string?
  if (n.expr == nullptr) {
    *this << indentation() << "printf(\"%s\\n\", \"" << n.value << "\");";

  } else {
    const Ptr<TypeExpr> type = n.expr->type();
    print("", *type, *n.expr, 0);
    *this << ";";
  }

  emit_trailing_comments(n);
  *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_quantifier(const Quantifier &n) {

  if (n.type == nullptr) {
    bool down_count = n.from->constant() && n.to->constant() &&
                      n.to->constant_fold() < n.from->constant_fold();
    *this << "for (" << value_type << " " << n.name << " = " << *n.from << "; "
          << n.name << " " << (down_count ? ">=" : "<=") << " " << *n.to << "; "
          << n.name << " += ";
    if (n.step == nullptr) {
      *this << "1";
    } else {
      *this << *n.step;
    }
    *this << ")";
    return;
  }

  const Ptr<TypeExpr> resolved = n.type->resolve();

  if (auto e = dynamic_cast<const Enum *>(resolved.get())) {
    if (e->members.empty()) {
      // degenerate loop
      *this << "for (int " << n.name << " = 0; " << n.name << " < 0; " << n.name
            << "++)";
    } else {
      // common case
      *this << "for (__typeof__(" << e->members[0].first << ") " << n.name
            << " = " << e->members[0].first << "; " << n.name
            << " <= " << e->members[e->members.size() - 1].first << "; "
            << n.name << "++)";
    }
    return;
  }

  if (auto r = dynamic_cast<const Range *>(resolved.get())) {
    *this << "for (" << value_type << " " << n.name << " = " << *r->min << "; "
          << n.name << " <= " << *r->max << "; " << n.name << "++)";
    return;
  }

  if (auto s = dynamic_cast<const Scalarset *>(resolved.get())) {
    *this << "for (" << value_type << " " << n.name << " = 0; " << n.name
          << " <= " << *s->bound << "; " << n.name << "++)";
    return;
  }

  assert(!"missing case in visit_quantifier()");
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_range(const Range &) {
  //TODO: update visit_range to new standards
  *this << value_type;
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_record(const Record &n) {
  //TODO: update visit_record to new standards
  *this << "struct " << (pack ? "__attribute__((packed)) " : "") << "{\n";
  indent();
  for (const Ptr<VarDecl> &f : n.fields) {
    *this << *f;
  }
  dedent();
  *this << indentation() << "}";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_return(const Return &n) {
  *this << indentation() << "return";
  if (n.expr != nullptr) {
    *this << " " << *n.expr;
  }
  *this << ";";
  emit_trailing_comments(n);
  *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_rsh(const Rsh &n) {
  *this << "(" << *n.lhs << " >> " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_ruleset(const Ruleset &) {
  // this is unreachable because generate_c is only ever called with a Model
  // and all rule are flattened during visit_model
  assert(!"unreachable");
  __builtin_unreachable();
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_scalarset(const Scalarset &n) {
  //TODO: update visit_scalarset to new standards
  *this << value_type;
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_scalarsetunion(const ScalarsetUnion &n) { 
  //TODO: update visit_scalarsetunion to new standards
}


// << ------------------------------------------------------------------------------------------ >> 

void visit_simplerule(const SimpleRule &n) {
  //TODO: update visit_simplerule to new standards
  id_t id = next_rule_id++;

  *this << indentation() << CodeGenerator::M_RULE_GUARD__FUNC_ATTRS << "\n"
        << indentation() << "bool " ROMP_RULE_GUARD_PREFIX << n.name << "(";

  // parameters
  if (n.quantifiers.empty()) {
    *this << "void";
  } else {
    std::string sep;
    for (const Quantifier &q : n.quantifiers) {
      if (q.type == nullptr || q.decl == nullptr || q.decl->type == nullptr)
        throw Error("(rule-guard) Quantifier is missing type/decl info !! \t[dev-error]",q.loc);
      *this << sep // ;
            << "const "  // quantifier parameters should never be edited
            << *(q.type) << " " << q.name;
      /// if (auto t = dynamic_cast<const TypeExprID *>(q.type.get()))
      //   *this << *t; //t->name;
      // else
      //   *this << value_type;
      // *this << " " << q.name;
      sep = ", ";
    }
  }

  *this << ") const "  /* " throw (" ROMP_MODEL_EXCEPTION_TYPE ")" */  "{\n";
  indent();
  *this << indentation() << "using namespace ::" ROMP_TYPE_NAMESPACE ";\n";
  
  *this << indentation() << "try {\n";
  indent(); 

  // any aliases that are defined in an outer scope
  for (const Ptr<AliasDecl> &a : n.aliases) {
    *this << *a;
  }

  *this << indentation() << "return ";
  if (n.guard == nullptr) {
    *this << "true";
  } else {
    *this << *n.guard;
  }
  *this << ";\n";

  // clean up aliases
  for (const Ptr<AliasDecl> &a : n.aliases) {
    *this << "#undef " << a->name << "\n";
  }

  dedent();
  // *this << indentation() << "} catch (...) { ::std::throw_with_nested( "
  //                               ROMP_MAKE_MODEL_ERROR_RULE_GUARD(n,id) " ); }\n";
  *this << indentation() << "} catch (...) { throw "
                                ROMP_MAKE_MODEL_ERROR_RULE_GUARD(n,id) "; }\n";

  dedent();
  *this << indentation() << "}\n\n";

# ifdef DEBUG
    *this << std::flush;  // flush output more frequently for easier debug
# endif

  *this << indentation() << CodeGenerator::M_RULE_ACTION__FUNC_ATTRS << "\n"
        << indentation() << "void " ROMP_RULE_ACTION_PREFIX << n.name << "(";

  // parameters
  if (n.quantifiers.empty()) {
    *this << "void";
  } else {
    std::string sep;
    for (const Quantifier &q : n.quantifiers) {
      if (q.type == nullptr || q.decl == nullptr || q.decl->type == nullptr)
        throw Error("(rule-action) Quantifier is missing type/decl info !! \t[dev-error]",q.loc);
      *this << sep // ;
            << "const " // quantifier parameters should never be edited
            << *(q.type) << " " << q.name;
      // if (auto t = dynamic_cast<const TypeExprID *>(q.type.get()))
      //   *this << *t; //t->name;
      // else
      //   *this << value_type;
      // *this << " " << q.name;
      sep = ", ";
    }
  }

  *this << ") " /* " throw (" ROMP_MODEL_EXCEPTION_TYPE ")" */ "{\n";
  indent();
  *this << indentation() << "using namespace ::" ROMP_TYPE_NAMESPACE ";\n";
  
  *this << indentation() << "try {\n";
  indent(); 

  // aliases, variables, local types, etc.
  for (const Ptr<AliasDecl> &a : n.aliases) {
    emit_leading_comments(*a);
    *this << *a;
  }
  for (const Ptr<Decl> &d : n.decls) {
    if (d == nullptr) continue; // (TMP FIX) not sure why vector's keep getting null Ptr values
    emit_leading_comments(*d);
    *this << *d;
  }

  for (const Ptr<Stmt> &s : n.body) {
    emit_leading_comments(*s);
    *this << *s;
  }

  // clean up any aliases we defined
  for (const Ptr<Decl> &d : n.decls) {
    if (auto a = dynamic_cast<const AliasDecl *>(d.get())) {
      *this << "#undef " << a->name << "\n";
    }
  }
  for (const Ptr<AliasDecl> &a : n.aliases) {
    *this << "#undef " << a->name << "\n";
  }

  dedent();
  // *this << indentation() << "} catch (...) { ::std::throw_with_nested( " 
  //                       ROMP_MAKE_MODEL_ERROR_RULE_ACTION(n,id) " ); }\n";
  *this << indentation() << "} catch (...) { throw " 
                        ROMP_MAKE_MODEL_ERROR_RULE_ACTION(n,id) "; }\n";

  dedent();
  *this << indentation() << "}\n";

# ifdef DEBUG
    *this << std::flush;  // flush output more frequently for easier debug
# endif
}


// << ------------------------------------------------------------------------------------------ >> 

void visit_startstate(const StartState &n) {
  //TODO: update visit_startstate to new standards
  id_t id = next_startstate_id++;
  
  *this << indentation() << CodeGenerator::M_STARTSTATE__FUNC_ATTRS 
        << " void " ROMP_STARTSTATE_PREFIX << n.name << "(";

  // parameters
  if (n.quantifiers.empty()) {
    *this << "void";
  } else {
    std::string sep;
    for (const auto q : n.quantifiers) {
      if (q.type == nullptr || q.decl == nullptr || q.decl->type == nullptr)
        throw Error("(startstate) Quantifier is missing type/decl info !! \t[dev-error]",q.loc);
      *this << sep // ;
            << "const " // quantifier parameters should never be edited
            << *(q.type) << " " << q.name;
      /// if (auto t = dynamic_cast<const TypeExprID *>(q.type.get()))
      //   *this << *t; //t->name;
      // else
      //   *this << value_type;
      // *this << " " << q.name;
      sep = ", ";
    }
  }

  *this << ")"  /* " throw (" ROMP_MODEL_EXCEPTION_TYPE ")" */  "{\n";
  indent();
  *this << indentation() << "using namespace ::" ROMP_TYPE_NAMESPACE ";\n"; 

  *this << indentation() << "try {\n";
  indent(); 

  // aliases, variables, local types, etc.
  for (const Ptr<AliasDecl> &a : n.aliases) {
    emit_leading_comments(*a);
    *this << *a;
  }
  for (const Ptr<Decl> &d : n.decls) {
    emit_leading_comments(*d);
    *this << *d;
  }

  for (const Ptr<Stmt> &s : n.body) {
    emit_leading_comments(*s);
    *this << *s;
  }

  // clean up any aliases we defined
  for (const Ptr<Decl> &d : n.decls) {
    if (auto a = dynamic_cast<const AliasDecl *>(d.get())) {
      *this << "#undef " << a->name << "\n";
    }
  }
  for (const Ptr<AliasDecl> &a : n.aliases) {
    *this << "#undef " << a->name << "\n";
  }

  dedent();
  // *this << indentation() << "} catch (...) { ::std::throw_with_nested( " 
  //                       ROMP_MAKE_MODEL_ERROR_STARTSTATE(n, id) " ); }\n";
  *this << indentation() << "} catch (...) { throw " 
                        ROMP_MAKE_MODEL_ERROR_STARTSTATE(n, id) "; }\n";

  dedent();
  *this << indentation() << "}\n\n";
# ifdef DEBUG
    *this << std::flush;  // flush output more frequently for easier debug
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_sucast(const SUCast &n) { 
  //TODO: update visit_sucast to new standards
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_sub(const Sub &n) {
  *this << "(" << *n.lhs << " - " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_switch(const Switch &n) {

  // Murphi permits switch statements with non-constant case expressions, while
  // C’s switch statements do not support this. To deal with this discrepancy,
  // we emit switch statements as more flexible if-then-else blocks instead.

  // make the variable declaration and if-then-else block appear as a single
  // statement to any enclosing code
  *this << indentation() << "do {\n";
  indent();

  // we need to declare a temporary for the expression here because it may not
  // be pure, so we cannot necessarily safely emit it repeatedly in the
  // if-then-else conditions
  *this << indentation() << "__typeof__(" << *n.expr << ") res_ = " << *n.expr
        << ";\n";

  bool first = true;
  for (const SwitchCase &c : n.cases) {
    if (first) {
      *this << indentation();
    } else {
      *this << " else ";
    }
    if (!c.matches.empty()) {
      std::string sep = "";
      *this << "if (";
      for (const Ptr<Expr> &m : c.matches) {
        *this << sep << "res_ == " << *m;
        sep = " || ";
      }
      *this << ") ";
    }
    *this << "{\n";
    indent();
    for (const Ptr<Stmt> &s : c.body) {
      emit_leading_comments(*s);
      *this << *s;
    }
    dedent();
    *this << indentation() << "}";
    first = false;
  }
  *this << "\n";

  dedent();
  *this << indentation() << "} while (0);";
  emit_trailing_comments(n);
  *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_switchcase(const SwitchCase &n) {
  if (n.matches.empty()) {
    *this << indentation() << "default:\n";
  } else {
    for (const Ptr<Expr> &m : n.matches) {
      *this << indentation() << "case " << *m << ":\n";
    }
  }
  indent();
  for (const Ptr<Stmt> &s : n.body) {
    emit_leading_comments(*s);
    *this << *s;
  }
  *this << indentation() << "break;\n";
  dedent();
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_ternary(const Ternary &n) {
  *this << "(" << *n.cond << " ? " << *n.lhs << " : " << *n.rhs << ")";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_typedecl(const TypeDecl &n) {
  //TODO: update visit_typedecl to new standards
  // If we are typedefing something that is an enum, save this for later lookup.
  // See CGenerator/HGenerator::visit_constdecl for the purpose of this.
  if (auto e = dynamic_cast<const Enum *>(n.value.get()))
    enum_typedefs[e->unique_id] = n.name;

  // *this << indentation() << "typedef " << *n.value << " " << n.name << ";";
  // emit_trailing_comments(n);
  // *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_typeexprid(const TypeExprID &n) { *this << n.name; }

// << ------------------------------------------------------------------------------------------ >> 

void visit_undefine(const Undefine &n) {
  *this << indentation() << '(' << *n.rhs << ").Undefine();";
  emit_trailing_comments(n);
  *this << std::endl;
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_while(const While &n) {
  *this << indentation() << "while " << *n.condition << " {\n";
  indent();
  for (const Ptr<Stmt> &s : n.body) {
    emit_leading_comments(*s);
    *this << *s;
  }
  dedent();
  *this << indentation() << "}";
  emit_trailing_comments(n);
  *this << "\n";
}

// << ------------------------------------------------------------------------------------------ >> 

void visit_xor(const Xor &n) {
  *this << "(" << *n.lhs << " ^ " << *n.rhs << ")";
}

// write out a single line comment, accounting for the fact that '\' is an
// escape leader in C that we should suppress if it is escaping the trailing new
// line
static void write_content(const Comment &c, std::ostream &out) {
  assert(!c.multiline);

  // detect if we have a trailing backslash
  size_t i = 0;
  for (; i < c.content.size(); ++i) {
    if (c.content[i] == '\\') {
      bool remainder_is_space = true;
      for (size_t j = i + 1; j < c.content.size(); ++j) {
        if (!isspace(c.content[j])) {
          remainder_is_space = false;
          break;
        }
      }
      if (remainder_is_space) {
        break;
      }
      ++i; // skip escape
    }
  }

  out << c.content.substr(0, i);
}

size_t ModelGenerator::emit_leading_comments(const Node &n) {
  size_t count = 0;
  size_t i = 0;
  for (const Comment &c : comments) {
    // has this not yet been printed?
    if (!emitted[i]) {
      // does this precede the given node?
      if (c.loc.end.line < n.loc.begin.line ||
          (c.loc.end.line == n.loc.begin.line &&
           c.loc.end.column <= n.loc.begin.column)) {

        // do some white space adjustment for multiline comments
        if (c.multiline) {
          *this << indentation() << "/*";
          bool dropping = false;
          for (const char &b : c.content) {
            if (b == '\n') {
              *this << "\n" << indentation() << " ";
              dropping = true;
            } else if (dropping) {
              if (!isspace(b)) {
                out << b;
                dropping = false;
              }
            } else {
              out << b;
            }
          }
          *this << "*/\n";

        } else { // single line comments can be emitted simpler
          *this << indentation() << "//";
          write_content(c, out);
          *this << "\n";
        }

        emitted[i] = true;
      }
    }
    ++i;
  }
  return count;
}

size_t ModelGenerator::drop_comments(const position &pos) {
  size_t count = 0;
  size_t i = 0;
  for (const Comment &c : comments) {
    // does this precede the given node?
    if (c.loc.end.line < pos.line ||
        (c.loc.end.line == pos.line && c.loc.end.column <= pos.column)) {
      // mark it as emitted so it will be skipped in future
      emitted[i] = true;
    }
    ++i;
  }
  return count;
}

size_t ModelGenerator::emit_trailing_comments(const Node &n) {
  size_t count = 0;
  size_t i = 0;
  for (const Comment &c : comments) {
    if (!emitted[i] && !c.multiline && c.loc.begin.line == n.loc.end.line) {
      *this << " //";
      write_content(c, out);
      emitted[i] = true;
      ++count;
    }
    ++i;
  }
  return count;
}

ModelGenerator::~ModelGenerator() {}
