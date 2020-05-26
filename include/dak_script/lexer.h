#ifndef _DAK_SCRIPT_LEXER_H
#define _DAK_SCRIPT_LEXER_H

#include "token.h"
#include <vector>

namespace dak_script
{
class Lexer
{
protected:
	struct substr
	{
		const char *start;
		uint32_t size;
	};

private:
	const char *m_data;
	uint32_t m_size;
	uint32_t m_index;

	uint32_t m_line_number;
	uint32_t m_character_number;

	std::vector<substr> m_identifiers;
	std::vector<Token_Literal> m_literals;

	std::vector<Token> m_tokens;

	std::vector<Token_Pos> m_positions;

	Token parse_identifier();
	Token parse_slash();
	Token parse_string_literal();
	Token parse_char_literal();
	Token parse_num_literal();

	Token parse_hex_literal();
	Token parse_binary_literal();
	Token parse_decimal_literal();

	Token make_error();

	Token make_literal(char);
	Token make_literal(const char *);
	Token make_literal(double);
	Token make_literal(long long int);

	Token next();

	char peek_char();
	char peek_char(uint32_t);

	void pop_char();
	void pop_char(uint32_t);

	void break_line();

	Token make_token(Token_Value);
	Token make_identifier(const char *, uint32_t);

public:
	Lexer(const char *data, size_t size);

	Token_Module lex();
};
} // namespace dak_script

#endif