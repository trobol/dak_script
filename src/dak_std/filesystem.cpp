#include <dak_std/filesystem.h>

#ifdef WINDOWS
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif

std::string get_working_directory()
{
	char buff[FILENAME_MAX];
	getcwd(buff, FILENAME_MAX);
	return std::string(buff);
}