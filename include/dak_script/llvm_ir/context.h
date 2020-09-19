#ifndef _DAK_SCRIPT_LLVM_IR_CONTEXT_H
#define _DAK_SCRIPT_LLVM_IR_CONTEXT_H

namespace dak_script
{
class LLVM_IR_Module;
class LLVM_IR_Context
{
	LLVM_IR_Module *m_module;
	unsigned m_tmp_index;

public:
	LLVM_IR_Context(LLVM_IR_Module *module) : m_module{module} {}
	unsigned capture_tmp()
	{
		unsigned i = m_tmp_index;
		++m_tmp_index;
		return i;
	}
};
} // namespace dak_script
#endif