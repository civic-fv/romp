/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file bfs-prob.hpp
 * 
 * @brief code for the probability table generating bfs
 * 
 * @date 2023/01/10
 * @version 0.3
 */


#ifndef __romp__GENERATED_CODE
#include "include.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#include "types.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "walker.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "bfs.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "options.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#endif

namespace romp {


struct ProbEntry {
  uint32_t cond_count=0;
  const Rule& rule;
  uint16_t event_count[_ROMP_RULE_COUNT];
  ProbEntry() = delete;
  ProbEntry(const Rule& rule_) 
    : rule(rule_)
  { 
    std::memset(event_count, 0u, sizeof(uint16_t)*_ROMP_RULE_COUNT); 
  }
  friend ostream_tsv& operator << (ostream_tsv& out, const ProbEntry& d) {
    out << d.rule.rID << '\t' 
        << '"' << d.rule << '"';
    for (size_t i=0ul; i<_ROMP_RULE_COUNT; ++i)
        out << '\t' << d.event_count[i] / d.cond_count;  
    out << '\n';
    out.out.flush();
    return out;
  }
};

#define _ROMP_RULE_COUNT_INC (_ROMP_RULE_COUNT+_ROMP_STARTSTATES_LEN)
struct ProbTable {
  size_t ap_count=0;
  ProbEntry* events[_ROMP_RULE_COUNT_INC];
  
  ProbTable() {
    size_t rs=0; size_t r=0;
    for (size_t i=0; i<_ROMP_RULE_COUNT; ++i) {
      if (r >= ::__caller__::RULESETS[rs].rules.size()) {
        rs++; r=0;
      }
      this->events[i] = new ProbEntry(::__caller__::RULESETS[rs].rules[r]);
    }
  }

  inline void increment_cond(const size_t cond) {
    events[cond]->cond_count++;
  }
  inline void increment_event(const Rule& cond, const Rule& event) {
    events[cond.rID]->event_count[event.rID]++;
  }
  friend ostream_tsv& operator << (ostream_tsv& out, const ProbTable& t) {
    out << "RULE\tID";
    for (size_t i=0; i<_ROMP_RULE_COUNT; ++i)
      out << '\t' << i;
    out << out.nl()
        << "ID\tLABEL";
    for (size_t i=0; i<_ROMP_RULE_COUNT; ++i)
      out << '\t' << t.events[i]->rule;
    out << out.nl();
    for (size_t i=0; i<_ROMP_RULE_COUNT; ++i)
      out << *(t.events);  
    return out;
  }
};

class ProbWalker : public BFSWalker {
public:
  ProbWalker(const Options& O_, size_t& val)
    : BFSWalker(O_,val)
  {}
  const Rule* last_rule() const {
    if (history_size() == 0)
      return nullptr; // last rule was a startstate
    return history[(history_level-1)%history_size()].rule;
  }
};



struct ProbBFSHandler {
  std::ofstream _tsv_file;
protected:
  typedef std::bitset<_ROMP_RULE_COUNT> RBitset;
  const Options& OPTIONS;
  std::deque<std::pair<ProbWalker*,RBitset*>> q;
  std::unordered_set<State_t> states;
  size_t rules_applied = 0ul;
  const size_t LIMIT;
  time_ms_t start_time;
  ostream_p out;
  ostream_tsv tsv;
  ProbTable prob_table;


public:

  ProbBFSHandler(const Options& OPTIONS_) 
    : OPTIONS(OPTIONS_),
      LIMIT(OPTIONS_.prob_bfs_limit),
      out(std::cout,OPTIONS_,0),
      _tsv_file(OPTIONS_.prob_bfs_out_tsv_file),
      tsv(_tsv_file)
  {}

