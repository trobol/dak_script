#ifndef _DAK_SCRIPT_ABSTRACT_SYNTAX_TREE_H
#define _DAK_SCRIPT_ABSTRACT_SYNTAX_TREE_H
#include <dak_script/token.h>
#include <dak_script/token_module.h>
#include <dak_std/linear_allocator.h>
#include <dak_std/vector.h>
#include <string>

namespace dak_script
{

struct Statement_Block
{
	dak_std::vector<Variable> variables;
	dak_std::vector<ExprAST *>
};

struct Parsed_Module
{
	// functions
	dak_std::vector<FunctionAST> functions;

	// variables
	dak_std::vector<Variable> variables;

	// types
	dak_std::vector<Type> types;
};

class Parser
{
	size_t m_index;

	Token_Module &m_token_module;

	dak_std::linear_allocator m_allocator;

public:
	Parsed_Module parse();

private:
	ExprAST *next();
	ExprAST *parse_num_expr();
	ExprAST *parse_paren_expr();
	ExprAST *parse_function_expr();

	ExprAST *parse_var_expr();

	Token &get_token();
};

enum Type_Category
{
	TYPE_CATEGORY_STRUCT,
	TYPE_CATEGORY_FUNCTION,
	TYPE_CATEGORY_I32,
	TYPE_CATEGORY_I64,
	TYPE_CATEGORY_U32,
	TYPE_CATEGORY_U64,
	TYPE_CATEGORY_F32,
	TYPE_CATEGORY_F64,

};

struct Type
{
	std::string identifier;
	Type_Category category;

	union {
		long int int_value;
		double float_value;
	};
};

struct Variable
{
};

/// ExprAST - Base class for all expression nodes.
class ExprAST
{
public:
	virtual ~ExprAST() {}
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST
{
	double Val;

public:
	NumberExprAST(double Val) : Val(Val) {}
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST
{
	std::string Name;
	dak_std::vector<std::string> Args;

public:
	PrototypeAST(const std::string &name, dak_std::vector<std::string> Args)
	    : Name(name), Args(std::move(Args))
	{
	}

	const std::string &getName() const { return Name; }
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST
{
	PrototypeAST *Proto;
	ExprAST *Body;

public:
	FunctionAST(PrototypeAST *Proto, ExprAST *Body)
	    : Proto{Proto}, Body{Body}
	{
	}
}; // namespace dak_script

} // namespace dak_script
#endif