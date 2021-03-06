#ifndef _DAK_SCRIPT_LLVM_IR_INSTRUCTION_H
#define _DAK_SCRIPT_LLVM_IR_INSTRUCTION_H
namespace dak_script
{

/*

first 3 bits are type mask


000 - unary
001 - binary

010 - allocation
011 - load/store
100 - terminator
101 -
110 -
111 -

*/
enum LLVM_IR_Instruction_Type
{
	LLVM_IR_INSTRUCTION_TYPE_UOP = 0b00000000,
	LLVM_IR_INSTRUCTION_TYPE_BOP = 0b00100000,
};

enum LLVM_IR_Instruction
{
	// terminator
	LLVM_IR_INSTRUCTION_RET,
	LLVM_IR_INSTRUCTION_SWITCH,
	LLVM_IR_INSTRUCTION_INDIRECTBR,
	LLVM_IR_INSTRUCTION_INVOKE,
	LLVM_IR_INSTRUCTION_CALLBR,
	LLVM_IR_INSTRUCTION_RESUME,
	LLVM_IR_INSTRUCTION_CATCHWITCH,
	LLVM_IR_INSTRUCTION_CATCHRET,
	LLVM_IR_INSTRUCTION_CLEANUPRET,
	LLVM_IR_INSTRUCTION_UNREACHABLE,

	// unary
	LLVM_IR_INSTRUCTION_FNEG,

	// binary
	LLVM_IR_INSTRUCTION_ADD = LLVM_IR_INSTRUCTION_TYPE_BOP & 0,
	LLVM_IR_INSTRUCTION_SUB,
	LLVM_IR_INSTRUCTION_MUL,
	LLVM_IR_INSTRUCTION_SDIV,
	LLVM_IR_INSTRUCTION_UDIV,

	LLVM_IR_INSTRUCTION_FADD,
	LLVM_IR_INSTRUCTION_FSUB,
	LLVM_IR_INSTRUCTION_FMUL,
	LLVM_IR_INSTRUCTION_FDIV,

	LLVM_IR_INSTRUCTION_UREM,
	LLVM_IR_INSTRUCTION_SREM,
	LLVM_IR_INSTRUCTION_FREM,

	// bitwise binary (grouped with above)
	LLVM_IR_INSTRUCTION_SHL,
	LLVM_IR_INSTRUCTION_LSHR,
	LLVM_IR_INSTRUCTION_ASHR,
	LLVM_IR_INSTRUCTION_AND,
	LLVM_IR_INSTRUCTION_OR,
	LLVM_IR_INSTRUCTION_XOR = LLVM_IR_INSTRUCTION_TYPE_BOP & 17,

	// vector
	LLVM_IR_INSTRUCTION_EXTRACTELEMENT,
	LLVM_IR_INSTRUCTION_INSERTELEMENT,
	LLVM_IR_INSTRUCTION_SHUFFLEVECTOR,

	// aggregate
	LLVM_IR_INSTRUCTION_EXTRACTVALUE,
	LLVM_IR_INSTRUCTION_INSERTVALUE,

	// memory access and addressing
	LLVM_IR_INSTRUCTION_ALLOCA,
	LLVM_IR_INSTRUCTION_LOAD,
	LLVM_IR_INSTRUCTION_STORE,
	LLVM_IR_INSTRUCTION_FENCE,
	LLVM_IR_INSTRUCTION_CMPXCHG,
	LLVM_IR_INSTRUCTION_ATOMICRMW,
	LLVM_IR_INSTRUCTION_GETELEMENTPTR,

	// conversion
	LLVM_IR_INSTRUCTION_TRUNC,
	LLVM_IR_INSTRUCTION_SEXT,
	LLVM_IR_INSTRUCTION_FPTRUNC,
	LLVM_IR_INSTRUCTION_FPEXT,
	LLVM_IR_INSTRUCTION_FPTOUI,
	LLVM_IR_INSTRUCTION_FPTOSI,
	LLVM_IR_INSTRUCTION_UITOFP,
	LLVM_IR_INSTRUCTION_SITOFP,
	LLVM_IR_INSTRUCTION_PTRTOINT,
	LLVM_IR_INSTRUCTION_INTTOPTR,
	LLVM_IR_INSTRUCTION_BITCAST,
	LLVM_IR_INSTRUCTION_ADDRSPACECAST,

	// other
	LLVM_IR_INSTRUCTION_ICMP,
	LLVM_IR_INSTRUCTION_FCMP,
	LLVM_IR_INSTRUCTION_PHI,
	LLVM_IR_INSTRUCTION_SELECT,
	LLVM_IR_INSTRUCTION_FREEZE,
	LLVM_IR_INSTRUCTION_CALL,
	LLVM_IR_INSTRUCTION_VA_ARG,
	LLVM_IR_INSTRUCTION_LANDINGPAD,
	LLVM_IR_INSTRUCTION_CATCHPAD,
	LLVM_IR_INSTRUCTION_CLEANUPPAD,

};

/*


bop:



*/
} // namespace dak_script
#endif