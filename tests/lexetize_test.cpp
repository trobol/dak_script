#include <catch2/catch.hpp>

#include <dak_script/lexetize.h>
#include <dak_script/reader.h>

#include <iostream>

using namespace dak::script;

const const char *expected_lexemes[] = {"class", "TestComponent", "extends", "Component", "{",
                                        "public", "int", "a", "=", "0", ";",
                                        "public", "bool", "b", ";",
                                        "float", "c", ";",
                                        "hook", "function", "(", "int", "p", ")", "{",
                                        "float", "d", "=", "10", ";",
                                        "d", "+=", "5", ";",
                                        "string", "asd", "=", "\"hello\"", ";",
                                        "if", "(", "d", "&&", "des", ")",
                                        "return", "test", ";",
                                        "for", "(", "int", "i", "=", "0", ";", "i", "<", "20", ";", "i", "++", ")",
                                        "{",
                                        "\"\\\"\"",
                                        "}",
                                        "0x1230",
                                        "}",
                                        "}"};

TEST_CASE("Lexetize Text", "[main]")
{

    Reader reader;

    reader.open("./tests/example_file.txt");

    std::vector<lexeme> lexemes = lexetize(reader.contents(), reader.length());

    for (int i = 0; i < lexemes.size(); i++)
    {

        for (int j = 0; j < lexemes[i].length; j++)
        {
            std::cout << lexemes[i].ptr[j];
            REQUIRE(lexemes[i].ptr[j] == expected_lexemes[i][j]);
        }
    }
}
