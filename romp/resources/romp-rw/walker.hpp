/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw.hpp
 *
 * @brief The primary simulation/random walk functions of romp-rw.
 *
 * @date 2022/05/11
 * @version 0.2
 */
#include <thread>
#include <mutex>
#ifndef __romp__GENERATED_CODE
#pragma once            // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "include.hpp"  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "decl.hpp"     // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "writer.hpp"  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "error.hpp"    // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "options.hpp"    // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#include "impls.hpp"    // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif

// << =================================== Type Declarations ==================================== >>

namespace romp {

using duration_ms_t = std::chrono::duration<long double,std::milli>;
using time_ms_t = std::chrono::time_point<std::chrono::high_resolution_clock,std::chrono::duration<long double,std::milli>>;

// using duration_ms_t = std::chrono::duration<long long,std::milli>;
// using time_ms_t = std::chrono::time_point<std::chrono::high_resolution_clock,std::chrono::duration<long long,std::milli>>;

using duration_msf_t = std::chrono::duration<long double,std::milli>;

using duration_mr_t = std::chrono::duration<long long,std::chrono::high_resolution_clock::period>;
using time_mr_t = std::chrono::time_point<std::chrono::high_resolution_clock,std::chrono::duration<long long,std::chrono::high_resolution_clock::period>>;

/**
 * @brief helper function rand_choice 
 * 
 */
template<typename T>
T rand_choice(RandSeed_t &seed, T min, T max) {
    //not done fully
    seed = (((seed ^ (seed >> 3)) >> 12) & 0xffff) | ((seed & 0x7fff) << 16); // modifies the seed
    int choice = seed % (max-min) + min;  // generates the random number
    return choice;
}

class RandWalker : public ::romp::IRandWalker {
private:
  static id_t next_id;
  const id_t id;
  const Options& OPTIONS;
  id_t start_id;
  const RandSeed_t init_rand_seed;
  RandSeed_t rand_seed;
  size_t _fuel; // = OPTIONS.depth;
  bool _valid = true;  // legacy 
  bool _is_error = false; // legacy
  Result::Cause status = Result::RUNNING;
  json_file_t* json = nullptr;
  // tripped thing
  IModelError* tripped = nullptr;
  IModelError* tripped_inside = nullptr;
  size_t _attempt_limit; // = OPTIONS.attempt_limit;
  const size_t init_attempt_limit; // = OPTIONS.attempt_limit;
  struct History {
    const Rule* rule;
  };
  size_t history_level = 0;
  constexpr size_t history_size() const {return _ROMP_HIST_LEN;}
  History history[_ROMP_HIST_LEN];
  size_t history_start = 0;
  /**
   * @brief call if rule is applied to store what rule made the change in the
   * history circular buffer.
   * @param r reference to the rule that was applied
   */
  void add_to_history(const Rule& r) {
    history[history_level%history_size()] = History{&r};
    ++history_level;
    if (history_level > history_size())
      ++history_start;
  }
#ifdef __ROMP__DO_MEASURE
  time_ms_t init_time;
  time_mr_t start_time;
  duration_mr_t active_time = duration_mr_t(0l);
  duration_ms_t total_time = duration_ms_t(0l);
#endif
  
  void init_state() noexcept {    
    const StartState& startstate = ::__caller__::STARTSTATES[start_id];
#ifdef __ROMP__DO_MEASURE
    start_time = time_mr();
#endif
    try {
      startstate.initialize(state);
      if (OPTIONS.do_trace)
        *json << "{\"$type\":\"init\",\"startstate\":" << startstate << ",\"state\":" << state <<"}";
    } catch (const IModelError& me) {
       __handle_exception/*<StartState,IModelError>*/(startstate,me);
    } catch (const std::exception& ex) {
      status = Result::UNKNOWN_CAUSE;
      __handle_exception/*<StartState,std::exception>*/(startstate,ex); 
    } catch (...) {
      status = Result::UNKNOWN_CAUSE;
      tripped_inside = new ModelStartStateError(startstate);
    }
    for (const auto& prop : ::__caller__::PROPERTIES)
      try {
        if (prop.check(state)) { // if tripped
          tripped = new ModelPropertyError(prop);
          tripped_inside = new ModelStartStateError(startstate);
          break;
        }
      } catch(IModelError& me) {
        __handle_exception/*<Property,IModelError>*/(prop,me);
      } catch (std::exception& ex) {
        __handle_exception/*<Property,std::exception>*/(prop,ex);
        status = Result::UNKNOWN_CAUSE;
      } catch (...) {
        status = Result::UNKNOWN_CAUSE;
      }
    // if (json != nullptr) delete json;
#ifdef __ROMP__DO_MEASURE
    active_time += time_mr() - start_time;
#endif
  }

