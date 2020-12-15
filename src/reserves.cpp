#include <dak_script/reserves.h>

namespace dak::script
{

std::unordered_map<std::string, keywords> keywords_map = {
	{"function", keywords::kw_function},
	{"hook", keywords::kw_hook},
	{"public", keywords::kw_public},
	{"private", keywords::kw_private},
	{"class", keywords::kw_class},
	{"extends", keywords::kw_extends},
	{"if", keywords::kw_if},
	{"else", keywords::kw_else},
	{"return", keywords::kw_return},
	{"for", keywords::kw_for}};

std::unordered_map<std::string, operations> operations_map = {
	{"+", operations::op_add},
	{"-", operations::op_sub},
	{"=", operations::op_assign},
	{"+=", operations::op_addassign},
	{"&&", operations::op_and},
	{"<", operations::op_less},
	{"++", operations::op_incr}};
} // namespace dak::script