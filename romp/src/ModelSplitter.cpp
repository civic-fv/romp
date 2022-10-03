/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file Model.hpp
 *
 * @brief   A Class that is a intermediary representation of the model,
 *        used to allow for generating the Cpp romp tools
 *        in a way that allows full context of the model.
 *
 * @date 2022/05/13
 * @version 0.1
 */

#include "ModelSplitter.hpp"

#include "../../common/escape.h"
#include "nested_escape.hpp"
#include "../../common/isa.h"
#include "nested_escape.hpp"
#include "type_traverse.hpp"
#include "CodeGenerator.hpp"
#include "options.h"
#include <cassert>
#include <cstddef>
// #include <cstdio>
#include <ctype.h>
#include <gmpxx.h>
#include <rumur/rumur.h>
// #include <rumur/except.h>
// #include <rumur/Comment.h>
// #include <string>
// #include <utility>
// #include <vector>

// #include <functional>
#include <typeinfo>


namespace romp {
using namespace rumur;

// << ========================================================================================== >> 
// <<                               CONSTRUCTORS & DECONSTRUCTORS                                >> 
// << ========================================================================================== >> 

ModelSplitter::ModelSplitter() {
  funct_info_list << ROMP_INFO_FUNCTS_DECL " = {";
  rule_info_list << ROMP_INFO_RULESETS_DECL " = {";
  prop_info_list << ROMP_INFO_PROPERTIES_DECL " = {";
  startstate_info_list << ROMP_INFO_STARTSTATES_DECL " = {";
}
ModelSplitter::~ModelSplitter() {}


// << ========================================================================================== >> 
// <<                               SPLIT MODEL FACTORY FUNCTION                                 >> 
// << ========================================================================================== >> 

// SplitModel ModelSplitter::split_model(const Model &n) {
//   sort_model(n.children);
//   return (SplitModel){Model(global_decls, (global_decls.size() > 0) ? global_decls[0]->loc : n.loc),
//                       Model(state_var_decls, (state_var_decls.size() > 0) ? state_var_decls[0]->loc : n.loc),
//                       Model(funct_decls, (funct_decls.size() > 0) ? funct_decls[0]->loc : n.loc),
//                       Model(rule_decls, (rule_decls.size() > 0) ? rule_decls[0]->loc : n.loc)};
// }

// void ModelSplitter::dispatch(const Node &n) {  // bad code all around
//   loc = location(n.loc);
//   try {
//     auto m = dynamic_cast<const Model&>(n);
//     sort_model(m.children);
//   } catch (std::bad_cast &ex) {
//     throw Error("!! Expected a Model !!", n.loc);
//   }    
// }



// << ========================================================================================== >> 
// <<                                 PRIVATE HELPER FUNCTIONS                                   >> 
// << ========================================================================================== >> 

// bool operator == (const rumur::location& l, const rumur::location& r) {
//   return (l.begin.line == r.begin.line && l.begin.column == r.begin.column
//        && l.end.column == r.end.column && l.end.line == r.end.line);
// }

// template< typename T >
// std::string int_to_hex( T i )
// {
//   std::stringstream stream;
//   stream << "0x" 
//          << std::setfill ('0') << std::setw(sizeof(T)*2) 
//          << std::hex << i;
//   return stream.str();
// }

// const std::string ModelSplitter::gen_new_anon_name() {
//   return "anon"+int_to_hex(anon_id++)+"_t";
// }

const std::string ModelSplitter::gen_new_anon_name() {
  char buff[24];
  std::sprintf(buff, "anon0x%x_t", anon_id++);
  return std::string(buff);
}

void ModelSplitter::make_name_unique(std::string &name) {
  if (cTypeNames.find(name) == cTypeNames.end())
    return;
  char buff[name.size()+24];
  std::sprintf(buff, (name+"__0x%x").c_str(), anon_id++);
  name = std::string(buff);
}

void ModelSplitter::insert_to_global_decls(Ptr<TypeDecl> n) {
  make_name_unique(n->name);
  global_decls.push_back(n);
  cTypeNames.insert(n->name);
}

void ModelSplitter::insert_to_global_decls(Ptr<ConstDecl> n) {
  make_name_unique(n->name);
  global_decls.push_back(n);
  cTypeNames.insert(n->name);
}
inline bool
  equal(const position& pos1, const position& pos2)  // added because newer bison versions don't emit this operator
  {
    return pos1.line == pos2.line && pos1.column == pos2.column;
  }
  inline bool
  equal(const location& loc1, const location& loc2) // added because newer bison versions don't emit this operator
  {
    return equal(loc1.begin,loc2.begin) && equal(loc1.end, loc2.end);
  }
void ModelSplitter::sort_model(const std::vector<Ptr<Node>> &children) {
  for (const Ptr<Node> &_c : children) {
  // for (const Ptr<Node> &c : children) {
    Ptr<Node> c(_c->clone());

    if (const auto _td = dynamic_cast<const TypeDecl *>(c.get())) {
      Ptr<TypeDecl> td(_td->clone());
      dispatch(*td);
      insert_to_global_decls(td);
    } else if (const auto _cd = dynamic_cast<const ConstDecl *>(c.get())) {
      Ptr<ConstDecl> cd(_cd->clone());
      insert_to_global_decls(cd);
    } else if (const auto _vd = dynamic_cast<const VarDecl *>(c.get())) {
      Ptr<VarDecl> vd(_vd->clone());
      dispatch(*vd);
      state_var_decls.push_back(vd);
    } else if (const auto _f = dynamic_cast<const Function *>(c.get())) {
      Ptr<Function> f(_f->clone());
      dispatch(*f);
      funct_decls.push_back(f);
    } else if (const auto _r = dynamic_cast<const Rule *>(c.get())) {
      Ptr<Rule> r(_r->clone());
      // rule_decls.push_back(r);  // now sorting into type of usable rule types & flattening on the way down
      dispatch(*r);
    } else 
        // throw Error("Unexpected item in the global scope!!", _c->loc);
        throw Error("Unexpected item in the global scope!!", c->loc);
  }
}

std::string to_json(const Rule& rule, const std::string rule_type) {
  std::stringstream buf;
  buf << "{\"$type\":\"" << rule_type << "\",";
  if (auto _prop = dynamic_cast<const rumur::PropertyRule*>(&rule)) {
    buf << "\"type\":\"";
    switch (_prop->property.category) {
      case rumur::Property::ASSERTION:
        buf << "invariant"; break;
      case rumur::Property::ASSUMPTION:
        buf << "assume"; break;
      case rumur::Property::COVER:
        buf << "cover"; break;
      case rumur::Property::LIVENESS:
        buf << "liveness"; break;
    }
    buf << "\",\"expr\":\"" << nEscape(_prop->property.expr->to_string()) << "\",";
  } else if (auto _r = dynamic_cast<const rumur::SimpleRule*>(&rule)) {
    buf << "\"expr\":\"";
    if (_r->guard != nullptr)
      buf << nEscape(_r->guard->to_string());
    buf << "\",";
  }
  buf << "\"label\":\"" << nEscape(rule.name) << "\","
         "\"loc\":{\"$type\":\"location\","
                    "\"file\":\"" << nEscape(CodeGenerator::input_file_path.string()) <<  "\","
                    // "\"inside\":\"global\","
                    "\"start\":["<< rule.loc.begin.line << "," << rule.loc.begin.column << "],"  
                    "\"end\":["<< rule.loc.end.line << "," << rule.loc.end.column << "]}";
  return buf.str();
}

std::string to_json(const Function& rule) {
  std::stringstream buf;
  buf << "{\"$type\":\"" << ((rule.return_type == nullptr) 
                              ? "procedure" 
                              : "function\","
                                "\"return-type\":\"" + nEscape(rule.return_type->to_string())) << "\","
      << "\"label\":\"" << nEscape(rule.name) << "\","
         "\"params\":[";
  std::string sep = "";
  for (auto& p : rule.parameters) {
    buf << sep << "{\"$type\":\"param\","
                   "\"id\":\"" << nEscape(p->name) << "\","
                   "\"type\":\"" << nEscape(p->type->to_string()) << "\"}";
    sep = ",";
  }
  buf << "],\"loc\":{\"$type\":\"location\","
                    "\"file\":\"" << nEscape(CodeGenerator::input_file_path.string()) << "\","
                    // "\"inside\":\"global\","
                    "\"start\":["<< rule.loc.begin.line << "," << rule.loc.begin.column << "],"  
                    "\"end\":["<< rule.loc.end.line << "," << rule.loc.end.column << "]}}";
  return buf.str();
}



std::string to_string(const Function& f) {
  std::stringstream buf;
  buf << ((f.return_type != nullptr) ? "function " : "procedure ")
      << nEscape(f.name) << '(';
  if (f.parameters.size() >= 1) {
    const VarDecl* _p = f.parameters[0].get();
    const VarDecl* p = _p;
    if (_p->readonly) buf << "var ";
    buf << nEscape(_p->name);
    if (f.parameters.size() >= 2)
      for (int i=1; i<f.parameters.size(); ++i) {
        p = f.parameters[i].get();
        if (_p->readonly == p->readonly 
              && (_p->type->unique_id == p->type->unique_id || equal(_p->type->loc, p->type->loc)))
          buf << ',' << nEscape(p->name);
        else {
          buf << ": " << nEscape(_p->type->to_string()) << "; ";
          if (p->readonly)
            buf << "var ";
          buf << nEscape(p->name);
        }
        _p = p;
      }
    buf << ": " << nEscape(p->type->to_string());
  }
  if (f.return_type != nullptr)
    buf << ") : " << f.return_type->to_string() << ';';
  else buf << ");";
  return buf.str();
}





// << ========================================================================================== >> 
// <<                                  PARSING UTIL FUNCTIONS                                    >> 
// << ========================================================================================== >> 


// void ModelSplitter::visit_model(Model &n) {
//   sort_model(n.children);
// }


void ModelSplitter::visit_constdecl(ConstDecl &n) {
  // shouldn't have to do anything here.
}


void ModelSplitter::visit_typedecl(TypeDecl &n) {
  // if (ModelSplitter::pretty_type_reprs.find(n.value->unique_id) != ModelSplitter::pretty_type_reprs.end())
  dispatch(*(n.value));
  if (not isa<TypeExprID>(n.value.get()))
    ModelSplitter::pretty_type_reprs[n.value->unique_id] = std::string(n.name);
}


void ModelSplitter::visit_typeexprid(TypeExprID &n) {
  set_pretty_str_rep_type(n);
  // shouldn't need to do anything here
}


void ModelSplitter::visit_enum(Enum &n) {
  set_pretty_str_rep_type(n);
  // shouldn't need to do anything here
}


void ModelSplitter::visit_array(Array &n) {
  set_pretty_str_rep_type(n);
  //TODO: handle the cases of non-TypeExprId TypeExpr values & the nested enums.

  if (auto et_id = dynamic_cast<TypeExprID *>(n.element_type.get())) {
    // do nothing
  } else {
    dispatch(*(n.element_type));
    std::string name = gen_new_anon_name();
    Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(n.element_type->clone()), n.element_type->loc));
    insert_to_global_decls(decl);
    n.element_type = Ptr<TypeExprID>(new TypeExprID(name, decl, n.element_type->loc));
  }
  

  // mpz_class count = n.index_type->count();

  // assert(count > 0 && "index type of array does not include undefined");
  // count--;

  // // wrap the array in a struct so that we do not have the awkwardness of
  // // having to emit its type and size on either size of another node
  // *this << "struct " << (pack ? "__attribute__((packed)) " : "") << "{ "
  //       << *n.element_type << " data[" << count.get_str() << "];";

  // The index for this array may be an enum declared inline:
  //
  //   array [enum {A, B}] of foo
  //
  // If so, we need to emit it somehow so that the enum’s members can be
  // referenced later. We define it within this struct to avoid any awkward
  // lexical issues.

  // if (auto e = dynamic_cast<const Enum *>(n.index_type.get())) {
  //   std::string name = gen_new_anon_name();
  //   Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<Enum>(e->clone()), e->loc));
  //   insert_to_global_decls(decl);
  //   // n.index_type = Ptr<TypeExprID>(new TypeExprID(name, decl, e->loc));
  //   n.index_type = Ptr<TypeExpr>(new IndType(*e));
  // } else
   if (auto it_id = dynamic_cast<TypeExprID *>(n.index_type.get())) {
    // n.index_type = Ptr<IndType>(new IndType(*(it_id->referent->value)));
  } else {
    dispatch(*(n.index_type));
    std::string name = gen_new_anon_name();
    Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(n.index_type->clone()), n.index_type->loc));
    insert_to_global_decls(decl);
    n.index_type = Ptr<TypeExprID>(new TypeExprID(name, decl, n.index_type->loc));
    // n.index_type = Ptr<IndType>(new IndType(*(n.index_type)));
  }
  // *this << " }";
}


