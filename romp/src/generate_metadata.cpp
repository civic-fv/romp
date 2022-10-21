/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file generate_metadata.cpp
 * 
 * @brief Output the metadata constructs for the model_checker
 * 
 * @date 2022/10/18
 * @version 0.2
 */

#include "generate_metadata.hpp"
#include "romp_def.hpp"
#include "nested_escape.hpp"
#include <murphi/murphi.h>
#include <sstream> 

namespace romp {

  using namespace murphi;


// << ========================================================================================== >> 
// <<                                     HELPER FUNCTIONS                                       >> 
// << ========================================================================================== >> 

namespace  {

  using namespace murphi;

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

std::string to_json(const Rule& rule, const std::string rule_type) {
  std::stringstream buf;
  buf << "{\"$type\":\"" << rule_type << "\",";
  if (auto _prop = dynamic_cast<const murphi::PropertyRule*>(&rule)) {
    buf << "\"type\":\"";
    switch (_prop->property.category) {
      case murphi::Property::ASSERTION:
        buf << "invariant"; break;
      case murphi::Property::ASSUMPTION:
        buf << "assume"; break;
      case murphi::Property::COVER:
        buf << "cover"; break;
      case murphi::Property::LIVENESS:
        buf << "liveness"; break;
    }
    buf << "\",\"expr\":\"" << nEscape(_prop->property.expr->to_string()) << "\",";
  } else if (auto _r = dynamic_cast<const murphi::SimpleRule*>(&rule)) {
    buf << "\"expr\":\"";
    if (_r->guard != nullptr)
      buf << nEscape(_r->guard->to_string());
    buf << "\",";
  }
  buf << "\"label\":\"" << nEscape(rule.name) << "\","
         "\"loc\":{\"$type\":\"location\","
                    // "\"file\":\"" << nEscape(CodeGenerator::input_file_path.string()) <<  "\","
                    // "\"inside\":\"global\","
                    "\"start\":["<< rule.loc.begin.line << "," << rule.loc.begin.column << "],"  
                    "\"end\":["<< rule.loc.end.line << "," << rule.loc.end.column << "]}";
  return buf.str();
}

std::string to_json(const Function& funct) {
  std::stringstream buf;
  buf << "{\"$type\":\"" << ((funct.return_type == nullptr) 
                              ? "procedure" 
                              : "function\","
                                "\"return-type\":\"" + nEscape(funct.return_type->to_string())) << "\","
      << "\"label\":\"" << nEscape(funct.name) << "\","
         "\"params\":[";
  std::string sep = "";
  for (auto& p : funct.parameters) {
    buf << sep << "{\"$type\":\"param\","
                   "\"id\":\"" << nEscape(p->name) << "\","
                   "\"type\":\"" << nEscape(p->type->to_string()) << "\"}";
    sep = ",";
  }
  buf << "],\"loc\":{\"$type\":\"location\","
                    // "\"file\":\"" << nEscape(CodeGenerator::input_file_path.string()) << "\","
                    // "\"inside\":\"global\","
                    "\"start\":["<< funct.loc.begin.line << "," << funct.loc.begin.column << "],"  
                    "\"end\":["<< funct.loc.end.line << "," << funct.loc.end.column << "]}}";
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

  std::string to_json(const ErrorStmt& rule) {
    std::stringstream buf;
    buf << "{\"$type\":\"error-statement\",";
    buf << "\"label\":\"" << nEscape(rule.message) << "\","
            "\"loc\":{\"$type\":\"location\","
                      "\"start\":["<< rule.loc.begin.line << "," << rule.loc.begin.column << "],"  
                      "\"end\":["<< rule.loc.end.line << "," << rule.loc.end.column << "]}";
    return buf.str();
  }

  std::string to_json(const PropertyStmt& prop, const std::string prop_type) {
    std::stringstream buf;
    buf << "{\"$type\":\"property\","
        << "\"type\":\"" << prop_type << "\","
        << "\"label\":\"" << nEscape(prop.message == "" ? prop.property.expr->to_string() : prop.message) << "\","
        << "\"expr\":\"" << nEscape(prop.property.expr->to_string()) << "\","
            "\"loc\":{\"$type\":\"location\","
                      "\"start\":["<< prop.loc.begin.line << "," << prop.loc.begin.column << "],"  
                      "\"end\":["<< prop.loc.end.line << "," << prop.loc.end.column << "]}";
    return buf.str();
  }
} // namespace <anon> 



// << ========================================================================================== >> 
// <<                              GENERATOR FUNCTION DEFINITIONS                                >> 
// << ========================================================================================== >> 

void generate_type_ids_metadata(CodeGenerator& gen, const Node& n) {
  struct GenerateTypeIds : public murphi::ConstTraversal {
    id_t next_type_id = 0u;
    CodeGenerator& out;
    std::string sep;
    GenerateTypeIds(CodeGenerator& gen_) : out(gen_) {}
    void visit_typedecl(const TypeDecl& n) {
      if (next_type_id != n.type_id)
        throw Error("DEV ERROR : typeID/typedecl does not line up with it's id",n.loc);
      out << sep << '"' << n.name << '"';
      sep = ",";
      ++next_type_id;
    }
  };
  GenerateTypeIds generator(gen);
  generator.dispatch(n);
}

// << ------------------------------------------------------------------------------------------ >> 


void generate_record_members_metadata(CodeGenerator& gen, const Node& n) {
  struct GenerateMemberLabels : public murphi::ConstTraversal {
    id_t next_field_id = 0u;
    CodeGenerator& out;
    std::string sep;
    GenerateMemberLabels(CodeGenerator& gen_) : out(gen_) {}
    void visit_record(const Record& n) {
      if (next_field_id != n.first_field_id)
        throw Error("DEV ERROR : record does not line up with its field id's",n.loc);
      for (const auto& m : n.fields)
        dispatch(*m);
      for (const auto& m : n.fields) {
        out << sep << '"' << m->name << '"';
        sep = ",";
      }
      next_field_id += n.fields.size();
    }
  };
  GenerateMemberLabels generator(gen);
  gen << '{';
  generator.dispatch(n);
  gen << '}';
}

// << ------------------------------------------------------------------------------------------ >> 


void generate_ruleset_metadata(CodeGenerator& gen, const Node& n) {
  struct GenerateRulesetMetadata : public murphi::ConstTraversal {
    CodeGenerator& out;
    // std::string sep;
    GenerateRulesetMetadata(CodeGenerator& gen_) : out(gen_) {}
    void visit_simplerule(const SimpleRule& n) {
      out << ROMP_MAKE_RULE_INFO_STRUCT(n,to_json(n,"rule")) ",";
    }
  };
  GenerateRulesetMetadata generator(gen);
  gen << '{';
  generator.dispatch(n);
  gen << '}';
}

// << ------------------------------------------------------------------------------------------ >> 


std::pair<id_t,id_t> generate_property_metadata(CodeGenerator& gen, const Node& n) {
  struct GeneratePropertyMetadata : public murphi::ConstTraversal {
    id_t next_property_id = 0u;
    id_t next_cover_id = 0u;
    id_t next_liveness_id = 0u;
    CodeGenerator& out;
    // std::string sep;
    GeneratePropertyMetadata(CodeGenerator& gen_) : out(gen_) {}
    void visit_propertyrule(const PropertyRule& n) {
      std::string pt;
      id_t id = ~0u;
      switch (n.property.category) {
        case Property::ASSERTION: pt = ROMP_PROPERTY_TYPE_INVAR; break;
        case Property::ASSUMPTION: pt = ROMP_PROPERTY_TYPE_ASSUME; break;
        case Property::COVER: pt = ROMP_PROPERTY_TYPE_COVER; id=next_cover_id++; break;
        case Property::LIVENESS: pt = ROMP_PROPERTY_TYPE_LIVENESS; id=next_liveness_id++; break;
      }
      out << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,id,n.name,pt,to_json(n,"property")) ",";
      ++next_property_id;
      // murphi::ConstTraversal::visit_propertyrule(n);
    }
    void visit_propertystmt(const PropertyStmt& n) {
      id_t id = ~0u;
      switch (n.property.category) {
      case Property::ASSERTION:
        out << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,id,n.message,ROMP_PROPERTY_TYPE_ASSERT, to_json(n,"assert")) ",";
        break;
      case Property::ASSUMPTION:
        out << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,id,n.message,ROMP_PROPERTY_TYPE_ASSUME, to_json(n,"assume")) ",";
        break;
      case Property::COVER:
        id = next_cover_id++;
        out << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,id,n.message,ROMP_PROPERTY_TYPE_COVER, to_json(n,"cover")) ",";
        break;
      case Property::LIVENESS:
        id = next_liveness_id++;
        out << ROMP_MAKE_PROPERTY_INFO_STRUCT(n,id,n.message,ROMP_PROPERTY_TYPE_LIVENESS, to_json(n,"liveness")) ",";
        break;
      }
      ++next_property_id;
    }
  };
  GeneratePropertyMetadata generator(gen);
  gen << '{';
  generator.dispatch(n);
  gen << '}';
  return std::make_pair(generator.next_cover_id,generator.next_liveness_id);
}

