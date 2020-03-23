#include <catch2/catch.hpp>

#include <dak_script/lexetize.h>
#include <dak_script/reader.h>

#include <iostream>

using namespace dak::script;


std::string get_type_str(lexeme_type type) {
    switch (type)
    {
        case lexeme_type::unknown:
            return "unknown";
        case lexeme_type::operation:
            return "operation";
        case lexeme_type::word:
            return "word";
        case lexeme_type::control:
            return "control";
        default:
            break;
    }
}



TEST_CASE( "Lexetize Text", "[main]" ) {
    

    Reader reader;

    reader.open("./tests/example_file.txt");

    std::vector<lexeme> lexemes = lexetize(reader.contents(), reader.length());


    for(int i = 0; i < lexemes.size(); i++) {
        
        for(int j = 0; j < lexemes[i].length; j++) {
            std::cout << lexemes[i].ptr[j];
        }
        std::cout << " : " << get_type_str(lexemes[i].type) << '\n';
    }

}

