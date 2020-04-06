#include <catch2/catch.hpp>
#include <dak_script/file_descriptor.h>

#include "expectations.h"

using namespace dak::script;

TEST_CASE("file descriptor", "[file_descriptor]")
{

	file_descriptor fd = file_open("tests/example_file.txt");
	REQUIRE(fd != -1);

	size_t length = len(fd);

	REQUIRE(length == expected_text_length);

	int err = file_close(fd);
	REQUIRE(err == 0);
}
