/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file StateSpaceCalc.hpp
 * 
 * @brief Simple utility to calculate the total number of possible permutations 
 *        a murphi models state can be in.
 * 
 * @date 2022/08/19
 * @version 0.1
 */


#include <rumur/rumur.h>

namespace romp {

  mpz_class statespace_count(const rumur::Record& n);

}