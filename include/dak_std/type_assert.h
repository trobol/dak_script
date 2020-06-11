#ifndef _DAK_STD_TYPE_ASSERT_H
#define _DAL_STD_TYPE_ASSERT_H

#include <type_traits>

#define static_assert_trivial(T)                                               \
	static_assert(std::is_trivial::value, "type must be trivial")

#endif