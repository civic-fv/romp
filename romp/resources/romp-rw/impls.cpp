/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file impls.cpp
 * 
 * @brief implementations of functions that could not be put where they were declared,
 *        because they required something pre-decl'ed to be fully declared first.
 * 
 * @date 2022/10/05
 * @version 0.1
 */

#ifndef __romp__GENERATED_CODE
#pragma once
#include "pregen-fix.hpp"  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "include.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
#include "decl.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
#include "writers.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
#include "types.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
#include "error.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
#include "walker.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !! 
#endif

namespace romp {

  template<size_t EID, size_t B, class... U_M>
  inline void __assign(EnumType<EID,B>& _this, const ScalarsetUnionType<U_M...>& other) { _this = other.__get_value(); }
  template<size_t NID, size_t EID, size_t B, class... U_M>
  inline void __assign(ScalarsetType<NID,EID,B>& _this, const ScalarsetUnionType<U_M...>& other) { _this = other.__get_value(); }

  template<size_t L_ID, size_t L_B, size_t R_ID, size_t R_B>
  inline bool operator == (const EnumType<L_ID,L_B>& l, const EnumType<R_ID,R_B> r) { 
    return ((L_ID == R_ID) // this static expr should help the compiler optimize this per type definition. 
            && (l.value == r.value)); 
  }
  template<size_t L_ID, size_t L_B, size_t R_ID, size_t R_B>
  inline bool operator != (const EnumType<L_ID,L_B>& l, const EnumType<R_ID,R_B> r) { 
    return ((L_ID != R_ID) // this should help the compiler optimize this per type definition. 
            || (l.value != r.value)); 
  }

  template<class... L_M, class... R_M>
  inline bool operator == (const ScalarsetUnionType<L_M...>& l, const ScalarsetUnionType<R_M...> r) { return l.value == r.value; }
  template<class... L_M, class... R_M>
  inline bool operator != (const ScalarsetUnionType<L_M...>& l, const ScalarsetUnionType<R_M...> r) { return l.value != r.value; }

  template<size_t EID, size_t B, class... U_M>
  inline bool operator == (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u) {
#   if __cplusplus >= 201703L
      return ((ScalarsetUnionType<U_M...>::ContainsMember<EID,B>()) // this should help the compiler optimize this per specific templated instance. [[requires c++17]] to be static
              && (e.value == u.value));
#   else
      return e.value == u.value;
#   endif
  }
  template<size_t EID, size_t B, class... U_M>
  inline bool operator != (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u) {
#   if __cplusplus >= 201703L
      return (not (ScalarsetUnionType<U_M...>::ContainsMember<EID,B>()) // this should help the compiler optimize this per specific templated instance. [[requires c++17]]
              || (e.value != u.value));
#   else
      return e.value != u.value;
#   endif
  }
  template<class... U_M, size_t EID, size_t B>
  inline bool operator == (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e) { return (e == u); }
  template<class... U_M, size_t EID, size_t B>
  inline bool operator != (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e) { return (e != u); }

  /* this IsMember is the one associated with the IsMember() Murphi language operator */
  template<class ET, class... U_M>
  inline bool IsMember(const ScalarsetUnionType<U_M...>& u) {
    return ET::IsMember(u.value);
  }
  template<size_t EID, size_t B, class... U_M>
  inline bool IsMember(const ScalarsetUnionType<U_M...>& u) {
    return EnumType<EID,B>::IsMember(u.value);
  }

  ResultTree::~ResultTree() {
    for (auto p : unknown_causes) if (p!=nullptr) delete p;
    for (auto p : attempt_limits_reached) if (p!=nullptr) delete p;
    for (auto p : max_depths_reached) if (p!=nullptr) delete p;
#ifdef __romp__ENABLE_cover_property  
    for (auto p : completed_covers) if (p!=nullptr) delete p;
#endif
    for (auto _p : properties_violated)
      for (auto p : _p.second) if (p!=nullptr) delete p;
    for (auto _p : merrors_reached)
      for (auto p : _p.second) if (p!=nullptr) delete p;
#ifdef __romp__ENABLE_assume_property  
    for (auto _p : assumptions_violated)
      for (auto p : _p.second) if (p!=nullptr) delete p;
#endif
  }

