#ifndef _DAK_STD_ERROR_H
#define _DAK_STD_ERROR_H

namespace dak_std
{

class error
{
private:
	int m_error_num;

	error(int num) : m_error_num{num} {}

public:
	error() : m_error_num{0} {}
	bool operator==(int err) { return m_error_num == err; }
	bool operator!=(int err) { return m_error_num != err; }

	operator bool() { return m_error_num == 0; }

	char *str();
	int value() { return m_error_num; }

	friend error make_error();
};

error make_error();

} // namespace dak_std

#endif