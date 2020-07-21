#include <dak_script/ast.h>

namespace dak_script
{

//////////////////////
//   STRUCT BLOCK   //
//////////////////////

AST_Variable *AST_Struct_Block::find_variable(dak_std::string &name)
{
	auto result_pair = m_type->member_map.find(name);
	if (result_pair != m_type->member_map.end())
		return result_pair->second;
	else
		return nullptr;
}

AST_Variable *AST_Struct_Block::add_variable(dak_std::string &name)
{
	AST_Variable *v = new AST_Variable(name);
	m_type->members.push_back(v);
	m_type->member_map.insert({name, v});
	return v;
}

AST_Function *AST_Struct_Block::find_function(dak_std::string &name)
{
	return nullptr;
}
AST_Function *AST_Struct_Block::add_function(dak_std::string &name)
{
	// TODO SYNTAX ERROR
	return nullptr;
}

AST_Type *AST_Struct_Block::find_type(dak_std::string &name) { return nullptr; }
AST_Type *AST_Struct_Block::add_type(dak_std::string &name) { return nullptr; }

void AST_Struct_Block::add_statement(AST_Statement *statement)
{
	// TODO SYNTAX ERROR
}

/////////////////////////
//   STATEMENT BLOCK   //
/////////////////////////

AST_Variable *AST_Statement_Block::find_variable(dak_std::string &name)
{
	auto result_pair = m_variable_map.find(name);
	if (result_pair != m_variable_map.end())
		return result_pair->second;
	else
		return nullptr;
}
AST_Variable *AST_Statement_Block::add_variable(dak_std::string &name)
{
	AST_Variable *v = new AST_Variable(name);
	m_variables.push_back(v);
	m_variable_map.insert({name, v});
	return v;
}

AST_Function *AST_Statement_Block::find_function(dak_std::string &name)
{
	auto result_pair = m_function_map.find(name);
	if (result_pair != m_function_map.end())
		return result_pair->second;
	else
		return nullptr;
}

AST_Function *AST_Statement_Block::add_function(dak_std::string &name)
{
	AST_Function *f = new AST_Function(name);
	m_functions.push_back(f);
	m_function_map.insert({name, f});
	return f;
}

AST_Type *AST_Statement_Block::add_type(dak_std::string &name)
{
	AST_Type *t = new AST_Type(name);
	m_types.push_back(t);
	m_type_map.insert({name, t});
	return t;
}
AST_Type *AST_Statement_Block::find_type(dak_std::string &name)
{
	return nullptr;
}

void AST_Statement_Block::add_statement(AST_Statement *statement)
{
	m_statements.push_back(statement);
}

AST_Statement_Block::~AST_Statement_Block()
{
	for (AST_Statement *s : m_statements)
	{
		delete s;
	}
	for (AST_Function *f : m_functions)
	{
		delete f;
	}
	for (AST_Variable *v : m_variables)
	{
		delete v;
	}
}

//////////////////
//   FUNCTION   //
//////////////////

AST_Function::~AST_Function()
{
	for (AST_Variable *p : parameters)
	{
		delete p;
	}
}

AST_Variable *AST_Function::add_parameter(dak_std::string &name)
{
	AST_Variable *v = add_variable(name);
	parameters.push_back(v);
	return v;
}

} // namespace dak_script