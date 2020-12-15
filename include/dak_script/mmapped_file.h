#ifndef _DAK_SCRIPT_MAPPED_FILE_H
#define _DAK_SCRIPT_MAPPED_FILE_H

#include <dak_script/file_descriptor.h>
#include <string>

namespace dak::script
{

struct mmapped_file
{
	file_descriptor fd;
	size_t length;
	const char *contents;
	operator const char *() { return contents; }
};

mmapped_file map_file(file_descriptor fd);
mmapped_file map_file(file_descriptor fd, size_t length);

int unmap_file(mmapped_file file);

} // namespace dak::script

#endif