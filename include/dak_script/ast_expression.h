#ifndef _AST_EXPRESSION_DAK_SCRIPT_H
#define _AST_EXPRESSION_DAK_SCRIPT_H

#include <dak_script/token.h>
#include <dak_std/string.h>
#include <dak_std/vector.h>

namespace dak_script
{
struct AST_Type;

enum AST_Expression_Type
{
	AST_EXPRESSION_TYPE_CONSTRUCT,
	AST_EXPRESSION_TYPE_VARIABLE,
	AST_EXPRESSION_TYPE_BOP,
	AST_EXPRESSION_TYPE_UOP,
	AST_EXPRESSION_TYPE_LITERAL,
	AST_EXPRESSION_TYPE_PAREN,
	AST_EXPRESSION_TYPE_VALUE,
	AST_EXPRESSION_TYPE_CALL
};
struct AST_Expression
{
	const AST_Expression_Type type;
	AST_Expression(AST_Expression_Type t) : type{t} {}
	virtual ~AST_Expression() {}
};
struct AST_Construct_Expression : public AST_Expression
{
	dak_std::vector<dak_std::string> properties;
	dak_std::vector<AST_Expression *> values;
	AST_Type *construct_type;

	AST_Construct_Expression(AST_Type *t)
	    : AST_Expression(AST_EXPRESSION_TYPE_CONSTRUCT), construct_type{t}
	{
	}
};

struct AST_Variable;
struct AST_Variable_Expression : public AST_Expression
{
	AST_Variable *ptr;
	AST_Variable_Expression(AST_Variable *v)
	    : AST_Expression(AST_EXPRESSION_TYPE_VARIABLE), ptr{v} {};
};

struct AST_Paren_Expression : public AST_Expression
{
	AST_Expression *expr;
	AST_Paren_Expression()
	    : AST_Expression(AST_EXPRESSION_TYPE_PAREN), expr{nullptr}
	{
	}
};

struct AST_Literal_Expression : public AST_Expression
{
	Token_Literal literal;
	AST_Literal_Expression(Token_Literal l)
	    : AST_Expression(AST_EXPRESSION_TYPE_LITERAL), literal{l}
	{
	}
};

struct AST_Subscript_Operator
{
	AST_Variable *var;
	AST_Expression *expr;
};
enum AST_BOPERATOR
{
	AST_BOP_ADD,
	AST_BOP_SUB,
	AST_BOP_MULT,
	AST_BOP_DIV
};
struct AST_BOP_Expression : public AST_Expression
{
	AST_BOPERATOR bop;
	AST_Expression *lhs;
	AST_Expression *rhs;

	AST_BOP_Expression(Token_Value t)
	    : AST_Expression(AST_EXPRESSION_TYPE_BOP)
	{
		switch (t)
		{
			case '+':
				bop = AST_BOP_ADD;
				break;
			case '-':
				bop = AST_BOP_SUB;
				break;
			case '*':
				bop = AST_BOP_MULT;
				break;
			case '/':
				bop = AST_BOP_DIV;
				break;
			default:
				break;
		}
	}
};

enum AST_UOPERATOR
{
	AST_UOP_NOT,
	AST_UOP_PAREN,
	AST_UOP_REFERENCE,
	AST_UOP_DEREFERENCE
};
struct AST_UOP_Expression : public AST_Expression
{
	AST_UOPERATOR uop;
	AST_Expression *expr;
	AST_UOP_Expression() : AST_Expression(AST_EXPRESSION_TYPE_UOP) {}
};
struct AST_Call_Expression
{
};

void print_expression(AST_Expression *expr, int indent = 0);

} // namespace dak_script

#endif
