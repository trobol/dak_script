#ifndef _DAK_SCRIPT_TOKEN_H
#define _DAK_SCRIPT_TOKEN_H

#include <cstdint>
#include <dak_std/string.h>
#include <unordered_map>
#include <vector>

class File;

namespace dak_script
{

enum Token_Value : uint32_t
{
	TOKEN_EOF = 0,
	TOKEN_AT = '@',
	TOKEN_OPEN_BRACKET = '{',
	TOKEN_CLOSE_BRACKET = '}',

	TOKEN_OPEN_BRACE = '[',
	TOKEN_CLOSE_BRACE = ']',

	TOKEN_OPEN_PAREN = '(',
	TOKEN_CLOSE_PAREN = ')',

	TOKEN_COMMA = ',',
	TOKEN_DOT = '.',

	TOKEN_ASTERISK = '*',
	TOKEN_AMPERSAND = '&',
	TOKEN_PLUS = '+',
	TOKEN_MINUS = '-',

	TOKEN_COLON = ':',
	TOKEN_EQUALS = '=',
	TOKEN_SLASH = '/',
	TOKEN_BACKSLASH = '\\',
	TOKEN_SEMICOLON = ';',
	TOKEN_BREAK = '\n',
	TOKEN_QUOTE = '"',

	TOKEN_INDENT = 256,
	TOKEN_EMPTY,
	TOKEN_NUMBER,
	TOKEN_STRING,

	TOKEN_PLUSEQUALS,
	TOKEN_MINUSEQUALS,

	TOKEN_KEYWORD_IF,
	TOKEN_KEYWORD_ELSE,
	TOKEN_KEYWORD_THEN,
	TOKEN_KEYWORD_DEFER,
	TOKEN_KEYWORD_STRUCT,
	TOKEN_KEYWORD_TYPE,
	TOKEN_KEYWORD_UNINIT,
	TOKEN_KEYWORD_FUNC,
	TOKEN_KEYWORD_RETURN,
	TOKEN_KEYWORD_NULL,
	TOKEN_KEYWORD_NULLPTR,

	TOKEN_KEYWORD_TRUE,
	TOKEN_KEYWORD_FALSE,

	TOKEN_ERROR,

};

enum Token_Type
{
	TOKEN_TYPE_IDENTIFIER = 0,
	TOKEN_TYPE_LITERAL = 1,
	TOKEN_TYPE_TOKEN = 2
};

struct Token
{
	Token_Type type : 2;
	union {
		Token_Value value;
		uint64_t index;
	};

	bool operator==(const Token_Value val)
	{
		return type == TOKEN_TYPE_TOKEN && value == val;
	}
	bool operator!=(const Token_Value val)
	{
		return type != TOKEN_TYPE_TOKEN || value != val;
	}
};

enum Token_Literal_Type
{
	LITERAL_TYPE_FLOAT,
	LITERAL_TYPE_UINT,
	LITERAL_TYPE_STRING,
	LITERAL_TYPE_CHAR
};

struct Token_Literal
{
	Token_Literal_Type type;
	union {
		char char_val;
		char *string_val;
		unsigned long uint_val;
		double float_val;
	};
};

struct Token_Pos
{
	uint32_t line_number;
	uint32_t character_number;
};

const char *token_value_to_name(Token_Value t);

const char *token_type_to_name(Token_Type t);

class Token_Module;
dak_std::string token_to_string(Token t, Token_Module *m);

struct Token_Value_Hash
{
	size_t operator()(Token_Value const &s) const noexcept { return s; }
};

} // namespace dak_script

#endif