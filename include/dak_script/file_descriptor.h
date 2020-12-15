#ifndef _DAK_SCRIPT_FILE_HANDLE_H
#define _DAK_SCRIPT_FILE_HANDLE_H
#include <string>

namespace dak::script
{

enum file_mode
{
	READ_ONLY = 1,
	WRITE_ONLY = 2,
	READ_WRITE = 3
};

typedef int file_descriptor;

file_descriptor file_open(std::string path, file_mode mode = READ_ONLY);
file_descriptor file_open(const char *path, file_mode mode = READ_ONLY);

int file_close(file_descriptor fd);

size_t len(file_descriptor fd);

} // namespace dak::script

#endif