  void ResultTree::insert(const Result* res) {
    switch (res->cause) {
      case Result::ATTEMPT_LIMIT_REACHED:
        attempt_limits_reached.push_back(res);
        break;
      case Result::MAX_DEPTH_REACHED:
        max_depths_reached.push_back(res);
        break;
      case Result::PROPERTY_VIOLATED: {
        const auto _me_p = dynamic_cast<const ModelPropertyError*>(res->tripped);
        if (properties_violated.find(*_me_p) == properties_violated.end())
          properties_violated[*_me_p] = std::vector<const Result*>{res};
        else
          properties_violated[*_me_p].push_back(res);
        ++n_properties_violated;
        break;
      }
      case Result::MERROR_REACHED: {
        const auto _me_e = dynamic_cast<const ModelMErrorError*>(res->tripped);
        if (merrors_reached.find(*_me_e) == merrors_reached.end())
          merrors_reached[*_me_e] = std::vector<const Result*>{res};
        else
          merrors_reached[*_me_e].push_back(res);
        ++n_merrors_reached;
        break;
      }
#ifdef __romp__ENABLE_assume_property
      case Result::ASSUMPTION_VIOLATED: {
        const auto _me_a = dynamic_cast<const ModelPropertyError*>(res->tripped);
        if (assumptions_violated.find(*_me_a) == assumptions_violated.end())
          assumptions_violated[*_me_a] = std::vector<const Result*>{res};
        else
          assumptions_violated[*_me_a].push_back(res);
        ++n_assumptions_violated;
        break;
      }
#endif
#ifdef __romp__ENABLE_cover_property
      case Result::COVER_COMPLETE:
        completed_covers.push_back(res);
        break;
#endif
      case Result::UNKNOWN_CAUSE:
      default:
        unknown_causes.push_back(res);
        break;
    }
#ifdef __ROMP__DO_MEASURE
    total_walk_active_time += res->active_time;
    total_walk_time += res->total_time;
#endif
    ++size;
    rules_fired += res->depth;
  }

  std::ostream& operator << (std::ostream& out, const ResultTree& results) {
    ostream_p _out(out, results.OPTIONS);
    _out << results;
    return out;
  }

