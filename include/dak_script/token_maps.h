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
		      {"func", TOKEN_KEYWORD_FUNC},
		      {"uninit", TOKEN_KEYWORD_UNINIT},
		      {"return", TOKEN_KEYWORD_RETURN},
		      {"nullptr", TOKEN_KEYWORD_NULLPTR},
		      {"null", TOKEN_KEYWORD_NULL}});
}
#endif