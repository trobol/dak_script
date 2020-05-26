#include <dak_script/lexer.h>
#include <dak_script/mmapped_file.h>
#include <iostream>

using namespace dak_script;

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		return 1;
	}
	file_descriptor fd = file_open(argv[1]);

	mmapped_file file = map_file(fd);

	Lexer lexer(file.contents, file.length);

	Token_Module mod = lexer.lex();

	for (Token &t : mod.tokens)
	{
		if (t.type == TOKEN_TYPE_IDENTIFIER)
		{
			printf("%s\n", mod.buffer + t.index);
		}
		else if (t.type == TOKEN_TYPE_LITERAL)
		{
			Token_Literal &l = mod.literals[t.index];
			switch (l.type)
			{
				case LITERAL_TYPE_CHAR:
					printf("%c\n", l.char_val);
					break;
				case LITERAL_TYPE_FLOAT:
					printf("%f\n", l.float_val);
					break;
				case LITERAL_TYPE_INT:
					printf("%i\n", l.int_val);
					break;
				case LITERAL_TYPE_STRING:
					printf("%s\n", l.string_val);
					break;
				default:
					break;
			}
		}
		else if (t.type == TOKEN_TYPE_TOKEN)
		{
			printf("%s\n", token_value_to_name(t.value));
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