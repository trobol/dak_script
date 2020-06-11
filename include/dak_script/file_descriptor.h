#ifndef _DAK_SCRIPT_FILE_HANDLE_H
#define _DAK_SCRIPT_FILE_HANDLE_H
#include <string>

namespace dak_script
{

enum file_mode
{
	READ_ONLY = 00,
	WRITE_ONLY = 01,
	READ_WRITE = 02
};

class file_descriptor
{
private:
	int m_id;
	file_descriptor(int);

public:
	file_descriptor(const file_descriptor &) = delete;

	file_descriptor(file_descriptor &&);

	int close();

	size_t size() const;

	static file_descriptor open(const std::string &path, file_mode mode);
	static file_descriptor open(std::string &&path, file_mode mode);
	static file_descriptor open(const char *path, file_mode mode);

	int id() const { return m_id; }
};

} // namespace dak_script

#endif