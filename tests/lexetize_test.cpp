#include <catch2/catch.hpp>

#include <dak_script/lexetize.h>
#include <dak_script/reader.h>

#include <iostream>

using namespace dak::script;

#include "expectations.h"

const char *expected_lexemes[] = {"class", "TestComponent", "extends", "Component", "{",
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

TEST_CASE("lexetize file", "[lexetize]")
{

    std::vector<lexeme> lexemes = lexetize(expected_text, expected_text_length);

    for (int i = 0; i <  lexemes.size(); i++)
    {

        for (int j = 0; j < lexemes[i].length; j++)
        {
            REQUIRE(lexemes[i].ptr[j] == expected_lexemes[i][j]);
        }
    }
}
