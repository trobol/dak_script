#ifndef _DAK_SCRIPT_AST_AST_H
#define _DAK_SCRIPT_AST_AST_H
#include "ast_type.h"
#include <dak_script/ast_expression.h>
#include <dak_std/string.h>
#include <dak_std/vector.h>
#include <unordered_map>

namespace dak_script
{

enum AST_Statement_Type
{
	AST_STATEMENT_TYPE_UNKNOWN,
	AST_STATEMENT_TYPE_STATEMENT,
	AST_STATEMENT_TYPE_STATEMENT_BLOCK,
	AST_STATEMENT_TYPE_FUNCTION_BLOCK,
	AST_STATEMENT_TYPE_STRUCT_BLOCK,
	AST_STATEMENT_TYPE_DECLARATION,
	AST_STATEMENT_TYPE_IF_ELSE,
	AST_STATEMENT_TYPE_SWITCH,
	AST_STATEMENT_TYPE_ASSIGN,
	AST_STATEMENT_TYPE_RETURN,
};

struct AST_Declaration_Statement;

struct AST_Expression;

struct AST_Variable
{
	bool is_type_inferred;
	AST_Declaration_Statement *declaration;
	dak_std::string name;
	AST_Type_Ref type;

	AST_Variable(dak_std::string &n, AST_Type_Ref t) : name{n}, type{t} {}
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
	const AST_Statement_Type m_statement_type;
	AST_Statement(const AST_Statement_Type t) : m_statement_type{t} {};
	AST_Statement() : m_statement_type{AST_STATEMENT_TYPE_UNKNOWN} {};
	virtual ~AST_Statement() {}
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

struct AST_Return_Statement : public AST_Statement
{
	AST_Expression *value;
	AST_Return_Statement(AST_Expression *v)
	    : AST_Statement(AST_STATEMENT_TYPE_RETURN), value{v}
	{
	}
};

struct AST_Function;

struct AST_Base_Block : public AST_Statement
{

	AST_Base_Block(const AST_Statement_Type t) : AST_Statement{t} {}
	AST_Base_Block *parent;

	virtual AST_Variable *find_variable(dak_std::string &name) = 0;
	virtual AST_Variable *add_variable(dak_std::string &name,
					   AST_Type_Ref type) = 0;

	virtual AST_Function *add_function(dak_std::string &name) = 0;
	virtual AST_Function *find_function(dak_std::string &name) = 0;

	virtual void add_statement(AST_Statement *) = 0;

	virtual AST_Type_Ref add_type(dak_std::string &) = 0;
	virtual AST_Type_Ref find_type(dak_std::string &) = 0;
};

struct AST_Struct_Block : public AST_Base_Block
{
private:
	AST_Type_Struct_Data *m_type;

public:
	AST_Struct_Block(AST_Type_Ref type)
	    : AST_Base_Block{AST_STATEMENT_TYPE_STRUCT_BLOCK},
	      m_type{type.get_struct()}
	{
	}
	AST_Variable *find_variable(dak_std::string &name);

	AST_Variable *add_variable(dak_std::string &name, AST_Type_Ref type);

	AST_Function *find_function(dak_std::string &name);
	AST_Function *add_function(dak_std::string &name);

	AST_Type_Ref find_type(dak_std::string &name);
	AST_Type_Ref add_type(dak_std::string &name);

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

	AST_Type_Map m_type_map;

public:
	AST_Statement_Block()
	    : AST_Base_Block{AST_STATEMENT_TYPE_STATEMENT_BLOCK}
	{
	}
	AST_Variable *find_variable(dak_std::string &name);
	AST_Variable *add_variable(dak_std::string &name, AST_Type_Ref type);

	AST_Function *find_function(dak_std::string &name);
	AST_Function *add_function(dak_std::string &name);

	AST_Type_Ref add_type(dak_std::string &name);
	AST_Type_Ref find_type(dak_std::string &name);

	void add_statement(AST_Statement *statement);

	dak_std::vector<AST_Function *> &functions() { return m_functions; }
	dak_std::vector<AST_Variable *> &variables() { return m_variables; }
	dak_std::vector<AST_Statement *> &statements() { return m_statements; }

	~AST_Statement_Block();
};

struct AST_Function : public AST_Statement_Block
{

	dak_std::string name;
	dak_std::vector<AST_Variable *> parameters;
	dak_std::vector<AST_Type_Ref> returns;
	AST_Function(dak_std::string &n) : name{n} {}
	~AST_Function();

	AST_Variable *add_parameter(dak_std::string &name, AST_Type_Ref type);

	void add_return(AST_Type_Ref type) { returns.push_back(type); }
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
	AST_Switch_Statement() : AST_Statement{AST_STATEMENT_TYPE_SWITCH} {}
};

struct AST_Declaration_Statement : public AST_Statement
{
	AST_Variable *variable;
	AST_Expression *value;

public:
	AST_Declaration_Statement(AST_Variable *variable, AST_Expression *value)
	    : AST_Statement{AST_STATEMENT_TYPE_DECLARATION}, variable{variable},
	      value{value}
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
	    : AST_Statement{AST_STATEMENT_TYPE_ASSIGN}, variable{variable},
	      value{value}
	{
	}
	~AST_Assign_Statement() { delete value; }
};

void print_statement(AST_Statement *s, int indent = 0);

} // namespace dak_script

#endif
