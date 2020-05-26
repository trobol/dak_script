#include <catch2/catch.hpp>
#include <dak_script/file_descriptor.h>
#include <dak_script/mmapped_file.h>

#include "expectations.h"

using namespace dak_script;

TEST_CASE("mmapped file", "[mmapped_file]")
{

	file_descriptor fd = file_open("tests/example_file.txt");
	REQUIRE(fd != -1);

	mmapped_file file = map_file(fd);

	REQUIRE(file.contents != nullptr);

	for (int i = 0; i < expected_text_length; i++)
	{
		REQUIRE(file.contents[i] == expected_text[i]);
	}

	int err = unmap_file(file);

	REQUIRE(err == 0);
}
