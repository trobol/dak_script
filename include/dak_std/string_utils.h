#ifndef _DAK_STD_STRING_UTILS
#define _DAK_STD_STRING_UTILS

namespace dak_std
{

inline constexpr bool str_less(const char *lhs, const char *rhs) noexcept
{
	while (*lhs && *rhs && *lhs == *rhs)
	{
		++lhs;
		++rhs;
	}
	return *lhs < *rhs;
}

inline constexpr bool str_greater(const char *lhs, const char *rhs) noexcept
{
	while (*lhs && *rhs && *lhs == *rhs)
	{
		++lhs;
		++rhs;
	}
	return *lhs > *rhs;
}

inline constexpr bool str_equal(const char *lhs, const char *rhs) noexcept
{
	while (*lhs && *rhs && *lhs == *rhs)
	{
		++lhs;
		++rhs;
	}
	return *lhs == *rhs;
}

template <std::size_t N>
constexpr const size_t min_str_len(const char *(&data)[N])
{
	std::size_t s = 0xffffffff;
	for (size_t i = 0; i < N; i++)
	{
		const char *str = data[i];
		size_t j = 0;
		while (str[j] != 0 && j < s)
		{
			j++;
		}
		if (j < s)
		{
			s = j;
		}
	}
	return s;
}

template <std::size_t N>
constexpr const size_t max_str_len(const char *(&data)[N])
{
	std::size_t s = 0;
	for (size_t i = 0; i < N; i++)
	{
		const char *str = data[i];
		size_t j = 0;
		while (str[j])
		{
			j++;
		}
		if (j > s)
		{
			s = j;
		}
	}
	return s;
}

} // namespace dak_std

#endif