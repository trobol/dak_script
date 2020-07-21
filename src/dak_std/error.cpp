#include <cstring>
#include <errno.h>

#include <dak_std/error.h>
namespace dak_std
{
error make_error() { return error(errno); }

char *error::str() { return std::strerror(m_error_num); }
} // namespace dak_std
