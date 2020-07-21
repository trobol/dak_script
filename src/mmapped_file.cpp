#include <dak_script/mmapped_file.h>
#include <dak_std/assert.h>
#include <dak_std/error.h>

#ifdef __unix__
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#elif defined(WIN32) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace dak_script
{
mmapped_file::mmapped_file(file_descriptor &fd, size_t size, const char *data)
    : m_fd{fd}, m_size{size}, m_data{data}
{
}

mmapped_file mmapped_file::map(file_descriptor &fd)
{
	return mmapped_file::map(fd, fd.size());
}

mmapped_file::~mmapped_file() {}
#ifdef __unix__

mmapped_file mmapped_file::map(file_descriptor &fd, size_t length)
{

	void *ptr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd.id(), 0u);
	if (ptr == MAP_FAILED)
		return {fd, 0, nullptr};

	return mmapped_file(fd, length, static_cast<const char *>(ptr));
}

dak_std::error mmapped_file::unmap()
{
	int err = munmap((void *)m_data, m_size);
	m_data = nullptr;
	m_size = 0;

	if (err == 0)
	{
		return dak_std::error();
	}
	else
	{
		return dak_std::make_error();
	}
}

#elif defined(WIN32) || defined(_WIN32)

#endif
} // namespace dak_script