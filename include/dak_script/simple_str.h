#ifndef _DAK_SCRIPT_SIMPLE_STR_H
#define _DAK_SCRIPT_SIMPLE_STR_H

#include <cstdint>

namespace dak
{
class simple_str
{
private:
	char *m_ptr;
	uint64_t m_size : 63; // small string 7 - size
	bool m_is_large : 1;

public:
	static simple_str from(char const *start, uint64_t size);
};

/*
64bit
sizeof ptr = 4 bytes
sizeof size = 4 bytes

7 + null

32bit
sizeof ptr = 2 bytes
sizeof size = 2 bytes
*/

} // namespace dak

#endif