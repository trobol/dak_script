
#include <dak_script/parser.h>
#include <stdarg.h>

namespace dak_script
{

void syntax_error(Token_Pos &pos, const char *fmt, ...)
{
	char buffer[500];
	sprintf(buffer, "Syntax error at %i:%i, %s\n", pos.line_number,
		pos.character_number, fmt);
	va_list argptr;
	va_start(argptr, fmt);
	vprintf(buffer, argptr);
	va_end(argptr);
}

// AST_Type *Parser::find_type(dak_std::string &name) {}

Parsed_Module *Parser::parse()
{
	m_parsed_module = new Parsed_Module();
	m_current_block = new AST_Statement_Block();
	m_parsed_module->top_block = m_current_block;
	Token &tok = peek_token();

	AST_Statement *statement = parse_next_statement();
	do
	{
		statement = parse_next_statement();

		if (statement != nullptr)
		{
			m_current_block->statements.push_back(statement);
		}
	} while (!m_eof);

	return m_parsed_module;
}

AST_Statement *Parser::parse_struct()
{
	AST_Statement_Block *block = new AST_Statement_Block();
	block->parent = m_current_block;
	m_current_block = block;
}

AST_Statement *Parser::parse_type_statement()
{
	Token &tok = pop_n_peek_token();
	if (tok.type != TOKEN_TYPE_IDENTIFIER)
	{
		// TODO SYNTAX ERROR
		return nullptr;
	}
	AST_Expression *expr = parse_next_expression();
}
AST_Statement *Parser::parse_next_statement()
{
	Token &tok = peek_token();
	if (tok.type == TOKEN_TYPE_TOKEN)
	{
		switch (tok.value)
		{
			case TOKEN_KEYWORD_FUNC:
				return parse_func_dec();
			case '}':
				end_block();
				return nullptr;
			case TOKEN_EOF:
				m_eof = true;
				return nullptr;
			default:
				pop_token();
				break;
		}
	}
	else if (tok.type == TOKEN_TYPE_IDENTIFIER)
	{
		dak_std::string &name = m_token_module.identifiers[tok.index];
		Token &next_tok = peek_token(1);
		if (next_tok.type == TOKEN_TYPE_TOKEN)
		{
			switch (next_tok.value)
			{
				case '(':
					return parse_void_fuc_statement(name);
				case ':':
					return parse_dec_statement(name);
				case '=':
					return parse_assign_statement(name);
				case '.':
					// TODO handle dot operator
					pop_token();
					break;

				case '{':
					// TODO object construction
					pop_token();
					break;
				case '[':
					// TODO array access
					pop_token();
					break;
				case '*':
				case '/':
				case '+':
				case '-':
					// TODO math operation
					// assignment (+=...)
					pop_token();
					break;
				default:
					// TODO syntax error
					pop_token();
					break;
			}
		}
		else
		{
			pop_token();
		}
	}
	else
	{
		pop_token();
		// TODO SYNTAX ERROR
	}
}

void Parser::end_block()
{
	if (m_current_block->parent == nullptr)
	{
		syntax_error(m_token_module.positions[m_index],
			     "unexpected '}' (end of block) after %s",
			     token_value_to_name(peek_token(-1).value));
	}
	m_current_block = m_current_block->parent;
}
AST_Variable *Parser::find_variable(dak_std::string &name)
{
	AST_Statement_Block *block = m_current_block;

	while (block != nullptr)
	{
		AST_Variable *v = block->find_variable(name);
		if (v != nullptr)
		{
			return v;
		}
		block = block->parent;
	}
}

AST_Expression *Parser::parse_func_expr(dak_std::string &name) {}
AST_Expression *Parser::parse_num_expr() {}
AST_Expression *Parser::parse_paren_expr() {}

AST_TY
AST_Function *Parser::parse_func_dec()
{
	Token &tok = pop_n_peek_token();
	if (tok.type != TOKEN_TYPE_IDENTIFIER)
	{
		// TODO SYNTAX ERROR
		return nullptr;
	}
	dak_std::string &name = m_token_module.identifiers[tok.index];

	AST_Function *func = m_current_block->add_function(name);

	func->parent = m_current_block;

	tok = pop_n_peek_token();

	if (tok.type != TOKEN_TYPE_TOKEN)
	{
		// TODO SYNTAX ERROR
		syntax_error(m_token_module.positions[m_index],
			     "expected '(' got %s",
			     token_type_to_name(tok.type));
	}
	else if (tok.value != TOKEN_OPEN_PAREN)
	{
		// TODO SYNTAX ERROR
		syntax_error(m_token_module.positions[m_index],
			     "expected '(' got %s",
			     token_value_to_name(tok.value));
	}
	// (name: Type, name: Type)
	while (true)
	{
		Token &name_tok = pop_n_peek_token();
		if (name_tok.type != TOKEN_TYPE_IDENTIFIER)
		{
			// TODO SYNTAX ERROR
			syntax_error(m_token_module.positions[m_index],
				     "expected identifer got %s",
				     token_type_to_name(name_tok.type));
			return nullptr;
		}
		Token colon = pop_n_peek_token();
		if (colon != TOKEN_COLON)
		{
			// TODO SYNTAX ERROR
			syntax_error(m_token_module.positions[m_index],
				     "Syntax error, expected colon");
			return nullptr;
		}

		Token &type_tok = pop_n_peek_token();
		if (type_tok.type != TOKEN_TYPE_IDENTIFIER)
		{
			// TODO SYNTAX ERROR
			syntax_error(m_token_module.positions[m_index],
				     "expected identifer got %s",
				     token_type_to_name(type_tok.type));
			return nullptr;
		}

		AST_Variable *param = func->add_parameter(name);

		Token punct = pop_n_peek_token();
		if (punct.type == TOKEN_TYPE_TOKEN)
		{
			if (punct.value == TOKEN_CLOSE_PAREN)
			{
				break;
			}
			else if (punct.value != TOKEN_COMMA)
			{
				// TODO SYNTAX ERROR
				syntax_error(m_token_module.positions[m_index],
					     "expected comma got %s",
					     token_value_to_name(punct.value));
				return nullptr;
			}
		}
		else
		{
			// TODO SYNTAX ERROR
			syntax_error(m_token_module.positions[m_index],
				     "expected token got %s",
				     token_type_to_name(punct.type));
			return nullptr;
		}
		pop_token();
	}

	parse_block();

	m_current_block = func;
}

void Parser::parse_block()
{
	Token &tok = peek_token();
	while (tok != TOKEN_CLOSE_BRACE && tok != TOKEN_EOF)
	{
		parse_next_statement();
		tok = peek_token();
	}

	pop_token();
}

AST_Expression *Parser::parse_next_expression()
{

	Token &tok = peek_token();
	if (tok.type == TOKEN_TYPE_TOKEN)
	{
		switch (tok.value)
		{
			case TOKEN_EOF:
				// TODO EOF
				break;
			default:
				pop_token();
				break;
		}
	}
	else if (tok.type == TOKEN_TYPE_IDENTIFIER)
	{
		dak_std::string &name = m_token_module.identifiers[tok.index];
		Token &next_tok = peek_token(1);
		if (next_tok.type == TOKEN_TYPE_IDENTIFIER)
		{
			// TODO process syntax error
			printf("Error identifier: %s unexpected", name);
		}
		else
		{
			switch (next_tok.value)
			{
				case '=':
					parse_assign_statement(name);
					break;
				case ':':
					parse_dec_statement(name);
					break;
				case '.':
					// TODO handle dot operator
					pop_token();
					break;
				case '(':
					parse_func_expr(name);
					break;
				case '{':
					// TODO object construction
					pop_token();
					break;
				case '[':
					// TODO array access
					pop_token();
					break;
				case '*':
				case '/':
				case '+':
				case '-':
					// TODO math operation
					// assignment (+=...)
					pop_token();
					break;
				default:
					// TODO syntax error
					pop_token();
					break;
			}
		}
	}
	else
	{
		pop_token();
	}
}
AST_Declaration_Statement *Parser::parse_dec_statement(dak_std::string &name)
{
	AST_Variable *var = m_current_block->add_variable(name);
	AST_Declaration_Statement *var_dec =
	    new AST_Declaration_Statement(var, nullptr);
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
		m_current_block->statements.push_back(var_dec);
	}
}
AST_Assign_Statement *Parser::parse_assign_statement(dak_std::string &name)
{
	AST_Variable *var = find_variable(name);

	// pop off identifier and =
	pop_token(2);

	AST_Expression *value = parse_next_expression();

	AST_Assign_Statement *var_assign = new AST_Assign_Statement(var, value);

	if (peek_token() == TOKEN_BREAK)
	{
		m_current_block->statements.push_back(var_assign);
	}
}
AST_Statement *Parser::parse_void_fuc_statement(dak_std::string &name)
{
	pop_token(2);
}

} // namespace dak_script
