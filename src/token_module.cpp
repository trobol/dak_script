#include <dak_script/token_module.h>

namespace dak_script
{
Token_Module::Token_Module(dak_std::vector<Token> &t,
			   dak_std::vector<Token_Pos> &p,
			   dak_std::vector<Token_Literal> &l,
			   dak_std::vector<dak_std::string> &i)
    : m_tokens{std::move(t)}, m_positions{std::move(p)}, m_literals{std::move(l)},
      m_identifiers{std::move(i)}

{
}

Token_Module::~Token_Module()
{
	for (const Token_Literal &l : m_literals)
	{
		if (l.type == LITERAL_TYPE_STRING)
		{
			delete[] l.string_val;
		}
	}
}

const Token_Literal Token_Module::get_literal(const Token& t) const {
	_dak_assert(t.type == TOKEN_TYPE_LITERAL);
	return m_literals[t.index];
}

const dak_std::string& Token_Module::get_identifier(const Token& t) const {
	_dak_assert(t.type == TOKEN_TYPE_IDENTIFIER);
	return m_identifiers[t.index];
}


 Token_Literal Token_Module::get_literal(Token t) {
	_dak_assert(t.type == TOKEN_TYPE_LITERAL);
	return m_literals[t.index];
}

 dak_std::string& Token_Module::get_identifier(Token t)  {
	_dak_assert(t.type == TOKEN_TYPE_IDENTIFIER);
	return m_identifiers[t.index];
}
} // namespace dak_script
