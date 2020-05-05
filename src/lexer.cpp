#include <dak_script/lexer.h>
#include <dak_script/character_type.h>

namespace dak::script
{

char Lexer::peek_char()
{
	return m_data[m_index];
}

void Lexer::pop_char()
{
	m_index++;
}

std::vector<Token> Lexer::lex()
{
}

Token Lexer::next()
{
	char c = peek_char();

	switch (c)
	{
	case 0:
		return Token{TOKEN_EOF};
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
	case '/':
		return parse_slash();
	default:
		return make(static_cast<Token_Type>(c));
	}
}

} // namespace dak::script