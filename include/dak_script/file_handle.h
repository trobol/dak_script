#ifndef _DAK_SCRIPT_FILE_HANDLE_H
#define _DAK_SCRIPT_FILE_HANDLE_H
#include <string>

namespace dak::script
{
struct file_handle
{

	
	bool open(std::string path);
	bool close();

	bool read_into(const char* dst, size_t length);
};

} // namespace dak::script

#endif