#ifndef _DAK_SCRIPT_LLVM_IR_CONTEXT_H
#define _DAK_SCRIPT_LLVM_IR_CONTEXT_H
#include "line.h"

namespace dak_script
{
class LLVM_IR_Module;
class LLVM_IR_Context
{
public:
	dak_std::vector<LLVM_IR_Line> m_lines;

	LLVM_IR_Context() = default;
	LLVM_IR_Value append_line(LLVM_IR_Line line)
	{
		size_t end = m_lines.size();
		m_lines.push_back(line);
		return LLVM_IR_Value::create_ref(end);
	}
};
} // namespace dak_script
#endif