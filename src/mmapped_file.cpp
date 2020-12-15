#include <dak_script/mmapped_file.h>

#ifdef __unix__
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#elif defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#endif

namespace dak::script
{
#ifdef __unix__
mmapped_file map_file(file_descriptor fd)
{
	return map_file(fd, len(fd));
}

mmapped_file map_file(file_descriptor fd, size_t length)
{

	void *ptr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u);
	if (ptr == MAP_FAILED)
		return {fd, 0, nullptr};

	return {
		fd,
		length, static_cast<const char *>(ptr)};
}

int unmap_file(mmapped_file file)
{
	return munmap((void *)file.contents, file.length);
}

#elif defined(WIN32) || defined(_WIN32)

#endif
} // namespace dak::script