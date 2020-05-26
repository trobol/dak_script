#include <dak_script/token.h>

#include <unordered_map>

namespace dak_script
{

const std::unordered_map<Token_Value, const char *> token_name_map = {
    {TOKEN_INDENT, "TOKEN_INDENT"},
    {TOKEN_EMPTY, "TOKEN_EMPTY"},
    {TOKEN_NUMBER, "TOKEN_NUMBER"},
    {TOKEN_STRING, "TOKEN_STRING"},
    {TOKEN_PLUSEQUALS, "TOKEN_PLUSEQUALS"},
    {TOKEN_MINUSEQUALS, "TOKEN_MINUSEQUALS"},
    {TOKEN_KEYWORD_IF, "TOKEN_KEYWORD_IF"},
    {TOKEN_KEYWORD_ELSE, "TOKEN_KEYWORD_ELSE"},
    {TOKEN_KEYWORD_THEN, "TOKEN_KEYWORD_THEN"},
    {TOKEN_KEYWORD_DEFER, "TOKEN_KEYWORD_DEFER"},
    {TOKEN_KEYWORD_STRUCT, "TOKEN_KEWORD_STRUCT"},
    {TOKEN_KEYWORD_FUNC, "TOKEN_KEYWORD_FUNC"},
    {TOKEN_KEYWORD_TYPE, "TOKEN_KEYWORD_TYPE"},
    {TOKEN_KEYWORD_UNINITIALIZED, "TOKEN_KEYWORD_UNINITIALIZED"},
    {TOKEN_BREAK, "TOKEN_BREAK"},
    {TOKEN_ERROR, "TOKEN_ERROR"},
    {TOKEN_EOF, "TOKEN_EOF"},
    {TOKEN_OPEN_BRACKET, "{"},
    {TOKEN_CLOSE_BRACKET, "}"},
    {TOKEN_OPEN_BRACE, "["},
    {TOKEN_CLOSE_BRACE, "]"},
    {TOKEN_OPEN_PAREN, "("},
    {TOKEN_CLOSE_PAREN, ")"},
    {TOKEN_COMMA, ","},
    {TOKEN_ASTERISK, "*"},
    {TOKEN_COLON, ":"},
    {TOKEN_EQUALS, "="},
    {TOKEN_SLASH, "/"},
    {TOKEN_AMPERSAND, "&"},
    {TOKEN_LINE_FEED, "LINE FEED"},
    {TOKEN_BACKSLASH, "\\"},
    {TOKEN_SEMICOLON, ";"},
    {TOKEN_QUOTE, "\""},
    {TOKEN_EMPTY, "EMPTY"}};

const char *token_value_to_name(Token_Value t)
{
	auto token_name = token_name_map.find(t);

	if (token_name == token_name_map.end())
	{
		return "UNKNOWN TOKEN";
	}
	else
	{
		return token_name->second;
	}
}

} // namespace dak_script