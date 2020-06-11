#ifndef _DAK_SCRIPT_ABSTRACT_SYNTAX_TREE_H
#define _DAK_SCRIPT_ABSTRACT_SYNTAX_TREE_H
#include <string>
#include <vector>

namespace dak_script
{
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
	std::vector<std::string> Args;

public:
	PrototypeAST(const std::string &name, std::vector<std::string> Args)
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