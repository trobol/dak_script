#ifndef _DAK_SCRIPT_LLVM_IR_GENERATOR_H
#define _DAK_SCRIPT_LLVM_IR_GENERATOR_H

#include "context.h"
#include "module.h"
#include <fstream>

namespace dak_script
{
class Parsed_Module;
class AST_Statement;
class AST_Expression;
class LLVM_IR_Generator
{
	// TODO settings
	std::ofstream m_stream;
	unsigned m_tmp_index;

private:
	void proccess_statement(AST_Statement *statement);

	void proccess_declaration(AST_Statement *statement);

	void proccess_expression(AST_Expression *expr, dak_std::string result);

	void proccess_bop_expression(AST_Expression *expr,
				     dak_std::string result);

	// void process_function(AST_Function *func);

public:
	LLVM_IR_Module *generate(Parsed_Module *);
};
} // namespace dak_script
#endif