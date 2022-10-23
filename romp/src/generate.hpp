#pragma once

#include "CodeGenerator.hpp"
#include <cstddef>
#include <iostream>
#include <murphi/murphi.h>
#include <vector>
#include <string>



/// output C++ code equivalent of the given model
void generate(const murphi::Model &m,
                const std::vector<murphi::Comment> &comments,
                romp::CodeGenerator &gen,
                const std::string& build_cmds);
