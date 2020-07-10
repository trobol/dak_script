#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstring>
#include <dak_std/string.h>

namespace dak_std
{

static std::size_t const high_bit_mask =
    static_cast<std::size_t>(1) << (sizeof(std::size_t) * CHAR_BIT - 1);
static std::size_t const sec_high_bit_mask =
    static_cast<std::size_t>(1) << (sizeof(std::size_t) * CHAR_BIT - 2);

template <typename T>
unsigned char *uchar_cast(T *p)
{
	return reinterpret_cast<unsigned char *>(p);
}

template <typename T>
unsigned char const *uchar_cast(T const *p)
{
	return reinterpret_cast<unsigned char const *>(p);
}

template <typename T>
unsigned char &most_sig_byte(T &obj)
{
	return *(reinterpret_cast<unsigned char *>(&obj) + sizeof(obj) - 1);
}

template <int N>
bool lsb(unsigned char byte)
{
	return byte & (1u << N);
}

template <int N>
bool msb(unsigned char byte)
{
	return byte & (1u << (CHAR_BIT - N - 1));
}

template <int N>
void set_lsb(unsigned char &byte, bool bit)
{
	if (bit)
	{
		byte |= 1u << N;
	}
	else
	{
		byte &= ~(1u << N);
	}
}

template <int N>
void set_msb(unsigned char &byte, bool bit)
{
	if (bit)
	{
		byte |= 1u << (CHAR_BIT - N - 1);
	}
	else
	{
		byte &= ~(1u << (CHAR_BIT - N - 1));
	}
}

string::string() noexcept : string{"", static_cast<std::size_t>(0)} {}

string::string(char const *str, std::size_t size)
{
	if (size <= sso_capacity)
	{
		strncpy(m_data.sso.string, str, size);
		m_data.sso.string[size] = 0;
		set_sso_size(size);
	}
	else
	{
		m_data.non_sso.ptr = new char[size + 1];
		strncpy(m_data.non_sso.ptr, str, size);
		m_data.non_sso.ptr[size] = 0;
		set_non_sso_data(size, size);
	}
}

string::string(char const *str) : string{str, strlen(str)} {}

string::string(const string &str)
{
	if (str.sso())
	{
		m_data.sso = str.m_data.sso;
	}
	else
	{
		new (this) string{str.data(), str.size()};
	}
}

string::string(string &&string) noexcept
{
	m_data = string.m_data;
	string.set_moved_from();
}

string &string::operator=(string const &other)
{
	auto copy = other;
	swap(copy, *this);
	return *this;
}

string &string::operator=(string &&other)
{
	this->~string();
	m_data = other.m_data;
	other.set_moved_from();
	return *this;
}

string::~string()
{
	if (!sso())
	{
		delete[] m_data.non_sso.ptr;
	}
}

char const *string::data() const noexcept
{
	return sso() ? m_data.sso.string : m_data.non_sso.ptr;
}

std::size_t string::size() const noexcept
{
	if (sso())
	{
		return sso_size();
	}
	else
	{
		return read_non_sso_data().first;
	}
}

std::size_t string::capacity() const noexcept
{
	if (sso())
	{
		return sizeof(m_data) - 1;
	}
	else
	{
		return read_non_sso_data().second;
	}
}

void string::set_moved_from() { set_sso_size(0); }

// We are using sso if the last two bits are 0
bool string::sso() const noexcept
{
	return !lsb<0>(m_data.sso.size) && !lsb<1>(m_data.sso.size);
}

// good
void string::set_sso_size(unsigned char size) noexcept
{
	m_data.sso.size = static_cast<uint8_t>(sso_capacity - size) << 2;
}

// good
std::size_t string::sso_size() const noexcept
{
	return sso_capacity - ((m_data.sso.size >> 2) & 63u);
}

void string::set_non_sso_data(std::size_t size, std::size_t capacity)
{
	auto &size_hsb = most_sig_byte(size);
	auto const size_high_bit = msb<0>(size_hsb);

	auto &cap_hsb = most_sig_byte(capacity);
	auto const cap_high_bit = msb<0>(cap_hsb);
	auto const cap_sec_high_bit = msb<1>(cap_hsb);

	set_msb<0>(size_hsb, cap_sec_high_bit);

	cap_hsb <<= 2;
	set_lsb<0>(cap_hsb, cap_high_bit);
	set_lsb<1>(cap_hsb, !size_high_bit);

	m_data.non_sso.size = size;
	m_data.non_sso.capacity = capacity;
}

std::pair<std::size_t, std::size_t> string::read_non_sso_data() const
{
	auto size = m_data.non_sso.size;
	auto capacity = m_data.non_sso.capacity;

	auto &size_hsb = most_sig_byte(size);
	auto &cap_hsb = most_sig_byte(capacity);

	// Remember to negate the high bits
	auto const cap_high_bit = lsb<0>(cap_hsb);
	auto const size_high_bit = !lsb<1>(cap_hsb);
	auto const cap_sec_high_bit = msb<0>(size_hsb);

	set_msb<0>(size_hsb, size_high_bit);

	cap_hsb >>= 2;
	set_msb<0>(cap_hsb, cap_high_bit);
	set_msb<1>(cap_hsb, cap_sec_high_bit);

	return std::make_pair(size, capacity);
}

bool operator==(const string &lhs, const char *rhs) noexcept
{
	return !std::strcmp(lhs.data(), rhs);
}

bool operator==(const char *lhs, const string &rhs) noexcept
{
	return rhs == lhs;
}

bool operator==(const string &lhs, const string &rhs) noexcept
{
	if (lhs.size() != rhs.size())
		return false;
	return !std::strcmp(lhs.data(), rhs.data());
}

std::ostream &operator<<(std::ostream &stream, const string &string)
{
	return stream << string.data();
}

} // namespace dak_std
