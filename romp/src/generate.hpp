#pragma once

#include "CodeGenerator.hpp"
#include <cstddef>
#include <iostream>
#include <murphi/murphi.h>
#include <vector>
#include <string>

/// output C code equivalent of the given node
///
/// \param m \c murphi::Model to translate
/// \param comments List of source code comments
/// \param pack Whether all structs are packed
/// \param out Stream to write translation to
void generate_c(const murphi::Model &m,
                const std::vector<murphi::Comment> &comments,
                romp::CodeGenerator &out,
                const std::string& build_cmds);
