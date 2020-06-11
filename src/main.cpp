#include <ctime>
#include <dak_script/lexer.h>
#include <dak_script/mmapped_file.h>
#include <dak_script/token.h>
#include <fstream>
#include <iostream>

#include <dak_std/vector.h>

using namespace dak_script;

int main(int argc, char *argv[])
{

	clock_t start_clock = std::clock();
	if (argc != 2)
	{
		return 1;
	}
	file_descriptor fd = file_descriptor::open(argv[1], READ_ONLY);

	mmapped_file file = mmapped_file::map(fd);

	Lexer lexer(file.data(), file.size());

	Token_Module mod = lexer.lex();

	std::ofstream output("output.txt");

	for (const Token &t : mod.tokens)
	{
		if (t.type == TOKEN_TYPE_IDENTIFIER)
		{
			output << mod.buffer + t.index << '\n';
		}
		else if (t.type == TOKEN_TYPE_LITERAL)
		{
			Token_Literal &l = mod.literals[t.index];
			switch (l.type)
			{
				case LITERAL_TYPE_CHAR:
					output << l.char_val << '\n';
					break;
				case LITERAL_TYPE_FLOAT:
					output << l.float_val << '\n';
					break;
				case LITERAL_TYPE_INT:
					output << l.int_val << '\n';
					break;
				case LITERAL_TYPE_STRING:
					output << l.string_val << '\n';
					break;
				default:
					break;
			}
		}
		else if (t.type == TOKEN_TYPE_TOKEN)
		{
			output << token_value_to_name(t.value) << '\n';
		}
	}

	int err_mmf = file.unmap();

	int err_fd = fd.close();

	clock_t total_clock = std::clock() - start_clock;
	printf("%fs (%d clocks)\n", ((float)total_clock) / CLOCKS_PER_SEC,
	       total_clock);
	if (err_mmf != 0)
	{
		return err_mmf;
	}
	else
	{
		return err_fd;
	}
}