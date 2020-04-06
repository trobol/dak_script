#ifndef _DAK_SCRIPT_KEYWORD_H
#define _DAK_SCRIPT_KEYWORD_H

#include <unordered_map>
#include <string>

namespace dak::script
{

enum struct keywords
{
	kw_public,
	kw_private,
	kw_hook,
	kw_function,
	kw_class,
	kw_extends,

	kw_if,
	kw_else,

	kw_return,
	kw_for
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

} // namespace dak::script

#endif