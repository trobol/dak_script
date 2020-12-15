#ifndef _DAK_SCRIPT_CHARACTER_TYPE_H
#define _DAK_SCRIPT_CHARACTER_TYPE_H

namespace dak::script
{
enum struct character_type
{
	letter,
	number,
	bracket,
	whitespace,
	operation,
	quotation,
	unknown,
	newline,
	punctuation,

};

character_type get_character_type(char c);
} // namespace dak::script

#endif