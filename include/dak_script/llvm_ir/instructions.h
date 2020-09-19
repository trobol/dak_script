#ifndef _DAK_SCRIPT_LLVM_IR_INSTRUCTIONS_H
#define _DAK_SCRIPT_LLVM_IR_INSTRUCTIONS_H
namespace dak_script
{
enum LLVM_IR_Instructions
{
	LLVM_IR_RET,
	LLVM_IR_RET,
	LLVM_IR_SWITCH,
	LLVM_IR_INDIRECTBR,
	LLVM_IR_INVOKE,
	LLVM_IR_CALLBR,
	LLVM_IR_RESUME,
	LLVM_IR_CATCHWITCH,
	LLVM_IR_CATCHRET,
	LLVM_IR_CLEANUPRET,
	LLVM_IR_UNREACHABLE,

	LLVM_IR_FNEG,

	LLVM_IR_ADD,
	LLVM_IR_FADD,
	LLVM_IR_SUB,
	LLVM_IR_FSUB,
	LLVM_IR_MUL,
	LLVM_IR_FMUL,
	LLVM_IR_UDIV,
	LLVM_IR_SDIV,
	LLVM_IR_FDIV,
	LLVM_IR_UREM,
	LLVM_IR_SREM,
	LLVM_IR_FREM,

	LLVM_IR_SHL,
	LLVM_IR_LSHR,
	LLVM_IR_ASHR,
	LLVM_IR_AND,
	LLVM_IR_OR,
	LLVM_IR_XOR,

	LLVM_IR_EXTRACTELEMENT,
	LLVM_IR_INSERTELEMENT,
	LLVM_IR_SHUFFLEVECTOR,
	LLVM_IR_EXTRACTVALUE,
	LLVM_IR_INSERTVALUE,

	LLVM_IR_ALLOCA,
	LLVM_IR_LOAD,
	LLVM_IR_STORE,
	LLVM_IR_FENCE,
	LLVM_IR_CMPXCHG,
	LLVM_IR_ATOMICRMW,
	LLVM_IR_GETELEMENTPTR,
};
}
#endif