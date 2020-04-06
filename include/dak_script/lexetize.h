#ifndef _DAK_SCRIPT_LEXETIZE_H
#define _DAK_SCRIPT_LEXETIZE_H

#include <vector>

namespace dak::script
{

enum struct lexeme_type
{
    unknown,
    operation,
    word,
    control,
    literal
};

struct lexeme
{
    const char *ptr;
    size_t length;
    lexeme_type type;
};

std::vector<lexeme> lexetize(const char *contents, size_t length);

} // namespace dak::script

#endif