#pragma once

#include "location.hh"
#include <cstddef>
#include <stdexcept>
#include <string>

#ifndef ROMP_API_WITH_RTTI
#define ROMP_API_WITH_RTTI __attribute__((visibility("default")))
#endif

namespace romp {

/* A basic exception to allow us to easily catch only the errors thrown by
 * ourselves.
 */
class ROMP_API_WITH_RTTI Error : public std::runtime_error {

public:
  location loc;

  Error(const std::string &message, const location &loc_);
  Error(const std::string &prefix, const Error &sub);
};

} // namespace romp