void ModelSplitter::visit_range(Range &n) {
  set_pretty_str_rep_type(n);
  // shouldn't need to do anything here
}


void ModelSplitter::visit_record(Record &n) {
  set_pretty_str_rep_type(n);
  //TODO: handle the cases of non-TypeExprId TypeExpr values
  std::vector<Ptr<VarDecl>> _fields(n.fields.size());

  for (Ptr<VarDecl> &f : n.fields) {  // pre output any inplace type definitions
    
    if (auto et_id = dynamic_cast<TypeExprID *>(f->type.get())) {
      _fields.push_back(Ptr<VarDecl>(f));
    } else {
      dispatch(*(f->type));
      std::string name = gen_new_anon_name();
      Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(f->type), f->loc));
      insert_to_global_decls(decl);
      _fields.push_back(Ptr<VarDecl>(new VarDecl(f->name, 
                                          Ptr<TypeExprID>(new TypeExprID(name, decl, f->loc)),
                                           f->loc)));
    }
  }
  n.fields = _fields;
}


void ModelSplitter::visit_scalarset(Scalarset &n) {
  set_pretty_str_rep_type(n);
  // shouldn't need to do anything here
}


void ModelSplitter::visit_vardecl(VarDecl &n) {
  // DEBUG: check that no VarDecl is reached that has a non-TypeExprId type! 
  if (auto et_id = dynamic_cast<const TypeExprID *>(n.type.get())) {
    // do nothing
  } else {
    dispatch(*(n.type));
    std::string name = gen_new_anon_name();
    Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(n.type), n.type->loc));
    insert_to_global_decls(decl);
    n.type = Ptr<TypeExprID>(new TypeExprID(name, decl, n.type->loc));
    // throw Error("An inline type declaration was reached before being processed by the type handler!!"
    //                 " :: `"+n.type->to_string()+"`",
    //             n.loc);
  }
}


