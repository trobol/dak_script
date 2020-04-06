#include <catch2/catch.hpp>
#include <dak_script/reader.h>
#include "expectations.h"
#include <iostream>

using namespace dak::script;

TEST_CASE( "reads contents correctly", "[reader]" ) {
	Reader reader;
   	reader.open("tests/example_file.txt");

	REQUIRE(reader.length() == expected_text_length);

	for(int i = 0; i < reader.length(); i++) {
		REQUIRE(reader.contents()[i] == expected_text[i]);
	}

	reader.close();
}

