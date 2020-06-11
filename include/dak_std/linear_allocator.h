#ifndef _DAK_STD_LINEAR_ALLOCATOR_H
#define _DAK_STD_LINEAR_ALLOCATOR_H
#include <vector>

namespace dak_std
{

class linear_allocator
{
private:
	// where the next object will be allocated (if it fits)
	void *m_page_head;
	// the end of the current page
	void *m_page_tail;

	struct page
	{
		void *data;
		page *last;
	};

	// linked list to clean up pages
	// this is instead of a vector because hopefully the cache of context
	// that uses this class will be preserved
	page *m_page_list_tail;
	const size_t m_page_size;

public:
	linear_allocator(const size_t page_size)
	    : m_page_size{page_size}, m_page_list_tail{nullptr}
	{
		add_page();
	}

	~linear_allocator()
	{
		page *current = m_page_list_tail;

		while (current != nullptr)
		{
			page *p = m_page_list_tail->last;

			delete[] current->data;
			delete current;

			current = p;
		}

		m_page_list_tail = nullptr;
		m_page_head = nullptr;
		m_page_tail = nullptr;
	}

	template <typename T, typename... Args>
	T *allocate(Args... args)
	{
		constexpr const type_size = sizeof(T);
		if (m_page_tail - m_page_head < type_size)
		{
			add_page();
		}

		void *old_head = m_page_head;

		m_page_head += type_size;
		return new old_head T(args...);
	}

private:
	void add_page()
	{
		void *data = ::operator new(m_page_size);

		page *new_page = new page{data, m_page_list_tail};
		m_page_list_tail = new_page;

		m_page_head = data;
		m_page_tail = data + m_page_size;
	}
};
} // namespace dak_std

#endif