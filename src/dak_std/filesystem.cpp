#include <dak_std/filesystem.h>

#ifdef WINDOWS
#include <direct.h>
#define getcwd _getcwd

#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace dak_std
{

string get_working_directory()
{
	char buff[FILENAME_MAX];
	getcwd(buff, FILENAME_MAX);
	return string(buff);
}

bool is_directory(const string &path)
{
	struct stat sb;
	stat(path.data(), &sb);
	return sb.st_mode & S_IFDIR;
}

} // namespace dak_std
