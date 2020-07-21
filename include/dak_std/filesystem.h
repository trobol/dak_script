#ifndef _DAK_STD_FILESYSTEM_H
#define _DAK_STD_FILESYSTEM_H

#include <dak_std/string.h>

namespace dak_std
{
dak_std::string get_working_directory();

bool is_directory(const dak_std::string &);

} // namespace dak_std

#endif