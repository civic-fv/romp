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
// #include "walker.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif

namespace romp {

constexpr size_t _ROMP_ATTEMPT_LIMIT_DEFAULT() {
# if (_ROMP_RULE_SELECTION_ALGO == (1ul))
    return ((_ROMP_MAX_RULESET_RULE_COUNT) * (_ROMP_RULESETS_LEN)); //TODO might cause compilation issues
# elif (_ROMP_RULE_SELECTION_ALGO == (2ul))
    return (_ROMP_RULE_COUNT);
# else
    return (INT16_MAX);
# endif
}

  template<size_t EID, size_t B, class... U_M>
  inline void __assign(EnumType<EID,B>& _this, const ScalarsetUnionType<U_M...>& other) { _this = other.__get_value(); }
  template<size_t EID, size_t B, class... U_M>
  inline void __assign(ScalarsetType<EID,B>& _this, const ScalarsetUnionType<U_M...>& other) { _this = other.__get_value(); }

  Result::~Result() { if (tripped != nullptr) delete tripped; if (inside != nullptr) delete inside; }

  // template<size_t L_ID, size_t L_B, size_t R_ID, size_t R_B>
  // inline bool operator == (const EnumType<L_ID,L_B>& l, const EnumType<R_ID,R_B> r) {
  //   return ((L_ID == R_ID) // this static expr should help the compiler optimize this per type definition.
  //           && (l.value == r.value));
  // }
  // template<size_t L_ID, size_t L_B, size_t R_ID, size_t R_B>
  // inline bool operator != (const EnumType<L_ID,L_B>& l, const EnumType<R_ID,R_B> r) {
  //   return ((L_ID != R_ID) // this should help the compiler optimize this per type definition.
  //           || (l.value != r.value));
  // }

  // template<class... L_M, class... R_M>
  // inline bool operator == (const ScalarsetUnionType<L_M...>& l, const ScalarsetUnionType<R_M...> r) { return l.value == r.value; }
  // template<class... L_M, class... R_M>
  // inline bool operator != (const ScalarsetUnionType<L_M...>& l, const ScalarsetUnionType<R_M...> r) { return l.value != r.value; }

//   template<size_t EID, size_t B, class... U_M>
//   inline bool operator == (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u) {
// #   if __cplusplus >= 201703L
//       return ((ScalarsetUnionType<U_M...>::ContainsMember<EID,B>()) // this should help the compiler optimize this per specific templated instance. [[requires c++17]] to be static
//               && (e.value == u.value));
// #   else
//       return e.value == u.value;
// #   endif
//   }
//   template<size_t EID, size_t B, class... U_M>
//   inline bool operator != (const EnumType<EID,B>& e, const ScalarsetUnionType<U_M...>& u) {
// #   if __cplusplus >= 201703L
//       return (not (ScalarsetUnionType<U_M...>::ContainsMember<EID,B>()) // this should help the compiler optimize this per specific templated instance. [[requires c++17]]
//               || (e.value != u.value));
// #   else
//       return e.value != u.value;
// #   endif
//   }
//   template<class... U_M, size_t EID, size_t B>
//   inline bool operator == (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e) { return (e == u); }
//   template<class... U_M, size_t EID, size_t B>
//   inline bool operator != (const ScalarsetUnionType<U_M...>& u, const EnumType<EID,B>& e) { return (e != u); }

  // /* this IsMember is the one associated with the IsMember() Murphi language operator */
  // template<class ET, typename VT>
  // inline bool IsMember(const VT& u) {
  //   return ET::IsMember(u.__get_value());
  // }
  // template<size_t EID, size_t B, class... U_M>
  // inline bool IsMember(const ScalarsetUnionType<U_M...>& u) {
  //   return EnumType<EID,B>::IsMember(u.value);
  // }

  // << ------------------------------------------------------------------------------------------ >>

  ostream_p::ostream_p(std::ostream& out_, const Options& OPTIONS_, unsigned int level_)
    : out(out_), _width(level_*OPTIONS_.tab_size), OPTIONS(OPTIONS_)
    { _indentation = std::string(_width,OPTIONS_.tab_char); }
  inline const stream_void ostream_p::dedent() {
    if (((signed)_width)-((signed)OPTIONS.tab_size) >= 0)
      _width-=OPTIONS.tab_size;
    _indentation = std::string(_width,OPTIONS.tab_char);
    return S_VOID;
  }
  inline const stream_void ostream_p::indent() { _indentation = std::string((_width+=OPTIONS.tab_size),OPTIONS.tab_char); return S_VOID; }

