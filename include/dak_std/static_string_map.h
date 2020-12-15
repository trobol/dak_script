#ifndef _DAK_STD_STRING_MAP
#define _DAK_STD_STRING_MAP

#include <cstring>
#include <functional>
#include <utility>
#include <vector>

#include "string_utils.h"

namespace dak_std
{
template <typename Value, std::size_t N = 0>
class Static_String_Map
{
public:
	using pair_type = std::pair<const char *, Value>;
	using key_type = const char *;

private:
	const char *m_data[N];
	Value m_tokens[N];
	const size_t m_min_str_size;
	const size_t m_max_str_size;
	const Value m_default;

	template <std::size_t... I>
	constexpr Static_String_Map(const Value default_value,
				    const pair_type (&data)[N],
				    std::index_sequence<I...>)
	    : m_data{data[I].first...}, m_tokens{data[I].second...},
	      m_min_str_size{min_str_len<N>(m_data)},
	      m_max_str_size{max_str_len<N>(m_data)}, m_default{default_value}
	{

		for (size_t left = 0, right = N - 1; right > 0;
		     right = left, left = 0)
		{
			for (size_t i = 0; i < right; ++i)
			{
				if (str_less(m_data[i + 1], m_data[i]))
				{
					Value tmp_val = m_tokens[i];
					m_tokens[i] = m_tokens[i + 1];
					m_tokens[i + 1] = tmp_val;

					const char *tmp_str = m_data[i];
					m_data[i] = m_data[i + 1];
					m_data[i + 1] = tmp_str;
					left = i;
				}
			}
		}
	}

public:
	constexpr Static_String_Map(const Value default_value,
				    const pair_type (&data)[N]) noexcept
	    : Static_String_Map(default_value, data,
				std::make_index_sequence<N>())
	{
	}
	Value find_substr(const char *str, size_t length) const noexcept
	{
		char buffer[m_max_str_size + 1] = {};
		if (length > m_max_str_size)
		{
			return m_default;
		}
		buffer[m_max_str_size + 1] = 0;
		memcpy((void *)buffer, (void *)str, length);

		return find(buffer);
	}
	Value find(const char *str) const noexcept
	{
		int l = 0;
		int r = N - 1;
		while (l <= r)
		{
			int m = l + (r - l) / 2;

			const char *lhs = m_data[m];
			const char *rhs = str;
			while (*lhs && *rhs && *lhs == *rhs)
			{
				++lhs;
				++rhs;
			}
			if (*lhs < *rhs)
				l = m + 1;
			else if (*lhs == *rhs)
				return m_tokens[m];
			else
				r = m - 1;
		}
		return m_default;
	}

	constexpr const size_t smallest_str_len() const noexcept
	{
		return m_min_str_size;
	}

	constexpr const char *const *get_data() const noexcept
	{
		return m_data;
	}

	constexpr std::size_t size() const noexcept { return N; }
};

template <typename Value, std::size_t N>
static constexpr auto Build_Static_String_Map(
    const Value default_value,
    const std::pair<const char *, Value> (&data)[N]) noexcept
{
	return Static_String_Map<Value, N>(default_value, data);
}

} // namespace dak_std

#endif