#ifndef _DAK_SCRIPT_AST_AST_H
#define _DAK_SCRIPT_AST_AST_H

namespace dak_script
{

class Variable;
class ExprAST
{
public:
	virtual ~ExprAST() {}
};

class VariableDecExprAST : public ExprAST
{
	Variable *m_variable;
	ExprAST *m_value;

public:
	VariableDecExprAST(Variable *variable, ExprAST *value)
	    : m_variable{variable}, m_value{value}
	{
	}
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST
{
	double Val;

public:
	NumberExprAST(double Val) : Val(Val) {}
};

} // namespace dak_script

#endif
