#include <dak_script/llvm_ir/context.h>
#include <dak_script/llvm_ir/generator.h>
#include <dak_script/llvm_ir/value.h>
#include <dak_script/parser.h>
#include <dak_std/filesystem.h>
#include <iostream>

namespace dak_script
{

llvm::Value *log_error_value(const char *str)
{
	std::cout << str << '\n';
	return nullptr;
}

llvm::Module *LLVM_IR_Generator::generate(Parsed_Module *parsed_module,
					  llvm::LLVMContext &context)
{
	LLVM_IR_Generator_Impl generator(parsed_module, context);

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
		process_statement(statement);
	}
	m_stream << "}";
	m_stream.close();
	*/

	// process_block(parsed_module->top_block);

	AST_Statement_Block *block = parsed_module->top_block;

	generator.process_statement(parsed_module->top_block);
	// m_ir_module->m_functions.push_back(m_current_context);

	return generator.m_ir_module;
}

// TODO: does not work with nested functions
void LLVM_IR_Generator_Impl::process_statement_block(AST_Statement *statement)
{
	AST_Statement_Block *block =
	    static_cast<AST_Statement_Block *>(statement);
	for (AST_Function *f : block->functions())
	{
		process_function_block(f);
	}

	for (AST_Statement *s : block->statements())
	{
		process_statement(s);
	}
}

llvm::AllocaInst *
LLVM_IR_Generator_Impl::create_alloca_entry(llvm::Type *type,
					    llvm::StringRef name)
{
	llvm::IRBuilder<> tmp_builder(
	    &m_current_function->getEntryBlock(),
	    m_current_function->getEntryBlock().begin());
	return tmp_builder.CreateAlloca(type, nullptr, name);
}

void LLVM_IR_Generator_Impl::process_function_block(AST_Statement *statement)
{
	llvm::Function *parent_function = m_current_function;

	AST_Function *func_statement = static_cast<AST_Function *>(statement);
	AST_Statement_Block *block_statement =
	    static_cast<AST_Statement_Block *>(statement);
	// create function arguments
	llvm::FunctionType *func_type = get_function_type(func_statement);

	llvm::Function *func =
	    llvm::Function::Create(func_type, llvm::Function::ExternalLinkage,
				   func_statement->name.data(), m_ir_module);
	m_current_function = func;
	llvm::BasicBlock *basic_block =
	    llvm::BasicBlock::Create(m_context, "entry", func);
	m_builder.SetInsertPoint(basic_block);
	// Set names for all arguments.
	unsigned i = 0;
	for (auto &arg : func->args())
		arg.setName(func_statement->parameters[i++]->name.data());

	// record stack index

	// create stack space for arguments
	for (size_t i = 0; i < func_statement->parameters.size(); i++)
	{
		AST_Variable *var = func_statement->parameters[i];
		llvm::Argument *param = func->getArg(i);
		llvm::AllocaInst *alloca =
		    create_alloca_entry(param->getType(), param->getName());
		// Store the initial value into the alloca.
		m_builder.CreateStore(param, alloca);

		m_variable_stack.push_back({var, alloca});
	}

	process_statement_block(statement);

	m_current_function = parent_function;
}

llvm::FunctionType *
LLVM_IR_Generator_Impl::get_function_type(AST_Function *function)
{
	std::vector<llvm::Type *> arg_types(function->parameters.size());
	for (size_t i = 0; i < function->parameters.size(); i++)
	{
		arg_types[i] = get_type(function->parameters[i]->type);
	}

	llvm::Type *return_type = function->returns.size() > 0
				      ? get_type(function->returns[0])
				      : llvm::Type::getVoidTy(m_context);

	return llvm::FunctionType::get(return_type, arg_types, false);
}

llvm::Type *LLVM_IR_Generator_Impl::get_type(AST_Type_Ref type)
{

	switch (type.get_kind())
	{

		case TYPE_KIND_U8:
			return llvm::Type::getInt8Ty(m_context);
		case TYPE_KIND_U16:
			return llvm::Type::getInt16Ty(m_context);
		case TYPE_KIND_U32:
			return llvm::Type::getInt32Ty(m_context);
		case TYPE_KIND_U64:
			return llvm::Type::getInt64Ty(m_context);
		case TYPE_KIND_I8:
			return llvm::Type::getInt8Ty(m_context);
		case TYPE_KIND_I16:
			return llvm::Type::getInt16Ty(m_context);
		case TYPE_KIND_I32:
			return llvm::Type::getInt32Ty(m_context);
		case TYPE_KIND_I64:
			return llvm::Type::getInt64Ty(m_context);
		case TYPE_KIND_F32:
			return llvm::Type::getFloatTy(m_context);
		case TYPE_KIND_F64:
			return llvm::Type::getDoubleTy(m_context);

		case TYPE_KIND_UNKNOWN:
		case TYPE_KIND_STRUCT:
		case TYPE_KIND_ENUM:
		case TYPE_KIND_ALIAS:
			return llvm::Type::getVoidTy(m_context);
	}
}

