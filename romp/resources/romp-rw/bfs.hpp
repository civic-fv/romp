/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file bfs.hpp
 * 
 * @brief code for the preemptive bfs before romp launch
 * 
 * @date 2023/01/10
 * @version 0.3
 */


#ifndef __romp__GENERATED_CODE
#include "include.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#include "types.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "walker.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "options.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#endif

namespace std {
  template<>
  struct hash<::romp::State_t> {
    inline size_t operator () (const ::romp::State_t& state) const { 
      return state.__romp__model_hash();
    }
  };

} //namespace std

namespace romp {

  class BFSWalker : public IRandWalker {
  protected:
    const Options& OPTIONS;
    id_t _start_id;
    size_t _depth = 0ul;
    Result::Cause status = Result::NO_CAUSE;
    IModelError* tripped = nullptr;
    IModelError* tripped_inside = nullptr;
    size_t history_level = 0ul;
    constexpr size_t history_size() const { return _ROMP_HIST_LEN*2+1; }
    RandWalker::History history[_ROMP_HIST_LEN*2+1];
    size_t history_start = 0ul;
    /**
     * @brief call if rule is applied to store what rule made the change in the
     * history circular buffer.
     * @param r reference to the rule that was applied
     */
    void add_to_history(const Rule& r) {
      history[history_level%history_size()] = RandWalker::History{&r};
      ++history_level;
      if (history_level > history_size())
        ++history_start;
    }
#   ifdef __ROMP__DO_MEASURE
      time_mr_t start_time;
      duration_mr_t active_time = duration_mr_t(0l);
#   endif

    template<typename R, typename E>
    void __handle_exception(const R& r, const E& er) noexcept {
      tripped_inside = r.make_error();
    }
  
  public:

    BFSWalker(const Options OPTIONS_, id_t start_id_)
      : OPTIONS(OPTIONS_), 
#       if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
          enable_liveness(OPTIONS_.liveness),
#       endif
        _start_id(start_id_)
    {
      state.__rw__ = this;
      // std::memset(history, 0u, sizeof(RandWalker::History)*history_size());
    }

    ~BFSWalker() {
      // if (tripped != nullptr) delete tripped;
      // if (tripped_inside != nullptr) delete tripped_inside;
    }

  static BFSWalker* copy(const BFSWalker* b_w) {
    BFSWalker* walker = (BFSWalker*) std::malloc(sizeof(BFSWalker));
    std::memcpy(walker,b_w,sizeof(BFSWalker));
    walker->state.__rw__ = walker;
    return walker;
  }

  void init_state() noexcept {    
    const StartState& startstate = ::__caller__::STARTSTATES[_start_id];
#   ifdef __ROMP__DO_MEASURE
      start_time = time_mr();
#   endif
    try {
      startstate.initialize(state);
    } catch (const IModelError& me) {
       __handle_exception(startstate,me);
    } catch (const std::exception& ex) {
      status = Result::UNKNOWN_CAUSE;
      __handle_exception(startstate,ex); 
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
        __handle_exception(prop,me);
      } catch (std::exception& ex) {
        __handle_exception(prop,ex);
        status = Result::UNKNOWN_CAUSE;
      } catch (...) {
        status = Result::UNKNOWN_CAUSE;
      }
#   ifdef __ROMP__DO_MEASURE
      active_time += time_mr() - start_time;
#   endif
    }

  inline void finalize() noexcept {
    if (status == Result::UNKNOWN_CAUSE) {
    } else if (_depth >= OPTIONS.depth) {
      status = Result::MAX_DEPTH_REACHED;
    }
  }

  const Result* get_result() noexcept {
    Result* result = new Result{
                  0ul, 0ul,
                  _start_id, status, _depth,
                  tripped, tripped_inside
#ifdef __ROMP__DO_MEASURE
                  ,active_time, duration_mr_t(0ul)
#endif
                  };
    tripped = nullptr;
    tripped_inside = nullptr;
    return result;
  }

    bool is_done() const { return status != Result::RUNNING || _depth >= OPTIONS.depth; }

    bool pass = false;

    void sim1Step_no_trace(const Rule& r) noexcept {
#     ifdef __ROMP__DO_MEASURE
        start_time = time_mr();
#     endif
      pass = false;
      try {  
        if ((pass = r.guard(state)) == true) {
          r.action(state);
          ++_depth;
          add_to_history(r);
        }
      } catch(IModelError& me) {
        __handle_exception(r,me);
        pass = false;
      } catch (std::exception& ex) {
        __handle_exception(r,ex);
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
            __handle_exception(prop,me);
          } catch (std::exception& ex) {
            __handle_exception(prop,ex);
            status = Result::UNKNOWN_CAUSE;
          } catch (...) {
            status = Result::UNKNOWN_CAUSE;
          }
#     ifdef __ROMP__DO_MEASURE
        active_time += time_mr() - start_time;
#     endif             
    }


