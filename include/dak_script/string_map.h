#ifndef _DAK_SCRIPT_STRING_MAP
#define _DAK_SCRIPT_STRING_MAP

#include <vector>
#include <utility>
#include <functional>
#include <cstring>

#include "string_utils.h"

template <typename Value, std::size_t N>
class String_Map
{
public:
	using pair_type = std::pair<const char *, Value>;
	using key_type = const char *;

private:
	const char *m_data[N];
	Value m_tokens[N];
	const size_t m_min_str_size;
	const Value m_default;

	template <std::size_t... I>
	constexpr String_Map(const Value default_value, const pair_type (&data)[N], std::index_sequence<I...>)
		: m_data{data[I].first...},
		  m_tokens{data[I].second...},
		  m_min_str_size{min_str_len<N>(m_data)},
		  m_default{default_value}
	{

		for (size_t left = 0, right = N - 1; right > 0; right = left, left = 0)
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
	constexpr String_Map(const Value default_value, const pair_type (&data)[N]) noexcept : String_Map(default_value, data, std::make_index_sequence<N>())
	{
	}
	Value find_substr(const char *str, const char *end) const noexcept
	{
		int l = 0;
		int r = N - 1;
		while (l <= r)
		{
			int m = l + (r - l) / 2;

			if (substr_less(m_data[m], str, end))
				l = m + 1;
			else if (!substr_greater(m_data[m], str, end))
				return m_tokens[m];
			else
				r = m - 1;
		}
		return m_default;
	}
	Value find(const char *str) const noexcept
	{
		int l = 0;
		int r = N - 1;
		while (l <= r)
		{
			int m = l + (r - l) / 2;

			if (str_less(m_data[m], str))
				l = m + 1;
			else if (!str_greater(m_data[m], str))
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

	constexpr std::size_t size() const noexcept
	{
		return N;
	}
};

template <typename Value, std::size_t N>
static constexpr auto build_String_Map(const Value default_value, const std::pair<const char *, Value> (&data)[N]) noexcept
{
	return String_Map<Value, N>(default_value, data);
}

#endif