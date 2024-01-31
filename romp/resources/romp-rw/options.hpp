/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw-options.hpp
 *
 * @brief the handler for the configuration of a random walk
 *
 * @date 2022/10/05
 * @version 0.3
 */

#ifndef __romp__GENERATED_CODE
#pragma once
#include "include.hpp"
#include "decl.hpp"
#include "writers.hpp"
#include "error.hpp"
#include <functional>
#include <iostream>
#include <string>
#endif

namespace romp {

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

    /**
     * @brief the number of concurrent threads a system supports \n
     *        \b NOTE: if \c 0 then number is unknown & user must provide with \c -ptn / \c --threads flags.
     */
    const unsigned int __SYSTEM_THREAD_COUNT = ::std::thread::hardware_concurrency();
    unsigned int get_default_thread_count() {
      switch (__SYSTEM_THREAD_COUNT) {
      case 0: return 0;
      case 1: 
      case 2:
        return 1;
      default:
        return __SYSTEM_THREAD_COUNT - 2;
      }
    }
constexpr size_t _ROMP_ATTEMPT_LIMIT_DEFAULT();
#define _ROMP_START_ID_DEFAULT ((unsigned)(~(0u)))
struct Options {
  // size_t history_length = 4;
  bool do_trace = false;
  unsigned int threads =  get_default_thread_count(); 
  size_t depth = 1ul<<12u; // INT16_MAX;      
  unsigned int walks = threads*_ROMP_THREAD_TO_RW_RATIO; 
  unsigned int rand_seed = INIT_SEED;
  std::string seed_str = std::to_string(INIT_SEED);
  bool do_single = false;
  bool do_even_start = false;
  id_t start_id = _ROMP_START_ID_DEFAULT;
  bool skip_launch_prompt = false;
  size_t attempt_limit = _ROMP_ATTEMPT_LIMIT_DEFAULT(); // disabled if _ROMP_ATTEMPT_LIMIT_DEFAULT
  std::string trace_dir = "./traces/"; // path for the trace file to be created during each walk
  bool deadlock = true; // do deadlock protections
#ifdef __romp__ENABLE_liveness_property
  bool liveness = false;
  size_t lcount = INT16_MAX;
#endif
#ifdef __romp__ENABLE_cover_property
  bool complete_on_cover = false;
  id_t cover_count = INT16_MAX; 
#endif
  bool r_cover = false;
// #ifdef __romp__ENABLE_assume_property
  bool r_assume = false;
// #endif
  bool report_error = false; // print results for each walker in addition to the summery
  bool report_all = false;
  bool report_show_type = false;
  bool report_emit_state = true;
  unsigned int tab_size = 2;
  char tab_char = ' ';
  // bfs options ----
  bool do_bfs = false;
  bool bfs_single = true;
  size_t bfs_coefficient = _ROMP_BFS_COEF;
  size_t bfs_limit = INT16_MAX; // max number of states to explore before giving up
  // prob-bfs options ---
  bool do_prob_bfs = false;
  bool prob_bfs_single = true;
  std::string prob_bfs_out_tsv_file = "./" __model__filename_stem ".rP.tsv";
  size_t prob_bfs_limit = UINT16_MAX; // max number of states to explore before giving up

  const std::string get_trace_dir() const noexcept {
    if (do_single) return trace_dir;
    std::stringstream buf; buf << INIT_TIME_STAMP;
    return trace_dir + "/" __model__filename_stem "_" + buf.str();
  }
  const std::string get_trace_file_path(id_t rw_id) const noexcept {
    if (not do_single)
      return get_trace_dir() + "/" + std::to_string(rw_id) + ".trace.json";
    std::stringstream buf; buf << INIT_TIME_STAMP;
    return trace_dir + "/" + __model__filename_stem + "_" + buf.str() + ".trace.json"; 
  }
  bool report_any() const {
    return (report_all || do_single || report_error || r_assume || r_cover);
  }

  template<class O>
  friend ojstream<O>& operator << (ojstream<O>& json, const Options& opts) noexcept;



  void parse_args(int argc, char **argv);

  const stream_void write_config(ostream_p& out) const noexcept;

}; // struct options


// Options OPTIONS;

} // namespace romp
