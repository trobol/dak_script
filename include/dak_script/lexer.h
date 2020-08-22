#ifndef _DAK_SCRIPT_LEXER_H
#define _DAK_SCRIPT_LEXER_H

#include <dak_script/token_module.h>
#include <dak_std/string.h>
#include <dak_std/vector.h>
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
	size_t m_size;
	size_t m_index;

	uint32_t m_line_number;
	uint32_t m_character_number;

	dak_std::vector<dak_std::string> m_identifiers;
	dak_std::vector<Token_Literal> m_literals;

	std::unordered_map<dak_std::string, uint32_t> m_symbol_map;
	dak_std::vector<dak_std::string> m_symbol_table;

	dak_std::vector<dak_std::string> m_string_literals;

	dak_std::vector<Token> m_tokens;

	dak_std::vector<Token_Pos> m_positions;

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
	Token make_literal(double);
	Token make_literal(long long int);
	Token make_literal(char *);

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