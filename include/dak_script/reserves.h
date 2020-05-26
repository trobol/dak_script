#ifndef _DAK_SCRIPT_KEYWORD_H
#define _DAK_SCRIPT_KEYWORD_H

#include <unordered_map>
#include <string>

namespace dak_script
{

enum struct keywords
{
	KEYWORD_PUBLIC,
	KEYWORD_PRIVATE,
	KEYWORD_function,
	KEYWORD_class,
	KEYWORD_extends,

	KEYWORD_if,
	KEYWORD_else,

	KEYWORD_return,
	KEYWORD_for
};

enum struct operations
{
	op_add,
	op_addassign,
	op_assign,
	op_incr,
	op_sub,
	op_dot,

	op_and,
	op_less

};

extern std::unordered_map<std::string, keywords> keywords_map;
extern std::unordered_map<std::string, operations> operations_map;

} // namespace dak_script

#endif