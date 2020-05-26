#ifndef _DAK_STD_STRING_H
#define _DAK_STD_STRING_H

#include <cstdlib>
#include <cstring>

namespace dak_std
{
class string
{
private:
	char *m_ptr;
	size_t m_size;
	size_t m_capacity;

public:
	string() noexcept;
	// allocated space will be size+1 for null terminator
	string(size_t size) : string{'*', size} {}
	string(const char c, size_t size) : m_size{size}, m_capacity{size}
	{
		m_ptr = static_cast<char *>(std::malloc(m_size + 1));
		// TODO: check that memory was actually allocated
		for (size_t i = 0; i < m_size; ++i)
		{
			m_ptr[m_size] = c;
		}
		m_ptr[m_size] = NULL;
	}
	string(char const *c_str, size_t size);
	string(char const *c_str);
	string(const string &str);
	string(string &&str) noexcept;

	~string() { free(m_ptr); }

	string &operator=(string const &other);

	char &operator[](size_t i) { return m_ptr[i]; }

	size_t size() const noexcept { return m_size; }
	size_t capacity() const noexcept { return m_capacity; }

	char const *data() const noexcept { return m_ptr; }
};
} // namespace dak_std

#endif