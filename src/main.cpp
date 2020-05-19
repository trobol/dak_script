#include <dak_script/mmapped_file.h>
#include <dak_script/lexer.h>
#include <iostream>

using namespace dak::script;

int main()
{

	file_descriptor fd = file_open("../example_file.txt");

	mmapped_file file = map_file(fd);

	Lexer lexer(file.contents, file.length);

	Token_Module mod = lexer.lex();

	for (Token &t : mod.tokens)
	{
		if (t.characteristic == TOKEN_IS_IDENTIFIER)
		{
			printf("%s\n", mod.buffer + t.index);
		}
		else
		{
			printf("%s\n", token_type_to_name(t.type));
		}
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