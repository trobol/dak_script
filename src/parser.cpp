
#include <dak_script/parser.h>

namespace dak_script
{

Type *Parser::find_type(const char *identifier, const Scope_Block &context) {}

Parsed_Module *Parser::parse()
{
	m_parsed_module = new Parsed_Module();
	Token &tok = peek_token();
	bool eof = false;
	while (!eof)
	{
		if (tok.type == TOKEN_TYPE_TOKEN)
		{
			switch (tok.value)
			{
				case TOKEN_KEYWORD_FUNCTION:
					parse_function_dec_expr();
					break;
				case TOKEN_EOF:
					eof = true;
					break;
				default:
					break;
			}
		}
		else if (TOKEN_TYPE_IDENTIFIER)
		{
			Token &next_tok = peek_token(1);
			if (next_tok.type == TOKEN_TYPE_IDENTIFIER)
			{
				// TODO process syntax error
			}
			else
			{
				switch (next_tok.value)
				{
					case '=':
						parse_var_assign_expr();
					case ':':
						parse_var_dec_expr();
						break;
					case '.':
						// TODO handle dot operator
						break;
					case '(':
						parse_function_call_expr();
						break;
					case '{':
						// TODO object construction
						break;
					case '[':
						// TODO array access
						break;
					case '*':
					case '/':
					case '+':
					case '-':
						// TODO math operation
						// assignment (+=...)
						break;
					default:
						// TODO syntax error
						break;
				}
			}
		}
	}
}

ExprAST *Parser::next() {}

ExprAST *Parser::parse_num_expr() {}
ExprAST *Parser::parse_paren_expr() {}
ExprAST *Parser::parse_function_call_expr() {}
ExprAST *Parser::parse_var_dec_expr()
{
	const char *name = m_token_module.buffer + peek_token().index;
	Variable *var = m_current_scope->add_variable(name);
	VariableDecExprAST *var_dec =
	    m_allocator.allocate<VariableDecExprAST>(var, nullptr);
	pop_token();
	// type given
	if (peek_token().type == TOKEN_TYPE_IDENTIFIER)
	{

		var->is_type_inferred = false;

		// TODO type
		pop_token();
	}

	if (peek_token() == TOKEN_EQUALS)
	{
		var->is_type_inferred = true;
	}

	if (peek_token() == TOKEN_BREAK)
	{
		return var_dec;
	}
}

void Parser::parse_function_dec_expr() {}

} // namespace dak_script
