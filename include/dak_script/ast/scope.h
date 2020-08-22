#ifndef _DAK_SCRIPT_AST_SCOPE_H
#define _DAK_SCRIPT_AST_SCOPE_H
#include "../ast.h"
#include <dak_std/linear_allocator.h>
#include <dak_std/vector.h>
#include <string>
#include <unordered_map>

namespace dak_script
{

class Function;

class Scope_Block
{

public:
	Scope_Block *m_parent;
	dak_std::vector<AST_Statement *> m_expressions;

	std::unordered_map<dak_std::string, AST_Variable *> m_var_map;

	// list of types
	AST_Type_Map m_types;

	// list of functions
	std::unordered_map<const char *, Function *> m_func_map;

	dak_std::linear_allocator m_func_allocator;

public:
	Scope_Block(Scope_Block *parent);
	AST_Variable *find_variable(dak_std::string& name)
	{
		auto result_pair = m_var_map.find(name);
		if (result_pair != m_var_map.end())
			return result_pair->second;
		else
			return nullptr;
	}

	Scope_Block *parent() { return m_parent; }

	AST_Variable *add_variable(dak_std::string& name)
	{
		AST_Variable *v = new AST_Variable(name);
		m_var_map.insert({name, v});
		return v;
	}

	Function *add_function(const char *name, Scope_Block *parent);
}; // namespace dak_script

class Function
{
	dak_std::string m_identifier;
	dak_std::vector<AST_Variable> m_parameters;
	Scope_Block m_block;

public:
	Function(Scope_Block *parent) : m_block(parent) {}
};
} // namespace dak_script

#endif