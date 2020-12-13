#include <dak_script/llvm_ir/context.h>
#include <dak_script/llvm_ir/generator.h>
#include <dak_script/llvm_ir/value.h>
#include <dak_script/parser.h>
#include <dak_std/filesystem.h>

namespace dak_script
{
LLVM_IR_Module *LLVM_IR_Generator::generate(Parsed_Module *parsed_module)
{
	m_ir_module = new LLVM_IR_Module();

	/*
	// dak_std::string filename = get_filename(parsed_module->path);
	m_stream.open("output.ll");

	// for now just put everything within a main function

	m_stream << "define i32 @main() {\n";
	AST_Statement_Block *block = parsed_module->top_block;
	for (AST_Variable *var : block->variables())
	{
		const unsigned align = 4;
		m_stream << '%' << var->name << ".addr";
		m_stream << " = alloca"
			 << " i32"
			 << ", align" << align << "\n";
	}
	for (AST_Statement *statement : block->statements())
	{
		proccess_statement(statement);
	}
	m_stream << "}";
	m_stream.close();
	*/

	// process_block(parsed_module->top_block);

	AST_Statement_Block *block = parsed_module->top_block;
	m_current_context = new LLVM_IR_Context();

	for (AST_Statement *s : block->statements())
	{
		proccess_statement(s);
	}

	m_ir_module->m_functions.push_back(m_current_context);

	return m_ir_module;
}

void LLVM_IR_Generator::process_block(AST_Statement_Block *block)
{
	m_current_context = new LLVM_IR_Context();
	for (AST_Function *f : block->functions())
	{
		process_block(f);
	}

	m_ir_module->m_functions.push_back(m_current_context);
}

LLVM_IR_Value LLVM_IR_Generator::proccess_statement(AST_Statement *statement)
{
	switch (statement->m_statement_type)
	{
		case AST_STATEMENT_TYPE_DECLARATION:
			return proccess_declaration(statement);
		case AST_STATEMENT_TYPE_ASSIGN:

			break;
		default:
			// TODO ERROR
			break;
	}
}

LLVM_IR_Value LLVM_IR_Generator::proccess_declaration(AST_Statement *statement)
{
	AST_Declaration_Statement *decl_statement =
	    static_cast<AST_Declaration_Statement *>(statement);

	LLVM_IR_Value alloc = m_current_context->append_line(
	    LLVM_IR_Line_Alloc(LLVM_IR_Type::i32, 1, 4));
	LLVM_IR_Value store =
	    m_current_context->append_line(LLVM_IR_Line_Store());

	if (decl_statement->value != nullptr)
	{
		LLVM_IR_Value value =
		    proccess_expression(decl_statement->value);
	}

	return alloc;
} // namespace dak_script

unsigned int flatten_expression(dak_std::vector<AST_Expression *> &list,
				AST_Expression *expr)
{
	switch (expr->type)
	{
		case AST_EXPRESSION_TYPE_BOP:
		{
			AST_BOP_Expression *bop_expr =
			    static_cast<AST_BOP_Expression *>(expr);
			flatten_expression(list, bop_expr->lhs);
			flatten_expression(list, bop_expr->rhs);
			break;
		}
		case AST_EXPRESSION_TYPE_UOP:
		{
			AST_UOP_Expression *uop_expr =
			    static_cast<AST_UOP_Expression *>(expr);
			flatten_expression(list, uop_expr->expr);
			break;
		}
		default:
			list.push_back(expr);
			break;
	}
}
LLVM_IR_Value LLVM_IR_Generator::proccess_expression(AST_Expression *expr)
{
	dak_std::vector<AST_Expression *> list;

	// TODO add the rest of the expressions
	switch (expr->type)
	{
		case AST_EXPRESSION_TYPE_BOP:
			proccess_bop_expression(expr);
			break;
		default:
			break;
	}
}

LLVM_IR_Value LLVM_IR_Generator::proccess_bop_expression(AST_Expression *expr)
{
	AST_BOP_Expression *bop_expr = static_cast<AST_BOP_Expression *>(expr);

	LLVM_IR_Value rhs = proccess_expression(bop_expr->rhs);
	LLVM_IR_Value lhs = proccess_expression(bop_expr->lhs);

	LLVM_IR_Line_BOP_Instr instr;

	// TODO this doesnt support unsigned integers
	// TODO support floats
	bool is_integer = true;
	if (is_integer)
	{
		instr = static_cast<LLVM_IR_Line_BOP_Instr>(
		    LLVM_IR_LINE_BOP_INSTR_ADD + bop_expr->bop);
	}
	else
	{
		instr = static_cast<LLVM_IR_Line_BOP_Instr>(
		    LLVM_IR_LINE_BOP_INSTR_FADD + bop_expr->bop);
	}

	m_current_context->append_line(LLVM_IR_Line_BOP(instr, rhs, lhs));
}
// void LLVM_IR_Generator::process_function(AST_Function *func) {}

} // namespace dak_script