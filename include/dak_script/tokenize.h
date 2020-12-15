#ifndef _DAK_SCRIPT_TOKENIZE_H
#define _DAK_SCRIPT_TOKENIZE_H

#include "token.h"
#include "mapped_file.h"

#include <vector>
#include "lexetize.h"


namespace dak::script {

    enum struct token_type {
        reserved,
        identifier,
        literal,
        typename
    }

    enum struct reserved_token {

    }

    struct token
    {
        token_type type;
        union {
            reserved_token reserved;
            uint32_t stringIndex;
        }
    };
    
	
    std::vector<Token> tokenize(std::vector<lexeme> lexemes);
}



#endif