#include <dak_script/parser.h>
#include <dak_script/file_descriptor.h>
#include <dak_script/mmapped_file.h>
#include <dak_script/lexetize.h>
#include <dak_script/character_type.h>
#include <iostream>

namespace dak::script
{

std::string lex_str(lexeme lex)
{
	std::string str(lex.ptr, lex.length);
	return str;
}

parsed_unit parse_operation(lexeme lex)
{
	auto op = operations_map.find(lex_str(lex));
	if (op != operations_map.end())
	{
		return parsed_unit(operation, op->second);
	}
	else
	{
		return {unknown};
	}
}

parsed_unit parse_word(lexeme lex)
{
	std::string key = lex_str(lex);
	auto kw = keywords_map.find(key);

	if (kw != keywords_map.end())
	{
		return {keyword, kw->second};
	}
	character_type c = get_character_type(lex.ptr[0]);
	if (c == character_type::quotation || c == character_type::number)
	{
		return {literal};
	}

	return {identifier};
}

parsed_unit parse_lexeme(lexeme lex)
{
	switch (lex.type)
	{
	case lexeme_type::unknown:
		return {unknown};
		break;
	case lexeme_type::operation:
		return parse_operation(lex);
		break;
	case lexeme_type::word:
		return parse_word(lex);
		break;
	case lexeme_type::control:
		return {control};

	default:
		break;
	}
}

std::vector<parsed_unit> Parser::parse(std::vector<lexeme> lexemes)
{
	std::vector<parsed_unit> types(lexemes.size());
	for (int i = 0; i < lexemes.size(); i++)
	{
		types[i] = parse_lexeme(lexemes[i]);
	}
	return types;
}

void Parser::addFunction(std::string name, FunctionPointer ptr)
{
	functions.insert({name, ptr});
}
} // namespace dak::script