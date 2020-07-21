#ifndef _AST_EXPRESSION_DAK_SCRIPT_H
#define _AST_EXPRESSION_DAK_SCRIPT_H

#include <dak_std/string.h>
#include <dak_std/vector.h>

namespace dak_script
{
struct AST_Type;

struct AST_Expression
{
};
struct AST_Struct_Construct_Expression : public AST_Expression
{
	dak_std::vector<dak_std::string> properties;
	dak_std::vector<AST_Expression *> values;
	AST_Type *type;

	AST_Struct_Construct_Expression(AST_Type *t) : type{t} {}
};

enum AST_BOPERATOR
{
	AST_BOP_ADD,
	AST_BOP_SUB,
	AST_BOP_DIV,
	AST_BOP_MULT,
	AST_BOP_PAREN
};
struct AST_BOP_Expression
{
	AST_BOPERATOR bop;
	AST_Expression *lhs;
	AST_Expression *rhs;
};

enum AST_UOPERATOR
{
	AST_UOP_NOT
};
struct AST_UOP_Expression
{
	AST_UOPERATOR uop;
	AST_Expression *expr;
};
struct AST_Call_Expression
{
};

} // namespace dak_script

#endif