void ModelSplitter::visit_function(Function &n) {
  //TODO: handle the cases of non-TypeExprID TypeExpr values
  funct_info_list << ROMP_MAKE_FUNCT_INFO_STRUCT(n, to_json(n), to_string(n)) ",";

  if (n.return_type != nullptr)
    if (auto et_id = dynamic_cast<TypeExprID *>(n.return_type.get())) {
      // do nothing
    } else {
      dispatch(*(n.return_type));
      std::string name = gen_new_anon_name();
      Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(n.return_type->clone()), n.return_type->loc));
      insert_to_global_decls(decl);
      n.return_type = Ptr<TypeExprID>(new TypeExprID(name, decl, n.return_type->loc));
    }

  // std::vector<Ptr<VarDecl>> _parameters(n.parameters.size());
  for (Ptr<VarDecl> &p : n.parameters)
    if (auto et_id = dynamic_cast<TypeExprID *>(p->type.get())) {
      // do nothing
    } else {
      dispatch(*(p->type));
      std::string name = gen_new_anon_name();
      Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(p->type->clone()), p->type->loc));
      insert_to_global_decls(decl);
      p->type = Ptr<TypeExprID>::make(name, decl, p->type->loc);
    }
  // n.parameters = _parameters;

#ifdef DEBUG
  // for (Ptr<VarDecl> &p : n.parameters)
  //   if (not isa<TypeExprID>(p->type.get()))
  //     throw Error("Failed ot update func/proc parameter !! (still a non TypeExprID after processing) \t[dev-error]",p->loc);
