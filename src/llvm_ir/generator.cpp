#include <dak_script/llvm_ir/generator.h>
#include <dak_script/parser.h>
#include <dak_std/filesystem.h>

namespace dak_script
{
LLVM_IR_Module *LLVM_IR_Generator::generate(Parsed_Module *parsed_module)
{
	LLVM_IR_Module *ir_module = new LLVM_IR_Module();
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
	return ir_module;
}

void LLVM_IR_Generator::proccess_statement(AST_Statement *statement)
{
	switch (statement->m_statement_type)
	{
		case AST_STATEMENT_TYPE_DECLARATION:
			proccess_declaration(statement);
			break;
		case AST_STATEMENT_TYPE_ASSIGN:

			break;
		default:
			// TODO ERROR
			break;
	}
}

void LLVM_IR_Generator::proccess_declaration(AST_Statement *statement)
{
	AST_Declaration_Statement *decl_statement =
	    dynamic_cast<AST_Declaration_Statement *>(statement);
	if (decl_statement->value != nullptr)
	{
		dak_std::string name = decl_statement->variable->name;
		proccess_expression(decl_statement->value, name);
	}
}

void LLVM_IR_Generator::proccess_expression(AST_Expression *expr,
					    dak_std::string result)
{
	// TODO add the rest of the expressions
	switch (expr->type)
	{
		case AST_EXPRESSION_TYPE_BOP:
			proccess_bop_expression(expr, result);
			break;
		default:
			break;
	}
}

void LLVM_IR_Generator::proccess_bop_expression(AST_Expression *expr,
						dak_std::string result)
{
	AST_BOP_Expression *bop_expr = dynamic_cast<AST_BOP_Expression *>(expr);
}
// void LLVM_IR_Generator::process_function(AST_Function *func) {}

} // namespace dak_script