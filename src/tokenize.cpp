#include <dak_script/tokenize.h>
#include <dak_script/character_type.h>

#include <iostream>

namespace dak::script
{

      
    struct substr {
        const char* ptr;
        size_t length;
    };

    struct FilePosition {
        size_t line;
        size_t character;
    };

    struct token_scanner {
        const char* contents;
        size_t length;
        size_t start, end;
        std::vector<substr> lexemes;
        std::vector<FilePosition> positions;
        size_t line;
        const char next() {
            return contents[end];
        }
        const char last() {
            return contents[end-1];
        }

        const char operator[](const size_t i) {
            if(i < 0 || i > length) {
                return NULL;
            }
            return contents[i];
        }
        void flush(){
            if(start != end) {
                lexemes.push_back({contents+start, end-start});
            }
        }
        void flush(size_t offset, size_t length) {

        }
    };

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
                    end++;
                    break;
                }
            } else if(contents[end] == '\n')
                break;
        }
    }

    /*
        Split the file into parseable slices
    */
    
    std::vector<Token> tokenize(const char* contents, size_t length) {
       
        

        size_t start = 0;
        char lastChar = 0;
        for (size_t end = 0; end < length; end++) {
            const char c = contents[end];
            
            
            if (c == '/') {
                if(contents[end+1] == '/') {
                    if(start != end) {
                        raw_tokens.push_back({contents+start, end-start});
                    }
                    scan_for_character('\n', contents, length, end);
                    start = end+1;

            
                } else if (contents[end+1] == '*') {
                    if(start != end) {
                        raw_tokens.push_back({contents+start, end-start});
                    }
                    std::cout << "multi line \n";
                    end+=2;
                    while(end < length-1) {
                        end++;
                        if (contents[end] == '*' && contents[end+1] == '/') {
                            std::cout << "end\n";
                            break;
                        } else if(contents[end] == '\n') {
                            lineCount++;
                            std::cout << "endl\n";
                        }
                        std::cout << "skip\n";
                        
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
                            raw_tokens.push_back({contents+start, end-start});
                        }
                        start = end+1;
                        break;
                    case character_type::bracket:
                    case character_type::punctuation:
                        if(start != end) {
                            raw_tokens.push_back({contents+start, end-start});
                        }
                        raw_tokens.push_back({contents+end, 1});
                        start = end+1;
                        break;

                    case character_type::operation:
                        if(start != end && get_character_type(lastChar) != character_type::operation) {
                            raw_tokens.push_back({contents+start, end-start});
                            start = end;
                        }
                        
                        break;
                    case character_type::quotation:
                        if(start != end) {
                            raw_tokens.push_back({contents+start, end-start});
                            start = end;
                        }
                        parse_string(c, contents, length, end);
                        raw_tokens.push_back({contents+start, end-start});
                        start = end;
                        break;
                    default:
                        if(start != end && get_character_type(lastChar) == character_type::operation) {
                            raw_tokens.push_back({contents+start, end-start});
                            start = end;
                        }
                        break;
                }
            }
            lastChar = c;
        }

        for(int i = 0; i < raw_tokens.size(); i++) {
            for( int j = 0; j < raw_tokens[i].length; j++)
                std::cout << raw_tokens[i].ptr[j];
            std::cout << " | ";
        }



    }

    Token get_token(MappedFile& file, size_t& start, size_t& end);

} 