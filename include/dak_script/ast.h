#ifndef _DAK_SCRIPT_AST_AST_H
#define _DAK_SCRIPT_AST_AST_H
#include <dak_script/ast_expression.h>
#include <dak_std/string.h>
#include <dak_std/vector.h>
#include <unordered_map>
#include "ast_type.h"

namespace dak_script
{

struct AST_Declaration_Statement;

struct AST_Expression;

struct AST_Variable
{
	bool is_type_inferred;
	AST_Declaration_Statement *declaration;
	dak_std::string name;
	AST_Type_Ref type;

	AST_Variable(dak_std::string &n) : name{n} {}
};

struct AST_Type
{
	dak_std::string name;
	dak_std::vector<AST_Variable *> members;
	std::unordered_map<dak_std::string, AST_Variable *> member_map;

	AST_Type(dak_std::string &n) : name{n} {}
};

// top level
struct AST_Statement
{
	virtual ~AST_Statement() {}
	// virtual void codegen() = 0;
	virtual void print(unsigned indent = 0)
	{
		const char buffer[50] = {};

		if (indent > 50)
			indent = 50;

		for (unsigned i = 0; i < indent; i++)
		{
			buffer[i] == '\t';
		}
		printf("%s", buffer);
	}
};

struct AST_Function;

struct AST_Base_Block : public AST_Statement
{
	AST_Base_Block *parent;

	virtual AST_Variable *find_variable(dak_std::string &name) = 0;
	virtual AST_Variable *add_variable(dak_std::string &name) = 0;

	virtual AST_Function *add_function(dak_std::string &name) = 0;
	virtual AST_Function *find_function(dak_std::string &name) = 0;

	virtual void add_statement(AST_Statement *) = 0;

	virtual AST_Type *add_type(dak_std::string &) = 0;
	virtual AST_Type *find_type(dak_std::string &) = 0;
};

struct AST_Struct_Block : public AST_Base_Block
{
private:
	AST_Type *m_type;

public:
	AST_Struct_Block(AST_Type *type) : m_type{type} {}
	AST_Variable *find_variable(dak_std::string &name);

	AST_Variable *add_variable(dak_std::string &name);

	AST_Function *find_function(dak_std::string &name);
	AST_Function *add_function(dak_std::string &name);

	AST_Type *find_type(dak_std::string &name);
	AST_Type *add_type(dak_std::string &name);

	void add_statement(AST_Statement *statement);
};

struct AST_Statement_Block : public AST_Base_Block
{
private:
	dak_std::vector<AST_Statement *> m_statements;

	dak_std::vector<AST_Variable *> m_variables;
	std::unordered_map<dak_std::string, AST_Variable *> m_variable_map;

	dak_std::vector<AST_Function *> m_functions;
	std::unordered_map<dak_std::string, AST_Function *> m_function_map;

	dak_std::vector<AST_Type *> m_types;
	std::unordered_map<dak_std::string, AST_Type *> m_type_map;

public:
	AST_Variable *find_variable(dak_std::string &name);
	AST_Variable *add_variable(dak_std::string &name);

	AST_Function *find_function(dak_std::string &name);
	AST_Function *add_function(dak_std::string &name);

	AST_Type *add_type(dak_std::string &name);
	AST_Type *find_type(dak_std::string &name);

	void add_statement(AST_Statement *statement);

	dak_std::vector<AST_Function *> &functions() { return m_functions; }
	dak_std::vector<AST_Variable *> &variables() { return m_variables; }
	dak_std::vector<AST_Statement *> &statements() { return m_statements; }
	dak_std::vector<AST_Type *> &types() { return m_types; }
	~AST_Statement_Block();
};

struct AST_Function : public AST_Statement_Block
{

	dak_std::string name;
	dak_std::vector<AST_Variable *> parameters;
	dak_std::vector<AST_Type *> returns;
	AST_Function(dak_std::string &n) : name{n} {}
	~AST_Function();

	AST_Variable *add_parameter(dak_std::string &name);

	void add_return(AST_Type *type) { returns.push_back(type); }
};

struct AST_IfElse_Statement : public AST_Statement
{
	AST_Expression *condition;
	AST_Statement *if_block;
	AST_Statement *else_block;

	AST_IfElse_Statement(AST_Expression *condition) : condition{condition}
	{
	}
	~AST_IfElse_Statement()
	{
		delete condition;
		delete if_block;
		delete else_block;
	}
};

struct AST_For_Statement : public AST_Statement
{
	AST_Expression *init;
	AST_Expression *check;
	AST_Expression *incr;
	AST_Statement *block;

	AST_For_Statement() {}
	~AST_For_Statement()
	{
		delete init;
		delete check;
		delete incr;
		delete block;
	}
};

struct AST_While_Statement : public AST_Statement
{
	AST_Expression *check;
	AST_Statement *block;

public:
	AST_While_Statement() {}
	~AST_While_Statement()
	{
		delete check;
		delete block;
	}
};

struct AST_Switch_Statement : public AST_Statement
{
public:
	AST_Switch_Statement() {}
};

struct AST_Declaration_Statement : public AST_Statement
{
	AST_Variable *variable;
	AST_Expression *value;

public:
	AST_Declaration_Statement(AST_Variable *variable, AST_Expression *value)
	    : variable{variable}, value{value}
	{
	}
	~AST_Declaration_Statement() { delete value; }
	void print(unsigned indent = 0)
	{
		AST_Statement::print();
		printf("Declaration Statement: %s \n", variable->name);
		print_expression(value, indent);
	}
};

struct AST_Assign_Statement : public AST_Statement
{
	AST_Variable *variable;
	AST_Expression *value;

public:
	AST_Assign_Statement(AST_Variable *variable, AST_Expression *value)
	    : variable{variable}, value{value}
	{
	}
	~AST_Assign_Statement() { delete value; }
};

void print_statement(AST_Statement *s, int indent = 0);

} // namespace dak_script

#endif
