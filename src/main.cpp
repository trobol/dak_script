#include <dak_script/mmapped_file.h>
#include <dak_script/lexer.h>
#include <iostream>

using namespace dak::script;

int main(int argc, char *argv[])
{

	if(argc != 2) {
		return 1;
	}
	file_descriptor fd = file_open(argv[1]);

	mmapped_file file = map_file(fd);

	Lexer lexer(file.contents, file.length);

	Token_Module mod = lexer.lex();
	
	for (Token &t : mod.tokens)
	{
		
		printf("%i\n", t.type);
		
	}
	
	int err_mmf = unmap_file(file);

	int err_fd = file_close(fd);

	if (err_mmf != 0)
	{
		return err_mmf;
	}
	else
	{
		return err_fd;
	}
}