#endif

  std::vector<Ptr<Decl>> _decls/* (n.decls.size()) */;
  for (Ptr<Decl> &d : n.decls)
    if (auto vd = dynamic_cast<VarDecl *>(d.get())) {
      if (auto et_id = dynamic_cast<TypeExprID *>(vd->type.get())) {
        // do nothing
      } else {
        dispatch(*(vd->type));
        std::string name = gen_new_anon_name();
        Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(vd->type->clone()), vd->type->loc));
        insert_to_global_decls(decl);
        vd->type = Ptr<TypeExprID>(new TypeExprID(name, decl, vd->type->loc));
      }
      _decls.push_back(Ptr<VarDecl>(vd->clone()));
    } else if (auto td = dynamic_cast<TypeDecl *>(d.get())) {
      insert_to_global_decls(Ptr<TypeDecl>(td->clone()));
    } else if (auto cd = dynamic_cast<ConstDecl *>(d.get())) {
      insert_to_global_decls(Ptr<ConstDecl>(cd->clone()));
    }
  n.decls = _decls;
#ifdef DEBUG
  // for (Ptr<Decl> &d : n.decls)
  //   if (d == nullptr)
  //     throw Error("Function decls contains nullptr!! \t[dev-error]", n.loc);
#endif
}

void ModelSplitter::_visit_quantifier(Quantifier& q) {
  if (q.type != nullptr) {
    if (not isa<TypeExprID>(q.type.get())) {
      dispatch(*(q.type));
      std::string name = gen_new_anon_name();
      Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(q.type), q.type->loc));
      insert_to_global_decls(decl);
      q.type = Ptr<TypeExprID>(new TypeExprID(name, decl, q.type->loc));
      q.decl->type = q.type;
    }
  } else if (q.from != nullptr && q.to != nullptr) {
    if (not q.from->constant()) throw Error("All bounds of a Ruleset's quantifier must NOT be dependent on variables !!",q.from->loc);
    if (not q.to->constant()) throw Error("All bounds of a Ruleset's quantifier must NOT be dependent on variables !!",q.to->loc);
    if (q.step == nullptr)
      q.step = Ptr<Number>::make("1",q.type->loc);
    else if (not q.step->constant()) 
      throw Error("A bounds (including the step) of a Ruleset's quantifier must NOT be dependent on variables !!", q.step->loc);
    auto range = Ptr<Range>::make(q.from, q.to, q.loc);
    std::string name = gen_new_anon_name();
    Ptr<TypeDecl> decl(new TypeDecl(name, range, q.loc));
    insert_to_global_decls(decl);
    q.decl->type = Ptr<TypeExprID>::make(name, decl, q.loc);
  } else 
    throw Error("the Quantifier has broken bounds!!", q.loc);
  if (q.type == nullptr || q.decl == nullptr || q.decl->type == nullptr)
    throw Error("(model-splitter) Quantifier is missing type/decl info !! \t[dev-error]",q.loc);
}

