#include <dak_script/token_module.h>

namespace dak_script
{
Token_Module::Token_Module(dak_std::vector<Token> &t,
			   dak_std::vector<Token_Pos> &p,
			   dak_std::vector<Token_Literal> &l,
			   dak_std::vector<dak_std::string> &i)
    : tokens{std::move(t)}, positions{std::move(p)}, literals{std::move(l)},
      identifiers{std::move(i)}

{
}

Token_Module::~Token_Module()
{
	for (const Token_Literal &l : literals)
	{
		if (l.type == LITERAL_TYPE_STRING)
		{
			delete[] l.string_val;
		}
	}
}
} // namespace dak_script
