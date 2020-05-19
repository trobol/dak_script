#include <dak_script/lexer.h>
#include <dak_script/character_type.h>
#include <dak_script/character_traits.h>
#include <dak_script/token_maps.h>
#include <cstring>
#include <iostream>

namespace dak::script
{

	Token Lexer::make_token(Token_Type t)
	{
		return Token{TOKEN_IS_TOKEN, t};
	}

	Token Lexer::make_identifier(const char *start, uint32_t size)
	{
		m_identifiers.push_back({start, size});
		return Token{TOKEN_IS_IDENTIFIER, .index = (m_identifiers.size() - 1)};
	}

	Lexer::Lexer(const char *data, size_t size) : m_data{data},
												  m_size{size},
												  m_index{0},
												  m_character_number{0},
												  m_line_number{0} {};

	char Lexer::peek_char()
	{
		if (m_index >= m_size)
		{
			return 0;
		}
		//std::cout << m_data[m_index];
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
		m_character_number++;
		m_index++;
	}

	Token_Module Lexer::lex()
	{

		Token token;

		do
		{
			token = next();
			m_tokens.push_back(token);
			m_positions.push_back(Token_Pos{m_line_number, m_character_number});
		} while (token.characteristic != TOKEN_IS_TOKEN || token.type != TOKEN_EOF);

		uint32_t buffer_size = 0;
		for (substr &s : m_identifiers)
		{
			buffer_size += s.size + 1;
		}

		char *buffer = new char[buffer_size];

		uint32_t write_offset = 0;
		for (Token &t : m_tokens)
		{
			if (t.characteristic == TOKEN_IS_IDENTIFIER)
			{
				char *write_pos = buffer + write_offset;
				substr s = m_identifiers[t.index];
				memcpy(write_pos, s.start, s.size);
				write_pos[s.size] = 0;
				t.index = write_offset;
				write_offset += s.size + 1;
			}
		}

		return Token_Module{std::move(m_tokens), std::move(m_positions), buffer, buffer_size};
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
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			return parse_identifier();
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
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

			return make_token(static_cast<Token_Type>(c));
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

		Token_Type t = token_keyword_map.find_substr(m_data + start, m_data + m_index - 1);

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
			return make_token(static_cast<Token_Type>(c));
		}
	}

	void Lexer::break_line()
	{
		m_character_number = 0;
		m_line_number++;
	}

	Token Lexer::parse_num_literal()
	{
		unsigned int integral_digits = 0;
		unsigned int fractional_digits = 0;
		unsigned int integral_value = 0;
		unsigned int fractional_value = 0;
		char c = peek_char();
		

		while (true)
		{
			uint8_t digit_val = c - '0';

			switch (c)
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (fractional_digits > 0)
				{
					fractional_value = (fractional_value * fractional_digits) + digit_val;
					fractional_digits *= 10;
				}
				else
				{
					integral_value = (integral_value * integral_value) + digit_val;
					integral_digits *= 10;
				}
				break;
			case '.':
				if (fractional_digits > 0)
				{
					//add better error
					return make_token(TOKEN_ERROR);
				}
				else
				{
					fractional_digits = 1;
				}

			default:
			}
		}
	}
} // namespace dak::script