  // << ------------------------------------------------------------------------------------------ >>

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
      case Result::DEADLOCK:
        deadlocks_reached.push_back(res);
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
    ostream_p _out(out, results.OPTIONS, 0);
    _out << results;
    return out;
  }

  ostream_p& operator << (ostream_p& out, const ResultTree& r) {
    int i = 1; // int j = 1;
    size_t issues = 0; size_t abs_issues = 0;
#ifdef __romp__ENABLE_assume_property
    if (r.OPTIONS.r_assume && r.n_assumptions_violated > 0) {
      issues += r.assumptions_violated.size();
      abs_issues += r.n_assumptions_violated;
      out << out.indentation() << "\033[1;4mASSUMPTION(S) VIOLATED (n="<< r.assumptions_violated.size()
          << " |n|=" << r.n_assumptions_violated << "):\033[0m\n";
      out.indent(); i = 1;
      for (const auto& _a : r.assumptions_violated) {
        if (i > _ROMP_HIST_LEN && not (r.OPTIONS.report_all || r.OPTIONS.report_error)) {
          out << out.indentation() << "-(..) ... " << _a.second.size()-(i-1) << " more ...\n";
          break;
        }
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
    if ((r.OPTIONS.attempt_limit != _ROMP_ATTEMPT_LIMIT_DEFAULT() && r.OPTIONS.deadlock)
          && r.attempt_limits_reached.size() > 0) {
        out << out.indentation() << "\033[1;4mATTEMPT LIMIT(S) REACHED (n="
                << r.attempt_limits_reached.size() << "):\033[0m\n";
        out.indent();
        i = 1;
        for (const auto& _al : r.attempt_limits_reached) {
          if (i > _ROMP_HIST_LEN && not (r.OPTIONS.report_all)) {
            out << out.indentation() << "-(..) ... " << r.attempt_limits_reached.size()-(i-1) << " more ...\n";
            break;
          }
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
    if ((r.OPTIONS.deadlock)
          && r.deadlocks_reached.size() > 0) {
        out << out.indentation() << "\033[1;4mDEADLOCK(S) REACHED (n="
                << r.deadlocks_reached.size() << "):\033[0m\n";
        out.indent();
        i = 1;
        for (const auto& _al : r.deadlocks_reached) {
          if (i > _ROMP_HIST_LEN && not (r.OPTIONS.report_all)) {
            out << out.indentation() << "-(..) ... " << r.deadlocks_reached.size()-(i-1) << " more ...\n";
            break;
          }
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
     if (r.OPTIONS.r_cover && r.completed_covers.size() > 0) {
      out << out.indentation() << "\033[1;4mCOVER(S) COMPLETED (n="
                << r.completed_covers.size() << "):\033[0m\n";
        out.indent();
        i = 1;
        for (const auto& _c : r.completed_covers) {
          if (i > _ROMP_HIST_LEN+1 && not (r.OPTIONS.report_all)) {
            out << out.indentation() << "-[..] ... " << r.completed_covers.size()-(i-1) << " more ...\n";
            break;
          }
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
    if (r.OPTIONS.report_all && r.max_depths_reached.size() > 0) {
      out << out.indentation() << "\033[1;4mMAX DEPTH(S) REACHED (n="
                << r.max_depths_reached.size() << "):\033[0m";
        out.indent();
        i = 1;
        for (const auto& _r : r.max_depths_reached) {
          if (i > _ROMP_HIST_LEN && not (r.OPTIONS.report_all)) {
            out << out.indentation() << "-(..) ... " << r.max_depths_reached.size()-(i-1) << " more ...\n";
            break;
          }
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
        int j = 0;
        for (const auto& a : _a.second) {
          if (j > _ROMP_HIST_LEN && not (r.OPTIONS.report_all || r.OPTIONS.report_error)) {
            out << out.indentation() << "-[..] ... " << _a.second.size()-j << " more ...\n";
            break;
          }
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
            << "\033[1m-(" << (i) << ") " << _info.type << " \"" << _info.label << "\":\033[0m "
                "(x"<< _a.second.size() <<")\n";
        out.indent();
        int j = 0;
        for (const auto& a : _a.second) {
          if (j > 2 && not (r.OPTIONS.report_all || r.OPTIONS.report_error)) {
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
    if (r.OPTIONS.report_all && r.unknown_causes.size() > 0) {
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
        << out.nl() << "\033[1;4mRW SUMMARY:\033[0m" << out.indent()
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
        << out.nl() << "         RW runtime: " << r.get_time();
#endif
    out.out << "\n\n" << std::flush;
    return out;
  }


void print_help() {
  using namespace std;
  Options default_opts;
  // clang-format off
  std::cout <<
    "This is a murphi model checker generated from the romp random walker tool.\n"
    "   generated from: " __model__filename "\n"
    "\n\n"
    "CLI USAGE:    <> - required  {} - optional  * - can have 0 or more\n"
    "   ./<this-file> {options}*\n"
    "\n"
    "RULE SELECTION ALGO: \n"
    "    note: change this using the --selection-algo/-s option in the romp tool\n"
# if (_ROMP_RULE_SELECTION_ALGO == (0ul))
    "  ---- 100% random everything [opt 0] ----\n"
    "  (1) At every step CHOOSE a random rule.\n"
    "  (2) CHOOSE the ruleset params at random.\n"
    "  (3) CHECK the guard\n"
    "      IF it returns true THEN GOTO step 4\n"
    "        ELSE RETURN to step 1 for next simulation step.\n"
    "  (4) APPLY the rule.\n"
    "  (5) CHECK the global properties\n"
    "  (6) RETURN to step 1 for the next simulation step\n"
# elif (_ROMP_RULE_SELECTION_ALGO == (2ul))
    "  ---- Random everything without replacement until successful [opt: 2] ----\n"
    "  (1) CREATE a \"bag\" of all rules with all of their ruleset param options\n"
    "  (2) CHOOSE a rule with its ruleset param(s) from the \"bag\" at random\n"
    "      (IF bag empty, THEN end walk early -deadlock-)\n"
    "  (3) CHECK the guard,\n"
    "      IF it returns true THEN GOTO step 4,\n"
    "        ELSE RETURN to step 2 for the next simulation step.\n"
    "  (4) APPLY the rule.\n"
    "  (5) CHECK the global properties (IF any fail THEN end the walk)\n"
    "  (6) RETURN to step 1 for the next simulation step.\n"
# elif (_ROMP_RULE_SELECTION_ALGO == (3ul))
    "  ----  Heuristic Symmetry Reduction [opt: 3] ----\n"
    "  (1) At every step CHOOSE a random rule\n"
    "  (2) CHOOSE it's ruleset parameters by the using next combination in\n"
    "       lexicographic order.\n"
    "  (3) CHECK the guard,\n"
    "      IF it returns true THEN GOTO step 4 ELSE GOTO step 5.\n"
    "  (4) APPLY the rule.\n"
    "  (5) CHECK the global properties (IF any fail THEN end the walk)\n"
    "  (6) regardless of the results of step 3\n"
    "      RETURN to step 1 for the next simulation step.\n"
# else // default
    "  ---- Random Ruleset params without replacement [opt 1: DEFAULT] ----\n"
    "  (1) CREATE a \"bag\" of all of the rules (not specifying ruleset params)\n"
    "  (2) CHOOSE a rule at random from the \"bag\" of rules\n"
    "      (IF rule \"bag\" empty THEN end walk early -deadlock-)\n"
    "  (3) CREATE a \"bag\" of all possible ruleset param combinations possible\n"
    "  (4) CHOOSE a set of ruleset params from the params \"bag\" at random\n"
    "      (IF params bag empty, but params to fill THEN RETURN to step 2)\n"
    "  (5) CHECK the guard,\n"
    "      IF it returns true THEN GOTO step 6,\n"
    "        ELSE RETURN to step 4 for the next simulation step.\n"
    "  (6) APPLY the rule\n"
    "  (7) CHECK the global properties (if any fail end the walk)\n"
    "  (8) RETURN to step 1 for the next simulation step.\n"
# endif
    "\n"
    "NOTE:\n"
    "  Option flags and arguments are NOT POSIX compliant!\n"
    "  Please separate all options and their arguments with spaces,\n"
    "   and do not join multiple short option flags into one.\n"
    "    (i.e. `-s <str/int>` and `-y` must be input as\n"
    "          ``-y -s 5`` and NOT ``-ys 5``, ``-ys5``, \n"
    "            ``-ys=5``, ``-y -s=5``, or ``-y --seed=5``)\n"
    "\n"
    "GENERAL OPTIONS:\n"
    "   -h | --help      Display help information (this page).\n"
    "   -y | -l          Launch without prompting (skip launch prompt).\n"
    "   --list-starts    Output a list of all the ruleset expanded\n"
    "     | -ls            startstates & their id's\n"
    "                     (see --start-id/-sid for more info)\n"
    "\n"
    "RANDOM WALKER OPTIONS:\n"
    "  --depth <int>     Maximum number of rules to apply in a walk \n"
    "    | -d <int>        before termination.\n"
    "                      default: " << default_opts.depth << "\n"
    "  --threads <int>   Specifies the number of threads to use.\n"
    "    | -ptn <int>      default: " << default_opts.threads << " (machine specific)\n"
    "  --walks <int>     Specifies the number of random  walks to do.\n"
    "     | -w <int>       default: " << _ROMP_THREAD_TO_RW_RATIO << " * #-of-threads\n"
    "  --single-walk     Perform a single random walker on a single thread.\n"
    "     | -sw            note: overrides -ptn/--threads \n"
    "                              & -w/--walks/--walk-count\n"
    "  --seed <str/int>  Random seed for generating the random walks\n"
    "    | -s <str/int>    default: current system time\n"
    "  --even-start      Determine startstate for even distribution\n"
    "    | -es             rather than random choice (default behavior).\n"
    "  --start-id <id>   Set a single startstate to use (For all walks).\n"
    "    | -sid <id>       <id> is an int determined by a startstate's\n"
    "                      position in the file after ruleset expansion.\n"
    "                      Valid <id> values are integers between:\n"
    "                         0 to " << _ROMP_STARTSTATES_LEN-1 << " inclusive\n"
    "                      Use -ls/--list-starts to see mappings of id's\n"
    "                        to the ruleset expanded startstates of\n"
    "                        of your model.\n"
    "                      NOTE: overrides --even-start/-es\n"
    "\n"
    "INITIAL BFS CONFIGURATION:\n"
    "You can start your romp with a limited Breadth first search by using the\n"
    " following command.  This can allow you to increase the likely converge of the\n"
    " statespace covered by each romp, but does prevent you from using the normal\n"
    " strategy of using a mass romp then repeating walks of interest in a \n"
    " single walk with traces enabled.  This is because the pseudo random nature of\n"
    " the romp process is not preserved through the BFS process.  We recommend\n"
    " instead just rerunning the same config with traces enabled if you need more\n"
    " detailed information, it may be slower but it will work.\n"
    "  --bfs {single|multi} {int}  Enables an initial Breadth First Search of the\n"
    "    | -bfs {s|m} {int}          statespace, that is either single threaded or\n"
    "                                multithreaded (defaults to single).\n"
    "                                The BFS will terminate and a swarm of random\n"
    "                                walkers will start when there are enough\n"
    "                                unique states in the BFS queue to have the\n"
    "                                number of walkers specified with the `-w` flag\n"
    "                                where each unique state gets {int} random walks\n"
    "                                to increase the total coverage\n"
    "                                ({int} defaults to " << default_opts.bfs_coefficient << ").\n"
    "  --bfs-limit <int>           Sets a limit on how long the initial BFS can go\n"
    "    | -bfsl <int>               on for.  This is measured in number of rules\n"
    "                                applied. (<int> defaults to " << default_opts.bfs_limit << ")\n"
    "\n"
    "PROPERTY CONFIGURATIONS:\n"
    "  --no-deadlock           Disable Deadlock detection.\n"
    "    | -nd                   (overrides all property options below)\n"
#ifdef __romp__ENABLE_liveness_property
    "  --liveness-check {int}  Allows you to enable a heuristic test for\n"
    "    | -lc {int}             rumur's liveness property. Where it \n"
    "                            require the properties expr to resolve\n"
    "                            to true with in {int} rule applications\n"
    "                            since the start or the last time it was\n"
    "                            true."
    "                            {int} - an optional arg (see above).\n"
    "                              default: " << default_opts.lcount << "\n"
#endif
#ifdef __romp__ENABLE_cover_property
    "  --complete-on-cover {int} Allows you to enable a heuristic test"
    "    | --cover-check {int}     for rumur's cover property. Where it\n"
    "    | -cc {int}               considers a walk complete once every\n"
    "                              cover property has been reached {int}\n"
    "                              times.\n"
    "                              {int} - an optional arg (see above).\n"
    "                                default: " << default_opts.cover_count << "\n"
#endif
    "  --attempt-guard {int}   Stop a random walk if no randomly \n"
    "    | -ag {int}             selected rule can be applied to a State\n"
    "                            after {int} many rules in a row.\n"
    "                            {int} - an optional arg (see above).\n"
    "                              (default: 2x #-of-rules in the model)\n"
    "  --loop-limit {int}      Same thing as --attempt-guard/-ag. \n"
    "    | -ll {int}             {int} - an optional arg (see above).\n"
    "                              (default: 2x #-of-rules in the model)\n"
    "\n"
    "Trace Options\t\n"
    "  --trace {dir-path}    Enable detailed traces to be made for every\n"
    "    | -t {dir-path}       random walk performed. Outputs as a \n"
    "                          separate ``compressed json'' file for \n"
    "                          each random walk performed.\n"
    "                          NOTE: slows down the process noticeably!\n"
    "                          {dir-path} - (optional) the directory you\n"
    "                            want to have the trace files output to.\n"
    "                            default: \""<< default_opts.trace_dir <<"\"\n"
    "\n"
    "RESULT OUTPUT OPTIONS:\n"
    "  --report-error        Provide detailed report for each walk that\n"
    "    | -re                 ends in an ``error''.\n"
    "    | -e                  (aka: violates a property or reaches a \n"
    "                            murphi error statement)\n"
    "                          (NOTE: --single-walk/-sw only outputs \n"
    "                            this and not the summery data)"
    "  --report-all          Report on all walks not just those with \n"
    "    | --all              ``errors''. Including those stopped by \n"
    "    | -a                  the --attempt-guard/-ag/--loop-limit/-ll\n"
    "                          option, or max --depth/-d being reached.\n"
#ifdef __romp__ENABLE_assume_property
    "                          This also performs --report-assume/-ra.\n"
    "  --report-assume       Report walks that are violate an assume\n"
    "    | --r-assume          property (defined by rumur), rather than\n"
    "    | -ra                 just discarding them as invalid states.\n"
    "                          (NOTE: only effective if --report-error\n"
    "                            is provided)\n"
#endif
#ifdef __romp__ENABLE_cover_property
    "                          This also performs --report-assume/-ra.\n"
    "  --report-cover        Report walks that ``complete on cover''\n"
    "    | --r-cover           (see --complete-on-cover for more info)\n"
    "    | -rc                 \n"
#endif
  //  "  --r-history <int>     Specify how much of a history of rules\n"
  //  "    | -rhl <int>          applied you want to see in a walks report\n"
  //  "                          <int> - (required) size of history buffer\n"
  //  "                            default: " << default_opts.history_length << "\n"
  //  "                          NOTE: larger the size == more RAM used.\n"
    "  --r-omit-state        Don't output the values in the model state\n"
    "    | -ros                in the results\n"
    "  --r-show-type         Output variable type next to name when\n"
    "    | -rst                reporting the value of the model state\n"
    "  --r-tab-size <int>    Set the indentation size for the result \n"
    "    | -rts <int>          output (NOTE: not used for trace output)\n"
    "                          (default: "<< default_opts.tab_size <<")\n"
    "  --r-use-tab           Indent using tab chars instead of spaces.\n"
    "    | -rut                (NOTE: not used in json trace output)\n"
    "                          (NOTE: overrides --r-tab-size/-rts)\n"
  //  "  --output <file-path>  Specify a file you wish to output to\n"
  //  "    | -o <file-path>      instead of to stdout.\n"
    "\n"
    << std::endl;
    // clang-format on
}

std::string validate_dir_path(const std::string val) {
  auto start = val.begin();
  auto end = --(val.end());
  while (start != val.end() && isspace(*start))
    ++start;
  while (end != start && isspace(*end))
    --end;
  if (start == end) {
    std::cerr << "invalid argument : ``" << val << "`` is not a valid file/dir path !!\n" << std::flush;
    exit(EXIT_FAILURE);
  }
  if (*end != '/' && *end != '\\')
    return std::string(start, end) + '/';
  return std::string(start, end);
}

void list_starts() {
  std::cout << "\nStartState List (w/ id's)\n";
  for (size_t i=0; i<_ROMP_STARTSTATES_LEN; ++i)
    std::cout << "  (" << i << ") " << ::__caller__::STARTSTATES[i] << "\n";
  std::cout << std::flush;
}


void Options::parse_args(int argc, char **argv) {
  Options default_opts;
  bool threads_provided = false;
  bool walks_provided = false;
  bool start_provided = false;
  bool guard_provided = false;

  for (int i = 1; i < argc; ++i) {

    if ("-h" == std::string(argv[i]) || "--help" == std::string(argv[i])) { // to print help message and ( result of comparison
                                                  // against a string literal is unspecified)
      print_help();
      exit(EXIT_SUCCESS);
    } else if ("-l" == std::string(argv[i]) || "-y" == std::string(argv[i])) {
      skip_launch_prompt = true;
    } else if ("-es" == std::string(argv[i]) || "--even-start" == std::string(argv[i])) {
      do_even_start = true;
    } else if ("-ls" == std::string(argv[i]) || "--list-starts" == std::string(argv[i])) {
      list_starts();
      exit(EXIT_SUCCESS);
    }
     else if ("-sid" == std::string(argv[i]) || "--start-id" == std::string(argv[i])) {
      start_provided = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        ++i;
        try {
          start_id = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided start-id was not a number (NaN) !! (for -sid/--start-id flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided start-id was out of range (for --sid/--start-id flag) must be "
                       "between 0 and " << _ROMP_STARTSTATES_LEN-1 << " to be a valid start-id!\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "invalid argument : -sid/--start-id requires you to provide a value immediately after (positive integer),\n"
                     "                      else exclude it to use default value: "
                  <<start_id<< std::endl;
        exit(EXIT_FAILURE);
      }
      if (start_id >= _ROMP_STARTSTATES_LEN) {
        std::cerr << "invalid argument : provided start-id was out of range (for --sid/--start-id flag) must be "
                      "between 0 and " << _ROMP_STARTSTATES_LEN-1 << " to be a valid start-id!\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
    }
     else if ("-d" == std::string(argv[i]) || "--depth" == std::string(argv[i])) {
      if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
        ++i;
        try {
          depth = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided walk/search depth was not a number (NaN) !! (for -d/--depth flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided walk/search depth was out of range (for -d/--depth flag) must be "
                       "unsigned int (aka must be positive)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "invalid argument : -d/--depth requires you to provide a value immediately after (positive integer),\n"
                     "                      else exclude it to use default value: "
                  << ((depth == INT32_MAX) ? "INT32_MAX" : std::to_string(depth)) << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if ("-ptn" == std::string(argv[i]) || "--threads" == std::string(argv[i])) {
      threads_provided = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        ++i;
        try {
          threads = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided walk/search threads was not a number (NaN) !! (for -ptn/--threads flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided walk/search threads was out of range (for -ptn/--threads flag) must be "
                       "unsigned int (aka must be positive)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr
            << "invalid argument : -ptn/--threads requires you to provide a value immediately after (positive integer),\n"
               "                      else exclude it to use default value: "
            << threads << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if ("-sw" == std::string(argv[i]) || "--single-walk" == std::string(argv[i])) {
      do_single = true;
    } else if ("-w" == std::string(argv[i]) || "--walks" == std::string(argv[i]) || "--walk-count" == std::string(argv[i])) {
      walks_provided = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
        ++i;
        try {
          walks = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided number of random walkers was not a number (NaN) !! (for "
                       "-w/--walk-count flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided number of random walkers was out of range "
                       "(for -w/--walks/--walk-count flag) must "
                       "be unsigned int (aka must be positive)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "invalid argument : -w/--walks requires you to provide a value immediately after (positive integer),\n"
                     "                      else exclude it to use default value (default: "
                  << _ROMP_THREAD_TO_RW_RATIO << " x #-of-threads)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
    } else if ("-s" == std::string(argv[i]) || "--seed" == std::string(argv[i])) {
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        seed_str = argv[i];
        try {
          rand_seed = std::stoul(argv[i + 1], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::hash<std::string> str_hash;
          rand_seed = str_hash(argv[i + 1]);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided seed was out of range (for -s/--seed flag) must be unsigned int\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
        i++;
      } else { // rand_seed = std::time(NULL); // no need
        std::cerr << "invalid argument : -s/--seed requires you to provide a seed after the flag\n"
                     "                   else exclude it to use default value: (current_system_time)\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
    } else if ("-nd" == std::string(argv[i]) || "--no-deadlock" == std::string(argv[i])) {
      deadlock = false;
#ifdef __romp__ENABLE_liveness_property
    } else if ("-lc" == std::string(argv[i]) || "--liveness-check" == std::string(argv[i])) {
      liveness = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
        ++i;
        try {
          lcount = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided liveness check limit was not a number (NaN) !! (for -lc/--liveness-check "
                       "flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided liveness check limit was out of range (for -lc/--liveness-check flag) "
                       "must be unsigned "
                       "int (aka must be positive)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      }
#endif
#ifdef __romp__ENABLE_cover_property
    } else if ("-cc" == std::string(argv[i]) || "--complete-on-cover" == std::string(argv[i]) || "--cover-check" == std::string(argv[i])) {
      complete_on_cover = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
        ++i;
        try {
          cover_count = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided cover property coverage goal was not a number (NaN) !!\n"
                       "                   |-> (for -cc/--cover-check/--complete-on-cover flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided cover property coverage goal was out of range must be unsigned int (aka "
                       "must be positive & less than 2.147 billion)\n"
                       "                 |-> (for -cc/--cover-check/--complete-on-cover flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      }
    } else if ("-rc" == std::string(argv[i]) || "--r-cover" == std::string(argv[i]) || "--report-cover" == std::string(argv[i])) {
      r_cover = true;
#endif
    } else if ("-ag" == std::string(argv[i]) || "-ll" == std::string(argv[i]) || "-al" == std::string(argv[i])
                || "--attempt-guard" == std::string(argv[i]) || "--loop-limit" == std::string(argv[i]) || "--attempt-limit" == std::string(argv[i])) {
      // do_attempt_guard = true;  // just check to make sure this value is not 0
      guard_provided = true;
      attempt_limit = _ROMP_RULE_COUNT * 2;
      if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
        ++i;
        try {
          attempt_limit = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided attempt limit was not a number (NaN) !!\n"
                       "                   |-> (for -al/--attempt-limit or -ag/--attempt-guard or -ll/--loop-limit flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided attempt limit was out of range must be unsigned int (aka "
                       "must be positive & less than 2.147 billion)\n"
                       "                   |-> (for -al/--attempt-limit or -ag/--attempt-guard or -ll/--loop-limit flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        attempt_limit = _ROMP_RULE_COUNT;
        std::cerr << "\nWARNING : no attempt limit was provided, but it was enabled.\n"
                     "        |-> default value will be used (default: " << _ROMP_RULE_COUNT << " (# of rules post ruleset expansion))\n"
                  << std::flush;
      }
    // } else if ("-rhl" == std::string(argv[i]) || "--r-history" == std::string(argv[i])) {
    //   // result_history = true;
    //   if (i + 1 < argc && '-' != argv[i + 1][0]) { // is it not argv[i+1]
    //     ++i;
    //     try {
    //       history_length = std::stoul(argv[i], nullptr, 0);
    //     } catch (std::invalid_argument &ia) {
    //       std::cerr << "invalid argument : provided history length count was not a number (NaN) !! (for "
    //                    "-rhl/--r-history flag)\n"
    //                 << std::flush;
    //       exit(EXIT_FAILURE);
    //     } catch (std::out_of_range &oor) {
    //       std::cerr << "invalid argument : provided history length count was out of range (for -rhl/--r-history flag) must "
    //                    "be unsigned int (aka must be positive)\n"
    //                 << std::flush;
    //       exit(EXIT_FAILURE);
    //     }
    //   }
    } else if ("-e" == std::string(argv[i]) || "-re" == std::string(argv[i]) || "--report-error" == std::string(argv[i])) {
      report_error = true;
    } else if ("-a" == std::string(argv[i]) || "--all" == std::string(argv[i]) || "--report-all" == std::string(argv[i]) || "-all" == std::string(argv[i])) {
      report_error = true;
      report_all = true;
#ifdef __romp__ENABLE_assume_property
      r_assume = true;
#else
      r_assume = false;
#endif
#ifdef __romp__ENABLE_cover_property
      r_cover = true;
#else
      r_cover = false;
#endif
    } else if ("-rst" == std::string(argv[i]) || "--show-type" == std::string(argv[i]) || "--r-show-type" == std::string(argv[i])) {
      report_show_type = true;
    } else if ("-ros" == std::string(argv[i]) || "--omit-state" == std::string(argv[i]) || "--r-omit-state" == std::string(argv[i])) {
      report_emit_state = false;
    } else if ("-rtc" == std::string(argv[i]) || "--tab-char" == std::string(argv[i]) || "--r-tab-char" == std::string(argv[i])) {
      tab_char = '\t';
    } else if ("-rts" == std::string(argv[i]) || "--tab-size" == std::string(argv[i]) || "--r-tab-size-" == std::string(argv[i])) {
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        ++i;
        try {
          tab_size = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided tab size was not a number (NaN) !!\n"
                       "                   |-> (for --r-tab-size/--tab-size/-rts flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided tab size was out of range must be unsigned int (aka "
                       "must be positive & less than 2.147 billion)\n"
                       "                   |-> (for --r-tab-size/--tab-size/-rts flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "invalid argument : --r-tab-size/--tab-size/-rts requires an unsigned int to follow as a parameter !!\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
#ifdef __romp__ENABLE_assume_property
    } else if ("-ra" == std::string(argv[i]) || "--r-assume" == std::string(argv[i]) || "--report-assume" == std::string(argv[i])) {
      r_assume = true;
#endif
    // } else if ("-o" == std::string(argv[i]) || "--output" == std::string(argv[i])) {
    //   output_results = true;
    //   if (i + 1 < argc && argv[i + 1][0] != '-')
    //     result_out_file = std::string(argv[++i]);
    //   else
    //     std::cerr << "\nWARNING : you have not specified an outfile after using the -o/--output flag !!\n"
    //                  "        |-> `${CWD}/results.txt` will be used by default !!\n"
    //               << std::flush;
    } else if ("-t" == std::string(argv[i]) || "--trace" == std::string(argv[i])) {
      do_trace = true;
      if (i + 1 < argc && argv[i + 1][0] != '-')
        trace_dir = validate_dir_path(std::string(argv[++i]));
      else
        std::cerr << "\nWARNING : you have not specified an out directory after using the -t/--trace flag !!\n"
                     "        |-> `./traces/` will be used by default !!\n"
                  << std::flush;
      std::cerr << "\nWARNING : enabling traces can significantly reduce performance "
                   "& can take up a large amount of system recourses !!\n"
                << std::flush;
    } else if ("-bfs" == std::string(argv[i]) || "--bfs" == std::string(argv[i])
               || "-BFS" == std::string(argv[i]) || "--BFS" == std::string(argv[i])) {
      do_bfs = true;
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        ++i;
        if ('m' == argv[i][0] || 'M' == argv[i][0]) {
          bfs_single = false;
          if (i + 1 < argc && '-' != argv[i + 1][0]) ++i;
        } else if ('s' == argv[i][0] || 'S' == argv[i][0]) {
          bfs_single == true;
          if (i + 1 < argc && '-' != argv[i + 1][0]) ++i;
        }
        try {
          bfs_coefficient = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided initial BFS Coefficient was not a number (NaN) !!\n"
                       "                   |-> (for --bfs/-bfs {single|multiple} {int} flag)\n"
                       "                                                         ^^^^^\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided initial BFS Coefficient was out of range must be unsigned int (aka "
                       "must be positive & less than 2.147 billion)\n"
                       "                   |-> (for --bfs/-bfs {single|multiple} {int} flag)\n"
                       "                                                         ^^^^^\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      }
    } else if ("-bfsl" == std::string(argv[i]) || "--bfs-limit" == std::string(argv[i])
               || "-bfs-l" == std::string(argv[i]) || "--bfsl" == std::string(argv[i])
               || "-bfs-limit" == std::string(argv[i]) || "--bfs-l" == std::string(argv[i])) {
      if (i + 1 < argc && '-' != argv[i + 1][0]) {
        ++i;
        try {
          bfs_limit = std::stoul(argv[i], nullptr, 0);
        } catch (std::invalid_argument &ia) {
          std::cerr << "invalid argument : provided initial BFS Limit was not a number (NaN) !!\n"
                       "                   |-> (for " << argv[i-1] << " flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        } catch (std::out_of_range &oor) {
          std::cerr << "invalid argument : provided initial BFS Limit was out of range must be unsigned int (aka "
                       "must be positive & less than 2.147 billion)\n"
                       "                   |-> (for `" << argv[i-1] << "` flag)\n"
                    << std::flush;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "invalid argument : `" << argv[i] << "` requires an unsigned int to follow as a parameter !!\n"
                  << std::flush;
        exit(EXIT_FAILURE);
      }
    } else {
      std::cerr << "ignored argument : `" << argv[i] << "` is not recognised as a argument and will be ignored\n"
                << std::flush;
    }
  } // end for loop
    // modifying values to match complex default values
    if (tab_char == '\t') {
      tab_size = 1;
    }
    if (do_single) {
      threads = 1;
      walks = 1;
      if (do_bfs) {
        do_bfs = false;
        std::cerr << "\nWARNING : Single walk (`--single-walk`/`-sw`) is not compatible and overrides initial BFS (`--bfs`)\n" << std::flush;
      }
    } else if (do_bfs) {
      if (bfs_limit == 0) {
        std::cerr << "\nERROR : The BFS Limit must be greater than 0 to be of any effect (usually a really big number) !!\n" << std::flush;
        exit(EXIT_FAILURE);
      }
    }

    // check for inconsistent or contradictory options here
    //[X]TODO (OPTIONAL) check OPTIONS to make sure config is valid and output
    // if (history_length == 0) {
    //   std::cerr << "\nERROR : history size cannot be 0 (--r-history/-rhl)\n" << std::flush;
    //   exit(EXIT_FAILURE);
    // }
    if (attempt_limit == 0) {
      std::cerr << "\nERROR : attempt limit cannot be 0 (--attempt-limit/-al/--loop-limit/-ll/--attempt-guard/-ag)\n" << std::flush;
      exit(EXIT_FAILURE);
    }
    if (depth == 0) {
      std::cerr << "\nERROR : max depth cannot be 0 (--depth/-d)\n" << std::flush;
      exit(EXIT_FAILURE);
    }
#ifdef __romp__ENABLE_cover_property
    if (complete_on_cover && cover_count == 0) {
      std::cerr << "\nERROR : cover check goal cannot be 0 (--cover-check/-cc)\n" << std::flush;
      exit(EXIT_FAILURE);
    }
#endif
#ifdef __romp__ENABLE_liveness_property
    if (liveness && lcount == 0) {
      std::cerr << "\nERROR : liveness limit cannot be 0 (--liveness-check/-lc)\n" << std::flush;
      exit(EXIT_FAILURE);
    }
#endif
    if (do_single) {
      if (walks_provided)
        std::cerr << "\nWARNING : -w/--walks/--walk_count is ignored when the -sw/--single-walk flag is set !!\n"
                  << std::flush;
      if (threads_provided)
        std::cerr << "\nWARNING : -ptn/--threads is ignored when the -sw/--single-walk flag(s) is set !!\n" << std::flush;
    } else { // not doing a single walk
      if (not threads_provided && threads == 0) {
        std::cerr << "\nERROR : could not determine hardware thread capacity & no --threads/-ptn option was provided !!\n"
                    "         try again using the --threads/-ptn flag to set the number of threads you want to use.\n"
                    <<std::flush;
        exit(EXIT_FAILURE);
      }
      if (threads == 0) {
        std::cerr << "\nERROR : number of threads cannot be 0 (--threads/-ptn)\n" << std::flush;
        exit(EXIT_FAILURE);
      }
      if (walks == 0) {
        std::cerr << "\nERROR : number of walks cannot be 0 (--walks/-w)\n" << std::flush;
        exit(EXIT_FAILURE);
      }
      if (not threads_provided)
        std::cerr << "\nINFO : the number of threads to use was not specified (with -ptn/--threads flags)\n"
                     "     |-> defaults to "
                  << threads << std::endl;
      if (not walks_provided)
        std::cerr << "\nINFO : the number of random walkers was not specified (with -w/--walks/--walk-count flags)\n"
                     "     |-> defaults to "
                  << _ROMP_THREAD_TO_RW_RATIO * threads << "(= " << _ROMP_THREAD_TO_RW_RATIO << " * "
                  << threads << ")\n"
                  << std::flush;
      if (threads_provided && not walks_provided)
        walks = _ROMP_THREAD_TO_RW_RATIO * threads;  // post parse assign default value
      if (threads_provided && walks_provided && threads > walks) {
        threads = walks;
        std::cerr << "\nWARNING : you specified more threads than walks !!\n"
                      "        |-> we will only launch `" << walks << "` threads!\n"
                  << std::flush;
      }
    }
    if (start_provided && do_even_start)
      std::cerr << "\nWARNING : --even-start/-es is ignored when --start-id/-sid is provided !!\n"
                  << std::flush;
    // warnings and end with errors as appropriate
    if (deadlock == false) {
      if (guard_provided && report_error)
        std::cerr << "\nWARNING : --no-deadlock/-nd suppresses the output of walks terminated for violating the rule attempt limit !!\n"
                       "        |-> (aka the --attempt-limit/-al/--loop-limit/-ll/--attempt-guard/-ag flags)\n" << std::flush;
#ifdef __romp__ENABLE_liveness_property
      if (liveness) {
        liveness = false;
        lcount = default_opts.lcount;
        std::cerr << "\nWARNING : --no-deadlock/-nd overrides/disables the --liveness-check/-lc flag !!\n" << std::flush;
      }
#endif
    }
// #ifdef __romp__ENABLE_assume_property
//     if (r_assume && not report_error) {
//       std::cerr << "\nINFO : --report-assume/--r-assume/-ra does nothing unless the --report-error/-re flag is set !!\n" << std::flush;
//     }
// #endif
#ifdef __romp__ENABLE_cover_property
    if (r_cover && not complete_on_cover) {
      std::cerr << "\nINFO : --report-cover/--r-cover/-rc does nothing unless the --complete-on-cover/-cc flag is set !!\n" << std::flush;
    }
#endif
}

const stream_void Options::write_config(ostream_p& out) const noexcept {
  Options defaults;
  std::string sep = "";
  std::string startstate_str = ((start_id < _ROMP_STARTSTATES_LEN)
                                ? ({std::stringstream buf; buf << __caller__::STARTSTATES[start_id]; buf.str();})
                                : ((do_even_start)
                                    ? ("even/distributed (" + std::to_string(walks/_ROMP_STARTSTATES_LEN) + " walks per startstate)" )
                                    : "randomly assigned \t(default)"));
  std::string deadlock_str = "";
  if (deadlock) {
#   ifdef __romp__ENABLE_liveness_property
      if (liveness) {
        deadlock_str += sep + "liveness property violations";
        sep = ", ";
      }
#   endif
    if (attempt_limit != defaults.attempt_limit) deadlock_str += sep + "attempt limit";
  } else deadlock_str = "NO DETECTION (" + std::string((deadlock == defaults.deadlock) ? " \t(default)" : "");
  sep = "";
  std::string report_str = "property violations | error statements reached";
  std::string pw_report_str = "";
  bool _compound = false;
# ifdef __romp__ENABLE_assume_property
    if (r_assume) {
      _compound = true;
      // report_str += " | " "assume property violated";
      pw_report_str += "assume property violated";
      sep = " | ";
    }
# endif
# ifdef __romp__ENABLE_cover_property
    // if (complete_on_cover) report_str += " | " "cover properties completed";
    if (complete_on_cover && r_cover) {
      _compound = true;
      pw_report_str += sep + "cover properties completed";
      sep = " | ";
    }
# endif
# if (_ROMP_RULE_SELECTION_ALGO == (0ul)) // 100% radom
    std::string selection_algo_str = "100% random with replacement [opt: 0] \t (config when generating with romp)";
# elif (_ROMP_RULE_SELECTION_ALGO == (2ul)) // full no replacement
    std::string selection_algo_str = "Expanded Rule Random replacement without replacement [opt: 2] \t(config when generating with romp)";
# elif (_ROMP_RULE_SELECTION_ALGO == (3ul)) // heuristic symmetry reduction
    std::string selection_algo_str = "Heuristic Symmetry Reduction [opt: 3] \t(config when generating with romp)";
# else                                      // per rule no replacement [default]
    std::string selection_algo_str = "Per Rule Random selection without replacement [opt: 1] \t(default : config when generating with romp)";
#endif
  if (report_all) pw_report_str = "ALL WALKS";
  else if (report_error) pw_report_str += sep + "property violations | error statements reached";
  else if (not _compound) pw_report_str = "NONE \t(default)";
  out << out.indentation()
      << "BASE LAUNCH CONFIG:"                                                      << out.indent() << out.nl()
      << " rule-selection-algo: " << selection_algo_str                                             << out.nl()
      << "             threads: " << threads << ((threads==defaults.threads) ? " \t(default)" : "") << out.nl()
      << "               walks: " << walks << ((walks==defaults.walks) ? " \t(default)" : "")       << out.nl()
      << "                seed: " << rand_seed << ((rand_seed==defaults.rand_seed) ? " \t(default:C++defined)" : "")  << out.nl()
      << "          startstate: " << startstate_str                                                 << out.nl()
      << "           max depth: " << depth << ((depth==defaults.depth) ? " \t(default)" : "")       << out.nl()
      << "            deadlock: " << deadlock_str                                                   << out.nl()
#ifdef __romp__ENABLE_symmetry
      << "   symmetry: YES, heuristic \t(config when generating with romp)"
#else
      << "   symmetry: NO  \t(config when generating with romp)"
#endif
      << out.dedent()                                                               << out.nl()
      << "INITIAL BFS OPTIONS:"                                     << out.indent() << out.nl();
  if (do_bfs) {
    out<<"   do initial BFS: YES"                                                         << out.nl()
       <<"  concurency mode: " << ((bfs_single) ? "SINGLE threaded \t(default)" : "MULTI-threaded" ) << out.nl()
       <<"  BFS coefficient: " << bfs_coefficient << out.nl()
       <<"        BFS limit: " << bfs_limit << ((bfs_limit==defaults.bfs_limit) ? " \t(default)" : "");
  } else {
    out << "\t>>\tDISABLED \t(default)\t<<";
  }
  out << out.dedent()                                                               << out.nl()
      << "TRACE OPTIONS:"                                           << out.indent() << out.nl();
  if (do_trace) {
    out<<"   do trace: YES"                                                         << out.nl()
       <<"  trace dir: \"" << trace_dir << '"' << ((trace_dir==defaults.trace_dir) ? " \t(default)" : "");
  } else {
    out << "\t>>\tDISABLED \t(default)\t<<";
  }
  out << out.dedent()                                                               << out.nl();
#if defined(__romp__ENABLE_assume_property) || defined(__romp__ENABLE_cover_property) || defined(__romp__ENABLE_liveness_property)
  out << "ENABLED SPECIAL/RUMUR PROPERTIES:"                        << out.indent()
#ifdef __romp__ENABLE_assume_property
                                                                                    << out.nl()
      << "      assume: YES, " << (r_assume ? "reporting" : "non-reporting \t(default)")
#endif
#ifdef __romp__ENABLE_cover_property
                                                                                    << out.nl()
      << "       cover: " << ((complete_on_cover)
                              ? "YES, " + std::string((r_cover) ? "reporting" : "non-reporting")
                              : "NO \t(default)" )                                    << out.nl()
      << " cover-count: " << ((complete_on_cover)
                              ? std::to_string(cover_count)
                              : "n/a")
#endif
#ifdef __romp__ENABLE_liveness_property
                                                                                    << out.nl()
      << "    liveness: " << ((liveness) ? "YES" : "NO \t(default)")                << out.nl()
      << "liveness lim: " << ((liveness)
                              ? std::to_string(lcount)
                              : "n/a")
#endif
      << out.dedent()                                                               << out.nl();
#endif
  out << "PER WALK REPORTS:"                                        << out.indent() << out.nl()
      << "     report: " << pw_report_str                                           << out.nl()
      << "history len: " << _ROMP_HIST_LEN << " \t(config when generating with romp)"<< out.nl()
      << "print state: " << ((report_emit_state)
                             ? ("YES"
                                + std::string((report_show_type)
                                                ? ", w/ type info"
                                                : "")
                                + std::string((report_emit_state==defaults.report_emit_state
                                                && report_show_type==defaults.report_show_type)
                                              ? " \t(default)"
                                              : ""))
                             : ("NO"
                                + std::string((report_emit_state==defaults.report_emit_state)
                                              ? " \t(default)"
                                              : "")))                               << out.nl()
#ifdef __ROMP__DO_MEASURE
      << "report time: YES \t(config when generating with romp)"
#else
      << "report time: NO  \t(config when generating with romp)"
#endif
      << out.dedent()                                                               << out.nl()
      << "WALKS INCLUDED IN FINAL REPORT:" << ((report_all) ? " \t[ALL]" : "")
                                                    << out.indent() << out.indent() << out.nl()
      << " - property violations      \t(default)"                                  << out.nl()
      << " - error statements reached \t(default)"                                  << out.nl();
  if (r_assume) out << " - assumptions violation"                                   << out.nl();
  if (r_cover) out << " - walks with completed cover property coverage"             << out.nl();
  if (report_all) {
    out << " - max depth reached"                                                   << out.nl()
        << " - attempt limit reached"
            << ((attempt_limit == defaults.attempt_limit)
                ? (" \t(`built-in`"
                    + std::string((deadlock)
                                  ? ")"
                                  : "; ignores -nd/--no-deadlock)"))
                : ((deadlock)
                    ? ""
                    : " \t(ignores -nd/--no-deadlock; DBG:``shouldn't be possible'')"))
                                                                                    << out.nl();
  }
  out << out.dedent() << out.dedent()                                               << out.nl();
  return S_VOID;
}

template<class O>
ojstream<O>& operator << (ojstream<O>& json, const Options& opts) noexcept {
  json << "{"
            "\"model\":\"" __model__filepath "\","
            "\"romp-id\":" << ROMP_ID << ","
            "\"root-seed\":\"" << opts.seed_str << "\","
            "\"walks\":" << opts.walks << ","
            "\"threads\":" << opts.threads << ","
            "\"do-single\":" << opts.do_single << ","
            "\"initial-bfs\":" << opts.do_bfs << ","
            "\"bfs-mode\":" << ((opts.do_bfs) ? ((opts.bfs_single) ? "\"single\"" : "\"multi\"") : "null") << ","
            "\"bfs-coef\":" << ((opts.do_bfs) ? std::to_string(opts.bfs_coefficient) : "null") << ","
            "\"bfs-limit\":" << ((opts.do_bfs) ? std::to_string(opts.bfs_limit) : "null") << ","
            "\"max-depth\":" << opts.depth << ","
            "\"abs-attempt-limit\":" << std::to_string(_ROMP_ATTEMPT_LIMIT_DEFAULT()) << ","
            "\"attempt-limit\":" << ((opts.attempt_limit != _ROMP_ATTEMPT_LIMIT_DEFAULT()
                                        && opts.deadlock)
                                      ? std::to_string(opts.attempt_limit)
                                      : "null") << ","
            "\"start-mode\":" << ((opts.start_id != _ROMP_START_ID_DEFAULT)
                                  ? ("\"single\"")
                                  : (((opts.do_even_start)
                                                  ? ("\"even\"")
                                                  : ("\"random\"")))) << ","
            "\"single-start-id\":" << ((opts.start_id != _ROMP_START_ID_DEFAULT)
                                        ? std::to_string(opts.start_id)
                                        : "null") << ","
#if (_ROMP_RULE_SELECTION_ALGO == (0ul))
            "\"rule-selection-algo-id\":0,"
            "\"rule-selection-algo-desc\":\"100% random\","
            "\"symmetry-reduction\":false,"
#elif (_ROMP_RULE_SELECTION_ALGO == (2ul))
            "\"rule-selection-algo-id\":2,"
            "\"rule-selection-algo-desc\":\"Rule Expanded Random without replacement\","
            "\"symmetry-reduction\":false,"
#elif (_ROMP_RULE_SELECTION_ALGO == (3ul))
            "\"rule-selection-algo-id\":3,"
            "\"rule-selection-algo-desc\":\"Heuristic Symmetry Reduction\","
            "\"symmetry-reduction\":true,"
#else
            "\"rule-selection-algo-id\":1,"
            "\"rule-selection-algo-desc\":\"Per Rule Random without Replacement\","
            "\"symmetry-reduction\":false,"
#endif
#ifdef __romp__ENABLE_assume_property
            "\"enable-assume\":true,"
#else
            "\"enable-assume\":false,"
#endif
#ifdef __romp__ENABLE_cover_property
            "\"enable-cover\":" << opts.complete_on_cover << ","
            "\"cover-count\":" << ((opts.complete_on_cover)
                                    ? std::to_string(opts.cover_count)
                                    : "null") << ","
#else
            "\"enable-cover\":false,"
            "\"cover-count\":null,"
#endif
#ifdef __romp__ENABLE_liveness_property
            "\"enable-liveness\":" << opts.liveness << ","
            "\"liveness-limit\":" << ((opts.liveness)
                                      ? std::to_string(opts.lcount)
                                      : "null") << ","
#else
            "\"enable-liveness\":false,"
            "\"liveness-limit\":null,"
#endif
#ifdef __ROMP__DO_MEASURE
            "\"do-measure\":true,"
#else
            "\"do-measure\":false,"
#endif
#ifdef __ROMP__SIMPLE_TRACE
            "\"simple-trace\":true,"
#else
            "\"simple-trace\":false,"
#endif
            "\"total-rule-count\":" << std::to_string(_ROMP_RULE_COUNT) << ","
            "\"possible-state-count\":" _ROMP_STATESPACE_COUNT_str ""
       << "}";
  return json;
}

inline std::ostream& operator << (std::ostream& out, const Options& opts) {
  ostream_p _out(out,opts,0); opts.write_config(_out); return out;
}
ostream_p& operator << (ostream_p& out, const Options& opts) noexcept { opts.write_config(out); return out; }


  RandWalker::RandWalker(const BFSWalker& bfs, RandSeed_t rand_seed_, const Options& OPTIONS_)
    : // RandWalker(OPTIONS_),
      rand_seed(rand_seed_), init_rand_seed(rand_seed_),
      _fuel(OPTIONS_.depth-bfs._depth),
      state(bfs.state), start_id(bfs._start_id), status(bfs.status), IS_BFS(true),
      history_start(bfs.history_start), history_level(bfs.history_level),
      put_msgs(bfs.put_msgs),
      id(RandWalker::next_id++),
      OPTIONS(OPTIONS_),
      sim1Step(((OPTIONS.do_trace)
                  ? std::function<void()>([this](){sim1Step_trace();})
                  : std::function<void()>([this](){sim1Step_no_trace();}))),
#     ifdef __romp__ENABLE_cover_property
        enable_cover(OPTIONS_.complete_on_cover), goal_cover_count(OPTIONS_.cover_count),
#     endif
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        enable_liveness(OPTIONS_.liveness), init_lcount(OPTIONS.lcount),
#     endif
      _attempt_limit(OPTIONS_.attempt_limit), init_attempt_limit(OPTIONS_.attempt_limit)
  {
#   ifdef __romp__ENABLE_symmetry
      for (int i=0; i<_ROMP_RULESETS_LEN; ++i) next_rule[i] = 0;
    #endif
#   ifdef __romp__ENABLE_cover_property
      for (int i=0; i<_ROMP_COVER_PROP_COUNT; ++i) cover_counts[i] = 0;
#   endif
#   if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
      for (int i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i) lcounts[i] = init_lcount;
#   endif
    state.__rw__ = this;
    if (OPTIONS.do_trace) {
      init_trace();
      bfs_trace(bfs);
    }
    // transfer history from bfs
    for (size_t i=bfs.history_start; i<bfs.history_level; ++i)
      history[i%history_size()] = bfs.history[i%bfs.history_size()];
    //NOTE: this is lazy and overwrites previous data while transferring data
    //     since the history buffer on a BFS Walker is always larger than a random walker
  }

  void RandWalker::bfs_trace(const BFSWalker& bfs) {
    *json << "{\"$type\":\"bfs-init\","
             "\"startstate\":" << ::__caller__::STARTSTATES[start_id] << ","
             "\"depth\":" << bfs._depth << ","
             "\"history\":[";
    std::string sep;
    for (size_t i=bfs.history_start; i<bfs.history_level; ++i) {
      *json << sep << *bfs.history[i%bfs.history_size()].rule;
    }
    *json << "],"
            "\"state\":" << bfs.state << '}';
  }


} // namespace romp