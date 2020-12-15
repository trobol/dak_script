#ifndef _DAK_SCRIPT_TOKEN_H
#define _DAK_SCRIPT_TOKEN_H

#include <cstdint>
class File;



namespace dak::script {

    class Token {
        private:
            uint16_t mLineNum;
            uint16_t charNum;
            
            Token();
            Token(const Token& token);
        public:
            enum Type {
                literal,
                reserved,
                identifier,
                type 
            };
           
    };
}


#endif