#include <dak_script/lexetize.h>
#include <dak_script/character_type.h>

#include <iostream>

namespace dak::script
{



    bool scan_for_character(const char character, const char* contents, size_t length, size_t& end) {
        while(end < length) {
            end++;
            if(contents[end] == character)
                return true;
        }
        return false;
    }

    bool parse_string(const char mark, const char* contents, size_t length, size_t& end) {
        while(end < length) {
            end++;
            if(contents[end] == mark) {
                if(end > 0 && contents[end-1] == '\\') {
                } else {
                    break;
                }
            } else if(contents[end] == '\n')
                break;
        }
    }

    
    std::vector<lexeme> lexetize(const char* contents, size_t length) {
       
        size_t lineCount;
        std::vector<lexeme> lexemes;
        lexeme_type current_type;

        size_t start = 0;
        for (size_t end = 0; end < length; end++) {
            const char c = contents[end];
            
    
            if (c == '/') {
                if(contents[end+1] == '/') {
                    if(start != end) {
                        lexemes.push_back({contents+start, end-start});
                    }
                    scan_for_character('\n', contents, length, end);
                    start = end+1;

            
                } else if (contents[end+1] == '*') {
                    if(start != end) {
                        lexemes.push_back({contents+start, end-start});
                    }
                    end+=2;
                    while(end < length-1) {
                        end++;
                        if (contents[end] == '*' && contents[end+1] == '/') {
                            break;
                        } else if(contents[end] == '\n') {
                            lineCount++;
            
                        }
                    }
                    end++;
                    start = end+1;
                }
                
            } else {
                character_type c_type = get_character_type(c);
                switch (c_type)
                {
                    case character_type::newline:
                        lineCount++;
                    case character_type::whitespace:
                        if(start != end) {
                            lexemes.push_back({contents+start, end-start, current_type});
                        }
                        lexeme_type::unknown;
                        start = end+1;
                        break;
                    case character_type::bracket:
                    case character_type::punctuation:
                        if(start != end) {
                            lexemes.push_back({contents+start, end-start, current_type});
                        }
                        lexemes.push_back({contents+end, 1, lexeme_type::control});
                        current_type = lexeme_type::unknown;
                        start = end+1;
                        break;

                    case character_type::operation:
                        if(start != end && current_type != lexeme_type::operation) {
                            lexemes.push_back({contents+start, end-start, current_type});
                            start = end;
                        }
                        current_type = lexeme_type::operation;
                        break;
                    case character_type::quotation:
                        if(start != end) {
                            lexemes.push_back({contents+start, end-start, current_type});
                            start = end;
                        }
                        parse_string(c, contents, length, end);
                        lexemes.push_back({contents+start, end-start+1, lexeme_type::word});
                        current_type = lexeme_type::unknown;
                        start = end+1;
                        break;
                    default:
                        if(start != end && current_type == lexeme_type::operation) {
                            lexemes.push_back({contents+start, end-start, current_type});
                            start = end;
                        }
                        current_type = lexeme_type::word;
                        break;
                }
            }
        }
        

        return lexemes;
    }
   
} 