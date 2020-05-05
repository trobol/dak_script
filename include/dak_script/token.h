#ifndef _DAK_SCRIPT_TOKEN_H
#define _DAK_SCRIPT_TOKEN_H

#include <cstdint>
class File;

namespace dak::script
{

enum Token_Type
{

    TOKEN_INDENT = 256,
    TOKEN_NUMBER,
    TOKEN_STRING,

    TOKEN_PLUSEQUALS,
    TOKEN_MINUSEQUALS,

    TOKEN_KEYWORD_IF,
    TOKEN_KEYWORD_ELSE,
    TOKEN_KEYWORD_THEN,
    TOKEN_KEYWORD_DEFER,
    TOKEN_KEWORD_STRUCT,
    TOKEN_KEYWORD_TYPE,
    TOKEN_KEYWORD_UNINITIALIZED,
    TOKEN_BREAK,

    TOKEN_ERROR,

    TOKEN_EOF,
};

struct Token
{
    Token_Type type = TOKEN_ERROR;
    union {
        unsigned long long integer_value;
        float float_value;
        double double_value;
        struct
        {
            uint64_t size;
            uint8_t *data;
        } string_value;
    };
};

} // namespace dak::script

#endif