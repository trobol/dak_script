#include <dak_script/ast/scope.h>

namespace dak_script
{
Scope_Block::Scope_Block(Scope_Block *parent)
    : m_parent{parent},
      m_func_allocator(5 * sizeof(Function))
{
}

Function *Scope_Block::add_function(const char *name, Scope_Block *parent)
{
	Function *f = m_func_allocator.allocate<Function>(parent);
	m_func_map.insert({name, f});
	return f;
}

} // namespace dak_script
