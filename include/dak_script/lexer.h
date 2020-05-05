#ifndef _DAK_SCRIPT_LEXER_H
#define _DAK_SCRIPT_LEXER_H

#include <vector>
#include "token.h"

namespace dak::script
{
class Parser;

class Lexer
{
private:
	const char *m_data;
	uint32_t m_size;
	uint32_t m_index;

	uint32_t m_line_number;
	uint32_t m_character_number;

	Token parse_identifier();
	Token parse_slash();

	Token next();

	char peek_char();
	void pop_char();

	Token make(Token_Type type);

public:
	Lexer(const char *data, size_t size) : m_data{data}, m_size{size}, m_index{0} {};

	std::vector<Token> lex();
};
} // namespace dak::script

#endif