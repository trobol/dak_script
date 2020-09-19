
#include <dak_script/parser.h>
#include <stdarg.h>

#include <dak_script/ast_expression.h>

namespace dak_script
{

Parsed_Module *Parser::parse()
{
	Parsed_Module *parsed_module = new Parsed_Module();
	AST_Statement_Block *top_block = new AST_Statement_Block();
	parsed_module->top_block = top_block;
	parsed_module->path = m_filename;
	m_current_block = top_block;
	Token &tok = peek_token();

	AST_Statement *statement = parse_next_statement();
	do
	{
		statement = parse_next_statement();

		if (statement != nullptr)
		{
			m_current_block->add_statement(statement);
		}
	} while (!m_eof);

	return parsed_module;
}

// AST_Type *Parser::find_type(dak_std::string &name) {}

void Parser::syntax_error(Token_Pos &pos, const char *fmt, ...)
{
	char buffer[500];
	sprintf(buffer, "Syntax error at %s:%i:%i, %s\n", m_filename,
		pos.line_number, pos.character_number, fmt);
	va_list argptr;
	va_start(argptr, fmt);
	vprintf(buffer, argptr);
	va_end(argptr);
}

AST_Statement *Parser::parse_struct(AST_Type *type)
{
	AST_Struct_Block *block = new AST_Struct_Block(type);
	block->parent = m_current_block;
	m_current_block = block;
	pop_token(2);
	return nullptr;
}

AST_Statement *Parser::parse_type_statement()
{
	Token &tok = pop_n_peek_token();
	if (tok.type != TOKEN_TYPE_IDENTIFIER)
	{
		// TODO SYNTAX ERROR
		return nullptr;
	}
	dak_std::string &name = m_token_module.get_identifier(tok);
	AST_Type *type = m_current_block->add_type(name);
	tok = pop_n_peek_token();
	if (tok == TOKEN_KEYWORD_STRUCT)
	{
		parse_struct(type);
		return nullptr;
	}
	else
	{
		// TODO SYNTAX ERROR
	}
	return nullptr;
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
			case TOKEN_KEYWORD_TYPE:
				return parse_type_statement();
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
		dak_std::string &name = m_token_module.get_identifier(tok);
		Token &next_tok = peek_token(1);
		if (next_tok.type == TOKEN_TYPE_TOKEN)
		{
			switch (next_tok.value)
			{
				case '(':
					return parse_void_fuc_statement(name);
				case ':':
					pop_token(2);
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
	return nullptr;
}

void Parser::end_block()
{
	if (m_current_block->parent != nullptr)
	{
		m_current_block = m_current_block->parent;
	}
	else
	{
		syntax_error(m_token_module.pos(m_index - 1),
			     "unexpected '}' (end of block) after %s",
			     token_value_to_name(peek_token(-1).value));
	}
	pop_token();
}
AST_Variable *Parser::find_variable(dak_std::string &name)
{
	AST_Base_Block *block = m_current_block;

	while (block != nullptr)
	{
		AST_Variable *v = block->find_variable(name);
		if (v != nullptr)
		{
			return v;
		}
		block = block->parent;
	}
	return nullptr;
}

AST_Expression *Parser::parse_func_expr(dak_std::string &name)
{
	return nullptr;
}
AST_Expression *Parser::parse_num_expr() { return nullptr; }
AST_Expression *Parser::parse_paren_expr() { return nullptr; }

AST_Expression *Parser::parse_bop_expr() {}

AST_Expression *Parser::parse_struct_construct_expr(dak_std::string &name)
{
	// get type
	AST_Type *type = m_current_block->find_type(name);

	AST_Construct_Expression *struct_expr =
	    new AST_Construct_Expression(type);

	dak_std::string prop;
	// Type{var_name = var_value };

	pop_token();
	while (true)
	{
		Token tok = peek_token();
		if (tok.type == TOKEN_TYPE_IDENTIFIER)
		{
			prop =
			    dak_std::string(m_token_module.get_identifier(tok));
		}
		else
		{
			syntax_error(m_token_module.pos(m_index),
				     "expected identifier, got %s",
				     token_to_string(tok, &m_token_module));
		}

		tok = pop_n_peek_token();
		if (tok != TOKEN_EQUALS)
		{

			syntax_error(m_token_module.pos(m_index),
				     "exprected =, got %s",
				     token_to_string(tok, &m_token_module));
		}

		tok = pop_n_peek_token();
		if (tok.type == TOKEN_TYPE_IDENTIFIER)
		{
			AST_Expression *expr = parse_next_expression();

			struct_expr->properties.push_back(prop);
			struct_expr->values.push_back(expr);
		}
		else
		{
			syntax_error(m_token_module.pos(m_index),
				     "exprected identifier, got %s",
				     token_to_string(tok, &m_token_module));
		}

		tok = pop_n_peek_token();
		if (tok.type == TOKEN_TYPE_TOKEN)
		{
			if (tok.value == TOKEN_COMMA)
			{
				pop_token();
				continue;
			}
			else if (tok.value == '}')
			{
				pop_token();
				break;
			}
		}

		syntax_error(m_token_module.pos(m_index),
			     "exprected identifier, got %s",
			     token_to_string(tok, &m_token_module));
	}
	return nullptr;
}

AST_Function *Parser::parse_func_dec()
{
	Token &tok = pop_n_peek_token();
	if (tok.type != TOKEN_TYPE_IDENTIFIER)
	{
		// TODO SYNTAX ERROR
		return nullptr;
	}
	dak_std::string &func_name = m_token_module.get_identifier(tok);

	AST_Function *func = m_current_block->add_function(func_name);

	func->parent = m_current_block;

	tok = pop_n_peek_token();

	if (tok != TOKEN_OPEN_PAREN)
	{
		// TODO SYNTAX ERROR
		syntax_error(m_token_module.pos(m_index), "expected '(' got %s",
			     token_to_string(tok, &m_token_module));
	}
	// parse parameters
	// (name: Type, name: Type)
	tok = peek_token(1);
	if (tok != TOKEN_CLOSE_PAREN)
	{
		while (true)
		{
			Token &name_tok = pop_n_peek_token();
			if (name_tok.type != TOKEN_TYPE_IDENTIFIER)
			{
				// TODO SYNTAX ERROR
				syntax_error(m_token_module.pos(m_index),
					     "expected identifer got %s",
					     token_type_to_name(name_tok.type));
				return nullptr;
			}
			Token colon = pop_n_peek_token();
			if (colon != TOKEN_COLON)
			{
				// TODO SYNTAX ERROR
				syntax_error(m_token_module.pos(m_index),
					     "Syntax error, expected colon");
				return nullptr;
			}

			Token &type_tok = pop_n_peek_token();
			if (type_tok.type != TOKEN_TYPE_IDENTIFIER)
			{
				// TODO SYNTAX ERROR
				syntax_error(m_token_module.pos(m_index),
					     "expected identifer got %s",
					     token_type_to_name(type_tok.type));
				return nullptr;
			}
			dak_std::string &param_name =
			    m_token_module.get_identifier(type_tok);
			AST_Variable *param = func->add_parameter(param_name);

			Token punct = pop_n_peek_token();
			if (punct.type == TOKEN_TYPE_TOKEN)
			{
				if (punct.value == TOKEN_CLOSE_PAREN)
				{
					pop_token();
					break;
				}
				else if (punct.value != TOKEN_COMMA)
				{
					// TODO SYNTAX ERROR
					syntax_error(
					    m_token_module.pos(m_index),
					    "expected comma got %s",
					    token_value_to_name(punct.value));
					return nullptr;
				}
			}
			else
			{
				// TODO SYNTAX ERROR
				syntax_error(m_token_module.pos(m_index),
					     "expected token got %s",
					     token_type_to_name(punct.type));
				return nullptr;
			}
			pop_token();
		}
	}
	else
	{
		pop_token(2);
	}

	tok = peek_token();
	if (tok.type == TOKEN_TYPE_IDENTIFIER)
	{
		dak_std::string &type_name = m_token_module.get_identifier(tok);
		AST_Type *type = m_current_block->find_type(type_name);
		func->add_return(type);
	}
	else if (tok == TOKEN_OPEN_PAREN)
	{
		pop_token();
		// parse return type(s)
		while (true)
		{
			Token &type_name = peek_token();
			if (type_name.type == TOKEN_TYPE_IDENTIFIER)
			{
				dak_std::string &type_name =
				    m_token_module.get_identifier(tok);
				AST_Type *type =
				    m_current_block->find_type(type_name);
				func->add_return(type);
			}
			else
			{
				syntax_error(
				    m_token_module.pos(m_index),
				    "unexpected %s in function declaration ",
				    token_to_string(type_name,
						    &m_token_module));
				return nullptr;
			}

			Token &punct = pop_n_peek_token();
			if (punct == TOKEN_CLOSE_PAREN)
			{
				break;
			}
			else if (punct != TOKEN_COMMA)
			{
				syntax_error(
				    m_token_module.pos(m_index),
				    "unexpected %s in function returns "
				    "declaration",
				    token_to_string(punct, &m_token_module));

				return nullptr;
			}
		}
	}
	else if (tok != TOKEN_OPEN_BRACKET)
	{
		// Syntax error
	}
	m_current_block = func;
	return nullptr;
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

AST_Expression *Parser::parse_uop_expr() {}

// iterative expression parser
AST_Expression *Parser::parse_next_expression()
{
	dak_std::vector<AST_Expression *> expression_stack;

	AST_Expression *last_expr = nullptr;

	while (true)
	{
		// parse first token
		Token &tok = peek_token();
		AST_Expression *expr = nullptr;
		if (tok.type == TOKEN_TYPE_LITERAL)
		{
			expr = new AST_Literal_Expression(
			    m_token_module.get_literal(tok));
		}
		else if (tok.type == TOKEN_TYPE_TOKEN)
		{

			switch (tok.value)
			{
				case TOKEN_EOF:
					m_eof = true;
					// todo, ensure expression is fully
					// closed
				case TOKEN_BREAK:
					if (expression_stack.size() > 0)
						// TODO syntax error
						return nullptr;
					else
						return last_expr;
				case '(':

					expression_stack.push_back(
					    new AST_Paren_Expression());
					break;
				case ')':
				{
					if (expression_stack.size() > 0 &&
					    expression_stack.back()->type ==
						AST_EXPRESSION_TYPE_PAREN)
					{
						AST_Paren_Expression
						    *paren_expr = dynamic_cast<
							AST_Paren_Expression *>(
							expression_stack
							    .back());

						paren_expr->expr = last_expr;

						expr = paren_expr;
						expression_stack.pop_back();
					}
					else
					{
						// TODO syntax error
					}
				}
				break;
				case '!':
					expr = new AST_UOP_Expression();
					break;
				case '.':
					// TODO handle dot operator
					break;
				case '+':
				case '-':
				case '*':
				case '/':

					if (last_expr == nullptr)
					{
						// it is a uop
					}
					else
					{
						AST_BOP_Expression *bop_expr =
						    new AST_BOP_Expression(
							tok.value);
						bop_expr->lhs = last_expr;
						expr = nullptr;
						expression_stack.push_back(
						    bop_expr);
					}
					break;

				default:
					syntax_error(
					    m_token_module.pos(m_index),
					    "unhandled token %c", tok.value);
					return nullptr;
			}
		}
		else if (tok.type == TOKEN_TYPE_IDENTIFIER)
		{
			dak_std::string &name =
			    m_token_module.get_identifier(tok);

			AST_Variable *var = find_variable(name);
			expr = new AST_Variable_Expression(var);
		}

		if (expression_stack.size() > 0 && expr != nullptr)
		{
			AST_Expression *back = expression_stack.back();
			if (back->type == AST_EXPRESSION_TYPE_BOP)
			{
				AST_BOP_Expression *bop_expr =
				    dynamic_cast<AST_BOP_Expression *>(back);
				bop_expr->rhs = expr;
				expr = back;
				expression_stack.pop_back();
			}
			else if (back->type == AST_EXPRESSION_TYPE_UOP)
			{
			}
		}

		last_expr = expr;
		pop_token();
	}
	return nullptr;
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

	var_dec->value = parse_next_expression();
	return var_dec;
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
		m_current_block->add_statement(var_assign);
	}
	return nullptr;
}
AST_Statement *Parser::parse_void_fuc_statement(dak_std::string &name)
{
	pop_token(2);
	return nullptr;
}

} // namespace dak_script
