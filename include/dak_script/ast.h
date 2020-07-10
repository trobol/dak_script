#ifndef _DAK_SCRIPT_AST_AST_H
#define _DAK_SCRIPT_AST_AST_H
#include <dak_std/string.h>
#include <dak_std/vector.h>
#include <unordered_map>

namespace dak_script
{

struct AST_Declaration_Statement;

struct AST_Variable
{
	bool is_type_inferred;
	// Type *type;
	AST_Declaration_Statement *declaration;
	dak_std::string name;
	AST_Variable(dak_std::string &n) : name{n} {}
};
struct AST_Expression
{
};

struct AST_Type
{
};

// top level
struct AST_Statement
{
	virtual ~AST_Statement() {}
};

struct AST_Function;

struct AST_Statement_Block : public AST_Statement
{
	AST_Statement_Block *parent;
	dak_std::vector<AST_Statement *> statements;
	dak_std::vector<AST_Variable *> variables;
	std::unordered_map<dak_std::string, AST_Variable *> variable_map;
	dak_std::vector<AST_Function *> functions;
	std::unordered_map<dak_std::string, AST_Function *> function_map;

	AST_Variable *find_variable(dak_std::string &name)
	{
		auto result_pair = variable_map.find(name);
		if (result_pair != variable_map.end())
			return result_pair->second;
		else
			return nullptr;
	}
	AST_Variable *add_variable(dak_std::string &name)
	{
		AST_Variable *v = new AST_Variable(name);
		variables.push_back(v);
		variable_map.insert({name, v});
		return v;
	}

	AST_Function *find_function(dak_std::string &name)
	{
		auto result_pair = function_map.find(name);
		if (result_pair != function_map.end())
			return result_pair->second;
		else
			return nullptr;
	}
	AST_Function *add_function(dak_std::string &name);

	~AST_Statement_Block();
};

struct AST_Function : public AST_Statement_Block
{

	dak_std::string name;
	dak_std::vector<AST_Variable *> parameters;
	AST_Function(dak_std::string &n) : name{n} {}
	~AST_Function()
	{
		for (AST_Variable *p : parameters)
		{
			delete p;
		}
	}

	AST_Variable *add_parameter(dak_std::string &name)
	{
		AST_Variable *v = add_variable(name);
		parameters.push_back(v);
		return v;
	}
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

} // namespace dak_script

#endif
