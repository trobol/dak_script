#ifndef _DAK_SCRIPT_LLVM_IR_GENERATOR_H
#define _DAK_SCRIPT_LLVM_IR_GENERATOR_H

#include "../ast_type.h"
#include "instruction.h"
#include "module.h"
#include "value.h"
#include <dak_std/string.h>
#include <dak_std/vector.h>
#include <fstream>
#include <initializer_list>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <map>
#include <utility>
#include <vector>

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

class AST_Variable;
class AST_Function;
class LLVM_IR_Generator
{
private:
	// TODO: settings
public:
	llvm::Module *generate(Parsed_Module *, llvm::LLVMContext &);
};

class LLVM_IR_Generator_Impl
{
private:
	llvm::LLVMContext &m_context;
	llvm::IRBuilder<> m_builder;

	// TODO: right now all identifiers are global :/

	std::vector<std::pair<AST_Variable *, llvm::AllocaInst *>>
	    m_variable_stack;
	llvm::Module *m_ir_module;
	Parsed_Module *m_module;

	llvm::Function *m_current_function;

	LLVM_IR_Generator_Impl(Parsed_Module *module,
			       llvm::LLVMContext &context)
	    : m_module{module}, m_context{context},
	      m_ir_module{new llvm::Module("main", m_context)},
	      m_builder(m_context)
	{
	}

	void process_statement_block(AST_Statement *statement);
	void process_statement(AST_Statement *statement);

	void process_assignment(AST_Statement *statement);
	void process_function_block(AST_Statement *statement);

	llvm::FunctionType *get_function_type(AST_Function *function);
	llvm::Type *get_type(AST_Type_Ref type);

	void process_return(AST_Statement *statement);
	void process_declaration(AST_Statement *statement);

	llvm::Value *process_expression(AST_Expression *expr);

	llvm::Value *process_bop_expression(AST_Expression *expr);

	llvm::Value *process_literal_expression(AST_Expression *expr);

	llvm::Value *process_variable_expression(AST_Expression *expr);

	llvm::AllocaInst *create_alloca_entry(llvm::Type *type,
					      llvm::StringRef name);

	void flatten_expression(dak_std::vector<AST_Expression *> &list,
				AST_Expression *node);
	friend class LLVM_IR_Generator;
};

} // namespace dak_script
#endif