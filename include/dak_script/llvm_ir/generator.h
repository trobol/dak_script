#ifndef _DAK_SCRIPT_LLVM_IR_GENERATOR_H
#define _DAK_SCRIPT_LLVM_IR_GENERATOR_H

#include "instruction.h"
#include "module.h"
#include <dak_std/string.h>
#include <dak_std/vector.h>
#include <fstream>
#include <initializer_list>

namespace dak_script
{
class Parsed_Module;
class AST_Statement;
class AST_Expression;
class AST_Statement_Block;
class LLVM_IR_Context;

/*
Generator:

Will output a module that can be serialized into LLVM IR (in text or eventually
bitcode) Holds settings like debug and metadata settings Uses LLVM_IR_Builder to
create the args

*/

class LLVM_IR_Generator
{
	// TODO settings
	LLVM_IR_Module *m_ir_module;

	LLVM_IR_Context *m_current_context;

private:
	void process_block(AST_Statement_Block *block);
	LLVM_IR_Value proccess_statement(AST_Statement *statement);

	LLVM_IR_Value proccess_declaration(AST_Statement *statement);

	LLVM_IR_Value proccess_expression(AST_Expression *expr,
					  dak_std::string result);

	LLVM_IR_Value proccess_bop_expression(AST_Expression *expr,
					      dak_std::string result);

	// void process_function(AST_Function *func);

	void flatten_expression(dak_std::vector<AST_Expression *> &list,
				AST_Expression *node);

public:
	LLVM_IR_Module *generate(Parsed_Module *);
};

} // namespace dak_script
#endif