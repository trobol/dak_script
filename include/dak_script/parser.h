#ifndef _DAK_SCRIPT_PARSER_H
#define _DAK_SCRIPT_PARSER_H

#include "token_module.h"
#include <dak_script/ast.h>
#include <dak_std/vector.h>
#include <string>
#include <unordered_map>

namespace dak_script
{

struct Parsed_Module
{
	// unused for now
	// dak_std::vector<Scope_Block *> imports;
	dak_std::string path;
	// exports
	AST_Statement_Block *top_block;

	Parsed_Module() {}
};

class Parser
{
	size_t m_index;

	Token_Module &m_token_module;

	AST_Base_Block *m_current_block;

	bool m_eof;

	dak_std::string m_filename;

public:
	Parser(Token_Module &token_module, dak_std::string filename)
	    : m_index{0}, m_token_module{token_module}, m_eof{false},
	      m_filename{filename}
	{
	}
	Parsed_Module *parse();

private:
	AST_Variable *find_variable(dak_std::string &);

	AST_Expression *parse_next_expression();
	AST_Expression *parse_func_expr(dak_std::string &);
	AST_Expression *parse_num_expr();
	AST_Expression *parse_paren_expr();
	AST_Expression *parse_struct_construct_expr(dak_std::string &);
	AST_Expression *parse_bop_expr();
	AST_Expression *parse_uop_expr();

	AST_Statement *parse_next_statement();
	AST_Statement *parse_struct(AST_Type_Ref);
	AST_Statement *parse_type_statement();
	AST_Declaration_Statement *parse_dec_statement(dak_std::string &);
	AST_Assign_Statement *parse_assign_statement(dak_std::string &);
	AST_Statement *parse_void_fuc_statement(dak_std::string &);

	AST_Function *parse_func_dec();

	void syntax_error(Token_Pos &pos, const char *fmt, ...);

	void end_block();

	void parse_block();

	Token &peek_token() { return m_token_module.get_token(m_index); }
	Token &peek_token(size_t i)
	{
		return m_token_module.get_token(m_index + i);
	}
	Token &pop_n_peek_token()
	{
		++m_index;
		return peek_token();
	}
	void pop_line()
	{
		Token tok;
		do
		{
			tok = peek_token();
			if (tok == TOKEN_EOF)
			{
				m_eof = true;
				return;
			}
			pop_token();
		} while (tok != TOKEN_BREAK);
	}
	void pop_token() { ++m_index; }
	void pop_token(size_t i) { m_index += i; }
};

} // namespace dak_script

#endif