    std::vector<std::pair<std::function<void(ostream_p&)>,location>> put_msgs;
    void put_handler(const std::function<void(ostream_p&)>& put_action, const location& loc) {
      put_msgs.push_back(std::make_pair(put_action,loc));
    }

    bool error_handler(id_t error_id) {
      tripped = new ModelMErrorError(error_id);
      status = Result::MERROR_REACHED;
      return true;
    }

    bool assertion_handler(bool expr, id_t prop_id) {
      if (expr) return false;
      tripped = new ModelPropertyError(prop_id);
      status = Result::PROPERTY_VIOLATED;
      return true;
    }
    bool invariant_handler(bool expr, id_t prop_id) {
      if (expr) return false;
      // no need to store exception in tripped if a property rule the catch will give us a better error dump
      // invar_handler is only called from a property rule
      status = Result::PROPERTY_VIOLATED;
      return true;
    }
# ifdef __romp__ENABLE_assume_property
    bool assumption_handler(bool expr, id_t prop_id) {
      if (expr) return false;
      tripped = new ModelPropertyError(prop_id);
      status = Result::ASSUMPTION_VIOLATED;
      return true;
    }
# else
    bool assumption_handler(bool expr, id_t prop_id) {
      return false;  // don't do anything if the assume property is not enabled
    }
# endif
    bool cover_handler(bool expr, id_t cover_id, id_t prop_id) {
      return false;  // BFS does not currently implement liveness
    }
# if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
  private:
    const bool enable_liveness; // = OPTIONS.liveness;
  public:
    bool is_live[_ROMP_LIVENESS_PROP_COUNT];
    bool liveness_handler(bool expr, id_t liveness_id, id_t prop_id) {
      if (not enable_liveness) return false;
      if (expr) {
        is_live[liveness_id] = true;
        return false;
      }
      if (--lcounts[liveness_id] > 0) return false;
      tripped = new ModelPropertyError(prop_id);
      return true;  // [?]TODO actually handle this as described in the help page
    }
    void reset_liveness() {
      for (size_t i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i)
        is_live[i] = false;
    }
    void merge_liveness(bool *liveness) {
      for (size_t i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i) {
        liveness[i] |= is_live[i];
        is_live[i] = false;
      }
    }
    void set_liveness_violation(id_t liveness_id) {
      tripped = new ModelPropertyError(*::__info__::LIVENESS_INFOS[liveness_id]);
      status = Result::PROPERTY_VIOLATED;
    }
# else
    bool liveness_handler(bool expr, id_t liveness_id, id_t prop_id) {
      return false;  // BFS does not currently implement liveness
    }
# endif

    // called when trying to print the results of the BFS walker when it finishes (will finish up trace file if necessary too)
    //  the calling context should ensure that the BFSWalker is not being used else where & safe output to the ostream 
    friend ostream_p& operator << (ostream_p& out, const BFSWalker& rw) {
      std::string res_color = get_color(rw.status);
      out << out.nl()
          << "======== BEGIN :: Report of BFS ERROR ========"                         << out.nl()
          << " BASIC INFO: "                                                          << out.indent() << out.nl()
          << "      Depth: " << rw._depth                                             << out.nl()
          << "   Start ID: " << rw._start_id                                          << out.nl()
          << " StartState: " << ::__caller__::STARTSTATES[rw._start_id]               << out.nl()
          << "     Result: " << res_color << std::to_string(rw.status) << "\033[0m"   << out.nl()
          << out.dedent()                                                             << out.nl()
          << "TRACE LITE:"                                            << out.indent() << out.nl();
      if (rw.OPTIONS.do_trace) 
        out << "NOTE - BFS does not currently support rich json traces" << out.nl();
      out << "History: ["                             << out.indent() << out.indent() << out.nl()
          << "-(0) " << ::__caller__::STARTSTATES[rw._start_id] << '\n';
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
          
#     ifdef __ROMP__DO_MEASURE
        out << out.dedent()                                                         << out.nl()
            << "TIME REPORT:"                                       << out.indent() << out.nl()
            << "Active Time: " << rw.active_time                                    << out.nl();
#     endif
      out << out.dedent()                                                           << out.nl()
          << "======== END :: Report of BFS ERROR ========"                         << out.nl();
      out.out.flush();

      return out;
    }
    // called when trying to print the results of the BFS walker when it finishes (will finish up trace file if necessary too)
    //  the calling context should ensure that the BFSWalker is not being used else where & safe output to the ostream 
    friend std::ostream& operator << (std::ostream& out, const BFSWalker& rw) 
    { ostream_p _out(out,rw.OPTIONS,0); _out << rw; return out; }