void LLVM_IR_Generator_Impl::process_statement(AST_Statement *statement)
{
	switch (statement->m_statement_type)
	{
		case AST_STATEMENT_TYPE_DECLARATION:
			process_declaration(statement);
			break;
		case AST_STATEMENT_TYPE_ASSIGN:
			process_assignment(statement);
			break;
		case AST_STATEMENT_TYPE_STATEMENT_BLOCK:
			process_statement_block(statement);
			break;
		case AST_STATEMENT_TYPE_FUNCTION_BLOCK:
			process_function_block(statement);
			break;
		case AST_STATEMENT_TYPE_RETURN:
			process_return(statement);
			break;
		default:
			// TODO ERROR
			break;
	}
}

void LLVM_IR_Generator_Impl::process_return(AST_Statement *statement)
{
	AST_Return_Statement *ret =
	    static_cast<AST_Return_Statement *>(statement);
	llvm::Value *val = process_expression(ret->value);
	m_builder.CreateRet(val);
}

void LLVM_IR_Generator_Impl::process_declaration(AST_Statement *statement)
{

	AST_Declaration_Statement *decl_statement =
	    static_cast<AST_Declaration_Statement *>(statement);

	// TODO: this isnt declaring a variable right now
	AST_Variable *var = decl_statement->variable;

	llvm::Value *val = process_expression(decl_statement->value);

	llvm::AllocaInst *alloca =
	    create_alloca_entry(val->getType(), val->getName());
	// Store the initial value into the alloca.
	m_builder.CreateStore(val, alloca);
	m_variable_stack.push_back({var, alloca});
}

void LLVM_IR_Generator_Impl::process_assignment(AST_Statement *statement) {}

llvm::Value *LLVM_IR_Generator_Impl::process_expression(AST_Expression *expr)
{
	dak_std::vector<AST_Expression *> list;

	// TODO add the rest of the expressions
	switch (expr->type)
	{
		case AST_EXPRESSION_TYPE_BOP:
			return process_bop_expression(expr);
		case AST_EXPRESSION_TYPE_LITERAL:
			return process_literal_expression(expr);
		case AST_EXPRESSION_TYPE_PAREN:
			return process_expression(
			    static_cast_expression<AST_Paren_Expression>(expr)
				->expr);
		case AST_EXPRESSION_TYPE_VARIABLE:
			return process_variable_expression(expr);
		default:
			return log_error_value("unsupported expression type");
	}
}

llvm::Value *
LLVM_IR_Generator_Impl::process_variable_expression(AST_Expression *expr)
{
	AST_Variable_Expression *var_expr =
	    static_cast_expression<AST_Variable_Expression>(expr);
	AST_Variable *var = var_expr->ptr;

	llvm::AllocaInst *alloc = nullptr;
	// TODO: find a non linear method
	for (auto end = &m_variable_stack.back();
	     end >= &m_variable_stack.front(); end--)
	{
		if ((size_t)end->first == (size_t)var)
		{
			alloc = end->second;
			std::cout << var->name << ' ' << end->first->name
				  << '\n';
			break;
		}
	}

	if (alloc)
		return m_builder.CreateLoad(alloc);
	else
		return log_error_value("could not find variable");
}

llvm::Value *
LLVM_IR_Generator_Impl::process_literal_expression(AST_Expression *expr)
{
	AST_Literal_Expression *lit_expr =
	    static_cast_expression<AST_Literal_Expression>(expr);

	switch (lit_expr->literal.type)
	{
		case LITERAL_TYPE_FLOAT:
			return llvm::ConstantFP::get(
			    m_context,
			    llvm::APFloat(lit_expr->literal.float_val));
		case LITERAL_TYPE_UINT:
			return llvm::ConstantInt::get(
			    m_context,
			    llvm::APInt(64, lit_expr->literal.uint_val));
			// TODO: correct number of bits and signed
		case LITERAL_TYPE_STRING:
			return log_error_value("string literals not supported");
			// TODO: support strings
		case LITERAL_TYPE_CHAR:
			return llvm::ConstantInt::get(
			    llvm::Type::getInt8Ty(m_context),
			    lit_expr->literal.char_val);
		default:
			return log_error_value(
			    "unknown literal type"); // TODO: handle errors
	}
}

llvm::Value *
LLVM_IR_Generator_Impl::process_bop_expression(AST_Expression *expr)
{
	AST_BOP_Expression *bop_expr =
	    static_cast_expression<AST_BOP_Expression>(expr);

	llvm::Value *rhs = process_expression(bop_expr->rhs);
	llvm::Value *lhs = process_expression(bop_expr->lhs);

	if (!rhs || !lhs)
		return nullptr;

	switch (bop_expr->bop)
	{
		case AST_BOP_ADD:
			return m_builder.CreateAdd(lhs, rhs, "addtmp");
		case AST_BOP_SUB:
			return m_builder.CreateSub(lhs, rhs, "subtmp");
		case AST_BOP_MULT:
			return m_builder.CreateMul(lhs, rhs, "multmp");
		case AST_BOP_DIV:
			return m_builder.CreateSDiv(lhs, rhs, "divtmp");
		default:
			return log_error_value("unknown bop type");
	}
}
// void LLVM_IR_Generator::process_function(AST_Function *func) {}

} // namespace dak_script