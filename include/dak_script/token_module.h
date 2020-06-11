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
	const char *buffer;
	uint32_t buffer_size;

	Token_Module(dak_std::vector<Token> &t, dak_std::vector<Token_Pos> &p,
		     dak_std::vector<Token_Literal> &l, const char *b,
		     uint32_t bs);

	Token_Module(const Token_Module &) = delete;

	~Token_Module();
};
} // namespace dak_script

#endif