    State_t state;
    friend RandWalker;
  };



struct BFSHandler {
protected:
  const Options& OPTIONS;
  std::deque<BFSWalker*> q;
  std::unordered_set<State_t> states;
  size_t rules_applied = 0ul;
  const size_t TARGET;
  time_ms_t start_time;
  ostream_p out;


public:

  BFSHandler(const Options& OPTIONS_) 
    : OPTIONS(OPTIONS_),
      TARGET(OPTIONS_.walks / OPTIONS_.bfs_coefficient),
      out(std::cout,OPTIONS_,0)
  {}

  ~BFSHandler() {
    for (BFSWalker* w : q) if (w != nullptr) delete w;
  }

  /**
   * @brief Launch a romp run where we first do a single threaded BFS before 
   *        launching the swarm of random walkers.
   * @param OPTIONS the options object defining how the romp run should work.
   *                (required that bfs and do_even start be true)
   */
  void launch() {
    start_time = time_ms();

    // - run through the startstates and add them to the queue ---- 
    for (size_t i=0; i<_ROMP_STARTSTATES_LEN; ++i) {
      auto walker = new BFSWalker(OPTIONS,i);
      walker->init_state();
      ++rules_applied;
      if (walker->is_done()) {  // discover error during 
        end_bfs_report_error(walker);
        return;
      } else if (insert_state(walker->state))
        q.push_back(walker);
    }

    if (OPTIONS.bfs_single) single_bfs();
    else multithreaded_bfs();

  }


protected:
  /**
   * @brief Perform the bfs in a single threaded manner
   *        NOTE: must be called after processing start states
   */
  void single_bfs() {
#   if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
      const bool enable_liveness = OPTIONS.liveness;
      bool liveness[_ROMP_LIVENESS_PROP_COUNT];
#   endif
    while (not q.empty() && q.size()<TARGET && rules_applied < OPTIONS.bfs_limit) {
      auto b_w = q.front();
      q.pop_front();
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        if (enable_liveness) std::memset(liveness,0u,sizeof(bool)*_ROMP_LIVENESS_PROP_COUNT);
#     endif
      for (size_t i=0; q.size()<TARGET && i<_ROMP_RULESETS_LEN; ++i)
        for (auto rule : ::__caller__::RULESETS[i].rules) {
          BFSWalker* walker = BFSWalker::copy(b_w); // copy base walker
          // walker->sim1step(rule);
          walker->sim1Step_no_trace(rule);
          if (walker->is_done()) {
            end_bfs_report_error(walker);
            return;
          }
#         if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
            if (enable_liveness) walker->merge_liveness(liveness);
#         endif
          if (walker->pass) ++rules_applied;
          if (insert_state(walker->state)) {
              q.push_back(walker);
            if (q.size() >= TARGET)
              break;
          } else delete walker;
        }
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        // end if liveness property violated
        if (enable_liveness && (size_t liveness_id = is_live(liveness)) < _ROMP_LIVENESS_PROP_COUNT) {
          b_w->set_liveness_violation(liveness_id);
          end_bfs_report_error(b_w);
          return;
        }
#     endif
      delete b_w;
    }

    if (not q.empty()) {
      end_bfs();
      this->launch_threads();
    } else
      end_bfs_solved();
  }


