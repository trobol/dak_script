#ifndef _DAK_STD_VECTOR_H
#define _DAK_STD_VECTOR_H

#include "assert.h"
#include <cstdlib>
#include <type_traits>

namespace dak_std
{

// lacking some optimizations but with fewer function calls
template <typename T>
class vector
{
private:
	T *m_begin;
	T *m_end;
	T *m_capacity;

public:
	vector() : m_begin{nullptr}, m_end{nullptr}, m_capacity{nullptr} {}
	~vector()
	{
		std::free(m_begin);
		m_begin = nullptr;
		m_end = nullptr;
		m_capacity = nullptr;
	}

	vector(vector &&v)
	{
		m_begin = v.m_begin;
		m_end = v.m_end;
		m_capacity = v.m_capacity;

		v.m_begin = nullptr;
		v.m_end = nullptr;
		v.m_capacity = nullptr;
	}

	vector(std::initializer_list<T> list)
	{
		T *begin = list.begin();
		T *end = list.end();
		size_t size = list.size();

		if (begin != end)
		{
			m_begin = (T *)std::malloc(size);
			m_end = m_begin + size;
			m_capacity = m_end;
			if constexpr (std::is_trivially_copyable_v<T>)
			{
				std::memcpy(m_begin, begin, size);
			}
			else
			{
				for (T *dst = m_begin, src = begin; src != end;
				     ++src, ++dst)
				{
					new (dst) T(*src);
				}
			}
		}
	}

	void push_back(const T &value)
	{
		if (m_end == m_capacity)
		{
			size_t capacity = m_capacity - m_begin;
			size_t new_capacity;
			if (capacity == 0)
			{
				new_capacity =
				    std::max(64 / sizeof(T), size_t(1));
			}
			else
			{
				new_capacity = capacity * 2;
			}
			reserve(new_capacity);
		}

		new (m_end) T(value);
		++m_end;
	}
	void push_back(T &&value)
	{
		if (m_end == m_capacity)
		{
			size_t capacity = m_capacity - m_begin;
			size_t new_capacity;
			if (capacity == 0)
			{
				new_capacity =
				    std::max(64 / sizeof(T), size_t(1));
			}
			else
			{
				new_capacity = capacity * 2;
			}
			reserve(new_capacity);
		}

		new (m_end) T(value);
		++m_end;
	}

	void reserve(size_t size)
	{
		T *new_begin;
		if constexpr (std::is_trivially_copyable_v<T>)
		{
			new_begin = (T *)std::realloc((void *)m_begin,
						      size * sizeof(T));
			_dak_assert(new_begin);
		}
		else
		{
			new_begin = (T *)std::malloc(size * sizeof(T));
			for (T *src = m_begin, dst = new_begin; src != m_end;
			     ++src, ++dst)
			{
				if constexpr (std::is_scalar_v<T>)
				{
					*dst = src;
				}
				else if (std::is_move_constructible_v<T>)
				{
					new (dst) T(std::move(*src));
				}
				else
				{
					new (dst) T(*src);
				}
			}

			std::free(m_begin);
		}

		m_end = new_begin + this->size();
		m_begin = new_begin;
		m_capacity = new_begin + size;
	}

	T &operator[](size_t i)
	{
		_dak_assert(i + m_begin >= m_end);
		return m_begin[i];
	}

	size_t capacity() const noexcept
	{
		return size_t(m_capacity - m_begin);
	}

	size_t size() const noexcept { return size_t(m_end - m_begin); }

	const T *begin() const noexcept { return m_begin; }
	const T *end() const noexcept { return m_end; }
	T *begin() noexcept { return m_begin; }
	T *end() noexcept { return m_end; }
};
} // namespace dak_std

#endif