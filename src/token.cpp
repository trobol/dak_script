#include <dak_script/token.h>

#include <iostream>
#include <unordered_map>

namespace dak_script
{

const char *token_value_to_name(Token_Value t)
{
	switch (t)
	{
		case TOKEN_INDENT:
			return "TOKEN_INDENT";
		case TOKEN_EMPTY:
			return "TOKEN_EMPTY";
		case TOKEN_NUMBER:
			return "TOKEN_NUMBER";
		case TOKEN_STRING:
			return "TOKEN_STRING";
		case TOKEN_PLUSEQUALS:
			return "TOKEN_PLUSEQUALS";
		case TOKEN_MINUSEQUALS:
			return "TOKEN_MINUSEQUALS";
		case TOKEN_KEYWORD_IF:
			return "TOKEN_KEYWORD_IF";
		case TOKEN_KEYWORD_ELSE:
			return "TOKEN_KEYWORD_ELSE";
		case TOKEN_KEYWORD_THEN:
			return "TOKEN_KEYWORD_THEN";
		case TOKEN_KEYWORD_DEFER:
			return "TOKEN_KEYWORD_DEFER";
		case TOKEN_KEYWORD_STRUCT:
			return "TOKEN_KEWORD_STRUCT";
		case TOKEN_KEYWORD_FUNCTION:
			return "TOKEN_KEYWORD_FUNC";
		case TOKEN_KEYWORD_TYPE:
			return "TOKEN_KEYWORD_TYPE";
		case TOKEN_KEYWORD_UNINITIALIZED:
			return "TOKEN_KEYWORD_UNINITIALIZED";
		case TOKEN_BREAK:
			return "TOKEN_BREAK";
		case TOKEN_ERROR:
			return "TOKEN_ERROR";
		case TOKEN_EOF:
			return "TOKEN_EOF";
		case TOKEN_AT:
			return "@";
		case TOKEN_OPEN_BRACKET:
			return "{";

		case TOKEN_CLOSE_BRACKET:
			return "}";
		case TOKEN_OPEN_BRACE:
			return "[";
		case TOKEN_CLOSE_BRACE:
			return "]";
		case TOKEN_OPEN_PAREN:
			return "(";
		case TOKEN_CLOSE_PAREN:
			return ")";
		case TOKEN_COMMA:
			return ",";
		case TOKEN_ASTERISK:
			return "*";
		case TOKEN_COLON:
			return ":";
		case TOKEN_EQUALS:
			return "=";
		case TOKEN_SLASH:
			return "/";
		case TOKEN_AMPERSAND:
			return "&";
		case TOKEN_LINE_FEED:
			return "LINE FEED";
		case TOKEN_BACKSLASH:
			return "\\";
		case TOKEN_SEMICOLON:
			return ";";
		case TOKEN_QUOTE:
			return "\"";

		default:
			return "UNKNOWN_TOKEN";
	} // namespace dak_script
} // namespace dak_script

} // namespace dak_script