  template<typename R, typename E>
  void __handle_exception(const R& r, const E& er) noexcept {
    if (OPTIONS.do_trace) {
       *json << "],\"error-trace\":[" << er; // << "]";
    }
    tripped_inside = r.make_error();
  }

public:
  const std::function<void()> sim1Step;
  size_t fuel() { return _fuel; }
  size_t attempt_limit() { return _attempt_limit; }
  // bool is_valid() { return _valid; }
  // bool is_error() { return _is_error; }
#ifdef __romp__ENABLE_cover_property
  // bool is_done() const { return (_is_error || (not _valid) || _fuel <= 0 || _attempt_limit <= 0 || complete_cover()); }
  bool is_done() const { return ((status != Result::RUNNING) ||  _fuel <= 0 || _attempt_limit <= 0 || complete_cover()); }
#else
  // bool is_done() const { return (_is_error || (not _valid) || _fuel <= 0 || _attempt_limit <= 0); }
  bool is_done() const { return not (_valid && _fuel > 0 && _attempt_limit > 0); }
#endif

  RandWalker(RandSeed_t rand_seed_, const Options& OPTIONS_) 
    : id(RandWalker::next_id++),
      rand_seed(rand_seed_), init_rand_seed(rand_seed_),
      OPTIONS(OPTIONS_),
      sim1Step(((OPTIONS.do_trace) 
                  ? std::function<void()>([this](){sim1Step_trace();}) 
                  : std::function<void()>([this](){sim1Step_no_trace();}))),
#     ifdef __romp__ENABLE_cover_property
        enable_cover(OPTIONS_.complete_on_cover), goal_cover_count(OPTIONS_.cover_count),
#     endif
#     ifdef __romp__ENABLE_liveness_property
        enable_liveness(OPTIONS_.liveness), init_lcount(OPTIONS.lcount),
#     endif
      _fuel(OPTIONS_.depth), _attempt_limit(OPTIONS_.attempt_limit), init_attempt_limit(OPTIONS_.attempt_limit)
  { 
    if (OPTIONS.start_id != ~0u) {
      rand_choice(rand_seed,0ul,_ROMP_STARTSTATES_LEN); // burn one rand operation for consistency
      start_id = OPTIONS.start_id;
    } else if (OPTIONS.do_even_start) {
      rand_choice(rand_seed,0ul,_ROMP_STARTSTATES_LEN); // burn one rand operation for consistency
      start_id = id % _ROMP_STARTSTATES_LEN;
    } else
      start_id = rand_choice(rand_seed,0ul,_ROMP_STARTSTATES_LEN);
    state.__rw__ = this; /* provide a semi-hidden reference to this random walker for calling the property handlers */ 
    if (OPTIONS.do_trace) {
      init_trace();
    } /* else {
      json = nullptr;
    } */
    for (int i=0; i<history_size(); ++i) this->history[i] = History{nullptr};
#ifdef __romp__ENABLE_symmetry
    for (int i=0; i<_ROMP_RULESETS_LEN; ++i) next_rule[i] = 0;
#endif
#ifdef __romp__ENABLE_cover_property
    for (int i=0; i<_ROMP_COVER_PROP_COUNT; ++i) cover_counts[i] = 0;
#endif
#ifdef __romp__ENABLE_liveness_property
    for (int i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i) lcounts[i] = init_lcount;
#endif
  } 

  ~RandWalker() { 
    if (json != nullptr) delete json; 
    if (tripped != nullptr) delete tripped;
    if (tripped_inside != nullptr) delete tripped_inside;
    // if (history != nullptr) delete[] history; 
  }

  inline void init() noexcept {
#ifdef __ROMP__DO_MEASURE
    init_time = time_ms();
#endif
    init_state();
  }

