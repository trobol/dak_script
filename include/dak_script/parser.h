#ifndef _DAK_SCRIPT_PARSER_H
#define _DAK_SCRIPT_PARSER_H

#include <dak_script/lexetize.h>
#include <dak_script/reserves.h>
#include <unordered_map>
#include <string>
#include <vector>

namespace dak_script
{

enum parsed_unit_type
{
	keyword,
	operation,
	identifier,
	control,
	literal,
	unknown
};

struct parsed_unit
{

	parsed_unit_type type;

	union {
		keywords keyword;
		operations operation;
	};
	parsed_unit() {}
	parsed_unit(parsed_unit_type type) : type{type} {}
	parsed_unit(parsed_unit_type type, keywords keyword) : type{type}, keyword{keyword} {}
	parsed_unit(parsed_unit_type type, operations operation) : type{type}, operation{operation} {}
};

typedef void (*FunctionPointer)();
class Parser
{
public:
	void addFunction(std::string name, FunctionPointer func);
	std::vector<parsed_unit> parse(std::vector<lexeme> lexemes);

private:
	std::unordered_map<std::string, FunctionPointer> functions;
};

} // namespace dak_script

#endif