void ModelSplitter::visit_and_check_quantifier(Rule& r, Quantifier& q) {
  if (q.type != nullptr) {
    set_pretty_str_rep_type(*q.type);
    auto type = q.type->resolve();
    if (type->is_simple()) {
      if (q.from == nullptr)
        q.from = Ptr<Number>::make(q.type->lower_bound(),q.type->loc);  // not valid str is c code
      if (q.to == nullptr)
        q.to = Ptr<Number>::make(q.type->upper_bound(), q.type->loc);   // not valid str is c code
      if (q.step == nullptr) {
        q.step = Ptr<Number>::make("1",q.type->loc);
      }
    } else {
      
    }
    if (not isa<TypeExprID>(q.type.get())) {
      dispatch(*(q.type));
      std::string name = gen_new_anon_name();
      Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(q.type), q.type->loc));
      insert_to_global_decls(decl);
      q.type = Ptr<TypeExprID>(new TypeExprID(name, decl, q.type->loc));
    }
  } else if (q.from != nullptr && q.to != nullptr) {
    if (not q.from->constant()) throw Error("All bounds of a Ruleset's quantifier must NOT be dependent on variables !!",q.from->loc);
    if (not q.to->constant()) throw Error("All bounds of a Ruleset's quantifier must NOT be dependent on variables !!",q.to->loc);
    auto range = Ptr<Range>::make(q.from, q.to, q.loc);
    set_pretty_str_rep_type(*range);
    std::string name = gen_new_anon_name();
    Ptr<TypeDecl> decl(new TypeDecl(name, range, q.loc));
    insert_to_global_decls(decl);
    q.type = Ptr<TypeExprID>::make(name, decl, q.loc);
    if (q.step == nullptr)
        q.step = Ptr<Number>::make("1",q.type->loc);
    else if (not q.step->constant()) throw Error("A bounds (including the step) of a Ruleset's quantifier must NOT be dependent on variables !!", q.step->loc);
  } else 
    throw Error("the Quantifier has broken bounds!!", q.loc);
}


