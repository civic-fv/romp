/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw-main.hpp
 *
 * @brief
 *
 * @date 2022/07/12
 * @version 0.3
 */


#ifndef __romp__GENERATED_CODE
#include "walker.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "bfs.hpp"  // LANGUAGE SERVER SUPPORT ONLY !!
#include "options.hpp" // LANGUAGE SERVER SUPPORT ONLY !!
#endif

// #include <unistd.h>
namespace romp {
  void init_trace_dir(const Options& OPTIONS) {
    std::string args = "mkdir -p \"" + OPTIONS.get_trace_dir() + "\"";
    int err = system(args.c_str());
    if (err) {
      std::cerr << "\nERROR :: trace directory ``" << OPTIONS.get_trace_dir() << "`` does not exists and could not be created !!\n\n"
                << std::flush;
      exit(EXIT_FAILURE);
    }
  }

  void launch_prompt(const Options& OPTIONS) {
    ostream_p out(std::cout,OPTIONS,0);
    std::cout << '\n';
    OPTIONS.write_config(out);
    std::cout.flush();
    for (;;) {
      std::cout << "Correct Config? [yes=launch/no=exit]: " << std::flush;
      std::string _val; char val;
      std::cin >> _val;
      if (_val.size()>0) val = std::tolower(_val[0]);
      switch (val) {
        case 'y':
        case 'l':
          return;
        case 'n':
        case 'e':
          exit(EXIT_SUCCESS); break;
        default:
          break;
      }
      std::cout << "COULDN'T RECOGNISE RESPONSE; TRY AGAIN\n";
    }
  }
}

int main(int argc, char **argv) {
  ::romp::Options OPTIONS;
  OPTIONS.parse_args(argc, argv);

  if (not (OPTIONS.skip_launch_prompt))
    ::romp::launch_prompt(OPTIONS);

  if (OPTIONS.do_trace)
    ::romp::init_trace_dir(OPTIONS);

  if (OPTIONS.do_bfs)
    ::romp::BFSHandler(OPTIONS).launch();
  else if (OPTIONS.do_single)
    ::romp::launch_single(OPTIONS);

  else
    ::romp::launch_threads(OPTIONS);
    // ::romp::launch_OpenMP(::romp::OPTIONS.rand_seed);


  return EXIT_SUCCESS;
}

//TODO add in signal intercept for kill/Ctrl-C to gracefully kill threads & output traces etc.