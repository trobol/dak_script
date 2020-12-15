#include <dak_script/llvm_ir/context.h>
#include <dak_script/llvm_ir/module.h>
#include <dak_script/llvm_ir/serializer.h>
#include <fstream>

namespace dak_script
{
void LLVM_IR_Serializer::serialize(LLVM_IR_Module *ir_module)
{
	std::ofstream output("example_ir.ld");
	for (LLVM_IR_Context *context : ir_module->m_functions)
	{
		serialize_context(output, context);
	}
}

void LLVM_IR_Serializer::serialize_context(std::ofstream &output,
					   LLVM_IR_Context *context)
{

	output << "define i32 test_func() {\n";
	m_reg_index = 1;

	for (const LLVM_IR_Line &line : context->m_lines)
	{
		serialize_line(output, line);
	}

	output << "}\n";
}

void LLVM_IR_Serializer::serialize_line(std::ofstream &output,
					const LLVM_IR_Line &line)
{
	switch (line.m_type)
	{
		case LLVM_IR_LINE_TYPE_ALLOC:
		{
			output << '%' << m_reg_index << " = alloca i32, align "
			       << line.m_alloc.m_align << '\n';
			m_reg_index++;
			break;
		}
		case LLVM_IR_LINE_TYPE_STORE:

			break;

		case LLVM_IR_LINE_TYPE_BOP:
		{
			const char *instr;
			switch (line.m_bop.m_instr)
			{
				case LLVM_IR_LINE_BOP_INSTR_ADD:
					instr = "add";
					break;
				case LLVM_IR_LINE_BOP_INSTR_MUL:
					instr = "mul";
					break;
				case LLVM_IR_LINE_BOP_INSTR_SUB:
					instr = "sub";
					break;
				case LLVM_IR_LINE_BOP_INSTR_UDIV:
					instr = "udiv";
					break;
				case LLVM_IR_LINE_BOP_INSTR_SDIV:
					instr = "sdiv";
					break;
				default:
					instr = "error";
					break;
			}
			output << '%' << m_reg_index << " = " << instr
			       << " nsw i32 "
			       << "rhs"
			       << ", "
			       << "lhs" << '\n';
			m_reg_index++;
		}
		break;

		case LLVM_IR_LINE_TYPE_UOP:
			/* code */
			break;
		default:
			break;
	}
}

} // namespace dak_script
