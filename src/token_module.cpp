#include <dak_script/token_module.h>

namespace dak_script
{
Token_Module::Token_Module(dak_std::vector<Token> &t,
			   dak_std::vector<Token_Pos> &p,
			   dak_std::vector<Token_Literal> &l, const char *b,
			   uint32_t bs)
    : tokens{std::move(t)}, positions{std::move(p)}, literals{std::move(l)},
      buffer{b}, buffer_size{bs}

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

	buffer_size = 0;
	delete[] buffer;
}
} // namespace dak_script
