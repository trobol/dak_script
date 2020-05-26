#ifndef _DAK_STD_STRING_H
#define _DAK_STD_STRING_H

#include <cstdlib>
#include <cstring>

namespace dak_std
{
class string
{
private:
	union {
		struct {
			char *ptr;
			size_t size;
			size_t capacity;
		};
	} m_data;
	

public:
	string() noexcept;
	// allocated space will be size+1 for null terminator
	string(size_t size) : string{'*', size} {}
	string(const char c, size_t size) : m_data{nullptr, size, size}
	{
		m_data.ptr = static_cast<char *>(std::malloc(m_data.size + 1));
		// TODO: check that memory was actually allocated
		for (size_t i = 0; i < m_data.size; ++i)
		{
			m_data.ptr[m_data.size] = c;
		}
		m_data.ptr[m_data.size] = NULL;
	}
	string(char const *c_str, size_t size);
	string(char const *c_str);
	string(const string &str);
	string(string &&str) noexcept {
		m_data = str.m_data;
		str.m_data.size = 0;
		str.m_data.ptr = nullptr;
		str.m_data.capacity = 0;
	}

	~string() { free(m_data.ptr); }

	string &operator=(string const &other) {
		
	}

	char &operator[](size_t i) { return m_data.ptr[i]; }

	size_t size() const noexcept { return m_data.size; }
	size_t capacity() const noexcept { return m_data.capacity; }

	char const *data() const noexcept { return m_data.ptr; }
};
} // namespace dak_std

#endif