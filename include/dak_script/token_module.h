#ifndef _DAK_SCRIPT_TOKEN_MODULE_H
#define _DAK_SCRIPT_TOKEN_MODULE_H

#include <dak_script/token.h>
#include <dak_std/vector.h>
#include <vector>

namespace dak_script
{
struct Token_Module
{
	dak_std::vector<Token> tokens;
	dak_std::vector<Token_Pos> positions;
	dak_std::vector<Token_Literal> literals;
	dak_std::vector<dak_std::string> identifiers;

	Token_Module(dak_std::vector<Token> &t, dak_std::vector<Token_Pos> &p,
		     dak_std::vector<Token_Literal> &l,
		     dak_std::vector<dak_std::string> &i);

	Token_Module(const Token_Module &) = delete;

	~Token_Module();
};
} // namespace dak_script

#endif