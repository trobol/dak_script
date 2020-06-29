#ifndef _DAK_SCRIPT_TOKEN_MAPS_H
#define _DAK_SCRIPT_TOKEN_MAPS_H

#include "token.h"
#include <dak_std/static_string_map.h>

namespace dak_script
{
constexpr const auto token_keyword_map =
    dak_std::Build_Static_String_Map<Token_Value>(
	TOKEN_EMPTY, {{"struct", TOKEN_KEYWORD_STRUCT},
		      {"type", TOKEN_KEYWORD_TYPE},
		      {"if", TOKEN_KEYWORD_IF},
		      {"else", TOKEN_KEYWORD_ELSE},
		      {"defer", TOKEN_KEYWORD_DEFER},
		      {"function", TOKEN_KEYWORD_FUNCTION},
		      {"uninitialized", TOKEN_KEYWORD_UNINITIALIZED}});
}
#endif