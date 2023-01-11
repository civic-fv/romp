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
 * @version 0.2
 */


#ifndef __romp__GENERATED_CODE
#include "include.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#include "types.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "walker.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "options.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#endif

namespace romp {

  class BFSWalker : public IRandWalker {
    const Options& OPTIONS;
    id_t _start_id;
    size_t _depth = 0ul;
    Result::Cause status = Result::NO_CAUSE;
    IModelError* tripped = nullptr;
    IModelError* tripped_inside = nullptr;
    size_t history_level = 0;
    constexpr size_t history_size() const { return _ROMP_HIST_LEN*2+1; }
    RandWalker::History history[_ROMP_HIST_LEN*2+1];
    size_t history_start = 0;
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
    std::function<void(size_t,size_t)> sim1step;

    BFSWalker(const Options OPTIONS_, id_t start_id_)
      : OPTIONS(OPTIONS_), start_id(start_id_)
    {
        sim1step = std::function<void(size_t,size_t)>([this](size_t i, size_t j) { 
                    sim1step_no_trace(::__caller__::RULESETS[i].rules[j]); });
    }

    ~BFSWalker() {
      if (json != nullptr) delete json;
      if (tripped != nullptr) delete tripped;
      if (tripped_inside != nullptr) delete tripped_inside;
    }

  void init_state() noexcept {    
    const StartState& startstate = ::__caller__::STARTSTATES[start_id];
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
                  0ul, true, 0ul,
                  start_id, status, depth,
                  tripped, tripped_inside
#ifdef __ROMP__DO_MEASURE
                  ,active_time, 0ul
#endif
                  };
    tripped = nullptr;
    tripped_inside = nullptr;
    return result;
  }

    void sim1Step_no_trace(const Rule& r) noexcept {
#     ifdef __ROMP__DO_MEASURE
        start_time = time_mr();
#     endif
      bool pass = false;
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
      return false;  // never throw anything if cover is not enabled by romp generator
    }
# ifdef __romp__ENABLE_liveness_property
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
#  else
    bool liveness_handler(bool expr, id_t liveness_id, id_t prop_id) {
      return false;  // never throw anything if cover is not enabled by romp generator
    }

    State_t state;
    friend RandWalker;
  };


  /**
   * @brief Launch threads with a collection of states to start with
   * @param OPTIONS a reference to an option object to use for the romp run
   * @param states a deque (internal queue container) that holds all of the states to start with.
   */
  void launch_threads(const Options& OPTIONS, std::deque<State_t> states) {
    RandWalker::reset_ids();
    auto tmp_seeds = gen_random_seeds(OPTIONS,rand_seed);
    std::queue<RandSeed_t> in_seeds(std::deque<RandSeed_t>(tmp_seeds.begin(),tmp_seeds.end()));
    // std::queue<RandWalkers*> parallel_rws; // probs threads
    std::queue<RandWalker*> out_rws;
    size_t walks_done = 0;
    std::mutex in_queue;
    std::mutex out_queue;
    // std::mutex _in_queue_mutex;
    // std::mutex _out_queue_mutex;

# ifdef DEBUG
    const auto pause_delay = std::chrono::milliseconds(250); //DEBUG SLOW ME DOWN
# else
    const auto pause_delay = std::chrono::milliseconds(5);
# endif

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
   * @brief Launch a romp run where we first do a single threaded BFS before 
   *        launching the swarm of random walkers.
   * @param OPTIONS the options object defining how the romp run should work.
   *                (required that bfs and do_even start be true)
   */
  void launch_bfs(const Options& OPTIONS) {
    std::queue<RandWalker*> q;
    std::unordered_set<State_t> states;

    // - run through the startstates and add them to the queue ---- 
    for (size_t i=0; i<_ROMP_STARTSTATES_LEN; ++i) {
      auto walker = new RandWalker(OPTIONS,)
    }


  }


} // namespace romp
