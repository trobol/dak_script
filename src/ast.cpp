#include <dak_script/ast.h>
#include <dak_std/static_string_map.h>

namespace dak_script
{

constexpr const auto type_kind_map =
    dak_std::Build_Static_String_Map<AST_Type_Kind>(TYPE_KIND_UNKNOWN,
						    {{"u8", TYPE_KIND_U8},
						     {"u16", TYPE_KIND_U16},
						     {"u32", TYPE_KIND_U32},
						     {"u64", TYPE_KIND_U64},
						     {"i8", TYPE_KIND_I8},
						     {"i16", TYPE_KIND_I16},
						     {"i32", TYPE_KIND_I32},
						     {"i64", TYPE_KIND_I64},
						     {"f32", TYPE_KIND_F32},
						     {"f64", TYPE_KIND_F64}});

//////////////////////
//   STRUCT BLOCK   //
//////////////////////

AST_Variable *AST_Struct_Block::find_variable(dak_std::string &name)
{
	/*
	auto result_pair = m_type->member_map.find(name);
	if (result_pair != m_type->member_map.end())
		return result_pair->second;
	else
	*/
	return nullptr;
}

AST_Variable *AST_Struct_Block::add_variable(dak_std::string &name,
					     AST_Type_Ref type)
{
	AST_Variable *v = new AST_Variable(name, type);
	/*
	m_type->members.push_back(v);
	m_type->member_map.insert({name, v});
	*/
	return v;
}

AST_Function *AST_Struct_Block::find_function(dak_std::string &name)
{
	return nullptr;
}
AST_Function *AST_Struct_Block::add_function(dak_std::string &name)
{
	// TODO SYNTAX ERROR
	return nullptr;
}

AST_Type_Ref AST_Struct_Block::find_type(dak_std::string &name)
{

	return AST_Type_Ref();
}
AST_Type_Ref AST_Struct_Block::add_type(dak_std::string &name)
{
	return AST_Type_Ref();
}

void AST_Struct_Block::add_statement(AST_Statement *statement)
{
	// TODO SYNTAX ERROR
}

/////////////////////////
//   STATEMENT BLOCK   //
/////////////////////////

AST_Variable *AST_Statement_Block::find_variable(dak_std::string &name)
{
	auto result_pair = m_variable_map.find(name);
	if (result_pair != m_variable_map.end())
		return result_pair->second;
	else
		return nullptr;
}
AST_Variable *AST_Statement_Block::add_variable(dak_std::string &name,
						AST_Type_Ref type)
{
	AST_Variable *v = new AST_Variable(name, type);
	m_variables.push_back(v);
	m_variable_map.insert({name, v});
	return v;
}

AST_Function *AST_Statement_Block::find_function(dak_std::string &name)
{
	auto result_pair = m_function_map.find(name);
	if (result_pair != m_function_map.end())
		return result_pair->second;
	else
		return nullptr;
}

AST_Function *AST_Statement_Block::add_function(dak_std::string &name)
{
	AST_Function *f = new AST_Function(name);
	m_functions.push_back(f);
	m_function_map.insert({name, f});
	return f;
}

// TODO: support user defined types
AST_Type_Ref AST_Statement_Block::add_type(dak_std::string &name)
{
	return AST_Type_Ref();
}

AST_Type_Ref AST_Statement_Block::find_type(dak_std::string &name)
{
	AST_Type_Kind k = type_kind_map.find(name.data());
	return AST_Type_Ref(k, nullptr);
}

void AST_Statement_Block::add_statement(AST_Statement *statement)
{
	m_statements.push_back(statement);
}

AST_Statement_Block::~AST_Statement_Block()
{
	for (AST_Statement *s : m_statements)
	{
		delete s;
	}
	for (AST_Function *f : m_functions)
	{
		delete f;
	}
	for (AST_Variable *v : m_variables)
	{
		delete v;
	}
}

//////////////////
//   FUNCTION   //
//////////////////

AST_Function::~AST_Function() {}

AST_Variable *AST_Function::add_parameter(dak_std::string &name,
					  AST_Type_Ref type)
{
	AST_Variable *v = add_variable(name, type);
	parameters.push_back(v);
	return v;
}

const char *get_ast_type_name(AST_Type_Ref ref)
{
	switch (ref.get_kind())
	{
		case TYPE_KIND_UNKNOWN:
			return "unknown";
		case TYPE_KIND_STRUCT:
			return "struct";
		case TYPE_KIND_ENUM:
			return "enum";
		case TYPE_KIND_ALIAS:
			return "alias";
		case TYPE_KIND_U8:
			return "u8";
		case TYPE_KIND_U16:
			return "u16";
		case TYPE_KIND_U32:
			return "u32";
		case TYPE_KIND_U64:
			return "u64";
		case TYPE_KIND_I8:
			return "i8";
		case TYPE_KIND_I16:
			return "i16";
		case TYPE_KIND_I32:
			return "i32";
		case TYPE_KIND_I64:
			return "i64";
		case TYPE_KIND_F32:
			return "f32";
		case TYPE_KIND_F64:
			return "f64";
	}
};

} // namespace dak_script