void ModelSplitter::visit_propertyrule(PropertyRule &n) {
  std::string pt;
  id_t id;
  switch (n.property.category) {
    case Property::ASSERTION: pt = ROMP_PROPERTY_TYPE_INVAR; id=next_invar_id++; break;
    case Property::ASSUMPTION: pt = ROMP_PROPERTY_TYPE_ASSUME; id=next_assume_id++; break;
    case Property::COVER: pt = ROMP_PROPERTY_TYPE_COVER; id=next_cover_id; break;
    case Property::LIVENESS: pt = ROMP_PROPERTY_TYPE_LIVENESS; id=next_liveness_id++; break;
  }
  prop_info_list << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,id,n.name,pt,to_json(n,"property")) ",";
  ++next_property_id;
  // for (Quantifier& q : n.quantifiers)
  //   _visit_quantifier(q);
  property_decls.push_back(Ptr<PropertyRule>::make(n));
}


void ModelSplitter::visit_simplerule(SimpleRule &n) {
  //TODO: handle the cases of non-TypeExprId TypeExpr values
  rule_info_list << ROMP_MAKE_RULE_INFO_STRUCT(n,to_json(n,"rule")) ",";
  // for (Quantifier& q : n.quantifiers)
  //   _visit_quantifier(q);
    // if (q.type != nullptr) 
    //   if (auto _td = dynamic_cast<TypeExprID *>(q.type.get())) {
    //     // do nothing
    //   } else {
    //     dispatch(*(q.type));
    //     std::string name = gen_new_anon_name();
    //     Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(q.type), q.type->loc));
    //     insert_to_global_decls(decl);
    //     q.type = Ptr<TypeExprID>(new TypeExprID(name, decl, q.type->loc));
    // }
  
  if (n.guard == nullptr)
    n.guard = rumur::True;

  std::vector<Ptr<Decl>> _decls(n.decls.size());
  for (Ptr<Decl> &d : n.decls)
    if (auto vd = dynamic_cast<VarDecl *>(d.get())) {
      if (auto _ = dynamic_cast<TypeExprID *>(vd->type.get())) {
        // do nothing
      } else {
         dispatch(*(vd->type));
        std::string name = gen_new_anon_name();
        Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(vd->type), vd->type->loc));
        insert_to_global_decls(decl);
        vd->type = Ptr<TypeExprID>(new TypeExprID(name, decl, vd->type->loc));
      }
      _decls.push_back(d);
    } else if (auto td = dynamic_cast<TypeDecl *>(d.get())) {
      insert_to_global_decls(Ptr<TypeDecl>(td));
    } else if (auto cd = dynamic_cast<ConstDecl *>(d.get())) {
      insert_to_global_decls(Ptr<ConstDecl>(cd));
    }
  n.decls = _decls;
  rule_decls.push_back(Ptr<SimpleRule>::make(n));
}

void ModelSplitter::visit_ruleset(rumur::Ruleset &n) {
  for (Quantifier& q : n.quantifiers)
      _visit_quantifier(q); 
      // if (auto _td = dynamic_cast<TypeExprID *>(q.type.get())) {
      //   // do nothing
      // } else {
      //   dispatch(*(q.type));
      //   std::string name = gen_new_anon_name();
      //   Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(q.type), q.type->loc));
      //   insert_to_global_decls(decl);
      //   q.type = Ptr<TypeExprID>(new TypeExprID(name, decl, q.type->loc));
      // }
  for (auto _r : n.rules) {
    for (auto _a : n.aliases)
      _r->aliases.push_back(rumur::Ptr<rumur::AliasDecl>(_a));
    for (auto q : n.quantifiers)
      _r->quantifiers.push_back(rumur::Quantifier(q));
    dispatch(*_r);
  }
}


void ModelSplitter::visit_aliasrule(rumur::AliasRule &n) {
  // for (Quantifier& q : n.quantifiers)
  //     _visit_quantifier(q); 
  for (auto _r : n.rules) {
    for (auto _a : n.aliases)
      _r->aliases.push_back(rumur::Ptr<rumur::AliasDecl>(_a));
    for (auto q : n.quantifiers)
      _r->quantifiers.push_back(rumur::Quantifier(q));
    dispatch(*_r);
  }
}