  ~ProbBFSHandler() {
    _tsv_file.close();
    for (auto [w, s] : q) {
      if (w != nullptr) delete w;
      if (s != nullptr) delete s;
    }
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
      auto walker = new ProbWalker(OPTIONS,i);
      auto r_e = new RBitset();
      r_e->reset();
      walker->init_state();
      ++rules_applied;
      if (walker->is_done()) {  // discover error during 
        end_bfs_report_error(walker);
        return;
      } else if (insert_state(walker->state))
        q.push_back(std::make_pair(walker, r_e));
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
    while (not q.empty() && rules_applied<LIMIT && rules_applied < OPTIONS.prob_bfs_limit) {
      auto[b_w, r_e] = q.front();
      q.pop_front();
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        if (enable_liveness) std::memset(liveness,0u,sizeof(bool)*_ROMP_LIVENESS_PROP_COUNT);
#     endif
      size_t rID = 0;
      std::deque<ProbWalker*> qBuff;
      for (size_t i=0; rules_applied<LIMIT && i<_ROMP_RULESETS_LEN; ++i)
        for (auto rule : ::__caller__::RULESETS[i].rules) {
          ProbWalker* walker = (ProbWalker*) std::malloc(sizeof(ProbWalker));
          std::memcpy(walker,b_w,sizeof(ProbWalker)); // copy base walker
          // walker->sim1step(rule);
          walker->sim1Step_no_trace(rule); 
          if (walker->is_done()) {
            end_bfs_report_error(walker);
            return;
          }
#         if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
            if (enable_liveness) walker->merge_liveness(liveness);
#         endif
          if (walker->pass) {
            ++rules_applied; //TODO insert code for keeping probability tables up to date
            prob_table.increment_cond(rID); // count this as a time when the rule ran
            if (not (*r_e)[rID]) {    //the rule that made b_w made a change to allow this rule to run
              const Rule* lastR = b_w->last_rule();
              if (lastR != nullptr) // the rule that ran before was not a start state
                prob_table.increment_event(*lastR, rule);
            }
            (*r_e)[rID] = true;
          } else 
            (*r_e)[rID] = false;
          if (insert_state(walker->state)) {
              qBuff.push_back(walker);
            if (q.size() >= LIMIT)
              break;
          } else delete walker;
          rID++;
        }
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        // end if liveness property violated
        if (enable_liveness && (size_t liveness_id = is_live(liveness)) < _ROMP_LIVENESS_PROP_COUNT) {
          b_w->set_liveness_violation(liveness_id);
          end_bfs_report_error(b_w);
          return;
        }
#     endif
      while (not qBuff.empty()) {
        RBitset* _r_e = (RBitset*) std::malloc(sizeof(RBitset));
        std::memcpy(_r_e, r_e, sizeof(RBitset));
        q.push_back(std::make_pair(qBuff.front(),_r_e));
        qBuff.pop_front();
      }
      delete b_w, r_e;
    }

    if (not q.empty()) {
      end_bfs();
      // this->launch_threads();
    } else
      end_bfs_solved();
    tsv << prob_table << tsv.nl();
    _tsv_file.close();
  }


  /**
   * @brief Perform the bfs in a multithreaded manner
   *        NOTE: must be called after processing start states
   */
  void multithreaded_bfs() {
    std::cerr << "\nNYI : multithreaded probability table generation is not yet implemented\n" << std::flush;
    exit(EXIT_FAILURE);
    /* std::mutex mut_in, mut_out;
    ProbWalker* bad = nullptr;
    std::vector<std::thread> threads;
    size_t cycle = 0ul;

#   ifdef DEBUG
      const auto pause_delay = std::chrono::milliseconds(20); //DEBUG SLOW ME DOWN
      const size_t update_coef = 1<<3;
#   else
      const auto pause_delay = std::chrono::milliseconds(50);
      const size_t update_coef = 1<<4;
#   endif

    std::function<void(ProbWalker*)> end_bfs_with_error_mt = [&] (ProbWalker* w) -> void {
      mut_out.lock();
      bad = w;
      mut_out.unlock();
    };

    std::function<void()> lambda_bfs = [&]() -> void {
      std::vector<ProbWalker*> buffer;
      const size_t bfs_limit = OPTIONS.prob_bfs_limit;
#     if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
        const bool enable_liveness = OPTIONS.liveness;
        bool liveness[_ROMP_LIVENESS_PROP_COUNT];
#     endif
      mut_in.lock();
      mut_out.lock();
      while (not q.empty() && q.size()<LIMIT && rules_applied < bfs_limit && bad == nullptr) {
        mut_out.unlock();
        auto b_w = q.front();
        q.pop_front();
        mut_in.unlock();
#       if (defined(__romp__ENABLE_liveness_property) && _ROMP_LIVENESS_PROP_COUNT > 0)
          if (enable_liveness) std::memset(liveness,0u,sizeof(bool)*_ROMP_LIVENESS_PROP_COUNT);
#       endif
        for (size_t i=0; i<_ROMP_RULESETS_LEN; ++i)
          for (auto rule : ::__caller__::RULESETS[i].rules) {
            ProbWalker* walker = (ProbWalker*) std::malloc(sizeof(ProbWalker));
            std::memcpy(walker,b_w,sizeof(ProbWalker)); // copy base walker
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
            //   // if (q.size() >= LIMIT) break;
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
        for (ProbWalker* w : buffer) {
          if (w->pass) ++rules_applied; //TODO insert code for keeping probability tables up to date
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
    while (not q.empty() && q.size()<LIMIT && rules_applied < OPTIONS.prob_bfs_limit && bad == nullptr) {
      mut_out.unlock();
      mut_in.unlock();
      
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
      // this->launch_threads(); // not needed for prob search
    } else
      end_bfs_solved();
    // Ideas
    //     - short term store new states in vector per threads then lock to add new states in bulk 
    */
  }

