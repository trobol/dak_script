#include <chrono>
#include <dak_script/lexer.h>
#include <dak_script/mmapped_file.h>
#include <dak_script/parser.h>
#include <dak_script/token.h>
#include <fstream>
#include <iostream>

#include <dak_std/vector.h>

using namespace dak_script;

int main(int argc, char *argv[])
{

	auto t_start = std::chrono::high_resolution_clock::now();
	if (argc != 2)
	{
		return 1;
	}
	file_descriptor fd = file_descriptor::open(argv[1], READ_ONLY);

	if (fd.id() == -1)
	{
		printf("unable to open %s\n", argv[1]);
		return 1;
	}
	mmapped_file file = mmapped_file::map(fd);

	Lexer lexer(file.data(), file.size());

	Token_Module mod = lexer.lex();

	std::ofstream output("output.txt");

	for (const Token &t : mod.tokens)
	{
		if (t.type == TOKEN_TYPE_IDENTIFIER)
		{
			output << "I_" << mod.identifiers[t.index] << ' ';
		}
		else if (t.type == TOKEN_TYPE_LITERAL)
		{
			Token_Literal &l = mod.literals[t.index];

			switch (l.type)
			{
				case LITERAL_TYPE_CHAR:
					output << l.char_val << ' ';
					break;
				case LITERAL_TYPE_FLOAT:
					output << l.float_val << ' ';
					break;
				case LITERAL_TYPE_INT:
					output << l.int_val << ' ';
					break;
				case LITERAL_TYPE_STRING:
					output << l.string_val << ' ';
					break;
				default:
					break;
			}
		}
		else if (t.type == TOKEN_TYPE_TOKEN)
		{
			if (t.value == TOKEN_BREAK)
			{
				output << '\n';
			}
			else
			{
				output << token_value_to_name(t.value) << ' ';
			}
		}
	}
	output.close();

	Parser parser(mod);

	Parsed_Module *parsed_module = parser.parse();

	for (size_t i = 0; i < parsed_module->top_block->statements.size(); i++)
	{
		printf("expr: %u\n", i);
	}

	printf("Variables:\n");
	for (AST_Variable *var : parsed_module->top_block->variables)
	{
		printf("	%s\n", var->name);
	}

	printf("Functions:\n");
	for (AST_Function *func : parsed_module->top_block->functions)
	{
		printf("	%s\n", func->name);
	}

	int err_mmf = file.unmap();

	int err_fd = fd.close();

	auto t_end = std::chrono::high_resolution_clock::now();
	printf(
	    "duration %fms \n",
	    std::chrono::duration<double, std::milli>(t_end - t_start).count());
	if (err_mmf != 0)
	{
		return err_mmf;
	}
	else
	{
		return err_fd;
	}
}