#ifndef _DAK_SCRIPT_ABSTRACT_SYNTAX_TREE_H
#define _DAK_SCRIPT_ABSTRACT_SYNTAX_TREE_H
#include "ast/ast.h"
#include "ast/scope.h"
#include "ast/type.h"
#include "ast/variable.h"
#include <dak_script/token.h>
#include <dak_script/token_module.h>
#include <dak_std/linear_allocator.h>
#include <dak_std/vector.h>

#include <string>

namespace dak_script
{

struct Parsed_Module
{
	// unused for now
	// dak_std::vector<Scope_Block *> imports;

	Scope_Block top_scope;

	Parsed_Module() : top_scope(nullptr) {}
};

} // namespace dak_script
#endif