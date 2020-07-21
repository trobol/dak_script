#ifndef _DAK_SCRIPT_MAPPED_FILE_H
#define _DAK_SCRIPT_MAPPED_FILE_H

#include <dak_script/file_descriptor.h>
#include <dak_std/error.h>
#include <dak_std/string.h>

namespace dak_script
{

class mmapped_file
{
private:
	const char *m_data;
	size_t m_size;
	file_descriptor &m_fd;

	mmapped_file(const mmapped_file &);

public:
	static mmapped_file map(file_descriptor &fd);
	static mmapped_file map(file_descriptor &fd, size_t size);

	mmapped_file(file_descriptor &fd, size_t size, const char *data);

	size_t size() const { return m_size; }
	const char *data() const { return m_data; }
	dak_std::error unmap();

	~mmapped_file();
};

} // namespace dak_script

#endif