#include <dak_script/character_type.h>

namespace dak::script
{

character_type get_character_type(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return character_type::letter;
	if (c >= '0' && c <= '9')
		return character_type::number;
	switch (c)
	{
	case '_':
		return character_type::letter;
		break;
	case '{':
	case '}':
	case '(':
	case ')':
	case '[':
	case ']':
		return character_type::bracket;
		break;

	case '\n':
		return character_type::newline;

	case ' ':
	case '\t':
		return character_type::whitespace;
		break;

	case '\'':
	case '"':
		return character_type::quotation;
		break;

	case ',':
	case ';':
		return character_type::punctuation;
		break;

	case '.':
	case '*':
	case '/':
	case '=':
	case '-':
	case '+':
	case '<':
	case '>':
	case '&':
	case '|':
	case '!':
		return character_type::operation;
		break;

	default:
		return character_type::unknown;
		break;
	}
}
} // namespace dak::script