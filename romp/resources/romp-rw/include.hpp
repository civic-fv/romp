/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw/include.hpp
 * 
 * @brief the includes needed for the generated model checker
 * 
 * @date 2022/10/05
 * @version 0.3
 */

#ifndef __romp__GENERATED_CODE
#pragma once  // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif

// #include <assert.h>
// #include <stdbool.h>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <iomanip>
// #include <stdlib.h>
#include <string>
#include <cstring>  // required for memset
#include <fstream>
#include <sstream>
#include <tuple>
#include <exception>
#include <vector>
#include <queue>
#include <memory>
#include <utility>
#include <functional>
#include <type_traits>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <ctime>
#include <bitset>
#include <random>

#ifndef __romp__GENERATED_CODE
#include "pregen-fix.hpp" // FOR PRE-CODEGEN LANGUAGE SUPPORT ONLY !!
#endif


#ifdef __clang__
using nullptr_t=std::nullptr_t;
#endif