// << ------------------------------------------------------------------------------------------ >> 


void generate_startstate_metadata(CodeGenerator& gen, const Node& n) {
  struct GenerateStartstateMetadata : public murphi::ConstTraversal {
    CodeGenerator& out;
    // std::string sep;
    GenerateStartstateMetadata(CodeGenerator& gen_) : out(gen_) {}
    void visit_startstate(const Startstate& n) {
      out << ROMP_MAKE_STARTSTATE_INFO_STRUCT(n,to_json(n,"startstate")) ",";
    }
  };
  GenerateStartstateMetadata generator(gen);
  gen << '{';
  generator.dispatch(n);
  gen << '}';
}

// << ------------------------------------------------------------------------------------------ >> 


void generate_error_metadata(CodeGenerator& gen, const Node& n) {
  struct GenerateMErrorMetadata : public murphi::ConstTraversal {
    CodeGenerator& out;
    // std::string sep;
    GenerateMErrorMetadata(CodeGenerator& gen_) : out(gen_) {}
    void visit_errorstmt(const ErrorStmt& n) {
      out << ROMP_MAKE_ERROR_INFO_STRUCT(n,to_json(n)) ",";
    }
  };
  GenerateMErrorMetadata generator(gen);
  gen << '{';
  generator.dispatch(n);
  gen << '}';
}

// << ------------------------------------------------------------------------------------------ >> 


void generate_function_metadata(CodeGenerator& gen, const Node& n) {
  struct GenerateFunctMetadata : public murphi::ConstTraversal {
    CodeGenerator& out;
    // std::string sep;
    GenerateFunctMetadata(CodeGenerator& gen_) : out(gen_) {}
    void visit_function(const Function& n) {
      out << ROMP_MAKE_FUNCT_INFO_STRUCT(n, to_json(n), to_string(n)) ",";
    }
  };
  GenerateFunctMetadata generator(gen);
  gen << '{';
  generator.dispatch(n);
  gen << '}';
}

} // namespace romp
