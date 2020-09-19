#ifndef _DAK_STD_STRING_H
#define _DAK_STD_STRING_H

// TODO

// this is heavily based on https://github.com/elliotgoodrich/SSO-23
// add the licence

#include <ostream>

namespace dak_std
{

class string
{

private:
	union Data {
		struct NonSSO
		{
			char *ptr;
			std::size_t size;
			std::size_t capacity;
		} non_sso;
		struct SSO
		{
			char string[sizeof(NonSSO) / sizeof(char) - 1];
			uint8_t size;
		} sso;
	} m_data;

public:
	using traits = std::char_traits<char>;

	string() noexcept;

	string(const char *string, std::size_t size);
	string(char c, std::size_t size);

	string(const char *str);

	string(const string &str);

	string(string &&string) noexcept;

	string &operator=(string const &other);

	string &operator=(string &&other);

	~string();

	char const *data() const noexcept;

	std::size_t size() const noexcept;

	std::size_t capacity() const noexcept;

	std::size_t resize(std::size_t);

	friend void swap(string &lhs, string &rhs)
	{
		std::swap(lhs.m_data, rhs.m_data);
	}

private:
	void set_moved_from();

	// We are using sso if the last two bits are 0
	bool sso() const noexcept;

	// good
	void set_sso_size(unsigned char size) noexcept;
	// good
	std::size_t sso_size() const noexcept;

	void set_non_sso_data(std::size_t size, std::size_t capacity);

	std::pair<std::size_t, std::size_t> read_non_sso_data() const;

public:
	static std::size_t const sso_capacity =
	    sizeof(typename Data::NonSSO) / sizeof(char) - 1;
};

bool operator==(const string &lhs, const char *rhs) noexcept;
bool operator==(const char *lhs, const string &rhs) noexcept;
bool operator==(const string &lhs, const string &rhs) noexcept;

bool operator<(const string &lhs, const string &rhs) noexcept;
bool operator<(const char *lhs, const string &rhs) noexcept;
bool operator<(const string &lhs, const char *rhs) noexcept;

bool operator>(const string &lhs, const string &rhs) noexcept;
bool operator>(const char *lhs, const string &rhs) noexcept;
bool operator>(const string &lhs, const char *rhs) noexcept;

std::ostream &operator<<(std::ostream &stream, const string &string);

} // namespace dak_std

namespace std
{
template <>
struct hash<dak_std::string>
{
	std::size_t operator()(dak_std::string const &str) const noexcept
	{
		const unsigned A = 54059;
		const unsigned B = 76963;
		const unsigned FIRSTH = 37;
		unsigned h = FIRSTH;
		const char *c = str.data();
		while (*c)
		{
			h = (h * A) ^ (c[0] * B);
			c++;
		}
		return h;
	}
};

string to_string(unsigned int val);
} // namespace std

#endif