#ifndef _DAK_SCRIPT_PARSER_H
#define _DAK_SCRIPT_PARSER_H

#include <dak_script/abstract_syntax_tree.h>
#include <dak_script/reserves.h>
#include <dak_std/vector.h>
#include <string>
#include <unordered_map>

namespace dak_script
{

class Parser
{
	size_t m_index;

	Token_Module &m_token_module;

	dak_std::linear_allocator m_allocator;

	Scope_Block *m_current_scope;

	Parsed_Module *m_parsed_module;

public:
	Parser(Token_Module &token_module)
	    : m_token_module{token_module}, m_allocator(500)
	{
	}
	Parsed_Module *parse();

private:
	ExprAST *next();
	ExprAST *parse_num_expr();
	ExprAST *parse_paren_expr();
	void parse_function_dec_expr();
	ExprAST *parse_function_call_expr();
	ExprAST *parse_var_dec_expr();
	ExprAST *parse_var_assign_expr();

	Token &peek_token() { return m_token_module.tokens[m_index]; }
	Token &peek_token(size_t i)
	{
		return m_token_module.tokens[m_index + i];
	}
	Token &pop_token()
	{
		++m_index;
		return m_token_module.tokens[m_index];
	};
	Token &pop_token(size_t i)
	{
		m_index += i;
		return m_token_module.tokens[m_index];
	}

	Type *find_type(const char *identifier, const Scope_Block &context);
};

} // namespace dak_script

#endif