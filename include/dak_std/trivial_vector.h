#ifndef _DAK_STD_trivial_VECTOR_H
#define _DAK_STD_trivial_VECTOR_H

/*
A vector that will only accept pod types
*/
#include "type_assert.h"

namespace dak_std
{
template <typename T>
class trivial_vector
{
	trivial_vector() { static_assert_trivial(T); }
	trivial_vector(unsigned int size) {}

	void push_back(const T &val)
	{
		if (m_end >= m_data_end)
		{
		}

		*m_end = val;
	}
	void detach_data()
	{
		m_start = nullptr;
		m_finish = nullptr;
		m_data_end = nullptr;
	}

	T *data() { return m_start; }
	T *begin() { return m_start; }
	T *end() { return m_end; }

	void reserve(unsigned int size)
	{
		_dak_assert(size > 0);
		void *new_data = realloc(m_start, size);
		assert(new_data);
		if (new_data != m_start)
		{
			m_end = new_data + (m_end - m_start);
			m_data_end = new_data + size;
		}
		m_start = new_data;
	}

	void resize(unsigned int size)
	{
		reserve(size);
		m_end = m_data_end;
	}
	void clear() { m_end = m_start; }

private:
	T *m_start;
	T *m_end;
	T *m_data_end;
}
} // namespace dak_std

#endif