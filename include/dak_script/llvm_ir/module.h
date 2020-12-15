#ifndef _DAK_SCRIPT_LLVM_IR_MODULE_H
#define _DAK_SCRIPT_LLVM_IR_MODULE_H

namespace dak_script
{
class LLVM_IR_Context;
// https://llvm.org/docs/LangRef.html#module-structure
class LLVM_IR_Module
{
public:
	// functions
	dak_std::vector<LLVM_IR_Context *> m_functions;
	// globals
	// symbol table
};
} // namespace dak_script
#endif