#ifndef _DAK_STD_LINKED_QUEUE_H
#define _DAK_STD_LINKED_QUEUE_H

namespace dak_std
{
template <typename T>
class linked_queue
{
private:
	struct pair
	{
		pair *next;
		T value;
	};
	pair *head;
	pair *tail;

public:
	void enqueue(T &v)
	{
		pair *p = new pair(tail, v);
		if (tail == nullptr)
			head = p;
		tail = p;
	}
	void dequeue()
	{

		if (head == nullptr)
			return;
		pair *p = head;
		head = head->next;
		delete p;
	}

	// T &operator[](size_t index) const { return m_front[index]; }

	T &front() const { return head->value; }
	T &back() const { return tail->value; }
};
} // namespace dak_std

#endif