void ModelSplitter::visit_startstate(StartState &n) {
  startstate_info_list << ROMP_MAKE_STARTSTATE_INFO_STRUCT(n,to_json(n,"startstate")) ",";
  // for (Quantifier& q : n.quantifiers)
  //   _visit_quantifier(q);
  std::vector<Ptr<Decl>> _decls(n.decls.size());
  for (Ptr<Decl> &d : n.decls)
    if (auto vd = dynamic_cast<VarDecl *>(d.get())) {
      if (auto et_id = dynamic_cast<TypeExprID *>(vd->type.get())) {
        // do nothing
      } else {
        dispatch(*(vd->type));
        std::string name = gen_new_anon_name();
        Ptr<TypeDecl> decl(new TypeDecl(name, Ptr<TypeExpr>(vd->type->clone()), vd->type->loc));
        insert_to_global_decls(decl);
        vd->type = Ptr<TypeExprID>(new TypeExprID(name, decl, vd->type->loc));
      }
      _decls.push_back(d/* Ptr<VarDecl>(vd->clone()) */);
    } else if (auto td = dynamic_cast<TypeDecl *>(d.get())) {
      insert_to_global_decls(Ptr<TypeDecl>(td->clone()));
    } else if (auto cd = dynamic_cast<ConstDecl *>(d.get())) {
      insert_to_global_decls(Ptr<ConstDecl>(cd->clone()));
    }
  n.decls = _decls;
  startstate_decls.push_back(Ptr<StartState>::make(n));
}



void ModelSplitter::__throw_unreachable_error(const Node &n) {
  throw Error("The Model Splitter & Organizer visited an unsupported syntactic element!!", n.loc);
}


std::unordered_map<size_t,std::string> ModelSplitter::pretty_type_reprs;
size_t ModelSplitter::model_unique_id = ~(0ul);

void ModelSplitter::set_pretty_str_rep_type(const Node& t, int max_level) {
  class pretty_str_rep : public ConstBaseTypeTraversal {
    std::stringstream out;
    int level = 0;
    const int max;
  public:
    pretty_str_rep(int max_) 
      : max(max_), ConstBaseTypeTraversal("Not a TypeExpr!! `pretty_str_rep` can't handle it \t[dev-error]") 
    {}
    std::string str() { return out.str(); }
    void visit_array(const Array& n) {
      if (level < max) {
        ++level;
        out << "Array[";
        dispatch(*n.index_type);
        out << "] of ";
        dispatch(*n.element_type);
      // } else if (level == max) {
      //   mpz_class size = n.index_type->count() - 1_mpz;
      //   out << "Array[" << count.get_str()
      //       << "] of ";
      //   dispatch(*n.element_type);
        --level;
      } else // if (level > max)
        out << "anon_array_t";
    }
    void visit_enum(const Enum& n) {
      if (level < max) {
        out << "Enum {";
        if (n.members.size() >= 1)
          out << n.members[0].first;
        if (n.members.size() == 2)
          out << ", " << n.members[1].first;
        else // if (n.members.size() > 2)
          out << ".." << n.members[n.members.size()-1].first;
        out << "}";
      } else if (level == max) {
        if (n.members.size() >= 1)
          out << n.members[0].first;
        if (n.members.size() >= 2)
          out << ".." << n.members[n.members.size()-1].first;
      } else // if (level >= max)
        out << "anon_enum_t"; 
    }
    void visit_range(const Range& n) { out << n.to_string(); }
    void visit_record(const Record& n) { 
      out << "anon_record_t"; 
    }
    void visit_scalarset(const Scalarset& n) { out << n.to_string(); }
    void visit_typeexprid(const TypeExprID& n) { out << n.to_string(); }
    // void dispatch(const Node& n) { n->visit(S_OUT); }
  };
  if (ModelSplitter::pretty_type_reprs.find(t.unique_id) != ModelSplitter::pretty_type_reprs.end())
    return;
  pretty_str_rep psr(max_level);
  psr.dispatch(t);
  ModelSplitter::pretty_type_reprs[t.unique_id] = std::string(psr.str()); 
}

const std::string ModelSplitter::get_pretty_rep(const rumur::TypeExpr& t) {
  auto res = ModelSplitter::pretty_type_reprs.find(t.unique_id);
  if (res != ModelSplitter::pretty_type_reprs.end())
    return res->second;
  if (const auto _tid = dynamic_cast<const TypeExprID*>(&t))
    return get_pretty_rep(*(_tid->referent->value));
  if (t.unique_id == ModelSplitter::model_unique_id)
    return ROMP_STATE_CLASS_NAME;
  return "__UNKNOWN_TYPE_REPR__";
}


// ModelSplitter &ModelSplitter::operator<<(std::string &s) {
//   out << s;
//   return *this;
// }

// ModelSplitter &ModelSplitter::operator<<(Node &n) {
//   dispatch(n);
//   return *this;
// }

} // namespace romp
