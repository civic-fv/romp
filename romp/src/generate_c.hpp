#pragma once

#include <cstddef>
#include <iostream>
#include <murphi/murphi.h>
#include <vector>
#include <string>

/// output C code equivalent of the given node
///
/// \param n Node to translate
/// \param comments List of source code comments
/// \param pack Whether all structs are packed
/// \param out Stream to write translation to
void generate_c(const murphi::Node &n,
                const std::vector<murphi::Comment> &comments, bool pack,
                std::ostream &out,
                const std::string& build_cmds);
