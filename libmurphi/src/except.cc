#include "location.hh"
#include <cstddef>
#include <murphi/except.h>
#include <stdexcept>
#include <string>

namespace murphi {

Error::Error(const std::string &message, const location &loc_)
    : std::runtime_error(message), loc(loc_) {}

Error::Error(const std::string &prefix, const Error &sub)
    : std::runtime_error(prefix + sub.what()), loc(sub.loc) {}

} // namespace murphi