  ostream_p& operator << (ostream_p& out, const ResultTree& r) {
    int i = 1; // int j = 1;
    size_t issues = 0; size_t abs_issues = 0;
#ifdef __romp__ENABLE_assume_property
    if (OPTIONS.r_assume && r.n_assumptions_violated > 0) {
      issues += r.assumptions_violated.size();
      abs_issues += r.n_assumptions_violated;
      out << out.indentation() << "\033[1;4mASSUMPTION(S) VIOLATED (n="<< r.assumptions_violated.size() 
          << " |n|=" << r.n_assumptions_violated << "):\033[0m\n";
      out.indent(); i = 1;
      for (const auto& _a : r.assumptions_violated) {  
        out << out.indentation()
            << "\033[1m-(" << (i++) << ") assume \"" << _a.first.label() << "\":\033[0m\n";
        out.indent();
        for (const auto& a : _a.second) {
          out << out.indentation()
              << "-[w#" << a->id << "] seed=" << a->root_seed << " start-id=" << a->start_id <<" depth=" << a->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << a->active_time << " (Δt=" << a->total_time << ')';
#endif
          if (not a->tripped->is_flat())
            out << out.nl()
                << "        quantifiers(" << a->tripped->quants() << ")\n";
          out << out.indentation() 
              << ((a->tripped->is_generic())
                  ? "        inside"
                  : "        last-rule")
              << "={"
              << a->inside->get_type()
              <<" \"" << a->inside->label() << "\"";
          if (not a->inside->is_flat())
              out << " quantifiers(" << a->inside->quants() << ")";
          out << "}\n";
        }
        out.dedent();
        ++i;
      }
      out.out << out._dedent() << std::endl;
    }
#endif
    if ((OPTIONS.attempt_limit != _ROMP_ATTEMPT_LIMIT_DEFAULT && OPTIONS.deadlock) 
          && r.attempt_limits_reached.size() > 0) {
        out << out.indentation() << "\033[1;4mATTEMPT LIMIT(S) REACHED (n=" 
                << r.attempt_limits_reached.size() << "):\033[0m\n";
        out.indent();
        i = 1;
        for (const auto& _al : r.attempt_limits_reached) {
          out << out.indentation()
              << "-(" << i << ") [w#" << _al->id << "] seed=" << _al->root_seed << " start-id=" << _al->start_id <<" depth=" << _al->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << _al->active_time << " (Δt=" << _al->total_time << ')';
#endif
          out << out.nl()
              << "        last-rule=";
          if (_al->inside != nullptr) {
            out << '{' << _al->inside->get_type() << " \"" << _al->inside->label() << "\"";
            if (not _al->inside->is_flat())
              out << " quantifiers(" << _al->inside->quants() << ")";
            out << "}\n";
          } else {
            out << "none\n";
          }
          ++i;
        }
      out.out << out._dedent() << std::endl;
     }
#ifdef __romp__ENABLE_cover_property
     if (OPTIONS.r_cover && r.completed_covers.size() > 0) {
      out << out.indentation() << "\033[1;4mCOVER(S) COMPLETED (n=" 
                << r.completed_covers.size() << "):\033[0m\n";
        out.indent();
        i = 1;
        for (const auto& _c : r.completed_covers) {
          out << out.indentation()
              << "-(" << i << ") [w#" << _c->id << "] seed=" << _c->root_seed << " start-id=" << _c->start_id <<" depth=" << _c->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << _c->active_time << " (Δt=" << _c->total_time << ')';
#endif
          out << out.nl()
              << "        last-rule={" << _c->inside->get_type() << " \"" << _c->inside->label() << "\"";
              if (not _c->inside->is_flat())
                out << " quantifiers(" << _c->inside->quants() << ")";
          out << "}\n";
          ++i; 
        }
      out.out << out._dedent() << std::endl;
     }
#endif
    if (OPTIONS.report_all && r.max_depths_reached.size() > 0) {
      out << out.indentation() << "\033[1;4mMAX DEPTH(S) REACHED (n=" 
                << r.max_depths_reached.size() << "):\033[0m";
        out.indent();
        i = 1;
        for (const auto& _r : r.max_depths_reached) {
          out << out.nl()
              << "-(" << i++ << ") [w#" << _r->id << "] seed=" << _r->root_seed << " start-id=" << _r->start_id;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << _r->active_time << " (Δt=" << _r->total_time << ')';
#endif
        }
      out.out << out._dedent() << std::endl;
    }
    if (r.n_merrors_reached > 0) {
      issues += r.merrors_reached.size();
      abs_issues += r.n_merrors_reached;
      out << out.indentation() << "\033[1;4mERROR STATEMENT(S) REACHED (n="<< r.merrors_reached.size() 
          << " |n|=" << r.n_merrors_reached << "):\033[0m\n";
      out.indent(); i = 1;
      for (const auto& _a : r.merrors_reached) {
        out << out.indentation()
            << "\033[1m-(" << (i++) << ") error \"" << _a.first.label() << "\":\033[0m\n";
        out.indent();
        for (const auto& a : _a.second) {
          out << out.indentation()
              << "-[w#" << a->id << "] seed=" << a->root_seed << " start-id=" << a->start_id <<" depth=" << a->depth
#ifdef __ROMP__DO_MEASURE
              << " t=" << a->active_time << " (Δt={" << a->total_time << ')'
#endif
              << out.nl()
              << "        IN-RULE"
              << "={" << a->inside->get_type() << " \"" << a->inside->label() << "\"";
          if (not a->inside->is_flat())
              out << " quantifiers(" << a->inside->quants() << ")";
          out << "}\n";
        }
        out.dedent();
        ++i;
      }
      out.out << out._dedent() << std::endl;
    }
    if (r.n_properties_violated > 0) {
      issues += r.properties_violated.size();
      abs_issues += r.n_properties_violated;
      out << out.indentation() << "\033[1;4mPROPERTY(S) VIOLATED (n="<< r.properties_violated.size() 
          << " |n|=" << r.n_properties_violated << "):\033[0m\n";
      out.indent(); i = 1;
      for (const auto& _a : r.properties_violated) {
        const PropertyInfo& _info =_a.first.info();
        out << out.indentation()
            << "\033[1m-(" << (i++) << ") " << _info.type << " \"" << _info.label << "\":\033[0m "
                "(x"<< _a.second.size() <<")\n";
        out.indent();
        int j = 0;
        for (const auto& a : _a.second) {
          if (j > 2 && not (OPTIONS.report_all || OPTIONS.report_error)) { 
            out << out.indentation() << "-[..] ... " << _a.second.size()-j << " more ...\n"; 
            break;
          }
          out << out.indentation()
              << "-[w#" << a->id << "] seed=" << a->root_seed << " start-id=" << a->start_id <<" depth=" << a->depth;
#ifdef __ROMP__DO_MEASURE
          out << " t=" << a->active_time << " (Δt=" << a->total_time << ')';
#endif
          if (not a->tripped->is_flat())
            out << out.nl()
                << "        quantifiers(" << a->tripped->quants() << ")";
          out << out.nl()
              << ((a->tripped->is_generic())
                  ? "        inside"
                  : "        last-rule")
              << "={"
              << a->inside->get_type()
              <<" \"" << a->inside->label() << "\"";
          if (not a->inside->is_flat())
              out << " quantifiers(" << a->inside->quants() << ")";
          out << "}\n";
          ++j;
        }
        out.dedent();
        ++i;
      }
      out.out << out._dedent() << std::endl;
    }
    if (OPTIONS.report_all && r.unknown_causes.size() > 0) {
      issues += r.unknown_causes.size();
      abs_issues += r.unknown_causes.size();
      out << out.indentation() << "\033[41;37;1;4mUNKNOWN ERROR(S) (n=" 
                << r.unknown_causes.size() << "):\033[21;24m\n";
        out.indent();
        i = 1;
        for (const auto& _r : r.unknown_causes) {
          out << out.indentation()
              << "-(" << i++ << ") ``" << ({_r->inside->write_root_excpt_what(out.out); "''\n";})
              << out._indent()
              << "-[w#" << _r->id << "] seed=" << _r->root_seed << " start-id=" << _r->start_id << " depth=" << _r->depth
#ifdef __ROMP__DO_MEASURE
              << " t=" << _r->active_time << " (Δt=" << _r->total_time << ")\n"
#endif
              << "        inside={"
              << _r->inside->get_type()
              << " \"" << _r->inside->label() << '"';
          if (not _r->inside->is_flat())
            out << " quantifiers(" << _r->inside->quants() << ")";
          out << "}\n";
          out.dedent();
        }
      out.out << out._dedent() << "\033[0m" << std::endl;
    }
    std::string color = ((issues>0) ? "\033[30;1;4m" : "\033[32;1m");
    out << out.nl()
        << out.nl() << "\033[1;4mSUMMARY:\033[0m" << out.indent()
        << out.nl() << "       issues found: n=" << color << issues << "\033[0m"
                                          << "  (|n|=" << color << abs_issues << "\033[0m)"
        << out.nl() << "total rules applied: " << r.rules_fired
        << out.nl() << "  avg rules applied: " << std::setprecision(1) << (r.rules_fired/r.size)
#ifndef __ROMP__DO_MEASURE
        << out.nl() << "            runtime: " << r.get_time();
#else
        << out.nl() << "    total walk time: t=" << r.total_walk_active_time << " "
                                          "(Δt=" << r.total_walk_time << ")" 
        << out.nl() << "     mean walk time: mean(t)=" << (r.total_walk_active_time/r.size) << " "
                                           "(mean(Δt)=" << (r.total_walk_time/r.size) << ')' 
        << out.nl() << "     actual runtime: " << r.get_time();
#endif
    out.out << "\n\n" << std::flush;
    return out;
  }


} // namespace romp
