#ifndef _DAK_SCRIPT_STRING_UTILS
#define _DAK_SCRIPT_STRING_UTILS

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

inline constexpr bool substr_less(const char *lhs, const char *rhs, const char* end) noexcept
{
	while (*lhs && rhs < end && *lhs == *rhs)
	{
		++lhs;
		++rhs;
	}
	return *lhs < *rhs;
}

inline constexpr bool substr_greater(const char *lhs, const char *rhs, const char* end) noexcept
{
	while (*lhs && rhs < end && *lhs == *rhs)
	{
		++lhs;
		++rhs;
	}
	return *lhs > *rhs;
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

#endif