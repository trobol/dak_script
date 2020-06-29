#ifndef _DAK_SCRIPT_AST_SCOPE_H
#define _DAK_SCRIPT_AST_SCOPE_H
#include "ast.h"
#include "variable.h"
#include <dak_std/linear_allocator.h>
#include <dak_std/vector.h>
#include <string>
#include <unordered_map>

namespace dak_script
{

class Function;

class Scope_Block
{
	struct c_str_hash_function
	{
		size_t operator()(const char *str) const
		{
			const unsigned A = 54059;
			const unsigned B = 76963;
			const unsigned FIRSTH = 37;
			unsigned h = FIRSTH;
			while (*str)
			{
				h = (h * A) ^ (str[0] * B);
				str++;
			}
			return h;
		}
	};
	const Scope_Block *m_parent;
	dak_std::vector<ExprAST *> m_expressions;

	std::unordered_map<const char *, Variable *, c_str_hash_function>
	    m_var_map;

	dak_std::linear_allocator m_var_allocator;

	// list of types
	dak_std::vector<Type> m_types;

	// list of functions
	std::unordered_map<const char *, Function *, c_str_hash_function>
	    m_func_map;

	dak_std::linear_allocator m_func_allocator;

public:
	Scope_Block(const Scope_Block *parent);
	Variable *find_variable(const char *name)
	{
		auto result_pair = m_var_map.find(name);
		if (result_pair != m_var_map.end())
			return result_pair->second;
		else
			return nullptr;
	}

	const Scope_Block *parent() { return m_parent; }

	Variable *add_variable(const char *name)
	{
		Variable *v = m_var_allocator.allocate<Variable>();
		m_var_map.insert({name, v});
		return v;
	}

	Function *add_function(const char *name, const Scope_Block *parent);
}; // namespace dak_script

class Function
{
	dak_std::string m_identifier;
	dak_std::vector<Variable> m_parameters;
	Scope_Block m_block;

public:
	Function(const Scope_Block *parent) : m_block(parent) {}
};
} // namespace dak_script

#endif