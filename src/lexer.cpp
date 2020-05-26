#include <dak_script/character_traits.h>
#include <dak_script/character_type.h>
#include <dak_script/lexer.h>
#include <dak_script/token.h>
#include <dak_script/token_maps.h>
#include <dak_std/string.h>
#include <iostream>

namespace dak_script
{

Token Lexer::make_token(Token_Value t) { return Token{TOKEN_TYPE_TOKEN, t}; }

Token Lexer::make_identifier(const char *start, uint32_t size)
{
	m_identifiers.push_back({start, size});
	return Token{TOKEN_TYPE_IDENTIFIER,
		     .index = (m_identifiers.size() - 1)};
}

Token Lexer::make_error() { return Token{TOKEN_TYPE_TOKEN, TOKEN_ERROR}; }

Token Lexer::make_literal(double f)
{
	m_literals.push_back(
	    Token_Literal{LITERAL_TYPE_FLOAT, .float_val = (f)});
	return Token{TOKEN_TYPE_LITERAL, .index = (m_literals.size() - 1)};
}

Token Lexer::make_literal(long long int i)
{
	m_literals.push_back(Token_Literal{LITERAL_TYPE_INT, .int_val = (i)});
	return Token{TOKEN_TYPE_LITERAL, .index = (m_literals.size() - 1)};
}
Lexer::Lexer(const char *data, size_t size)
    : m_data{data}, m_size{size}, m_index{0}, m_character_number{0},
      m_line_number{0} {};

char Lexer::peek_char()
{
	if (m_index >= m_size)
	{
		return 0;
	}
	// std::cout << m_data[m_index];
	return m_data[m_index];
}
char Lexer::peek_char(uint32_t i)
{
	size_t index = m_index + i;
	if (index >= m_size)
	{
		return 0;
	}
	return m_data[index];
}

void Lexer::pop_char()
{
	++m_character_number;
	++m_index;
}
void Lexer::pop_char(uint32_t i)
{
	m_character_number += i;
	m_index += i;
}

Token_Module Lexer::lex()
{
	Token token;

	do
	{
		token = next();
		m_tokens.push_back(token);
		m_positions.push_back(
		    Token_Pos{m_line_number, m_character_number});
	} while (token.type != TOKEN_TYPE_TOKEN || token.value != TOKEN_EOF);

	uint32_t buffer_size = 0;
	for (substr &s : m_identifiers)
	{
		buffer_size += s.size + 1;
	}

	char *buffer = new char[buffer_size];

	uint32_t write_offset = 0;
	for (Token &t : m_tokens)
	{
		if (t.type == TOKEN_TYPE_IDENTIFIER)
		{
			char *write_pos = buffer + write_offset;
			substr s = m_identifiers[t.index];
			memcpy(write_pos, s.start, s.size);
			write_pos[s.size] = 0;
			t.index = write_offset;
			write_offset += s.size + 1;
		}
	}

	return Token_Module{std::move(m_tokens), std::move(m_positions),
			    std::move(m_literals), buffer, buffer_size};
}

Token Lexer::next()
{
	char c;

	do
	{
		c = peek_char();
		if (c == ' ' || c == '\t')
		{
			pop_char();
		}
		else
		{
			break;
		}
	} while (c != 0);

	switch (c)
	{
		case 0:
			return make_token(TOKEN_EOF);
		case 'a' ... 'z':
		case 'A' ... 'Z':
			return parse_identifier();
		case '0' ... '9':
		case '.':
			return parse_num_literal();
		case '"':
			return parse_string_literal();
		case '\'':
			return parse_char_literal();
		case '/':
			return parse_slash();
		case '\n':
			pop_char();
			break_line();
			return make_token(TOKEN_BREAK);
		case ';':
			pop_char();
			return make_token(TOKEN_BREAK);
		default:
			pop_char();

			return make_token(static_cast<Token_Value>(c));
	}
}

Token Lexer::parse_identifier()
{
	size_t start = m_index;
	char c;
	do
	{
		pop_char();
		c = peek_char();
		if (c == 0)
		{
			return make_token(TOKEN_EOF);
		}

	} while (is_identifier_character(c));

	Token_Value t =
	    token_keyword_map.find_substr(m_data + start, m_data + m_index - 1);

	if (t == TOKEN_EMPTY)
	{
		return make_identifier(m_data + start, m_index - start);
	}
	else
	{
		return make_token(t);
	}
}

Token Lexer::parse_slash()
{
	pop_char();
	char c = peek_char();

	if (c == '/')
	{
		do
		{
			pop_char();
			c = peek_char();

			if (c == 0)
			{
				return make_token(TOKEN_EOF);
			}
		} while (c != '\n');

		return make_token(TOKEN_LINE_FEED);
	}
	else if (c == '*')
	{
		Token token = make_token(TOKEN_EMPTY);
		do
		{
			pop_char();
			c = peek_char();
			if (c == 0)
			{
				token = make_token(TOKEN_EOF);
				break;
			}
			if (c == '\n')
			{
				break_line();
				token = make_token(TOKEN_LINE_FEED);
			}
			else if (c == '/' && peek_char(1) == '*')
			{
				Token t = parse_slash();
				if (t.type == TOKEN_LINE_FEED)
				{
					token = t;
				}
				else if (t.type == TOKEN_EOF)
				{
					return t;
				}
			}
		} while (!(c == '*' && peek_char(1) == '/'));
		pop_char();
		return token;
	}
	else
	{
		return make_token(static_cast<Token_Value>(c));
	}
}

void Lexer::break_line()
{
	m_character_number = 0;
	m_line_number++;
}

Token Lexer::parse_char_literal()
{
	pop_char();
	return make_token(TOKEN_EMPTY);
}

char get_escaped_char(char c)
{
	switch (c)
	{
		case '"':
			return '"';
		case '?':
			return '?';
		case '\\':
			return '\\';
		case 'a':
			return '\a';
		case 'b':
			return '\b';
		case 'f':
			return '\f';
		case 'n':
			return '\n';
		case 'r':
			return '\r';
		case 't':
			return '\t';
		case 'v':
			return '\v';
		default:
			return 0;
	}
}

Token Lexer::parse_string_literal()
{
	pop_char();
	// calculate length
	size_t size = 0;
	while (true)
	{
		char c = peek_char(size);
		if (c == '"')
		{
			break;
		}
		else if (c == '\n' || c == 0)
		{
			return make_error();
		}
		else if (c != '\\')
		{
			++size;
		}
	}

	dak_std::string str(size);
	for (size_t i = 0; i < size; ++i)
	{
		char c = peek_char();
		if (c == '\\')
		{
			pop_char();
			c = get_escaped_char(peek_char());
			if (c == 0)
			{
				// invalid escape character
				make_error();
			}
		}
		str[i] = c;
	}
}

Token Lexer::parse_num_literal()
{
	char a = peek_char();
	char b = peek_char(1);

	if (a == '0')
	{
		if (b == 'x')
		{
			return parse_hex_literal();
		}
		if (b == 'b')
		{
			return parse_binary_literal();
		}
	}

	return parse_decimal_literal();
}

Token Lexer::parse_hex_literal()
{
	pop_char(2);

	long long int value = 0;
	while (true)
	{
		char c = peek_char();
		pop_char();

		uint8_t num;
		switch (c)
		{
			case '0' ... '9':
				num = c - '0';
				break;
			case 'a' ... 'f':
				num = c - 'a' + 10;
				break;
			case 'A' ... 'F':
				num = c - 'A' + 10;
				break;
			case 'g' ... 'z':
			case 'G' ... 'Z':
				return make_error();
			default:

				return make_literal(value);
		}

		value = (value << 4) | num;
	}
}

Token Lexer::parse_binary_literal()
{
	pop_char(2);

	long long int value = 0;
	while (true)
	{
		char c = peek_char();
		pop_char();

		switch (c)
		{
			case '0':
				value = value << 1;
				break;
			case '1':
				value = value << 1;
				value = value | 1;
				break;
			case '2' ... '9':
			case 'a' ... 'z':
			case 'A' ... 'Z':
				return make_error();
			default:
				return make_literal(value);
		}
	}
}

Token Lexer::parse_decimal_literal()
{
	unsigned int integral_digits = 0;
	unsigned int fractional_digits = 0;
	long long int integral_value = 0;
	long long int fractional_value = 0;

	while (true)
	{
		char c = peek_char();
		pop_char();
		uint8_t digit_val = c - '0';

		switch (c)
		{
			case '0' ... '9':
				if (fractional_digits > 0)
				{
					fractional_value = (fractional_value *
							    fractional_digits) +
							   digit_val;
					fractional_digits *= 10;
				}
				else
				{
					integral_value =
					    (integral_value * integral_digits) +
					    digit_val;
					integral_digits *= 10;
				}
				break;
			case '.':
				if (fractional_digits > 0)
				{
					// add better error
					return make_error();
				}
				else
				{
					fractional_digits = 1;
				}
				break;
			case 'a' ... 'z':
			case 'A' ... 'Z':
				return make_error();
			default:
				// end of number
				if (fractional_digits > 0)
				{
					double f = integral_value;
					f += (float)fractional_value /
					     fractional_digits;
					return make_literal(f);
				}
				else
				{
					return make_literal(integral_value);
				}
		}
	}
}

} // namespace dak_script