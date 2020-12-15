#ifndef _DAK_ASSERT_ASSERT_H
#define _DAK_ASSERT_ASSERT_H

#ifdef NDEBUG
#define _dak_assert(v)
#else
#include "debug_break.h"
#define _dak_assert(v)                                                         \
	if (!(v))                                                              \
		debug_break();
#endif

#endif