#include <dak_script/mmapped_file.h>

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
#ifdef __unix__

mmapped_file::mmapped_file(file_descriptor &fd, size_t size, const char *data)
    : m_fd{fd}, m_size{size}, m_data{data}
{
}
mmapped_file mmapped_file::map(file_descriptor &fd)
{
	return mmapped_file::map(fd, fd.size());
}

mmapped_file mmapped_file::map(file_descriptor &fd, size_t length)
{

	void *ptr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd.id(), 0u);
	if (ptr == MAP_FAILED)
		return {fd, 0, nullptr};

	return mmapped_file(fd, length, static_cast<const char *>(ptr));
}

int mmapped_file::unmap() { return munmap((void *)m_data, m_size); }

#elif defined(WIN32) || defined(_WIN32)

#endif
} // namespace dak_script