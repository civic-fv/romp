#include "ModelGenerator.hpp"
// #include "SubRangeSet.hpp"
#include "generate_state_stream.hpp"
#include "../../common/escape.h"
#include "../../common/isa.h"
// #include "options.h"
#include <cassert>
#include <cstddef>
#include <ctype.h>
#include <gmpxx.h>
#include <murphi/murphi.h>
#include <string>
#include <utility>
#include <vector>


namespace romp {

using namespace murphi;


// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_add(const Add &n) {
  *this << "(" << *n.lhs << " + " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_aliasdecl(const AliasDecl &n) {
  *this << "#define " << n.name << "() " << *n.value;
  emit_trailing_comments(n);
  *this << "\n";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_aliasrule(const AliasRule &) {
  // this is unreachable because generate_c is only ever called with a Model
  // and ModelGenerator::visit_model flattens all rules
  assert(!"unreachable");
  __builtin_unreachable();
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_aliasstmt(const AliasStmt &n) {
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
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_and(const And &n) {
  *this << "(" << *n.lhs << " && " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_array(const Array &n) {
  //[X] TODO: update ModelGenerator::visit_array to new standards
  *this << ROMP_TYPE_ARRAY "<" << *n.index_type << ',' 
                               << *n.element_type << '>'; 
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_assignment(const Assignment &n) {
  //[X]TODO: add assignment error handling
  *this << indentation() << "// " << n.lhs->to_string() << " := " << n.rhs->to_string() << ';';
  emit_trailing_comments(n);
  *this << '\n' 
        << indentation() << ROMP_UTIL_NAMESPACE "::Assignment<" << *n.lhs->type() << // ','
                                                                // << *n.rhs->type() <<
                                                              ">(" << *n.lhs << ", " 
                                                                << *n.rhs << ", " 
                                                                  ROMP_MAKE_LOCATION_STRUCT(n.loc)
                                                              << ");\n";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_band(const Band &n) {
  *this << "(" << *n.lhs << " & " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_bnot(const Bnot &n) {
  *this << "(~" << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_bor(const Bor &n) {
  *this << "(" << *n.lhs << " | " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_chooserule(const ChooseRule &n) {
  // this is unreachable because generate_c is only ever called with a Model
  // and all rules are flattened during ModelGenerator::visit_model
  assert(!"unreachable");
  __builtin_unreachable();
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_clear(const Clear &n) {
  //[X]TODO: update ModelGenerator::visit_clear to new standards
  *this << indentation() << "// Clear " << n.rhs->to_string() << ';';
  emit_trailing_comments(n);
  *this << '\n' << indentation() << '(' << *n.rhs << ").Clear();\n";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_constdecl(const ConstDecl &n) {
  //[X]TODO: update ModelGenerator::visit_constdecl to new standards
  // *this << indentation() << "static constexpr const ";
  *this << indentation() << "const ";

  // if this constant has an explicit type, use that
  if (n.type != nullptr) {
    *this << *n.type;

  } else {
    *this << ROMP_UTIL_NAMESPACE "::range_t";
  }
  // *this << ' ' << n.name << "() { return " << *n.value << "; }";
  *this << ' ' << n.name << " = " << *n.value << ';';
  emit_trailing_comments(n);
  *this << '\n';
# ifdef DEBUG
    *this << flush();
# endif
}


// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_div(const Div &n) {
  *this << "(" << *n.lhs << " / " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_element(const Element &n) {
  //[X]TODO: update ModelGenerator::visit_element to new standards
  const auto _a = n.array->type()->resolve();
  if (const auto a = dynamic_cast<const Array*>(_a.get())) {
  *this << "(" ROMP_UTIL_NAMESPACE "::Element<"<< *a->index_type << ','
                                               << *a->element_type
                                            << ">(" << *n.array << ", " 
                                                    << *n.index << ", " 
                                                    ROMP_MAKE_LOCATION_STRUCT(n.loc) "))"; 
  } else assert(!"unreachable");
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_enum(const Enum &n) {
  //[X]TODO: update ModelGenerator::visit_enum to new standards
  if (n.members.size() <= 0)
    throw Error("empty enum types are not allowed", n.loc);
  *this << ROMP_TYPE_ENUM << "<(/*"<< n.members[0].first << "*/" << enum_ids[n.members[0].first] << "),"
                                  "(" << n.members.size() << ")>";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_eq(const Eq &n) {
  //[X]TODO: update ModelGenerator::visit_eq to new standards
  *this << "(" << *n.lhs << " == " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_errorstmt(const ErrorStmt &n) {
  //[X]TODO: update ModelGenerator::visit_errorstmt to new standards
  id_t id = next_error_id++;
  *this << indentation() << "if (" ROMP_ERROR_HANDLER(id) ")\n";
  indent();
  *this << indentation() << "throw " ROMP_MAKE_MODEL_ERROR_ERROR(n,id) ";\n";
  dedent();
  emit_trailing_comments(n);
  *this << "\n";
# ifdef DEBUG
    *this << /*std::*/flush();  // flush output more frequently for easier debug
# endif
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_exists(const Exists &n) {
  *this << "({ bool res_ = false; " << n.quantifier << " { res_ |= " << *n.expr
        << "; } res_; })";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_exprid(const ExprID &n) {
  *this << "(";
  // if (is_pointer.count(n.value->unique_id) > 0) {
  //   *this << "*";
  // }
  *this << n.id;
  // if this refers to an alias, it will have been emitted as a macro
  // or if this refers to a constant it will be emitted as a static constexpr
  if (isa<AliasDecl>(n.value) /* || isa<ConstDecl>(n.value) */) {
    *this << "()";
  }
  *this << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_field(const Field &n) {
  //[X]TODO: update ModelGenerator::visit_field to new standards
  *this << '(' << *n.record << ".get</*"<<n.field<<"*/"<<n.record_field_index<<">())";
  // const auto t = n.record->type()->resolve();S
  // if (const Record* _r = dynamic_cast<const Record*>(t.get())) {
  //   for (size_t i=0; i<_r->fields.size(); ++i)
  //     if (_r->fields[i]->name == n.field) {
  //       *this << '(' << *n.record << ".get</*"<<n.field<<"*/"<<i<<">())";
  //       return;
  //     }
  //   throw Error("field (`"+n.field+"`) does not exist in record", n.loc);
  // }
  // throw Error("expected a record type", n.record->loc);
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_for(const For &n) {
  //[X]TODO: update ModelGenerator::visit_for to new standards

  *this << indentation() << n.quantifier << " {\n";
  indent();
  for (const Ptr<Stmt> &s : n.body) {
    emit_leading_comments(*s);
    *this << *s;
  }
  dedent();
  *this << indentation() << "}\n";
  emit_trailing_comments(n);
  *this << "\n";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_forall(const Forall &n) {
  //[X]TODO: update ModelGenerator::visit_forall to new standards
  // open a GNU statement expression
  *this << "({bool res_ = true; " << n.quantifier << " { res_ &= " << *n.expr
        << "; } res_; })";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_function(const Function &n) {
  //[X]TODO: update ModelGenerator::visit_function to new standards
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
  // *this << indentation() << "using namespace ::" ROMP_TYPE_NAMESPACE ";\n";
  
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
    *this << /*std::*/flush();  // flush output more frequently for easier debug
# endif
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_functioncall(const FunctionCall &n) {
  *this << n.name << "(";
  assert(n.function != nullptr && "unresolved function call in AST");
  auto it = n.function->parameters.begin();
  bool first = true;
  for (const Ptr<Expr> &a : n.arguments) {
    if (!first) {
      *this << ", ";
    }
    // if (!(*it)->readonly) {
    //   *this << "&";
    // }
    *this << *a;
    first = false;
    it++;
  }
  *this << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_geq(const Geq &n) {
  *this << "(" << *n.lhs << " >= " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_gt(const Gt &n) {
  *this << "(" << *n.lhs << " > " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_if(const If &n) {
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
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_ifclause(const IfClause &n) {
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
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_implication(const Implication &n) {
  *this << "(!" << *n.lhs << " || " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_ismember(const IsMember& n) {
  //[X]TODO: update ModelGenerator::visit_ismember to new standards
  *this << "(" ROMP_UTIL_NAMESPACE "::IsMember<" << *n.type_value << ">(" << *n.designator << "))";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_isundefined(const IsUndefined &n) {
  //[X]TODO: update ModelGenerator::visit_isundefined to new standards
  *this << '(' << *n.rhs << ".IsUndefined())";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_leq(const Leq &n) {
  *this << "(" << *n.lhs << " <= " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_lsh(const Lsh &n) {
  *this << "(" << *n.lhs << " << " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_lt(const Lt &n) {
  *this << "(" << *n.lhs << " < " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_mod(const Mod &n) {
  *this << "(" << *n.lhs << " % " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_model(const Model &n) {

  emit_leading_comments(n);

  *this << indentation() << "struct " ROMP_STATE_CLASS_NAME " {\n\n";
  indent();

  *this << indentation() << ROMP_RAND_WALKER_DECL "\n\n";

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

  *this << "\n";
  romp::generate_state_stream(*this,n);
  *this << "\n";
  dedent();
  *this << indentation() << "};\n\n" << /*std::*/flush();
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_mul(const Mul &n) {
  *this << "(" << *n.lhs << " * " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_multiset(const Multiset &n) {
  //[X]TODO: update ModelGenerator::visit_multiset to new standards
  *this << ROMP_TYPE_MULTISET << "<(/*" << n.size->to_string() << "*/(" << n.size->constant_fold()/*.get_str()*/ << ")),"
                              <<  *n.element_type << '>';
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_multisetadd(const MultisetAdd &n) {
  //[X]TODO: update ModelGenerator::visit_multisetadd to new standards
  *this << indentation() << "(" << *n.multiset << ").MultisetAdd((" << *n.value <<"));";
  emit_trailing_comments(n);
  *this << '\n';
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_multisetcount(const MultisetCount &n) {
  //[X]TODO: update ModelGenerator::visit_multisetcount to new standards
  *this << "((" << *n.ms_quantifier.multiset << ").MultisetCount([&](size_t " << n.ms_quantifier.name << ") -> bool { " 
                                                  "return ("<< *n.condition <<"); }))";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_multisetelement(const MultisetElement &n) {
  //[X]TODO: update ModelGenerator::visit_multisetelement to new standards
  //[X]TODO: implement error traces for bad accesses -- nvm validate and structure should prevent issues
  *this << "(" ROMP_UTIL_NAMESPACE "::MultisetElement((" << *n.multiset << "),"
                                                      "(" <<  *n.index << "),"
                                                      ROMP_MAKE_LOCATION_STRUCT(n.loc) "))";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_multisetremove(const MultisetRemove &n) {
  //[X]TODO: update ModelGenerator::visit_multisetremove to new standards
  // this is unreachable because we dont' support choose rule's and this is useless without them
  assert(!"unreachable");
  __builtin_unreachable();
  // *this << "((" << *n.multiset << ").MultisetRemove((" << *n.index << ")));";
  // emit_trailing_comments(n);
  // *this << '\n';
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_multisetremovepred(const MultisetRemovePred &n) {
  //[X]TODO: update ModelGenerator::visit_multisetremovepred to new standards
  *this << indentation() << "(" 
          << *n.ms_quantifier.multiset << ").MultisetRemovePred([&](size_t " << n.ms_quantifier.name << ") -> bool { "
                                                                  "return (" << *n.pred << "); });";
  emit_trailing_comments(n);
  *this << '\n';
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_multisetquantifier(const MultisetQuantifier &n) {
  //[X]TODO: update ModelGenerator::visit_multisetquantifier to new standards
  // this is unreachable because we let the Multiset type handle this for everything but choose rules
  //   which we don't support at all
  assert(!"unreachable");
  __builtin_unreachable();
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_negative(const Negative &n) {
  *this << "(-" << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_neq(const Neq &n) {
  //[X]TODO: update ModelGenerator::visit_neq to new standards
  *this << "(" << *n.lhs << " != " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_not(const Not &n) { *this << "(!" << *n.rhs << ")"; }

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_number(const Number &n) {
  *this << "((" ROMP_UTIL_NAMESPACE "::range_t)(" << n.value/*.get_str()*/ << "))";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_or(const Or &n) {
  *this << "(" << *n.lhs << " || " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_procedurecall(const ProcedureCall &n) {
  *this << indentation() << n.call << ";";
  emit_trailing_comments(n);
  *this << "\n";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_property(const Property &) {
  // this is unreachable because generate_c is only ever called with a Model
  // and nothing that contains a Property descends into it
  assert(!"unreachable");
  __builtin_unreachable();
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_propertyrule(const PropertyRule &n) {
  //[X]TODO: update ModelGenerator::visit_propertyrule to new standards
  id_t prop_id = next_property_id++;
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
  // *this << indentation() << "using namespace ::" ROMP_TYPE_NAMESPACE ";\n";
  
  *this << indentation() << "try {\n";
  indent(); 

  // any aliases this property uses
  for (const Ptr<AliasDecl> &a : n.aliases) {
    *this << *a;
  }

  // choose rule quantifiers
  for (const MultisetQuantifier& msq : n.ms_quantifiers) {
    *this << msq;
    // check choose rule's for choice validity
    *this << indentation() << "if (" << msq.name << " == (~((size_t)0u))) return true;\n";
  }

  *this << indentation() << "return ";
  id_t _id = 0;
  switch (n.property.category) {
  case Property::ASSERTION:
    // if (not is_prop_enabled(Property::ASSERTION)) // not needed always enabled
    //   throw Error("`assert`/`invariant` properties are not enabled !!", n.loc);
    *this << ROMP_INVARIANT_HANDLER(n,prop_id);
    break;

  case Property::ASSUMPTION:
    if (not is_prop_enabled(Property::ASSUMPTION))
      throw Error("`assume` properties are not enabled !!", n.loc);
    *this  << ROMP_ASSUMPTION_HANDLER(n,prop_id);
    break;

  case Property::COVER:
  if (not is_prop_enabled(Property::COVER))
      throw Error("`cover` properties are not enabled !!", n.loc);
    _id = next_cover_id++;
    *this  << ROMP_COVER_HANDLER(n,prop_id,_id);
    break;

  case Property::LIVENESS:
  if (not is_prop_enabled(Property::LIVENESS))
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
# ifdef DEBUG
    *this << /*std::*/flush();  // flush output more frequently for easier debug
# endif
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_propertystmt(const PropertyStmt &n) {
  //[X]TODO: update ModelGenerator::visit_propertystmt to new romp standards
  id_t id = next_property_id++;
  id_t _id = 0u;

  // *this << indentation() << "if (";
  // indent();

  switch (n.property.category) {
  case Property::ASSERTION:
  // if (not is_prop_enabled(Property::ASSUMPTION))  // not needed always enabled
  //     throw Error("`assert`/`invariant` properties are not enabled !!", n.loc);
    *this << indentation() << "if (" << ROMP_ASSERTION_HANDLER(n,id) << ") "
          /* << indentation() */ << "throw " ROMP_MAKE_MODEL_ERROR_PROPERTY(n,id) ";\n";
    // prop_info_list << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,id,n.message,ROMP_PROPERTY_TYPE_ASSERT, to_json(n,"assert")) ",";
    break;

  case Property::ASSUMPTION:
  if (not is_prop_enabled(Property::ASSUMPTION))
      throw Error("`assume` properties are not enabled !!", n.loc);
    *this << "#ifdef " ROMP_ASSUME_PREPROCESSOR_VAR "\n"
          << indentation() << "if (" << ROMP_ASSUMPTION_HANDLER(n,id) << ") "
          /* << indentation() */ << "throw " ROMP_MAKE_MODEL_ERROR_PROPERTY(n,id) ";\n"
              "#endif\n";
    // if (not processing_global_prop)
    //   prop_info_list << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,id,n.message,ROMP_PROPERTY_TYPE_ASSUME, to_json(n,"assume")) ",";
    break;

  case Property::COVER:
    if (not is_prop_enabled(Property::COVER))
      throw Error("`cover` properties are not enabled !!", n.loc);
    _id = next_cover_id++;
    *this << "#ifdef " ROMP_COVER_PREPROCESSOR_VAR "\n"
          << indentation() << "if (" << ROMP_COVER_HANDLER(n,id,_id) << ")"
          /* << indentation() */ << "throw " ROMP_MAKE_MODEL_ERROR_PROPERTY(n,id) ";\n"
          << "#endif\n";
    // if (not processing_global_prop)
    //   prop_info_list << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,_id,n.message,ROMP_PROPERTY_TYPE_COVER, to_json(n,"cover")) ",";
    break;

  case Property::LIVENESS:
    throw Error("liveness properties are NOT supported as embedded property statements only global rules!", n.loc);
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
    *this << /*std::*/flush();  // flush output more frequently for easier debug
# endif
# ifdef DEBUG
    *this << flush();
# endif
}


// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_put(const Put &n) {
  //[X]TODO: update ModelGenerator::visit_put to new standards (aka actually supported)

  // this lambda needs a by value/copy closure instead of the normal reference closure
  *this << _ROMP_PUT_HANDLER << "([=](" ROMP_OUT_STREAM_TYPE "& _romp_out) -> void { _romp_out";
  // is this a put of a literal string?
  if (n.expr == nullptr) {
    size_t pos; 
    std::string s = n.value;
    std::string token;
    while ((pos = s.find("\n")) != std::string::npos) {
      token = s.substr(0, pos);
      *this <<  " << \"" << escape(token) << "\" << _romp_out.nl()";
      s.erase(0, pos + 1);
    }
    *this <<  " << \"" << escape(s) << '"';

  } else {
    *this << " << (" << *n.expr << ')';
  }
  *this << " << _romp_out.nl(); }, " ROMP_MAKE_LOCATION_STRUCT(n.loc) ");";

  emit_trailing_comments(n);
  *this << "\n";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_quantifier(const Quantifier &n) {
  //[X]TODO: update ModelGenerator::visit_quantifier to new standards
  if (n.type == nullptr) {
    *this << "for (romp::range_t " << n.name << "=" << *n.from << "; "
              "((";
    if (n.step!=nullptr)
      *this << *n.step;
    else
      *this << "(1)";
    *this << ">0) "
      "? ("<<n.name<<"<="<<*n.to<<") "
      ": ("<<n.name<<">="<<*n.to<<")); "
          << n.name << " += ";
    if (n.step == nullptr) {
      *this << "1";
    } else {
      *this << *n.step;
    }
    *this << ")";
    return;
  }
  if (const auto _tid = dynamic_cast<const TypeExprID*>(n.type.get())) {
    if (_tid->name == "Boolean" || _tid->name == "boolean")
      throw Error("quantifiers of boolean types is not supported "
                  "(there is probably a better way to do whatever you are doing)", n.loc);
  }
  *this << "for (auto " << n.name << "=" << *n.type << "::__LB(); "
            << n.name << "!=" << *n.type << "::__UB(); "
            << n.name << ".__step())";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_range(const Range &n) {
  //[X]TODO: update ModelGenerator::visit_range to new standards
  *this << ROMP_TYPE_RANGE "<(/*(" << n.min->to_string() << ")*/(" << n.min->constant_fold()/*.get_str()*/ << ")),"
                            "(/*(" << n.max->to_string() << ")*/(" << n.max->constant_fold()/*.get_str()*/ << "))>";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_record(const Record &n) {
  //[X]TODO: update ModelGenerator::visit_record to new standards
  *this << ROMP_TYPE_RECORD "<" << n.first_field_id;
  std::string sep;
  for (const Ptr<VarDecl> &f : n.fields)
    *this << ',' << "/*" << f->name << "*/" << *f->type;
  *this << '>';
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_return(const Return &n) {
  *this << indentation() << "return";
  if (n.expr != nullptr) {
    *this << " (" << *n.expr << ')';
  }
  *this << ";";
  emit_trailing_comments(n);
  *this << "\n";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_rsh(const Rsh &n) {
  *this << "(" << *n.lhs << " >> " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_ruleset(const Ruleset &) {
  // this is unreachable because generate_c is only ever called with a Model
  // and all rule are flattened during ModelGenerator::visit_model
  assert(!"unreachable");
  __builtin_unreachable();
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_scalarset(const Scalarset &n) {
  //[X]TODO: update ModelGenerator::visit_scalarset to new standards
  std::string name1 = (((n.name != "") ? "_romp_"+n.name : "__romp__scalarset")
                          + '_' + n.count().get_str() + "_1");
  *this << ROMP_TYPE_SCALARSET "<" << enum_ids[name1] << ","
                                  "(/*" << n.bound->to_string() << "*/(" << n.count() << "))>";
                                  //  << *n.bound << '>';
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_scalarsetunion(const ScalarsetUnion &n) { 
  //[X]TODO: update ModelGenerator::visit_scalarsetunion to new standards
  *this << ROMP_TYPE_SCALAR_UNION "<";
  std::string sep;
  for (const auto& m : n.members) {
    *this << sep << *m;
    sep = ",";
  }
  *this << '>';
# ifdef DEBUG
    *this << flush();
# endif
}


// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_simplerule(const SimpleRule &n) {
  //[X]TODO: update ModelGenerator::visit_simplerule to new standards
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
  // *this << indentation() << "using namespace ::" ROMP_TYPE_NAMESPACE ";\n";
  
  *this << indentation() << "try {\n";
  indent(); 

  // any aliases that are defined in an outer scope
  for (const Ptr<AliasDecl> &a : n.aliases) {
    *this << *a;
  }

  // NOTE: not supporting choose rules
  // // choose rule quantifiers
  // for (const MultisetQuantifier& msq : n.ms_quantifiers) {
  //   *this << msq;
  //   // check choose rule's for choice validity
  //   *this << indentation() << "if (" << msq.name << " == (~((size_t)0u))) return false;\n";
  // }

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
    *this << /*std::*/flush();  // flush output more frequently for easier debug
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
  // *this << indentation() << "using namespace ::" ROMP_TYPE_NAMESPACE ";\n";
  
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
    *this << /*std::*/flush();  // flush output more frequently for easier debug
# endif
# ifdef DEBUG
    *this << flush();
# endif
}


// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_startstate(const StartState &n) {
  //[X]TODO: update ModelGenerator::visit_startstate to new standards
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
  // *this << indentation() << "using namespace ::" ROMP_TYPE_NAMESPACE ";\n";

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
    *this << /*std::*/flush();  // flush output more frequently for easier debug
# endif
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_sucast(const SUCast &n) { 
  //[X]TODO: update ModelGenerator::visit_sucast to new standards
  *this << "((" << *n.target << ')' << *n.rhs << ')';
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_sub(const Sub &n) {
  *this << "(" << *n.lhs << " - " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_switch(const Switch &n) {

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
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_switchcase(const SwitchCase &n) {
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
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_ternary(const Ternary &n) {
  *this << "(" << *n.cond << " ? " << *n.lhs << " : " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_typedecl(const TypeDecl &n) {
  //[X]TODO: update ModelGenerator::visit_typedecl to new standards
  *this << indentation() << "typedef " ROMP_TYPE_TYPEID "<" << n.type_id << ',' 
                                                            << *n.value << "> " 
                                      << n.name << ";";
  emit_trailing_comments(n);
  *this << "\n";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_typeexprid(const TypeExprID &n) { *this << n.name; }

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_undefine(const Undefine &n) {
  *this << indentation() << "// Undefine " << n.rhs->to_string() << ';';
  emit_trailing_comments(n);
  *this << '\n' << indentation() << '(' << *n.rhs << ").Undefine();\n";
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_vardecl(const VarDecl& n) {
  *this << indentation() << *n.type << ' ' << n.name << ';';
  emit_trailing_comments(n);
  *this << '\n';
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_while(const While &n) {
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
# ifdef DEBUG
    *this << flush();
# endif
}

// << ------------------------------------------------------------------------------------------ >> 

void ModelGenerator::visit_xor(const Xor &n) {
  *this << "(" << *n.lhs << " ^ " << *n.rhs << ")";
# ifdef DEBUG
    *this << flush();
# endif
}




// << ========================================================================================== >> 
// <<                                     UTILITY FUNCTIONS                                      >> 
// << ========================================================================================== >>

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
                *out << b;
                dropping = false;
              }
            } else {
              *out << b;
            }
          }
          *this << "*/\n";

        } else { // single line comments can be emitted simpler
          *this << indentation() << "//";
          write_content(c, *out);
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
      write_content(c, *out);
      emitted[i] = true;
      ++count;
    }
    ++i;
  }
  return count;
}


// inline ModelGenerator& ModelGenerator::operator << (const Node& n) {
//   dispatch(n);
//   return *this;
// }


template<typename T>
/* inline  */typename std::enable_if<!std::is_base_of<Node,T>::value,ModelGenerator&>::type ModelGenerator::operator << (const T& val) {
  *((CodeGenerator*)this) << val;
  return *this;
}
template<typename T>
/* inline  */typename std::enable_if<std::is_base_of<Node,T>::value,ModelGenerator&>::type ModelGenerator::operator << (const T& val) {
  dispatch(val);
  return *this;
}
// template<typename T>
// inline ModelGenerator& ModelGenerator::operator << (const T& val) {
//   *((CodeGenerator*)this) << val;
//   return *this;
// }
// template<>
// inline ModelGenerator& ModelGenerator::operator << <Node>(const Node& val) {
//   dispatch(val);
//   return *this;
// }
// template<typename T>
// inline ModelGenerator& operator << (ModelGenerator& gen, const T& val) {
//   ((CodeGenerator&)gen) << val;
//   return gen;
// }

//TODO: clean this up
// template<typename T>
// inline typename std::enable_if<std::is_base_of<murphi::Node,T>::value,ModelGenerator&>::type operator << (ModelGenerator& gen, const T& n) {
//   gen.dispatch(n);
//   return gen;
// }
// template<typename T>
// inline typename std::enable_if<!std::is_base_of<murphi::Node,T>::value,ModelGenerator&>::type operator << (ModelGenerator& gen, const T& val) {
//   (*((CodeGenerator*)&gen)) << val;
//   return gen;
// }
// template<>
// friend ModelGenerator&> operator << <bool>(ModelGenerator& gen, const bool& val) {
//   *((CodeGenerator*)&gen.out) << val;
//   return gen;
// }
// inline ModelGenerator& ModelGenerator::operator << (const Node &n) {
//   dispatch(n);
//   return *this;
// }
// template<>
// inline ModelGenerator& ModelGenerator::operator << <Node>(const Node &n) {
//   dispatch(n);
//   return *this;
// }
// template<>
// inline ModelGenerator& operator << <Node>(ModelGenerator& gen, const Node &n) {
//   gen.dispatch(n);
//   return gen;
// }

// ModelGenerator::~ModelGenerator() {}

} // namespace romp
