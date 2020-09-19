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
/*
// TODO make this less shit
string get_filename(const string &path)
{
	const char *end = path.end();
	const char *begin = path.begin();
	for (unsigned i = path.size(); i > 0; i--)
	{
		const char c = path[i];
		if (c == '.')
		{
			end = begin + i;
		}
		else if (c == '/')
		{
			return string(begin + i + 1, end);
		}
	}
	return "";
}
*/
} // namespace dak_std
