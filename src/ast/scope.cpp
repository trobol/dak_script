#include <dak_script/ast/scope.h>

namespace dak_script
{
Scope_Block::Scope_Block(const Scope_Block *parent)
    : m_parent{parent}, m_var_allocator(5 * sizeof(Variable)),
      m_func_allocator(5 * sizeof(Function))
{
}

Function *Scope_Block::add_function(const char *name, const Scope_Block *parent)
{
	Function *f = m_func_allocator.allocate<Function>(parent);
	m_func_map.insert({name, f});
	return f;
}

} // namespace dak_script