  inline void finalize() noexcept {
#ifdef __ROMP__DO_MEASURE
    total_time = (time_ms() - init_time);
#endif
    if (status == Result::UNKNOWN_CAUSE) {
    } else if (_attempt_limit <= 0) {
      status = Result::ATTEMPT_LIMIT_REACHED;
      const Rule* _last = history[(history_level-1)%history_size()].rule;
      if (_last != nullptr)
        tripped_inside = new ModelRuleError(*_last);
      else tripped_inside = nullptr;
    } else if (_fuel <= 0) {
      status = Result::MAX_DEPTH_REACHED;
#ifdef __romp__ENABLE_cover_property
    } else if (complete_cover()) { 
      status = Result::COVER_COMPLETE;
      tripped_inside = new ModelRuleError(*history[(history_level-1)%history_size()].rule);
#endif
    }
  }

  const Result* get_result() noexcept {
    if (OPTIONS.do_trace && json != nullptr) {
      trace_result_out();
      // delete json;
    }
    Result* result = new Result{
                  id,init_rand_seed,start_id,
                  status,
                  OPTIONS.depth - _fuel,
                  tripped,tripped_inside
#ifdef __ROMP__DO_MEASURE
                  ,active_time, total_time
#endif
                  };
    tripped = nullptr;
    tripped_inside = nullptr;
    return result;
  }


private:

  /**
   * @brief to pick a rule in random for simulation step
   */
  // const RuleSet& rand_ruleset(){
  //   return ::__caller__::RULESETS[rand_choice<size_t>(rand_seed,0ul,_ROMP_RULESETS_LEN)]; 
  // }

#ifdef __romp__ENABLE_symmetry
  // keeps track of what rule to call next for our heuristic symmetry reduction
  id_t next_rule[_ROMP_RULESETS_LEN];
#endif
  /**
   * @brief to pick a rule in random for simulation step
   */
  const Rule& get_rand_rule(){
    const size_t rs_id = rand_choice<size_t>(rand_seed,0ul,_ROMP_RULESETS_LEN);
    const RuleSet& rs = ::__caller__::RULESETS[rs_id];
#ifdef __romp__ENABLE_symmetry
    id_t& r_id = next_rule[rs_id];  // this is a reference
    const Rule& r = rs.rules[r_id]; 
    if (++r_id >= rs.rules.size())
      r_id = 0;
#else
     const Rule& r = rs.rules[rand_choice<size_t>(rand_seed,0ul,rs.rules.size())];
#endif
    return r;
  }

  void sim1Step_trace() noexcept {
#ifdef __ROMP__DO_MEASURE
    start_time = time_mr();
#endif
    // const RuleSet& rs = rand_ruleset();
    // const Rule& r = rand_rule(rs);
    const Rule& r = get_rand_rule();
    bool pass = false;
    try {  
      if ((pass = r.guard(state)) == true) {
        r.action(state);
        --_fuel;
        _attempt_limit = init_attempt_limit;
        add_to_history(r);
        *json << ",{\"$type\":\"rule-hit\",\"rule\":" << r << ","
                 "\"state\":" << state
              << "}";
      } else {
        *json << ",{\"$type\":\"rule-miss\",\"rule\":" << r << "}";
        --_attempt_limit;
      }      
    } catch(IModelError& me) {
      __handle_exception/*<Rule,IModelError>*/(r,me);
      pass = false;
    } catch (std::exception& ex) {
      __handle_exception/*<Rule,std::exception>*/(r,ex);
      pass = false;
      status = Result::UNKNOWN_CAUSE;
    } catch (...) {
      pass = false;
      status = Result::UNKNOWN_CAUSE;
    }
    if (pass)
      for (const auto& prop : ::__caller__::PROPERTIES)
        try {
          if (prop.check(state)) { // if tripped
            tripped = new ModelPropertyError(prop);
            tripped_inside = new ModelRuleError(r);
            *json << "],\"error-trace\":[" << *tripped; // << "]";
            break;
          }
        } catch(IModelError& me) {
          __handle_exception/*<Property,IModelError>*/(prop,me);
        } catch (std::exception& ex) {
          __handle_exception/*<Property,std::exception>*/(prop,ex);
          status = Result::UNKNOWN_CAUSE;
        } catch (...) {
          status = Result::UNKNOWN_CAUSE;
        }
#ifdef __ROMP__DO_MEASURE
    active_time += time_mr() - start_time;
#endif
    if (_fuel % _ROMP_FLUSH_FREQ == 0)
      json->out.flush();
  }

