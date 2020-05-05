#ifndef _DAK_SCRIPT_LEXETIZE_H
#define _DAK_SCRIPT_LEXETIZE_H

#include <vector>

namespace dak::script
{

enum struct Lexeme_Type
{

    LEXEME_UNKNOW,
    LEXEME_OPERATION,
    LEXEME_IDENTIFIER,
    LEXEME_CONTROL,
    LEXEME_LITERAL
};

struct Lexeme
{

    const char *ptr;
    size_t length;
    Lexeme_Type type;
};

std::vector<Lexeme> lexetize(const char *contents, size_t length);

} // namespace dak::script

#endif