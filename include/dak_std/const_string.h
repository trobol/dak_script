#ifndef _DAK_STD_CONST_STRING_H
#define _DAK_STD_CONST_STRING_H

namespace dak_std {
class const_string {
private:
	const char *m_ptr;
	uint32_t m_size;

public:
	uint32_t size();
	const_string(uint32_t size);
	constexpr const_string(const char *c_str);
}
} // namespace dak_std

#endif