  void sim1Step_no_trace() noexcept {
#ifdef __ROMP__DO_MEASURE
    start_time = time_mr();
#endif
    // const RuleSet& rs= rand_ruleset();
    // const Rule& r= rand_rule(rs);
    const Rule& r = get_rand_rule();
    bool pass = false;
    try {  
      if ((pass = r.guard(state)) == true) {
        r.action(state);
        --_fuel;
        _attempt_limit = init_attempt_limit;
        add_to_history(r);
      } else { --_attempt_limit; }
    } catch(IModelError& me) {
      __handle_exception/*<Rule,IModelError>*/(r,me);
      pass = false;
    } catch (std::exception& ex) {
      __handle_exception/*<Rule,std::exception>*/(r,ex);
      pass = false;
      status = Result::UNKNOWN_CAUSE;
    } catch (...) {
      pass = false;
      status = Result::UNKNOWN_CAUSE;
    }
    if (pass)
      for (const auto& prop : ::__caller__::PROPERTIES)
        try {
          if (prop.check(state)) { // if tripped
            tripped = new ModelPropertyError(prop);
            tripped_inside = new ModelRuleError(r);
            break;
          }
        } catch(IModelError& me) {
          __handle_exception/*<Property,IModelError>*/(prop,me);
        } catch (std::exception& ex) {
          __handle_exception/*<Property,std::exception>*/(prop,ex);
          status = Result::UNKNOWN_CAUSE;
        } catch (...) {
          status = Result::UNKNOWN_CAUSE;
        }
#ifdef __ROMP__DO_MEASURE
    active_time += time_mr() - start_time;
#endif             
  }

  void init_trace() {
    json = new json_file_t(OPTIONS.get_trace_file_path(id));
    *json << "{\"$type\":\"";
#ifdef __ROMP__SIMPLE_TRACE
    *json << "romp-simple-trace";
#else
    *json << "romp-trace";
#endif 
    *json << "\",\"$version\":\"" _ROMP_TRACE_JSON_VERSION "\"";
    *json << ",\"trace-id\":" << id 
          << ",\"seed\":" << init_rand_seed
          << ",\"start-id\":" << start_id
          << ",\"metadata\":" << OPTIONS // .write_metadata_json(json->out)
          << ",\"trace\":[";
  }

  void trace_result_out() const {
    using namespace std::chrono;
    *json << "]"; // close trace
    // if (_valid && tripped == nullptr) // if it didn't end in an error we need to: 
    if (tripped_inside == nullptr) // if it didn't end in an error we need to: 
      *json << ",\"error-trace\":[]"; // output empty error-trace
    *json << ",\"results\":{\"depth\":"<< OPTIONS.depth-_fuel <<",\"valid\":null,\"is-error\":null"
          << ",\"result\":\"" << std::to_string(status) << "\"" 
#ifdef __ROMP__DO_MEASURE
                                << ",\"active-time\":" << (duration_cast<duration_msf_t>(active_time).count()) 
                                << ",\"total-time\":" << (duration_cast<duration_msf_t>(total_time).count())
#else
                                << ",\"active-time\":null,\"total-time\":null" 
#endif
            << ",\"property-violated\":" << tripped
            << ",\"tripped-inside\":" << tripped_inside
            << ",\"attempts-final\":" << _attempt_limit
                              << "}" // closes results object
              << "}"; // closes top level trace object
    json->out.flush();
  }

public:
  bool do_report() const {
    if (OPTIONS.report_all) return true;
    switch (status) {
      case Result::UNKNOWN_CAUSE:
        return true;
      case Result::PROPERTY_VIOLATED:
      case Result::MERROR_REACHED:
        return OPTIONS.report_error;
#ifdef __romp__ENABLE_assume_property
      case Result::ASSUMPTION_VIOLATED:
        return OPTIONS.r_assume;
#endif
#ifdef __romp__ENABLE_cover_property
      case Result::COVER_COMPLETE:
        return OPTIONS.r_cover;
#endif
      default: return false;
    }
  }

