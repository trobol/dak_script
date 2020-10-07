#ifndef _DAK_SCRIPT_LLVM_IR_CONTEXT_H
#define _DAK_SCRIPT_LLVM_IR_CONTEXT_H
#include "line.h"

namespace dak_script
{
class LLVM_IR_Module;
class LLVM_IR_Context
{
	dak_std::vector<LLVM_IR_Line *> m_lines;

public:
	LLVM_IR_Context() = default;
	unsigned int add_line(LLVM_IR_Line *line) { m_lines.push_back(line); };
};
} // namespace dak_script
#endif