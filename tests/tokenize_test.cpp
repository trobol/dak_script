#include <catch2/catch.hpp>
#include <dak_script/tokenize.h>
#include <dak_script/reader.h>


using namespace dak::script;

TEST_CASE( "Tokenize Check", "[main]" ) {
   
   Reader reader;

   reader.open("./example_file.txt");

    tokenize(reader.contents(), reader.length());




}

