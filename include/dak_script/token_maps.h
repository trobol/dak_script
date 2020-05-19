#ifndef _DAK_SCRIPT_TOKEN_MAPS_H
#define _DAK_SCRIPT_TOKEN_MAPS_H

#include "string_map.h"
#include "token.h"

namespace dak::script
{
	constexpr const auto token_keyword_map = build_String_Map<Token_Type>(TOKEN_EMPTY, {{"struct", TOKEN_KEYWORD_STRUCT},
																						{"type", TOKEN_KEYWORD_TYPE},
																						{"if", TOKEN_KEYWORD_IF},
																						{"else", TOKEN_KEYWORD_ELSE},
																						{"defer", TOKEN_KEYWORD_DEFER},
																						{"func", TOKEN_KEYWORD_FUNC},
																						{"uninitialized", TOKEN_KEYWORD_UNINITIALIZED}});
}
#endif