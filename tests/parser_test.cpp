#include <catch2/catch.hpp>
#include <dak_script/parser.h>
#include <dak_script/file_descriptor.h>
#include <dak_script/mmapped_file.h>
#include <dak_script/lexetize.h>
#include <iostream>

#include "expectations.h"

using namespace dak::script;

std::vector<parsed_unit_type> expected_types = {
	keyword,	//"class",
	identifier, //"TestComponent",
	keyword,	//"extends",
	identifier, //"Component",
	control,	//"{",
	keyword,	//"public",
	identifier, //"int",
	identifier, // "a",
	operation,	// "=",
	literal,	// "0",
	control,	// ";",
	keyword,	// "public",
	identifier, // "bool",
	identifier, // "b",
	control,	// ";",
	identifier, // "float",
	identifier, // "c",
	control,	// ";",
	keyword,	// "hook",
	identifier, // "OnHook",
	control,	// "(",
	identifier, // "int",
	identifier, // "p",
	control,	// ")",
	control,	// "{",
	identifier, // "float",
	identifier, //"d",
	operation,	// "=",
	literal,	// "10",
	control,	// ";",
	identifier, // "d",
	operation,	// "+=",
	literal,	// "5",
	control,	// ";",
	identifier, // "string",
	identifier, // "asd",
	operation,	// "=",
	literal,	// "\"hello\"",
	control,	// ";",
	keyword,	// "if",
	control,	// "(",
	identifier, // "d",
	operation,	// "&&",
	identifier, // "des",
	control,	// ")",
	keyword,	// "return",
	identifier, // "test",
	control,	// ";",
	keyword,	// "for",
	control,	// "(",
	identifier, // "int",
	identifier, // "i",
	operation,	// "=",
	literal,	// "0",
	control,	// ";",
	identifier, // "i",
	operation,	// "<",
	literal,	// "20",
	control,	// ";",
	identifier, // "i",
	operation,	// "++",
	control,	// ")",
	control,	// "{",
	literal,	// "\"\\\"\"",
	control,	// "}",
	literal,	// "0x1230",
	control,	// "}",
	control,	// "}"
};

void testFunc() {}

TEST_CASE("parser", "[parser]")
{

	Parser parser;

	file_descriptor fd = file_open("tests/example_file.txt");

	mmapped_file mapped = map_file(fd);

	std::vector<lexeme> lexemes = lexetize(mapped, mapped.length);

	parser.addFunction("testFunc", testFunc);

	std::vector<parsed_unit> types = parser.parse(lexemes);

	REQUIRE(types.size() == expected_types.size());
	for (int i = 0; i < types.size(); i++)
	{
		REQUIRE(types[i].type == expected_types[i]);
	}
}
