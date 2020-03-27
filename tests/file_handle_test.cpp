#include <catch2/catch.hpp>
#include <dak_script/file_handle.h>

#include "expectations.h"


using namespace dak::script;

TEST_CASE( "file handle", "[file_handle]" ) {

    file_handle handle; 


	bool opened = handle.open("example_file.txt");
    REQUIRE( opened );
	
	
	const char input[expected_text_length] = {};


	bool read = handle.read_into(input, expected_text_length);

	REQUIRE(read);




	for(int i = 0; i < expected_text_length; i++) {
		REQUIRE(input[i] == expected_text[i]);
	}





	bool closed = handle.close();
	
	REQUIRE( closed );

}