  // called when trying to print the results of the random walker when it finishes (will finish up trace file if necessary too)
  //  the calling context should ensure that the RandWalker is not being used else where & safe output to the ostream 
  friend ostream_p& operator << (ostream_p& out, const RandWalker& rw) {
    std::string res_color = get_color(rw.status);
    out << out.nl()
        << "======== BEGIN :: Report of Walk #" << rw.id << " ========"             << out.nl()
        << "BASIC INFO: "                                           << out.indent() << out.nl()
        << "         w#: " << rw.id                                                 << out.nl()
        << "       Seed: " << rw.init_rand_seed                                     << out.nl()
        << "      Depth: " << rw.OPTIONS.depth - rw._fuel                              << out.nl()
        << "   Start ID: " << rw.start_id                                           << out.nl()
        << " StartState: " << ::__caller__::STARTSTATES[rw.start_id]                << out.nl()
        << "     Result: " << res_color << std::to_string(rw.status) << "\033[0m"   << out.nl()
        << out.dedent()                                                             << out.nl()
        << "TRACE LITE:"                                            << out.indent() << out.nl()
        << "NOTE - " << ((rw.OPTIONS.do_trace) 
                          ? "see \"" + rw.OPTIONS.trace_dir + std::to_string(rw.init_rand_seed) + ".json\" for full trace." 
                          : "use the --trace/-t option to generate a full & detailed trace." ) << out.nl()
        << "History: ["                             << out.indent() << out.indent() << out.nl()
        << "-(0) " << ::__caller__::STARTSTATES[rw.start_id] << '\n';
      if (rw.history_start > 0)
        out << out.indentation() << "-(..) ... forgotten past ...\n";
      for (size_t i=rw.history_start; i<rw.history_level; ++i)
        out << out.indentation() << "-(" << i+1 <<") " << *(rw.history[i%rw.history_size()].rule) << "\n";
    out << out.dedent() << out.indentation() << ']' << out.dedent() << out.dedent();
    if (rw.OPTIONS.report_emit_state)
      out                                                                           << out.nl()
          << "  State: " <<  out.indent() << out.indent() << rw.state << out.dedent() << out.dedent();
    if (rw.tripped != nullptr || rw.tripped_inside != nullptr) {
      out                                                                           << out.nl()
          << "ISSUE REPORT:"                                        << out.indent() << out.nl();
      if (rw.tripped != nullptr) {
        out << "Tripped: \033[31m" << *rw.tripped << "\033[0m"                      << out.nl();
        if (rw.tripped_inside != nullptr)
          out << "  Trace: "                                        << out.indent() << out.nl()
              << *rw.tripped_inside                                 << out.dedent() << out.nl();
              // << '}'                                                               << out.nl();
      }
    }
    if (rw.put_msgs.size() > 0) {
      out << "Put Statements: \"\"\""               << out.indent() << out.indent() << out.nl();
      for (auto msg : rw.put_msgs) {
        try {
          msg.first(out);
        } catch (std::exception& ex) {
          out << out.indent() << out.nl() << msg.second << " :: error occurred while evaluating put statement" 
              << out.nl() << ex << out.dedent() << out.nl();
        }
      }
      out << out.dedent() << out.nl() << "\"\"\"" << out.dedent() << out.nl();
    }
        
#ifdef __ROMP__DO_MEASURE
    out << out.dedent()                                                             << out.nl()
        << "TIME REPORT:"                                           << out.indent() << out.nl()
        << "Active Time: " << rw.active_time                                        << out.nl()           
        << " Total Time: " << rw.total_time                                         ;// << out.nl();
#endif
    out << out.dedent()                                                             << out.nl()
        << "======== END :: Report of Walk #" << rw.id << " ========"               << out.nl();
    out.out.flush();

    return out;
  }
  // called when trying to print the results of the random walker when it finishes (will finish up trace file if necessary too)
  //  the calling context should ensure that the RandWalker is not being used else where & safe output to the ostream 
  friend std::ostream& operator << (std::ostream& out, const RandWalker& rw) 
  { ostream_p _out(out,rw.OPTIONS,0); _out << rw; return out; }

  // NOTE: currently not supporting choose rules
  // size_t choose_handler(size_t occupance, const location& loc) {}

  std::vector<std::pair<std::function<void(ostream_p&)>,location>> put_msgs;
  void put_handler(const std::function<void(ostream_p&)>& put_action, const location& loc) {
    put_msgs.push_back(std::make_pair(put_action,loc));
  }

  bool error_handler(id_t error_id) {
    tripped = new ModelMErrorError(error_id);
    _valid = true; // legacy
    _is_error = true; // legacy
    status = Result::MERROR_REACHED;
    return true;
  }

