#include <dak_script/token.h>

#include <dak_script/token_module.h>
#include <iostream>
#include <unordered_map>

namespace dak_script
{

dak_std::string token_to_string(Token t, Token_Module *m)
{
	if (t.type == TOKEN_TYPE_TOKEN)
	{
		return token_value_to_name(t.value);
	}
	else if (t.type == TOKEN_TYPE_IDENTIFIER)
	{
		return m->get_identifier(t);
	}
	else if (t.type == TOKEN_TYPE_LITERAL)
	{
		return "literal";
	}
}

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
		case TOKEN_KEYWORD_FUNC:
			return "TOKEN_KEYWORD_FUNC";
		case TOKEN_KEYWORD_TYPE:
			return "TOKEN_KEYWORD_TYPE";
		case TOKEN_KEYWORD_UNINIT:
			return "TOKEN_KEYWORD_UNINIT";
		case TOKEN_KEYWORD_RETURN:
			return "TOKEN_KEYWORD_RETURN";
		case TOKEN_KEYWORD_NULL:
			return "TOKEN_KEYWORD_NULL";
		case TOKEN_KEYWORD_NULLPTR:
			return "TOKEN_KEYWORD_NULLPTR";
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
		case TOKEN_COLON:
			return ":";
		case TOKEN_EQUALS:
			return "=";

		case '-':
			return "-";
		case '+':
			return "+";
		case '/':
			return "/";
		case '*':
			return "*";

		case TOKEN_AMPERSAND:
			return "&";
		case TOKEN_BACKSLASH:
			return "\\";
		case TOKEN_DOT:
			return ".";
		case TOKEN_SEMICOLON:
			return ";";
		case TOKEN_QUOTE:
			return "\"";

		default:
			return "UNKNOWN_TOKEN";
	}
}
const char *token_type_to_name(Token_Type t)
{
	switch (t)
	{
		case TOKEN_TYPE_TOKEN:
			return "token";
		case TOKEN_TYPE_IDENTIFIER:
			return "identifier";
		case TOKEN_TYPE_LITERAL:
			return "literal";
		default:
			return "error";
	}
}

} // namespace dak_script