#ifndef _DAK_SCRIPT_TOKENIZE_H
#define _DAK_SCRIPT_TOKENIZE_H

#include "token.h"
#include "mapped_file.h"

#include <vector>


namespace dak::script {

	
    std::vector<Token> tokenize(const char* file, size_t length);
}



#endif