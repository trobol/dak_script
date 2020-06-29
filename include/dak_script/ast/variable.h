#ifndef _DAK_SCRIPT_AST_VARIABLE_H
#define _DAK_SCRIPT_AST_VARIABLE_H
#include "type.h"
#include <dak_std/string.h>

namespace dak_script
{

class VariableDecExprAST;
struct Variable
{
	dak_std::string name;
	bool is_type_inferred;
	Type *type;
	VariableDecExprAST *declaration;
};

} // namespace dak_script

#endif