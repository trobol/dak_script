#include <dak_script/file_descriptor.h>

#ifdef __unix__
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#elif defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#endif

namespace dak_script
{

file_descriptor::file_descriptor(int id) : m_id{id} {}

file_descriptor::file_descriptor(file_descriptor &&) {}

#ifdef __unix__

int file_descriptor::close() { return ::close(m_id); }

size_t file_descriptor::size() const
{
	if (m_id == -1)
		return 0;
	struct stat sb;
	if (fstat(m_id, &sb) == -1)
		return 0;

	return sb.st_size;
}

file_descriptor file_descriptor::open(const dak_std::string &path,
				      file_mode mode)
{
	return {::open(path.data(), mode)};
}

file_descriptor file_descriptor::open(dak_std::string &&path, file_mode mode)
{
	return {::open(path.data(), mode)};
}

#elif defined(WIN32) || defined(_WIN32)

file_descriptor file_descriptor::open(const dak_std::string &path,
				      file_mode mode = READ_ONLY)
{
	return file_descriptor::open(path.c_str());
}

file_descriptor file_descriptor::open(dak_std::string &&path,
				      file_mode mode = READ_ONLY)
{
	return ::open(path.c_str(), O_RDONLY);
}

void handle_close(file_descriptor handle);

size_t len(file_descriptor handle);

#endif

} // namespace dak_script
