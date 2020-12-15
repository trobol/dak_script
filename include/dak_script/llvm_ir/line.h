#ifndef _DAK_SCRIPT_LLVM_IR_LINE_H
#define _DAK_SCRIPT_LLVM_IR_LINE_H
#include "instruction.h"
#include "value.h"
#include <dak_std/vector.h>

namespace dak_script
{

enum LLVM_IR_Line_Type
{
	LLVM_IR_LINE_TYPE_UOP,
	LLVM_IR_LINE_TYPE_BOP,
	LLVM_IR_LINE_TYPE_ALLOC,
	LLVM_IR_LINE_TYPE_STORE
};

enum LLVM_IR_Line_BOP_Instr
{
	LLVM_IR_LINE_BOP_INSTR_ADD,
	LLVM_IR_LINE_BOP_INSTR_SUB,
	LLVM_IR_LINE_BOP_INSTR_MUL,
	LLVM_IR_LINE_BOP_INSTR_SDIV,
	LLVM_IR_LINE_BOP_INSTR_UDIV,

	LLVM_IR_LINE_BOP_INSTR_FADD,
	LLVM_IR_LINE_BOP_INSTR_FSUB,
	LLVM_IR_LINE_BOP_INSTR_FMUL,
	LLVM_IR_LINE_BOP_INSTR_FDIV,

	LLVM_IR_LINE_BOP_INSTR_UREM,
	LLVM_IR_LINE_BOP_INSTR_SREM,
	LLVM_IR_LINE_BOP_INSTR_FREM,

	// bitwise binary
	LLVM_IR_LINE_BOP_INSTR_SHL,
	LLVM_IR_LINE_BOP_INSTR_LSHR,
	LLVM_IR_LINE_BOP_INSTR_ASHR,
	LLVM_IR_LINE_BOP_INSTR_AND,
	LLVM_IR_LINE_BOP_INSTR_OR,
	LLVM_IR_LINE_BOP_INSTR_XOR

};

class LLVM_IR_Line_BOP
{
public:
	LLVM_IR_Line_BOP(LLVM_IR_Line_BOP_Instr instr, LLVM_IR_Value l,
			 LLVM_IR_Value r)
	    : m_instr{instr}, m_lhs{l}, m_rhs{r}
	{
	}
	LLVM_IR_Line_BOP(const LLVM_IR_Line_BOP &) = default;
	LLVM_IR_Line_BOP_Instr m_instr;
	LLVM_IR_Value m_lhs;
	LLVM_IR_Value m_rhs;
};

class LLVM_IR_Line_Alloc
{
public:
	LLVM_IR_Line_Alloc(LLVM_IR_Type type, int num_elements, int align)
	    : m_type{type}, m_num_elements{num_elements}, m_align{align}
	{
	}

	LLVM_IR_Type m_type;
	int m_num_elements;
	int m_align;
};

class LLVM_IR_Line_Store
{
};

class LLVM_IR_Line_UOP
{
public:
};

class LLVM_IR_Line
{
public:
	const LLVM_IR_Line_Type m_type;
	union {
		LLVM_IR_Line_UOP m_uop;
		LLVM_IR_Line_Alloc m_alloc;
		LLVM_IR_Line_Store m_store;
		LLVM_IR_Line_BOP m_bop;
	};

public:
	LLVM_IR_Line() = default;
	LLVM_IR_Line(const LLVM_IR_Line &) = default;
	LLVM_IR_Line(LLVM_IR_Line_UOP v)
	    : m_type{LLVM_IR_LINE_TYPE_UOP}, m_uop{v}
	{
	}

	LLVM_IR_Line(LLVM_IR_Line_BOP v)
	    : m_type{LLVM_IR_LINE_TYPE_BOP}, m_bop{v}
	{
	}

	LLVM_IR_Line(LLVM_IR_Line_Alloc v)
	    : m_type{LLVM_IR_LINE_TYPE_ALLOC}, m_alloc{v}
	{
	}

	LLVM_IR_Line(LLVM_IR_Line_Store v)
	    : m_type{LLVM_IR_LINE_TYPE_STORE}, m_store{v}
	{
	}
};

} // namespace dak_script

#endif