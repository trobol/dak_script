#ifndef _DAK_SCRIPT_TOKEN_H
#define _DAK_SCRIPT_TOKEN_H

#include <cstdint>
class File;



namespace dak::script {
    //https://github.com/jakisa/stork/blob/part01/source/tokens.hpp
    enum struct ReservedToken {
        inc,
        dec,
            
        add,
        sub,
        concat,
        mul,
        div,
        idiv,
        mod,
            
        bitwise_not,
        bitwise_and,
        bitwise_or,
        bitwise_xor,
        shiftl,
        shiftr,
            
        assign,
            
        add_assign,
        sub_assign,
        concat_assign,
        mul_assign,
        div_assign,
        idiv_assign,
        mod_assign,

        and_assign,
        or_assign,
        xor_assign,
        shiftl_assign,
        shiftr_assign,
        
        logical_not,
        logical_and,
        logical_or,
        
        eq,
        ne,
        lt,
        gt,
        le,
        ge,
        
        question,
        colon,
        
        comma,
        
        semicolon,
        
        open_round,
        close_round,
        
        open_curly,
        close_curly,
        
        open_square,
        close_square,

        kw_if,
        kw_else,
        kw_elif,

        kw_switch,
        kw_case,
        kw_default,

        kw_for,
        kw_while,
        kw_do,

        kw_break,
        kw_continue,
        kw_return,

        kw_hook,

        kw_public,
        kw_private
     
    };

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