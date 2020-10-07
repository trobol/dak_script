#ifndef _DAK_SCRIPT_LLVM_IR_ARG_H
#define _DAK_SCRIPT_LLVM_IR_ARG_H

#include <dak_std/assert.h>

namespace dak_script
{
/*
should float/int size be part of the enum?

without: 7 values 3 bits
		 with the other 5 bits could hold up to 31

with: 5 non-number
	  3 float
	  6 i1 i8 i16 i32 i64 i128

*/
enum LLVM_IR_Arg_Type
{
	LLVM_IR_ARG_TYPE_VOID,

	LLVM_IR_ARG_TYPE_FLOAT,
	LLVM_IR_ARG_TYPE_INT,

	LLVM_IR_ARG_TYPE_LABEL,
	LLVM_IR_ARG_TYPE_POINTER,

	LLVM_IR_ARG_TYPE_TYPE,

	LLVM_IR_ARG_TYPE_REG_REF,

	/*
	unsure about these
	LLVM_IR_ARG_TYPE_STRUCT,
	LLVM_IR_ARG_TYPE_ARRAY,
	LLVM_IR_ARG_TYPE_AGGREGATE
	*/

};

// <result> = add <ty> <op1>, <op2>          ; yields ty:result
// %val = add i32 a, 10

class LLVM_IR_Type
{
private:
	LLVM_IR_Arg_Type m_type : 3;
	unsigned int m_size : 4;
	bool m_is_unsigned : 1;

public:
	LLVM_IR_Type(LLVM_IR_Arg_Type type, bool un = false)
	    : m_type{type}, m_is_unsigned{un}
	{
	}
	bool is_unsigned() { return m_is_unsigned; }
};

class LLVM_IR_Value
{
private:
	LLVM_IR_Type m_type;
	union {
		double arg_float;
		unsigned long long int arg_int;
		struct Label_Value
		{
			// TODO figure this out
		} arg_label;
		struct Reg_Ref
		{
			unsigned int index;
		} arg_reg;
	} m_data;

public:
	LLVM_IR_Value(double f, unsigned int size)
	    : m_type{LLVM_IR_ARG_TYPE_FLOAT}, m_data{.arg_float = f}
	{
	}

	LLVM_IR_Value(unsigned long long int i, unsigned int size)
	    : m_type{LLVM_IR_ARG_TYPE_INT}, m_data{.arg_int = i}
	{
	}

	LLVM_IR_Value(const LLVM_IR_Value &a)
	    : m_type{a.m_type}, m_data{a.m_data}
	{
	}

	const LLVM_IR_Type type() { return m_type; }

	double float_type() { return m_data.arg_float; }

	unsigned long long int arg_int() { return m_data.arg_int; }
};

} // namespace dak_script
#endif