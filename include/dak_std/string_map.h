#ifndef _DAK_STD_STRING_MAP_H
#define _DAK_STD_STRING_MAP_H

#include <dak_std/vector.h>

namespace dak_std
{
template <typename Value>
class binary_string_tree
{
public:
	struct node
	{
		Value value;
		int right;
		int left;
	};

private:
};
} // namespace dak_std

#endif