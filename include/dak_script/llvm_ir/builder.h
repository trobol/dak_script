#ifndef _DAK_SCRIPT_LLVM_IR_BUILDER_H
#define _DAK_SCRIPT_LLVM_IR_BUILDER_H

#include "generator.h"

namespace dak_script
{
class LLVM_IR_Builder
{
private:
	// settings
public:
	LLVM_IR_Value make_int();
	LLVM_IR_Arg make_type();
	LLVM_IR_Arg make_float();
	LLVM_IR_Arg make_reg_ref();
};
} // namespace dak_script

#endif