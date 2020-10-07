#ifndef _DAK_SCRIPT_LLVM_IR_LINE_H
#define _DAK_SCRIPT_LLVM_IR_LINE_H
#include "arg.h"
#include "instruction.h"
#include <dak_std/vector.h>

namespace dak_script
{
class LLVM_IR_Line
{
public:
	LLVM_IR_Line(const LLVM_IR_Instruction instr) : m_instruction{instr} {}

	LLVM_IR_Arg_Type get_type()
	{
		return static_cast<LLVM_IR_Arg_Type>(
		    0b11100000 & static_cast<unsigned char>(m_instruction));
	}
	// identifier, maybe held externally?

	const LLVM_IR_Instruction m_instruction;
};

class LLVM_IR_Line_BOP : public LLVM_IR_Line
{
public:
	LLVM_IR_Line_BOP(const LLVM_IR_Instruction instr, LLVM_IR_Value l,
			 LLVM_IR_Value r)
	    : LLVM_IR_Line{instr}, m_lhs{l}, m_rhs{r}
	{
	}

	LLVM_IR_Value m_lhs;
	LLVM_IR_Value m_rhs;
};

class LLVM_IR_Line_UOP : public LLVM_IR_Line
{
};

} // namespace dak_script

#endif