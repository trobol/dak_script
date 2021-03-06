#ifndef _DAK_STD_LINEAR_ALLOCATOR_H
#define _DAK_STD_LINEAR_ALLOCATOR_H

namespace dak_std
{

class linear_allocator
{
private:
	// where the next object will be allocated (if it fits)
	char *m_page_head;
	// the end of the current page
	char *m_page_tail;

	struct page
	{
		char *data;
		page *last;
	};

	// linked list to clean up pages
	// this is instead of a vector because hopefully the cache of context
	// that uses this class will be preserved
	page *m_page_list_tail;
	const size_t m_page_size;

public:
	linear_allocator(const size_t page_size)
	    : m_page_size{page_size}, m_page_list_tail{nullptr},
	      m_page_head{nullptr}, m_page_tail{m_page_head}
	{
	}

	~linear_allocator()
	{
		page *current = m_page_list_tail;

		while (current != nullptr)
		{
			page *p = current->last;

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
		constexpr const size_t type_size = sizeof(T);
		if ((size_t(m_page_tail) - size_t(m_page_head)) < type_size)
		{
			add_page();
		}

		void *old_head = m_page_head;

		m_page_head += type_size;
		return new (old_head) T(args...);
	}

private:
	void add_page()
	{
		char *data = (char *)::operator new(m_page_size);

		page *new_page = new page{data, m_page_list_tail};
		m_page_list_tail = new_page;

		m_page_head = data;
		m_page_tail = data + m_page_size;
	}
};
} // namespace dak_std

#endif