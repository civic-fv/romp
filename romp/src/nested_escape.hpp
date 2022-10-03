/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file nested_escape.hpp
 * 
 * @brief a handy utility for escaping strings in a way that works with nesting strings isn strings.
 *        like when you want to generate c/c++ code that contains a string with json info 
 *          where a json string may or may-not contain `"`
 * 
 * @date 2022/07/20
 * @version 0.1
 */

#pragma once

#include <string>

/**
 * @brief a handy utility for escaping strings in a way that works with nesting strings isn strings.
 *        like when you want to generate c/c++ code that contains a string with json info 
 *          where a json string may or may-not contain `"`
 * @param val the string to have the escape sequences applied to (will not be edited)
 * @return \c std::string - the processed string
 */
std::string nEscape(const std::string& val);