  bool assertion_handler(bool expr, id_t prop_id) {
    if (expr) return false;
    tripped = new ModelPropertyError(prop_id);
    _valid = false;  // legacy
    _is_error = true;  // legacy
    status = Result::MERROR_REACHED;
    return true;
  }
  bool invariant_handler(bool expr, id_t prop_id) {
    if (expr) return false;
    // no need to store exception in tripped if a property rule the catch will give us a better error dump
    // invar_handler is only called from a property rule
    _valid = false;  // legacy
    _is_error = true; // legacy
    status = Result::PROPERTY_VIOLATED;
    return true;
  }
#ifdef __romp__ENABLE_assume_property
  bool assumption_handler(bool expr, id_t prop_id) {
    if (expr) return false;
    tripped = new ModelPropertyError(prop_id);
    _valid = false;  // legacy
    // this is what makes an assumption different from an assertion
    _is_error = false; // legacy
    status = Result::ASSUMPTION_VIOLATED;
    return true;
  }
#else
  bool assumption_handler(bool expr, id_t prop_id) {
    return false;  // don't do anything if the assume property is nto enabled
  }
#endif
#ifdef __romp__ENABLE_cover_property
  const bool enable_cover; // = OPTIONS.complete_on_cover;
  const id_t goal_cover_count; // = OPTIONS.cover_count;
  size_t cover_counts[_ROMP_COVER_PROP_COUNT];
  bool cover_handler(bool expr, id_t cover_id, id_t prop_id) {
    if (expr) cover_counts[cover_id]++;
    return false; // cover never throws an error
  }
#ifdef __GNUC__
  __attribute__((optimize("unroll-loops")))
#endif
  bool complete_cover() const {
    if (not enable_cover) return false;
    bool res = true;
    for (int i=0; i<_ROMP_COVER_PROP_COUNT; ++i) 
      res &= (cover_counts[i] >= goal_cover_count);
    return res;
  }
#else
  bool cover_handler(bool expr, id_t cover_id, id_t prop_id) {
    return false;  // never throw anything if cover is not enabled by romp generator
  }
#endif
#ifdef __romp__ENABLE_liveness_property
private:
  const bool enable_liveness; // = OPTIONS.liveness;
  const size_t init_lcount; // = OPTIONS.lcount;
  size_t lcounts[_ROMP_LIVENESS_PROP_COUNT];
public:
  bool liveness_handler(bool expr, id_t liveness_id, id_t prop_id) {
    if (not enable_liveness) return false;
    if (expr) {
      lcounts[liveness_id] = init_lcount;
      return false;
    }
    if (--lcounts[liveness_id] > 0) return false; 
    _valid = false;
    _is_error = true;
    tripped = new ModelPropertyError(prop_id);
    return true;  // [?]TODO actually handle this as described in the help page
  }
#else
  bool liveness_handler(bool expr, id_t liveness_id, id_t prop_id) {
    return false;  // never throw anything if cover is not enabled by romp generator
  }
#endif

protected:
  // always have this at the end of the RandWalker object def
  State_t state;
}; //? END class RandomWalker

id_t RandWalker::next_id = 0u;



/**
 * @brief A class that indexes and groups the various results a RandWalker can produce,
 *        and provides a helpful operator for writing a nice summary of the results 
 *        to a \c std::ostream as well.
 */
class ResultTree {
  const Options& OPTIONS;
  time_ms_t start_time = time_ms();
  time_ms_t end_time;
  size_t rules_fired = 0;
  size_t size = 0;
#ifdef __ROMP__DO_MEASURE
  duration_mr_t total_walk_active_time = duration_mr_t(0);
  duration_ms_t total_walk_time = duration_ms_t(0);
#endif
  std::vector<const Result*> unknown_causes;
  std::vector<const Result*> attempt_limits_reached;
  std::vector<const Result*> max_depths_reached;
  std::unordered_map<ModelPropertyError,std::vector<const Result*>> properties_violated;
  size_t n_properties_violated = 0;
#ifdef __romp__ENABLE_cover_property
  std::vector<const Result*> completed_covers;
#endif
#ifdef __romp__ENABLE_assume_property
  std::unordered_map<ModelPropertyError,std::vector<const Result*>> assumptions_violated;
  size_t n_assumptions_violated = 0;
#endif
  std::unordered_map<ModelMErrorError,std::vector<const Result*>> merrors_reached;
  size_t n_merrors_reached = 0;
public:
  ResultTree(const Options& OPTIONS_) : OPTIONS(OPTIONS_) {}
  ~ResultTree();
  void insert(const Result* res);
  void start_timer() { start_time = time_ms(); }
  void reset_timer() { start_time = time_ms(); }
  void stop_timer() { end_time = time_ms(); }
  duration_ms_t get_time() const { return end_time - start_time; }
  friend std::ostream& operator << (std::ostream& out, const ResultTree& results);
  friend ostream_p& operator << (ostream_p& out, const ResultTree& r);
};

/**
 * @brief to generate random seeds for the no of random-walkers
 * rand is generated using UNIX timestamp 
 * @param root_seed the parent seed for generating the random seeds.
 */
RandSeed_t gen_random_seed(RandSeed_t &root_seed) {
  return rand_choice(root_seed, 1u, UINT32_MAX);
}

/**
 * @brief generate all the random seeds for the various rand walkers
 * 
 */
std::unordered_set<RandSeed_t> gen_random_seeds(const Options& OPTIONS, RandSeed_t& root_seed)   {
  std::unordered_set<RandSeed_t> seeds;
  for(int i=0; (seeds.size()<OPTIONS.walks) && (i<OPTIONS.walks*2); i++)
    seeds.insert(gen_random_seed(root_seed));
  if (seeds.size()<OPTIONS.walks)
    std::cerr << "\nWARNING : provided seed was only able to produce " << seeds.size() << " unique walker seeds before timing out !!\n"
                 "        |-> ONLY " << seeds.size() << "/" << OPTIONS.walks << " walkers will be run!\n\n" << std::flush;
  return seeds;
}

// example of how to get a copy of an object in C++:
//   use the copy constructor (always has the signature)
//    ClassName(const ClassName &obj)
//  this means your's should look like:
//    auto copied_state = State_t(startstates[i%startstates.size()]);

void print_romp_results_summary(const ResultTree& summary) {
  std::cout << "\n\033[34;1m"
         "================================\n"
         "          ROMP RESULTS:         \n"
         "================================\n"
         "\033[0m\n\n"
         << summary;
}


/**
 * @brief implementing \c rw_count parallel \c RandWalker "simulations" which has the threads 
 *        and no of random-walkers specified by the user options .
 * @param rw_count the number of \c RandWalker 's to use.
 * @param rand_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 * @param thread_count the max number of threads to use to accomplish all said random walks.
 */
void launch_OpenMP(RandSeed_t root_seed) {
  std::cout << "\n\t!! NOT YET IMPLEMENTED !!\n" << std::endl; return; //!! temp, remove when finished !! 
  
  // std::vector<RandWalker> rws;
  // try {
  //   rws = gen_random_walkers(rw_count, root_seed, fuel);
  // } catch (const IModelError& ex) {
  //   std::cerr << "\nModel raised an error when initializing our start state(s)!! (message below)\n"
  //             << ex << std::endl;
  // }
  //[?]TODO: launch the random walkers !!
}

/**
 * @brief implementing \c rw_count parallel \c RandWalker "simulations" which has the threads 
 *        and no of random-walkers specified by the user options .
 * @param rw_count the number of \c RandWalker 's to use.
 * @param rand_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 * @param thread_count the max number of threads to use to accomplish all said random walks.
 */
void launch_threads(const Options& OPTIONS, RandSeed_t rand_seed) {
  auto tmp_seeds = gen_random_seeds(OPTIONS,rand_seed);
  std::queue<RandSeed_t> in_seeds(std::deque<RandSeed_t>(tmp_seeds.begin(),tmp_seeds.end()));
  // std::queue<RandWalkers*> parallel_rws; // probs threads
  std::queue<RandWalker*> out_rws;
  size_t walks_done = 0;
  std::mutex in_queue;
  std::mutex out_queue;
  // std::mutex _in_queue_mutex;
  // std::mutex _out_queue_mutex;

#ifdef DEBUG
  const auto pause_delay = std::chrono::milliseconds(250); //DEBUG SLOW ME DOWN
#else
  const auto pause_delay = std::chrono::milliseconds(5);
#endif

  auto lambda = [&]() { // code the threads run
    // std::lock_guard<std::mutex> in_queue(_in_queue_mutex);
    // std::lock_guard<std::mutex> out_queue(_out_queue_mutex);
    in_queue.lock();
    while (in_seeds.size() > 0) { 

      in_seeds.front(); RandWalker *rw = new RandWalker(in_seeds.front(),OPTIONS);
      in_seeds.pop(); 
      in_queue.unlock();

      rw->init();
      while (not rw->is_done())
        rw->sim1Step();
      rw->finalize();

      out_queue.lock();
      out_rws.push(rw);
      ++walks_done;
      out_queue.unlock();

      in_queue.lock();
    }
    in_queue.unlock();
  };

  ostream_p out(std::cout,OPTIONS,0);
  std::vector<std::thread> threads;
  ResultTree summary(OPTIONS);
  // std::vector<std::thread> threads(OPTIONS.threads);
  for (size_t i=0; i<OPTIONS.threads; ++i) {
    threads.push_back(std::thread(lambda));
  }
  // std::lock_guard<std::mutex> in_queue(_in_queue_mutex);
  // std::lock_guard<std::mutex> out_queue(_out_queue_mutex);

  if (OPTIONS.report_any()) {
    out << "\n\033[34;1m"
           "===================================\n"
           "  WALKS OF INTEREST ROMP RESULTS:  \n"
           "===================================\n"
           "\033[0m\n\n";
    out.out.flush();
  }
  std::this_thread::sleep_for(pause_delay*2);
  while (true) {
    while (true) {  // handel outputs
      std::this_thread::sleep_for(pause_delay);
      out_queue.lock();
      if (not (out_rws.size() > 0)) {
        out_queue.unlock();
        break;
      }
      RandWalker* rw = out_rws.front();
      out_rws.pop();
      out_queue.unlock();
      if (rw != nullptr) {
        if (rw->do_report())
          std::cout << *rw << std::endl;
        // todo get the results
        summary.insert(rw->get_result());
        delete rw;
      }
    }
    std::this_thread::sleep_for(pause_delay); 
    out_queue.lock();
    if (not (walks_done < OPTIONS.walks)) {
      out_queue.unlock();
      break;
    }
    out_queue.unlock();
  }
  // we might need to do this one more time for the last one

  summary.stop_timer();

  for (size_t i=0; i<OPTIONS.threads; ++i) // join threads
     threads[i].join();

  print_romp_results_summary(summary);
}
  

/**
 * @brief (NOT YET IMPLEMENTED) \n
 *        Implementing \c rw_count parallel \c RandWalker "simulations" which has the threads 
 *        and no of random-walkers specified by the user options .
 * @param root_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 */
void launch_CUDA(RandSeed_t root_seed);


/**
 * @brief (NOT YET IMPLEMENTED) \n
 *        Implementing \c rw_count parallel \c RandWalker "simulations" which has the threads 
 *        and no of random-walkers specified by the user options .
 * @param root_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 */
void launch_SYCL(RandSeed_t root_seed);


/**
 * @brief (NOT YET IMPLEMENTED) \n
 *        Implementing \c rw_count parallel \c RandWalker "simulations" which has the threads 
 *        and no of random-walkers specified by the user options .
 * @param root_seed the starting random seed that will generate all other random seeds
 * @param fuel the max number of rules any \c RandWalker will try to apply.
 */
void launch_OpenMPI(RandSeed_t root_seed);


/**
 * @brief Launches a single RandWalker (basically jst a simulation).
 * @param rand_seed the random seed
 * @param fuel the max number of rules to try to apply
 */
void launch_single(const Options& OPTIONS, RandSeed_t rand_seed) {
  RandWalker* rw = new RandWalker(rand_seed, OPTIONS);
  rw->init();
  ResultTree summary(OPTIONS);
  while( not rw->is_done() )
    rw->sim1Step();
  rw->finalize();
  std::cout << "SINGLE ROMP RESULT:\n\t" 
            << *rw << '\n' << std::endl;
  summary.stop_timer();
  summary.insert(rw->get_result());
  delete rw;
  print_romp_results_summary(summary);
}


// void Sim1Step(RandWalker::State state, Rule rule, size_t state_count) {
//   for (int s = 0; s < state_count; s++)
//     if (rule.Guard(states[s])) {
//       rule.Run(states[s]);
//       states[i].rule_applied(
//           rule.id); // this keeps track of history and other overhead
//       // These could possibly be parallelized even better for GPU using
//       // shared memory. (not implemented here, could introduce data races)
//       for (int i = 0; i < _ROMP_INVARIANTS_LEN; i++)
//         states[s].valid |= State::INVARIANTS[i](
//             states[i]); // this will need to change after we figure shit out
//       for (int a = 0; a < _ROMP_ASSERTIONS_LEN; a++)
//         states[s].valid |= State::ASSERTIONS[a](
//             states[i]); // this will need to change after we figure shit out
//     }
// }


// << ========================================================================================== >> 
// <<                                         ROMP CODE                                          >> 
// << ========================================================================================== >> 
}
// template<class S, class R>
