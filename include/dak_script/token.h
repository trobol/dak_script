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
	TOKEN_OPEN_BRACKET = '{',
	TOKEN_CLOSE_BRACKET = '}',

	TOKEN_OPEN_BRACE = '[',
	TOKEN_CLOSE_BRACE = ']',

	TOKEN_OPEN_PAREN = '(',
	TOKEN_CLOSE_PAREN = ')',

	TOKEN_COMMA = ',',

	TOKEN_ASTERISK = '*',
	TOKEN_AMPERSAND = '&',

	TOKEN_COLON = ':',
	TOKEN_EQUALS = '=',
	TOKEN_SLASH = '/',
	TOKEN_BACKSLASH = '\\',
	TOKEN_SEMICOLON = ';',
	TOKEN_LINE_FEED = '\n',
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
	TOKEN_KEYWORD_UNINITIALIZED,
	TOKEN_KEYWORD_FUNC,
	TOKEN_BREAK,

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
};

enum Token_Literal_Type
{
	LITERAL_TYPE_FLOAT,
	LITERAL_TYPE_INT,
	LITERAL_TYPE_STRING,
	LITERAL_TYPE_CHAR
};

struct Token_Literal
{
	Token_Literal_Type type;
	union {
		char char_val;
		char *string_val;
		long long int int_val;
		double float_val;
	};
};

struct Token_Pos
{
	uint32_t line_number;
	uint32_t character_number;
};

const char *token_value_to_name(Token_Value t);

extern const std::unordered_map<Token_Value, const char *> keyword_map;

} // namespace dak_script

#endif