  // /**
  //  * @brief Launch threads with a collection of states to start with
  //  */
//   void launch_threads() {
//     states.clear(); // clear states to free up memory
//     // RandWalker::reset_ids();
//     auto tmp_seeds = gen_random_seeds(OPTIONS,OPTIONS.rand_seed);
//     std::vector<ProbWalker*> l(q.begin(),q.end()); // transfer contents for speed later
//     std::queue<RandSeed_t> in_seeds(std::deque<RandSeed_t>(tmp_seeds.begin(),tmp_seeds.end()));
//     // std::queue<RandWalkers*> parallel_rws; // probs threads
//     std::queue<RandWalker*> out_rws;
//     size_t walks_done = 0;
//     std::mutex in_queue;
//     std::mutex out_queue;
//     size_t progress = 0ul;
//     // std::mutex _in_queue_mutex;
//     // std::mutex _out_queue_mutex;

// #   ifdef DEBUG
//       const auto pause_delay = std::chrono::milliseconds(250); //DEBUG SLOW ME DOWN
//       const size_t update_coef = 1<<6;
// #   else
//       const auto pause_delay = std::chrono::milliseconds(20);
//       const size_t update_coef = 1<<8;
// #   endif

//     auto lambda = [&]() { // code the threads run
//       in_queue.lock();
//       while (in_seeds.size() > 0) { 
//         RandWalker *rw = new RandWalker(*l[in_seeds.size()%OPTIONS.prob_bfs_coefficient%l.size()],
//                                         in_seeds.front(),OPTIONS);
//         in_seeds.pop(); 
//         in_queue.unlock();

//         // rw->init(); // no need to init when starting from bfs
//         while (not rw->is_done())
//           rw->sim1Step();
//         rw->finalize();

//         out_queue.lock();
//         out_rws.push(rw);
//         ++walks_done;
//         out_queue.unlock();

//         in_queue.lock();
//       }
//       in_queue.unlock();
//     };

//     ostream_p out(std::cout,OPTIONS,0);
//     std::vector<std::thread> threads;
//     ResultTree summary(OPTIONS);
//     // std::vector<std::thread> threads(OPTIONS.threads);
//     for (size_t i=0; i<OPTIONS.threads; ++i) {
//       threads.push_back(std::thread(lambda));
//     }
//     // std::lock_guard<std::mutex> in_queue(_in_queue_mutex);
//     // std::lock_guard<std::mutex> out_queue(_out_queue_mutex);

//     out << "\n\033[34;1m"
//           "==================================\n"
//           "   PARALLEL RANDOM WALK STATUS:   \n"
//           "==================================\n"
//           "\033[0m\n\n";
//     out.out.flush();
    
//     std::this_thread::sleep_for(pause_delay*2);
//     while (true) {
//       while (true) {  // handel outputs
//         std::this_thread::sleep_for(pause_delay);
//         out_queue.lock();
//         if (not (out_rws.size() > 0)) {
//           out_queue.unlock();
//           break;
//         }
//         RandWalker* rw = out_rws.front();
//         out_rws.pop();
//         out_queue.unlock();
//         if (rw != nullptr) {
//           ++progress;
//           if (rw->do_report())
//             std::cout << *rw << std::endl;
//           // todo get the results
//           summary.insert(rw->get_result());
//           delete rw;
//         }
//       }
      
//       std::this_thread::sleep_for(pause_delay); 
//       out_queue.lock();
//       if (not (walks_done < OPTIONS.walks)) {
//         out_queue.unlock();
//         break;
//       }
//       out_queue.unlock();
//     }
//     // we might need to do this one more time for the last one

//     summary.stop_timer();

//     for (size_t i=0; i<OPTIONS.threads; ++i) // join threads
//       threads[i].join();

//     print_romp_results_summary(summary);
//     out.indent();
//     out << out.nl() << "Actual Runtime: " << (time_ms()-start_time) << "\n\n";
//     out.dedent();
//     out.out.flush();
//   }


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
  inline void end_bfs_report_error(ProbWalker* walker) {
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
          << ((rules_applied >= OPTIONS.prob_bfs_limit) 
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
