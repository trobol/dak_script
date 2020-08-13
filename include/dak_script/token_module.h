#ifndef _DAK_SCRIPT_TOKEN_MODULE_H
#define _DAK_SCRIPT_TOKEN_MODULE_H

#include <dak_script/token.h>
#include <dak_std/vector.h>
#include <vector>

namespace dak_script
{
class Token_Module
{
	dak_std::vector<Token> m_tokens;
	dak_std::vector<Token_Pos> m_positions;
	dak_std::vector<Token_Literal> m_literals;
	dak_std::vector<dak_std::string> m_identifiers;

public:
	Token_Module(dak_std::vector<Token> &t, dak_std::vector<Token_Pos> &p,
		     dak_std::vector<Token_Literal> &l,
		     dak_std::vector<dak_std::string> &i);

	Token_Module(const Token_Module &) = delete;

	const Token_Literal get_literal(const Token& t) const;
	const dak_std::string& get_identifier(const Token& t) const;

	Token_Literal get_literal(Token t);
	dak_std::string& get_identifier(Token t);

	dak_std::vector<Token>& tokens() {
		return m_tokens;
	}

	Token& get_token(size_t i) {
		return m_tokens[i];
	}

	Token_Pos& pos(size_t i) {
		return m_positions[i];
	}

	
	~Token_Module();
};
} // namespace dak_script

#endif