  /**
   * @brief Perform the bfs in a multithreaded manner
   *        NOTE: must be called after processing start states
   */
  void multithreaded_bfs() {
    std::mutex mut_in, mut_out;
    BFSWalker* bad = nullptr;
    std::vector<std::thread> threads;
    size_t cycle = 0ul;

#   ifdef DEBUG
      const auto pause_delay = std::chrono::milliseconds(20); //DEBUG SLOW ME DOWN
      const size_t update_coef = 1<<3;
#   else
      const auto pause_delay = std::chrono::milliseconds(50);
      const size_t update_coef = 1<<4;
#   endif

    std::function<void(BFSWalker*)> end_bfs_with_error_mt = [&] (BFSWalker* w) -> void {
      mut_out.lock();
      bad = w;
      mut_out.unlock();
    };

    std::function<void()> lambda_bfs = [&]() -> void {
      std::vector<BFSWalker*> buffer;
      const size_t bfs_limit = OPTIONS.bfs_limit;
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        const bool enable_liveness = OPTIONS.liveness;
        bool liveness[_ROMP_LIVENESS_PROP_COUNT];
#     endif
      mut_in.lock();
      mut_out.lock();
      while (not q.empty() && q.size()<TARGET && rules_applied < bfs_limit && bad == nullptr) {
        mut_out.unlock();
        auto b_w = q.front();
        q.pop_front();
        mut_in.unlock();
#       if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
          if (enable_liveness) std::memset(liveness,0u,sizeof(bool)*_ROMP_LIVENESS_PROP_COUNT);
#       endif
        for (size_t i=0; /*q.size()<TARGET &&*/ i<_ROMP_RULESETS_LEN; ++i)
          for (auto rule : ::__caller__::RULESETS[i].rules) {
            BFSWalker* walker = BFSWalker::copy(b_w);
            // walker->sim1step(rule);
            walker->sim1Step_no_trace(rule);
            if (walker->is_done()) {
              end_bfs_with_error_mt(walker);
              return;
            }
#           if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
              if (enable_liveness) walker->merge_liveness(liveness);
#           endif
            buffer.push_back(walker);
            // if (insert_state(walker->state)) {
            //   // ++rules_applied;
            //   // if (q.size() >= TARGET) break;
            // }
          }
#       if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
          // end if liveness property violated
          if (enable_liveness && (size_t liveness_id = is_live(liveness)) < _ROMP_LIVENESS_PROP_COUNT) {
            b_w->set_liveness_violation(liveness_id);
            end_bfs_with_error_mt(b_w);
            return;
          }
#       endif
        mut_out.lock();
        if (bad != nullptr) return; // end early if another thread found an error
        mut_out.unlock();
        mut_in.lock();
        for (BFSWalker* w : buffer) {
          if (w->pass) ++rules_applied;
          if (insert_state(w->state)) {
            q.push_back(w);
          } else delete w;
        }
        buffer.clear();
        delete b_w;
        mut_out.lock();
      }
      mut_out.unlock();
      mut_in.unlock();
    };

    for (size_t i=0; i<OPTIONS.threads; ++i) {
      threads.push_back(std::thread(lambda_bfs));
    }

    out << "\n\033[34;1m"
          "=====================================\n"
          "  INITIAL BFS MULTITHREADED STATUS:  \n"
          "=====================================\n"
          "\033[0m\n\n";
    out.out.flush();
    std::this_thread::sleep_for(pause_delay*2);

    mut_in.lock();
    mut_out.lock();
    while (not q.empty() && q.size()<TARGET && rules_applied < OPTIONS.bfs_limit && bad == nullptr) {
      mut_out.unlock();
      // if (cycle % update_coef == 0) {
      //   out << out.indentation() 
      //       << '[' << (time_mr() - start_time) << "] " 
      //         "States found: " << states.size() << "; "
      //         "Rules Applied: " << rules_applied << "; "
      //         "BFS Progress: " << ((long long)((q.size()*100)/(TARGET*100)))
      //       << " (" << q.size() << '/' << TARGET << ");\n";
      //   mut_in.unlock();
      //   out.out.flush();
      // } else 
        mut_in.unlock();
      // ++cycle;
      std::this_thread::sleep_for(pause_delay);
      mut_in.lock();
      mut_out.lock();
    }
    mut_in.unlock();
    mut_out.unlock();

    std::this_thread::sleep_for(pause_delay*2); // might be able to skip this
    for (auto& t : threads) {
      t.join(); // might be able to skip this
    }

    if (bad != nullptr) {
      end_bfs_report_error(bad);
      return;
    }

    if (not q.empty()) {
      out << "\n\033[34;1m"
             "=====================================\n"
             "   INITIAL BFS MULTITHREADED DONE    \n"
             "=====================================\n"
             "\033[0m\n\n";
      out.out.flush();
      end_bfs();
      this->launch_threads();
    } else
      end_bfs_solved();
    /* Ideas
        - short term store new states in vector per threads then lock to add new states in bulk 
    */
  }

