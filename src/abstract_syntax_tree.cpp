
#include <dak_script/abstract_syntax_tree.h>

namespace dak_script
{

Token &Parser::get_token() { return m_token_module.tokens[m_index]; }

Parsed_Module Parser::parse()
{
	Token &tok = get_token();
	bool eof = false;
	while (!eof)
	{
		if (tok.type == TOKEN_TYPE_TOKEN)
		{
			switch (tok.value)
			{
				case TOKEN_KEYWORD_FUNCTION:
					parse_function_expr();
					break;
				case TOKEN_EOF:
					eof = true;
					break;
				default:
					break;
			}
		}
	}
}

ExprAST *Parser::next() {}

ExprAST *Parser::parse_num_expr() {}
ExprAST *Parser::parse_paren_expr() {}
ExprAST *Parser::parse_function_expr()
{
	FunctionAST func;
	m_index++;
	if (get_token() == TOKEN_OPEN_PAREN)
	{
		// parse member function
	}
}

ExprAST *Parser::parse_var_expr() {}

} // namespace dak_script
