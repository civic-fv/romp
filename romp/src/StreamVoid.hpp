/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file StreamVoid.hpp
 * 
 * @brief A util for cleaner code 
 * 
 * @date 2022/10/21
 * @version 0.2
 */

#include <ostream>

namespace romp {

  // provide a way to inline custom manipulator type functions
  class _StreamVoid {
    void* _ = nullptr;
    friend inline std::ostream& operator << (std::ostream& out, const _StreamVoid&) { return out; }
  };

  typedef const _StreamVoid StreamVoid; 

  StreamVoid S_VOID;

}