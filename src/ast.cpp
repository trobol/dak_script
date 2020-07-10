#include <dak_script/ast.h>

namespace dak_script
{
AST_Function *AST_Statement_Block::add_function(dak_std::string &name)
{
	AST_Function *f = new AST_Function(name);
	functions.push_back(f);
	function_map.insert({name, f});
	return f;
}

AST_Statement_Block::~AST_Statement_Block()
{
	for (AST_Statement *s : statements)
	{
		delete s;
	}
	for (AST_Function *f : functions)
	{
		delete f;
	}
	for (AST_Variable *v : variables)
	{
		delete v;
	}
}
} // namespace dak_script