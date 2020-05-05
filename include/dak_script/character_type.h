#ifndef _DAK_SCRIPT_CHARACTER_TYPE_H
#define _DAK_SCRIPT_CHARACTER_TYPE_H

namespace dak::script
{
enum Character_Type
{
	CHARACTER_TYPE_LETTER,
	CHARACTER_TYPE_NUMBER,
	CHARACTER_TYPE_SPACE,
	CHARACTER_TYPE_BREAK,
	CHARACTER_TYPE_OTHER
};

Character_Type get_character_type(char c);

bool is_identifier_char(char c);

} // namespace dak::script

#endif