  /**
   * @brief Launch threads with a collection of states to start with
   */
  void launch_threads() {
    states.clear(); // clear states to free up memory
    // RandWalker::reset_ids();
    auto tmp_seeds = gen_random_seeds(OPTIONS,OPTIONS.rand_seed);
    std::vector<BFSWalker*> l(q.begin(),q.end()); // transfer contents for speed later
    std::queue<RandSeed_t> in_seeds(std::deque<RandSeed_t>(tmp_seeds.begin(),tmp_seeds.end()));
    // std::queue<RandWalkers*> parallel_rws; // probs threads
    std::queue<RandWalker*> out_rws;
    size_t walks_done = 0;
    std::mutex in_queue;
    std::mutex out_queue;
    size_t cycles = 0ul;
    size_t progress = 0ul;
    // std::mutex _in_queue_mutex;
    // std::mutex _out_queue_mutex;

#   ifdef DEBUG
      const auto pause_delay = std::chrono::milliseconds(250); //DEBUG SLOW ME DOWN
      const size_t update_coef = 1<<6;
#   else
      const auto pause_delay = std::chrono::milliseconds(20);
      const size_t update_coef = 1<<8;
#   endif

    auto lambda = [&]() { // code the threads run
      in_queue.lock();
      while (in_seeds.size() > 0) { 
        in_seeds.front(); RandWalker *rw = new RandWalker(*l[in_seeds.size()%OPTIONS.bfs_coefficient%l.size()],
                                                          in_seeds.front(),OPTIONS);
        in_seeds.pop(); 
        in_queue.unlock();

        // rw->init(); // no need to init when starting from bfs
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

    out << "\n\033[34;1m"
          "==================================\n"
          "   PARALLEL RANDOM WALK STATUS:   \n"
          "==================================\n"
          "\033[0m\n\n";
    out.out.flush();
    
    std::this_thread::sleep_for(pause_delay*2);
    while (true) {
      while (true) {  // handel outputs
        // if (cycles % update_coef == 0) { // this really slows things down
        //   out.indent();
        //   out << '[' << (time_ms() - start_time) << "] " 
        //       << progress << '/' << OPTIONS.walks
        //       << " walks complete" << out.nl();
        //   out.dedent();
        //   out.out.flush();
        // }
        ++cycles;
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
          ++progress;
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
    out.indent();
    out << out.nl() << "Actual Runtime: " << (time_ms()-start_time) << "\n\n";
    out.dedent();
    out.out.flush();
  }


  /**
   * @brief Helper function to insert states into the state hash set
   * @param state the state to be hashed and stored in the state.
   * @return \c bool - true if the state is a new addition false if seen before
   */
  inline bool insert_state(const State_t& state) {
    return std::get<1>(states.insert(state));
  }

# if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
    size_t was_live(bool* is_live) const {
      for (size_t i=0; i<_ROMP_LIVENESS_PROP_COUNT; ++i)
        if (not is_live[i]) return i;
      return _ROMP_LIVENESS_PROP_COUNT;
    }
# endif

  /**
   * @brief call when an error occurs during BFS (ends run early)
   *        NOTE: will delete walker
   * @param walker the walker that finished its run (will be deleted during call)
   */
  inline void end_bfs_report_error(BFSWalker* walker) {
    auto t = time_ms() - start_time;
    walker->finalize();
    std::string color = "\033[30;1;4m";
    out << '\n' << out.nl() 
        << "Error found during initial BFS"
        << out.nl() << *walker << '\n'
        << out.nl() << "\033[1;4mBFS SUMMARY:\033[0m" << out.indent()
        << out.nl() << "Error found see above for details"
        << out.nl() << "    States Found: " << states.size()
        << out.nl() << "   Rules Applied: " << rules_applied
        << out.nl() << "  Actual Runtime: " << t
        << "\n\n";
    delete walker;
    out.out << std::flush;
  }
  
  /**
   * @brief call when bfs ends with no new items in the queue
   */
  inline void end_bfs_solved() {
    auto t = time_ms() - start_time;
    std::string color = "\033[32;1m";
    out << out.nl()
        << "NO ERRORS found!  BFS had FULL COVERAGE!"
        << out.nl() << "\033[1;4mBFS SUMMARY:\033[0m" << out.indent()
        << out.nl() << "    States Found: " << states.size()
        << out.nl() << "   Rules Applied: " << rules_applied
        << out.nl() << "  Actual Runtime: " << t
        << "\n\n";
    out.out << std::flush;
  }

  inline void end_bfs() {
    auto t = time_ms() - start_time;
    out << out.nl()
        << "NO ERRORS found during initial BFS\n"
        << out.nl() 
          << ((rules_applied >= OPTIONS.bfs_limit) 
                ? "WARNING : BFS limit was reached, statespace might not have been sufficiently explored before launching the walkers !!\n" 
                : std::string(""))
        << out.nl() << "\033[1;4mBFS SUMMARY:\033[0m" << out.indent()
        << out.nl() << "    States Found: " << states.size()
        << out.nl() << "   Rules Applied: " << rules_applied
        << out.nl() << "     BFS Runtime: " << t
        << "\n\n";
    out.out << std::flush;
  }

};


} // namespace romp
