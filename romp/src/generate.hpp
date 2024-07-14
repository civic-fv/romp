#pragma once

#include <cstddef>
#include <iostream>
#include <murphi/murphi.h>
#include <vector>
#include <string>

namespace romp {
  class ModelGenerator;
}

/// output C++ code equivalent of the given model
void generate(const murphi::Model &m,
                const std::vector<murphi::Comment> &comments,
                romp::ModelGenerator &gen,
                const std::string& build_cmds);